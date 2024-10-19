Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [NTemplate] [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[NTemplate]     - filename of NTemplate.")
		Console.WriteLine(Constants.vbTab & "[ANTemplate]    - filename of ANTemplate.")
		Console.WriteLine(Constants.vbTab & "[Tot] - specifies type of transaction.")
		Console.WriteLine(Constants.vbTab & "[Dai] - specifies destination agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Ori] - specifies originating agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Tcn] - specifies transaction control number.")
		Console.WriteLine(Constants.vbTab & "[Encoding] - specifies ANTemplate encoding type.")
		Console.WriteLine(Constants.vbTab & Constants.vbTab & "0 - Traditional binary encoding.")
		Console.WriteLine(Constants.vbTab & Constants.vbTab & "1 - NIEM-conformant XML encoding.")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 7 Then
			Return Usage()
		End If

		If args(0) = "/?" OrElse args(0) = "help" Then
			Return Usage()
		End If

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const licenses As String = "FingerClient,PalmClient"
		'Const licenses As String = "FingerFastExtractor,PalmClient"

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

		Dim anyMatchingComponent = False
		Try
			' Obtain licenses
			For Each license As String In licenses.Split(","c)
				If NLicense.Obtain("/local", 5000, license) Then
					Console.WriteLine("Obtained license: {0}", license)
					anyMatchingComponent = True
				End If
			Next license
			If (Not anyMatchingComponent) Then
				Throw New NotActivatedException("Could not obtain any matching license")
			End If

			Dim nTemplateFileName As String = args(0)

			Dim tot As String = args(2)	' type of transaction
			Dim dai As String = args(3)	' destination agency identifier
			Dim ori As String = args(4)	' originating agency identifier
			Dim tcn As String = args(5)	' transaction control number
			Dim enc As String = args(6)	' encoding type

			If (tot.Length < 3) OrElse (tot.Length > 4) Then
				Console.WriteLine("Tot parameter should be 3 or 4 characters length.")
				Return -1
			End If

			Dim encoding As BdifEncodingType = If(enc = "1", BdifEncodingType.Xml, BdifEncodingType.Traditional)

			Dim packedNTemplate() As Byte = File.ReadAllBytes(nTemplateFileName)

			' Creating NTemplate object from packed NTemplate
			Using nTemplate = New NTemplate(packedNTemplate)

				'sets minutia format: true - if standard, false - otherwise. For palms only standard mintia format Is supported]
				Dim type9RecordFmtStd As Boolean = False
				If nTemplate.Palms IsNot Nothing Then
					If nTemplate.Palms.Records.Count > 0 Then
						type9RecordFmtStd = True
					End If
				End If

				' Creating ANTemplate object from NTemplate object
				Using tempANTemplate = New ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, type9RecordFmtStd, nTemplate)
					' Storing ANTemplate object in file
					tempANTemplate.Save(args(1), encoding)
					Console.WriteLine("Program produced file: " & args(1))
				End Using
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
