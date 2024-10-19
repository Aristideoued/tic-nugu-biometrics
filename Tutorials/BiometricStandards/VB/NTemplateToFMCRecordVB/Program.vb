Imports Microsoft.VisualBasic
Imports System
Imports System.IO

Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Const minutiaTruncationQualityThreshold As Byte = 0
	'         NOTE: ISO/IEC 19794-2 (informative) minutiae count range recommendations for card formats:
	'		 - FMCRecord.DefaultMinEnrollMC to FMCRecord.DefaultMaxEnrollMC for enroll, 
	'		 - FMCRecord.DefaultMinVerifyMC to FMCRecord.DefaultMaxVerifyMC for verify.
	'		
	Private Const minutiaTruncationMaximalCount As Integer = 48
	Private Const minutiaTruncationAlgorithm As NFMinutiaTruncationAlgorithm = NFMinutiaTruncationAlgorithm.QualityAndCenterOfMass

	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [NTemplate] [FMCRecord] [Version] [MinutiaeFormat] [SaveBiometricDataTemplate]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[NTemplate] - filename of NFCRecord.")
		Console.WriteLine(Constants.vbTab & "[FMCRecord] - filename of FMCRecord to be created.")
		Console.WriteLine(Constants.vbTab & "[Version] - FMCRecord version")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ISO2 - ISO/IEC 19794-2:2005")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ISO3 - ISO/IEC 19794-2:2011")
		Console.WriteLine(Constants.vbTab & "[tMinutiaeFormat] - card format of minutiae data.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "C - compact size")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "N - normal size (ISO2 only)")
		Console.WriteLine(Constants.vbTab & "SaveBiometricDataTemplate - FMCRecord save to buffer option")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - full Biometric Data Template (BDT) BER-TLV DO (Data Object)")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - minutiae data only")
		Console.WriteLine("")
		Console.WriteLine("examples:")
		Console.WriteLine(Constants.vbTab & "{0}  template.NTemplate fmcrecord.FMCRecord ISO3 C 1", TutorialUtils.GetAssemblyName())

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 5 Then
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

			Dim standard As BdifStandard = BdifStandard.Iso
			Dim standardVersion As NVersion
			Dim minutiaOrder As FmcrMinutiaOrder = FmcrMinutiaOrder.None
			Dim flags As UInteger = FMCRecord.FlagSkipAllExtendedData Or FMCRecord.FlagUseBiometricDataTemplate	' the most common use case of minutiae data only within on-card records

			If args(2).Equals("ISO2") Then
				standardVersion = FMCRecord.VersionIso20
			ElseIf args(2).Equals("ISO3") Then
				standardVersion = FMCRecord.VersionIso30
			Else
				Throw New ArgumentException("Wrong standard")
			End If

			Dim minutiaFormat As FmcrMinutiaFormat
			If args(3).Equals("C") Then
				minutiaFormat = FmcrMinutiaFormat.CompactSize
			ElseIf args(3).Equals("N") Then
				minutiaFormat = FmcrMinutiaFormat.NormalSize
			Else
				Throw New ArgumentException("Wrong minutia format")
			End If

			' Check if full FMCRecord Biometric Data Template (BDT) BER-TLV Data Object (DO) or minutiae buffer only to be saved
			Dim isBdtBerTlv As Boolean = args(4).Equals("1")

			Dim packedNTemplate() As Byte = File.ReadAllBytes(args(0))
			Dim nTemplate As New NTemplate(packedNTemplate)
			Dim nfTemplate As NFTemplate = nTemplate.Fingers
			If nfTemplate IsNot Nothing AndAlso nfTemplate.Records.Count > 0 Then
				' Retrieve NFRecord object from NFTemplate object
				Dim nfRecord As NFRecord = nfTemplate.Records(0)

				' Truncate minutiae by quality
				nfRecord.TruncateMinutiaeByQuality(minutiaTruncationQualityThreshold, minutiaTruncationMaximalCount)

				' Truncate minutiae using specified truncation algorithm (if more than desired minutiae with quality above minutiaTruncationQualityThreshold remain)
				nfRecord.TruncateMinutiae(minutiaTruncationAlgorithm, minutiaTruncationMaximalCount)

				' Create FMCRecord object from NFRecord object
				Dim _fmcRecord As New FMCRecord(nfRecord, standard, standardVersion, minutiaFormat, minutiaOrder, 0)

				' Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
				If _fmcRecord.Version = FMCRecord.VersionIso20 AndAlso (Not _fmcRecord.ValidateMinutiaeUniqueness()) Then
					Console.WriteLine("!!!WARNING!!!:")
					Console.WriteLine("Not all minutiae in FMCRecord are unique!")
					Console.WriteLine("Please, try using ISO3 version to remove non-unique minutiae while conversion.")
				End If

				If isBdtBerTlv Then
					' Store FMCRecord object in memory as ISO/IEC 19794-2 and ISO/IEC 7816-11 compliant Biometric Data Template (BDT) BER-TLV Data Object (DO)
					Dim storedFmcRecord() As Byte = _fmcRecord.Save(flags).ToArray()
					File.WriteAllBytes(args(1), storedFmcRecord)
				Else
					' Get minutiae data as buffer
					Dim minutiaeBuffer() As Byte = _fmcRecord.GetMinutiaeBuffer().ToArray()
					File.WriteAllBytes(args(1), minutiaeBuffer)
				End If
			Else
				Console.WriteLine("There are no NFRecords in NTemplate")
			End If

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
