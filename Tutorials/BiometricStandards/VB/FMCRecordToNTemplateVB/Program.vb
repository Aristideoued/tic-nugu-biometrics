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
		Console.WriteLine(Constants.vbTab & "{0} [FMCRecord] [NTemplate] [Version] [MinutiaeFormat] [ReadBerTlv]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[FMCRecord] - filename of FMCRecord.")
		Console.WriteLine(Constants.vbTab & "[NTemplate] - filename of NTemplate to be created.")
		Console.WriteLine(Constants.vbTab & "[Version] - FMCRecord version.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ISO2 - ISO/IEC 19794-2:2005.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "ISO3 - ISO/IEC 19794-2:2011.")
		Console.WriteLine(Constants.vbTab & "[MinutiaeFormat] - card format of minutiae data.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "C - compact size.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "N - normal size (ISO2 only).")
		Console.WriteLine(Constants.vbTab & "ReadBerTlvDo - FMCRecord read from buffer option")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - Biometric Data Template (BDT) or Cardholder")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "    Biometric Data (CBD) BER-TLV DO (Data Object)")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - minutiae data buffer only." & Constants.vbLf)
		Console.WriteLine()
		Console.WriteLine("example:")
		Console.WriteLine(Constants.vbTab & "{0}  fmcRecord.FMCRecord template.NTemplate ISO3 C 1", TutorialUtils.GetAssemblyName())

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

			Dim fmcRecordFileName As String = args(0)
			Dim outputFileName As String = args(1)

			Dim standard As BdifStandard = BdifStandard.Iso
			Dim flags As UInteger = 0 ' BdifTypes.FlagNonStrictRead - removes non-unique minutiae for FMCRecord.VersionIso30 only

			Dim standardVersion As NVersion
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

			' Check if full FMCRecord BER-TLV Data Object (DO) (e.g., Biometric Data Template (BDT) or Cardholder Biometric Data (CBD)) or minutiae buffer only is available
			Dim isBerTlv As Boolean = args(4).Equals("1")

			Dim storedFmcRecord() As Byte = File.ReadAllBytes(args(0))
			Dim _fmcRecord As FMCRecord = Nothing
			If isBerTlv Then
				' Create FMCRecord object from FMCRecord BER-TLV Data Object (DO) stored in memory (e.g., BDT or CBD BER-TLV DO)
				_fmcRecord = New FMCRecord(storedFmcRecord, standard, standardVersion, minutiaFormat, flags)
			Else 'if (!isBerTlv)
				' Create FMCrecord and read minutiae data from buffer to FMCRecord
				_fmcRecord = New FMCRecord(standard, standardVersion, minutiaFormat)
				_fmcRecord.SetMinutiaeBuffer(New NBuffer(storedFmcRecord))
			End If

			' Explicitly check minutiae uniqueness for FMCRecord v2.0 as well (since mandatory implicit check since v3.0 only)
			If _fmcRecord.Version = FMCRecord.VersionIso20 AndAlso (Not _fmcRecord.ValidateMinutiaeUniqueness()) Then
				Console.WriteLine("!!!WARNING!!!:")
				Console.WriteLine("Not all minutiae in FMCRecord are unique!")
				Console.WriteLine("Please, try using ISO3 version with BdifTypes.FlagNonStrictRead flag to remove non-unique minutiae while reading.")
			End If

			' Convert FMCRecord to NFRecord
			Dim nfRecord As NFRecord = _fmcRecord.ToNFRecord()

			' Add NFRecord to NFTemplate
			Dim nfTemplate As New NFTemplate()
			nfTemplate.Records.Add(nfRecord)
			' Set NFTemplate to NTemplate
			Dim nTemplate As New NTemplate()
			nTemplate.Fingers = nfTemplate

			' Pack NTemplate object
			Dim packedNTemplate() As Byte = nTemplate.Save().ToArray()
			File.WriteAllBytes(args(1), packedNTemplate)

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
