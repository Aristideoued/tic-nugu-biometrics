Imports Microsoft.VisualBasic
Imports System
Imports System.IO

Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [NTemplate] [FMRecord] [Standard] [Version] [FlagUseNeurotecFields]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[NTemplate] - filename of NFRecord.")
		Console.WriteLine(Constants.vbTab & "[FMRecord] - filename of FMRecord to be created.")
		Console.WriteLine(Constants.vbTab & "[Standard&Version] - FMRecord standard & version")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ANSI2 - ANSI/INCITS 378-2004")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ANSI3.5 - ANSI/INCITS 378-2009")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ISO2 - ISO/IEC 19794-2:2005")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ISO3 - ISO/IEC 19794-2:2011")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "MINEX - Minex compliant record (ANSI/INCITS 378-2004 without extended data)")
		Console.WriteLine(Constants.vbTab & "[FlagUseNeurotecFields] - 1 if FmrFingerView.FlagUseNeurotecFields flag is uses; otherwise, 0 flag was not used. For Minex compliant record must be 0.")
		Console.WriteLine(Constants.vbTab & "[Encoding] - specifies FMRecord encoding type.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - Traditional binary encoding")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - XML encoding (supported only for ISO3)")
		Console.WriteLine("")
		Console.WriteLine("examples:")
		Console.WriteLine(Constants.vbTab & "{0} ntemplate.dat fmrecord.dat ISO3 1 0", TutorialUtils.GetAssemblyName())
		Console.WriteLine(Constants.vbTab & "{0} ntemplate.dat fmrecord.dat MINEX 0 0", TutorialUtils.GetAssemblyName())

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 5 Then
			Return Usage()
		End If

		If args(0) = "/?" OrElse args(0) = "help" Then
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

			Dim nTemplateFileName As String = args(0)
			Dim outputFileName As String = args(1)
			Dim standard As BdifStandard = 0
			Dim flagUseNeurotecFields As Integer = Integer.Parse(args(3))
			Dim flags As UInteger = 0
			Dim version As NVersion

			Select Case args(2)
				Case "ANSI2"
					standard = BdifStandard.Ansi
					version = FMRecord.VersionAnsi20
				Case "ISO2"
					standard = BdifStandard.Iso
					version = FMRecord.VersionIso20
				Case "ISO3"
					standard = BdifStandard.Iso
					version = FMRecord.VersionIso30
				Case "ANSI3.5"
					standard = BdifStandard.Ansi
					version = FMRecord.VersionAnsi35
				Case "MINEX"
					If flagUseNeurotecFields <> 0 Then
						Throw New ArgumentException("MINEX compliant record and FlagUseNeurotecFields is incompatible")
					End If
					standard = BdifStandard.Ansi
					version = FMRecord.VersionAnsi35
					flags = FmrFingerView.FlagSkipRidgeCounts Or FmrFingerView.FlagSkipSingularPoints Or FmrFingerView.FlagSkipNeurotecFields
				Case Else
					Throw New ArgumentException("Version was not recognised")
			End Select

			flags = If(flagUseNeurotecFields = 1, flags Or FmrFingerView.FlagUseNeurotecFields, flags)

			Dim packedNTemplate() As Byte = File.ReadAllBytes(nTemplateFileName)

			' Creating NTemplate object from packed NTemplate
			Dim nTemplate = New NTemplate(packedNTemplate)

			' Retrieving NFTemplate object from NTemplate object
			Dim nfTemplate As NFTemplate = nTemplate.Fingers

			If nfTemplate IsNot Nothing Then
				' Creating FMRecord object from NFTemplate object
				Dim fmRecord = New FMRecord(nfTemplate, standard, version)
				' Storing FMRecord object in memory
				Dim encoding As BdifEncodingType = If(args(4) = "1", BdifEncodingType.Xml, BdifEncodingType.Traditional)
				Dim storedFmRecord() As Byte = fmRecord.Save(encoding, flags).ToArray()
				File.WriteAllBytes(outputFileName, storedFmRecord)
			Else
				Console.WriteLine("There are no NFRecord in NTemplate")
			End If

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
