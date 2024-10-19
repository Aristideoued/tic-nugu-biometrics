Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing
Imports Neurotec.IO

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Src] [Encoding]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[NImage]     - filename with Image file.")
		Console.WriteLine(Constants.vbTab & "[ANTemplate] - filename for ANTemplate.")
		Console.WriteLine(Constants.vbTab & "[Tot] - specifies type of transaction.")
		Console.WriteLine(Constants.vbTab & "[Dai] - specifies destination agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Ori] - specifies originating agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Tcn] - specifies transaction control number.")
		Console.WriteLine(Constants.vbTab & "[Src] - specifies source agency number.")
		Console.WriteLine(Constants.vbTab & "[Encoding] - specifies ANTemplate encoding type.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - Traditional binary encoding.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - NIEM-conformant XML encoding.")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 8 Then
			Return Usage()
		End If

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const license As String = "FingerClient"
		'Const license As String = "FingerFastExtractor"

		'=========================================================================

		'=========================================================================
		' TRIAL MODE
		'=========================================================================
		' Below code line determines whether TRIAL Is enabled Or Not. To use purchased licenses, don't use below code line.
		' GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
		' Also you can just set TRUE to "TrialMode" property in code.

		NLicenseManager.TrialMode = TutorialUtils.GetTrialModeFlag()

		Console.WriteLine("Trial mode: {0}", NLicenseManager.TrialMode)

		'=========================================================================

		Try
			' Obtain license
			If (Not NLicense.Obtain("/local", 5000, license)) Then
				Throw New ApplicationException(String.Format("Could not obtain license: {0}", license))
			End If

			Dim tot As String = args(2) ' type of transaction
			Dim dai As String = args(3) ' destination agency identifier
			Dim ori As String = args(4) ' originating agency identifier
			Dim tcn As String = args(5) ' transaction control number
			Dim src As String = args(6) ' source agency number
			Dim enc As String = args(7) ' encoding type

			If (tot.Length < 3) OrElse (tot.Length > 4) Then
				Console.WriteLine("Tot parameter should be 3 or 4 characters length.")
				Return -1
			End If

			Dim encoding As BdifEncodingType = If((enc = "1"), BdifEncodingType.Xml, BdifEncodingType.Traditional)

			'Create empty ANTemplate object with current version and only type 1 record in it.
			'Finger image must be compressed using valid compression algorithm for Type-13 record.
			'How to convert image to required compression algorithm please see "Media" tutorials, Like "CreateWsq".
			Using template = New ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, 0)
				Using imageBuffer = NFile.ReadAllBytes(args(0))
					' Create Type 14 record and add record to ANTemplate
					Dim record As ANType14Record = template.Records.AddType14(src, imageBuffer)

					' Store ANTemplate object with type 14 record in file
					template.Save(args(1), encoding)
				End Using
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try

	End Function
End Class
