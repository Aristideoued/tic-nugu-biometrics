Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.IO

Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage: {0} [FIRecord] [Standard] [Version] {{[image]}}", TutorialUtils.GetAssemblyName())
		Console.WriteLine(Constants.vbTab & "[FIRecord] - output FIRecord")
		Console.WriteLine(Constants.vbTab & "[Standard] - standard for the record (ANSI or ISO)")
		Console.WriteLine(Constants.vbTab & "[Version] - version for the record")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 1 - ANSI/INCITS 381-2004")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 2.5 - ANSI/INCITS 381-2009")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 1 - ISO/IEC 19794-4:2005")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 2 - ISO/IEC 19794-4:2011")
		Console.WriteLine(Constants.vbTab & "[image]    - one or more images")

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

		Dim fi As FIRecord = Nothing
		Try
			' Obtain license
			If (Not NLicense.Obtain("/local", 5000, license)) Then
				Throw New ApplicationException(String.Format("Could not obtain license: {0}", license))
			End If

			Dim standard = CType(System.Enum.Parse(GetType(BdifStandard), args(1), True), BdifStandard)
			Dim version As NVersion
			Select Case args(2)
				Case "1"
					version = If(standard = BdifStandard.Ansi, FIRecord.VersionAnsi10, FIRecord.VersionIso10)
				Case "2"
					If standard <> BdifStandard.Iso Then
						Throw New ArgumentException("Standard and version is incompatible")
					End If
					version = FIRecord.VersionIso20
				Case "2.5"
					If standard <> BdifStandard.Ansi Then
						Throw New ArgumentException("Standard and version is incompatible")
					End If
					version = FIRecord.VersionAnsi25
				Case Else
					Throw New ArgumentException("Version was not recognised")
			End Select

			Dim vertScanResolution As UShort = 500 'ppi
			Dim horzScanResolution As UShort = 500 'ppi
			Dim fPosition As BdifFPPosition = BdifFPPosition.RightThumb

			' Image must be compressed using valid compression algorithm for FIRecord.
			' How to convert image to required compression algorithm please see "Media" tutorials, Like "CreateWsq".						

			For i As Integer = 3 To args.Length - 1
				Using imageBuffer = NFile.ReadAllBytes(args(i))
					If fi Is Nothing Then
						fi = New FIRecord(standard, version, 10, fPosition, horzScanResolution, vertScanResolution, imageBuffer)
					Else
						fi.FingerViews.Add(fPosition, horzScanResolution, vertScanResolution, imageBuffer)
					End If
				End Using
			Next i

			If fi IsNot Nothing Then
				File.WriteAllBytes(args(0), fi.Save().ToArray())
				Console.WriteLine("FIRecord saved to {0}", args(0))
			Else
				Console.WriteLine("No images were added to FIRecord")
			End If

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		Finally
			If fi IsNot Nothing Then
				fi.Dispose()
			End If
		End Try
	End Function

	Private Shared Function IsRecordFirstVersion(ByVal record As FIRecord) As Boolean
		Return record.Standard = BdifStandard.Ansi AndAlso record.Version = FIRecord.VersionAnsi10 OrElse record.Standard = BdifStandard.Iso AndAlso record.Version = FIRecord.VersionIso10
	End Function
End Class
