Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Biometrics.Standards
Imports Neurotec.IO
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [NTemplate] [CbeffRecord] [PatronFormat]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[NTemplate] - filename of NTemplate.")
		Console.WriteLine(Constants.vbTab & "[CbeffRecord] - filename of CbeffRecord.")
		Console.WriteLine(Constants.vbTab & "[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation).")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 3 Then
			Return Usage()
		End If

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const licenses As String = "FingerClient,PalmClient,FaceClient,IrisClient"
		'Const licenses As String = "FingerFastExtractor,PalmClient,FaceFastExtractor,IrisFastExtractor"

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

			' Read NTemplate buffer
			Dim packedNTemplate = New NBuffer(File.ReadAllBytes(args(0)))

			' Combine NTemplate BDB format
			Dim bdbFormat As UInteger = BdifTypes.MakeFormat(CbeffBiometricOrganizations.Neurotechnologija, CbeffBdbFormatIdentifiers.NeurotechnologijaNTemplate)

			' Get CbeffRecord patron format
			' all supported patron formats can be found in CbeffRecord class documentation
			Dim patronFormat As UInteger = UInteger.Parse(args(2), Globalization.NumberStyles.AllowHexSpecifier)

			' Create CbeffRecord from NTemplate buffer
			Using cbeffRecord = New CbeffRecord(bdbFormat, packedNTemplate, patronFormat)
				' Saving NTemplate
				File.WriteAllBytes(args(1), cbeffRecord.Save().ToArray())
				Console.WriteLine("Template successfully saved")
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
