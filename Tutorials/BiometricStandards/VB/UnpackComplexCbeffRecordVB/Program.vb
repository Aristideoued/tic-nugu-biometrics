Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Biometrics.Standards
Imports Neurotec.IO
Imports Neurotec.Licensing

Friend Class Program
	Private Enum BdbFormat
		ANTemplate = &H1B8019
		FCRecordAnsi = &H1B0501
		FCRecordIso = &H1010008
		FIRecordAnsi = &H1B0401
		FIRecordIso = &H1010007
		FMRecordAnsi = &H1B0202
		FMRecordIso = &H1010002
		IIRecordAnsiPolar = &H1B0602
		IIRecordIsoPolar = &H101000B
		IIRecordAnsiRectilinear = &H1B0601
		IIRecordIsoRectilinear = &H1010009
	End Enum

	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ComplexCbeffRecord] [PatronFormat]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[ComplexCbeffRecord] - filename of CbeffRecord which will be created.")
		Console.WriteLine(Constants.vbTab & "[PatronFormat] - hex number identifying patron format (all supported values can be found in CbeffRecord class documentation).")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 2 Then
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

			' Read CbeffRecord buffer
			Dim packedCbeffRecord = New NBuffer(File.ReadAllBytes(args(0)))

			' Get CbeffRecord patron format
			' all supported patron formats can be found in CbeffRecord class documentation
			Dim patronFormat As UInteger = UInteger.Parse(args(1), Globalization.NumberStyles.AllowHexSpecifier)

			' Create CbeffRecord object
			Dim cbeffRecord = New CbeffRecord(packedCbeffRecord, patronFormat)

			' Start unpacking the record
			UnpackRecords(cbeffRecord)

			Console.WriteLine("Records sucessfully saved")
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function

	Private Shared Sub UnpackRecords(ByVal cbeffRecord As CbeffRecord)
		Dim recordNumber As Integer = 0
		UnpackRecords(cbeffRecord, recordNumber)
	End Sub

	Private Shared Sub UnpackRecords(ByVal cbeffRecord As CbeffRecord, ByRef recordNumber As Integer)
		If cbeffRecord.Records.Count = 0 Then
			' Write root record to file
			RecordToFile(cbeffRecord, recordNumber)
			recordNumber += 1
		Else
			' Go through all record in this CbeffRecord
			For Each record In cbeffRecord.Records
				' Start unpacking complex record
				UnpackRecords(record, recordNumber)
			Next record
		End If
	End Sub

	Private Shared Sub RecordToFile(ByVal record As CbeffRecord, ByVal recordNumber As Integer)
		Dim fileName As String
		Try
			' Find Record format
			fileName = String.Format("Record{0}_{1}.dat", recordNumber, System.Enum.GetName(GetType(BdbFormat), record.BdbFormat))
		Catch
			fileName = String.Format("Record{0}_UnknownFormat.dat", recordNumber)
		End Try

		' Save specified record
		File.WriteAllBytes(fileName, record.BdbBuffer.ToArray())
	End Sub
End Class
