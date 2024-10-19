Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.IO

Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage: {0} [IIRecord] [Standard] [Version] [image]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(Constants.vbTab & "[IIRecord] - output IIRecord")
		Console.WriteLine(Constants.vbTab & "[Standard] - standard for the record (ANSI or ISO)")
		Console.WriteLine(Constants.vbTab & "[Version] - version for the record")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 1 - ANSI/INCITS 379-2004")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 1 - ISO/IEC 19794-6:2005")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & " 2 - ISO/IEC 19794-6:2011")
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

		Const license As String = "IrisClient"
		'Const license As String = "IrisFastExtractor"

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

		Dim iiRec As IIRecord = Nothing
		Try
			' Obtain license
			If (Not NLicense.Obtain("/local", 5000, license)) Then
				Throw New ApplicationException(String.Format("Could not obtain license: {0}", license))
			End If

			Dim standard = CType(System.Enum.Parse(GetType(BdifStandard), args(1), True), BdifStandard)
			Dim version As NVersion
			Select Case args(2)
				Case "1"
					version = If(standard = BdifStandard.Ansi, IIRecord.VersionAnsi10, IIRecord.VersionIso10)
				Case "2"
					If standard <> BdifStandard.Iso Then
						Throw New ArgumentException("Standard and version is incompatible")
					End If
					version = IIRecord.VersionIso20
				Case Else
					Throw New ArgumentException("Version was not recognised")
			End Select

			Dim irisPosition As BdifEyePosition = BdifEyePosition.Left
			For i As Integer = 3 To args.Length - 1
				Using imageBuffer = NFile.ReadAllBytes(args(i))
					If iiRec Is Nothing Then
						iiRec = New IIRecord(standard, version, irisPosition, imageBuffer)
					Else
						iiRec.IrisImages.Add(irisPosition, imageBuffer)
					End If
				End Using
			Next i

			If iiRec IsNot Nothing Then
				File.WriteAllBytes(args(0), iiRec.Save().ToArray())

				Console.WriteLine("IIRecord saved to {0}", args(0))
			Else
				Console.WriteLine("No images were added to IIRecord")
			End If

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		Finally
			If iiRec IsNot Nothing Then
				iiRec.Dispose()
			End If
		End Try
	End Function

	Private Shared Function IsRecordFirstVersion(ByVal record As IIRecord) As Boolean
		Return record.Standard = BdifStandard.Ansi AndAlso record.Version = IIRecord.VersionAnsi10 OrElse record.Standard = BdifStandard.Iso AndAlso record.Version = IIRecord.VersionIso10
	End Function
End Class
