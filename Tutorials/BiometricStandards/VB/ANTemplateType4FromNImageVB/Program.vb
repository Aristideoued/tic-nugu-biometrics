Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Images
Imports Neurotec.Licensing
Imports Neurotec.IO

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [NImage] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[NImage]     - filename with image file.")
		Console.WriteLine(Constants.vbTab & "[ANTemplate] - filename for ANTemplate.")
		Console.WriteLine(Constants.vbTab & "[Tot] - specifies type of transaction.")
		Console.WriteLine(Constants.vbTab & "[Dai] - specifies destination agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Ori] - specifies originating agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Tcn] - specifies transaction control number.")
		Console.WriteLine(Constants.vbTab & "[Encoding] - specifies ANTemplate encoding type.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - Traditional binary encoding.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - NIEM-conformant XML encoding.")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 7 Then
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
			Dim enc As String = args(6) ' encoding type

			If (tot.Length < 3) OrElse (tot.Length > 4) Then
				Console.WriteLine("Tot parameter should be 3 or 4 characters length.")
				Return -1
			End If

			Dim encoding As BdifEncodingType = If((enc = "1"), BdifEncodingType.Xml, BdifEncodingType.Traditional)
			Dim imageScanningResolution As UInteger = ANType1Record.MinScanningResolution ' image scanning resolution
			Dim imageResolutionPpi As Single = 500 ' image current resolution

			' Create empty ANTemplate object with current version and only type 1 record in it.
			' Finger image must be compressed using valid compression algorithm for Type-4 record.
			' How to convert image to required compression algorithm please see "Media" tutorials, Like "CreateWsq".

			Using template = New ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, 0)
				Using imageBuffer = NFile.ReadAllBytes(args(0))
					' Create Type 4 record and add record to ANTemplate
					Dim record As ANType4Record = template.Records.AddType4(True, imageBuffer)

					Dim type1 As ANType1Record = CType(template.Records(0), ANType1Record)
					type1.NativeScanningResolution = imageScanningResolution
					type1.NominalTransmittingResolutionPpi = imageResolutionPpi

					' Store ANTemplate object with type 4 record in file
					template.Save(args(1), encoding)
				End Using
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
