Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing
Imports Neurotec.IO

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [FMRecord] [NTemplate] [Standard] [FlagUseNeurotecFields]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[FMRecord] - filename of FMRecord.")
		Console.WriteLine(Constants.vbTab & "[NTemplate] - filename of NTemplate to be created.")
		Console.WriteLine(Constants.vbTab & "[Standard] - FMRecord standard (ISO or ANSI)")
		Console.WriteLine(Constants.vbTab & "[FlagUseNeurotecFields] - 1 if FmrFingerView.FlagUseNeurotecFields flag is used; otherwise, 0 flag was not used.")
		Console.WriteLine()
		Console.WriteLine("example:")
		Console.WriteLine(Constants.vbTab & "{0} fmrecord.dat ntemplate.dat ISO 1", TutorialUtils.GetAssemblyName())

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 4 Then
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

			Dim fmRecordFileName As String = args(0)
			Dim outputFileName As String = args(1)
			Dim standard As BdifStandard = CType(System.Enum.Parse(GetType(BdifStandard), args(2), True), BdifStandard)

			Dim flagUseNeurotecFields As Integer = Integer.Parse(args(3))

			If fmRecordFileName = "/?" OrElse fmRecordFileName = "help" Then
				Return Usage()
			End If

			Dim storedFmRecord() As Byte = File.ReadAllBytes(fmRecordFileName)

			' Creating FMRecord object from FMRecord stored in memory
			Dim fmRecord As FMRecord = If(flagUseNeurotecFields = 1, New FMRecord(New NBuffer(storedFmRecord), FmrFingerView.FlagUseNeurotecFields, standard), New FMRecord(New NBuffer(storedFmRecord), standard))

			' Converting FMRecord object to NTemplate object
			Dim nTemplate As NTemplate = fmRecord.ToNTemplate()
			' Packing NTemplate object
			Dim packedNTemplate() As Byte = nTemplate.Save().ToArray()

			File.WriteAllBytes(outputFileName, packedNTemplate)

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
