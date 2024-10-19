Imports Microsoft.VisualBasic
Imports System
Imports System.IO

Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing
Imports System.Collections.Generic

Friend Class Program
	Private Shared ReadOnly Components() As String = {"Biometrics.Standards.Base", "Biometrics.Standards.Irises", "Biometrics.Standards.Fingers", "Biometrics.Standards.Faces", "Biometrics.Standards.Palms"}

	Private Enum RecordTypes
		ANTemplate
		FCRecord
		FIRecord
		FMRecord
		IIRecord
	End Enum

	Private Class RecordInformation
		Private privateRecordFile As String
		Public Property RecordFile() As String
			Get
				Return privateRecordFile
			End Get
			Set(ByVal value As String)
				privateRecordFile = value
			End Set
		End Property
		Private privateStandard As BdifStandard
		Public Property Standard() As BdifStandard
			Get
				Return privateStandard
			End Get
			Set(ByVal value As BdifStandard)
				privateStandard = value
			End Set
		End Property
		Private privateRecordType As RecordTypes
		Public Property RecordType() As RecordTypes
			Get
				Return privateRecordType
			End Get
			Set(ByVal value As RecordTypes)
				privateRecordType = value
			End Set
		End Property
		Private privatePatronFormat As UInteger
		Public Property PatronFormat() As UInteger
			Get
				Return privatePatronFormat
			End Get
			Set(ByVal value As UInteger)
				privatePatronFormat = value
			End Set
		End Property
	End Class

	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ComplexCbeffRecord] [PatronFormat] [[Record] [RecordType] [RecordStandard] [PatronFormat]] ...", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[ComplexCbeffRecord] - filename of CbeffRecord which will be created.")
		Console.WriteLine(Constants.vbTab & "[PatronFormat] - hex number identifying root record patron format (all supported values can be found in CbeffRecord class documentation).")

		Console.WriteLine(Constants.vbTab & "[[Record] [RecordType] [RecordStandard] [PatronFormat]] - record information. Block can be specified more than once.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "[Record] - filename containing the record.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "[RecordType] - one of record type values(ANTemplate, FCRecord, FIRecord, FMRecord, IIRecord)")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "[RecordStandard] - one of record standard values(ANSI, ISO or UNSPECIFIED if ANTemplate type is used).")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "[PatronFormat] - hex number identifying patron format.")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 6 OrElse (args.Length - 2) Mod 4 <> 0 Then
			Return Usage()
		End If

		' Parse record information in arguments
		Dim recordInformation() As RecordInformation
		Try
			recordInformation = ParseArguments(args)
		Catch
			Return Usage()
		End Try

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

			' Create root CbeffRecord
			Dim rootPatronFormat = UInteger.Parse(args(1), Globalization.NumberStyles.AllowHexSpecifier)
			Dim rootCbeffRecord = New CbeffRecord(rootPatronFormat)

			For Each info In recordInformation
				Dim cbeffRecord As CbeffRecord = Nothing
				Dim packedRecord = File.ReadAllBytes(info.RecordFile)

				' Create a record object according information specified in arguments
				Select Case info.RecordType
					Case RecordTypes.ANTemplate
						Dim anTemplate = New ANTemplate(packedRecord)
						If (Not anTemplate.IsValidated) Then
							Throw New Exception("ANSI/NIST template is not valid")
						End If
						cbeffRecord = New CbeffRecord(anTemplate, info.PatronFormat)
					Case RecordTypes.FCRecord
						Dim fcRecord = New FCRecord(packedRecord, info.Standard)
						cbeffRecord = New CbeffRecord(fcRecord, info.PatronFormat)
					Case RecordTypes.FIRecord
						Dim fiRecord = New FIRecord(packedRecord, info.Standard)
						cbeffRecord = New CbeffRecord(fiRecord, info.PatronFormat)
					Case RecordTypes.FMRecord
						Dim fmRecord = New FMRecord(packedRecord, info.Standard)
						cbeffRecord = New CbeffRecord(fmRecord, info.PatronFormat)
					Case RecordTypes.IIRecord
						Dim iiRecord = New IIRecord(packedRecord, info.Standard)
						cbeffRecord = New CbeffRecord(iiRecord, info.PatronFormat)
				End Select

				' Add the new CbeffRecord to complex root CbeffRecord
				rootCbeffRecord.Records.Add(cbeffRecord)
			Next info

			' Save specified record
			File.WriteAllBytes(args(0), rootCbeffRecord.Save().ToArray())
			Console.WriteLine("Record sucessfully saved")

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function

	Private Shared Function ParseArguments(ByVal args() As String) As RecordInformation()
		Dim infoList = New List(Of RecordInformation)()

		For i As Integer = 2 To args.Length - 1 Step 4
			Dim recInfo = New RecordInformation()
			recInfo.RecordFile = args(i)
			recInfo.RecordType = CType(System.Enum.Parse(GetType(RecordTypes), args(i + 1), True), RecordTypes)
			recInfo.Standard = CType(System.Enum.Parse(GetType(BdifStandard), args(i + 2), True), BdifStandard)
			recInfo.PatronFormat = UInteger.Parse(args(i + 3), Globalization.NumberStyles.AllowHexSpecifier)
			infoList.Add(recInfo)
		Next i

		Return infoList.ToArray()
	End Function
End Class
