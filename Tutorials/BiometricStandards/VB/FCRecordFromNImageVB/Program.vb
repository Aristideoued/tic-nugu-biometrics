Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.IO

Imports Neurotec.Images
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage: {0} [FCRecord] [Standard] [Version] {{[image]}}", TutorialUtils.GetAssemblyName())
		Console.WriteLine(Constants.vbTab & "[FCRecord] - output FCRecord")
		Console.WriteLine(Constants.vbTab & "[Standard] - standard for the record (ISO or ANSI)")
		Console.WriteLine(Constants.vbTab & "[Version] - version for the record")
		Console.WriteLine(Constants.vbTab & Constants.vbTab & "1 - ANSI/INCITS 375-2004")
		Console.WriteLine(Constants.vbTab & Constants.vbTab & "1 - ISO/IEC 19794-5:2005")
		Console.WriteLine(Constants.vbTab & Constants.vbTab & "3 - ISO/IEC 19794-5:2011")
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

		Const license As String = "FaceClient"
		'Const license As String = "FaceFastExtractor"

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

		Dim fc As FCRecord = Nothing
		Try
			' Obtain license
			If (Not NLicense.Obtain("/local", 5000, license)) Then
				Throw New ApplicationException(String.Format("Could not obtain license: {0}", license))
			End If

			Dim standard As BdifStandard = CType(System.Enum.Parse(GetType(BdifStandard), args(1), True), BdifStandard)
			Dim version As NVersion = Nothing

			Select Case args(2)
				Case "1"
					version = IIf(standard = BdifStandard.Ansi, FCRecord.VersionAnsi10, FCRecord.VersionIso10)
				Case "3"
					If standard <> BdifStandard.Iso Then Throw New ArgumentException("Standard and version is incompatible")
					version = FCRecord.VersionIso30
				Case Else
					Throw New ArgumentException("Version was not recognised")
			End Select

			Dim faceImageType As FcrFaceImageType = FcrFaceImageType.Basic

			For i As Integer = 3 To args.Length - 1
				Using imageBuffer = NFile.ReadAllBytes(args(i))
					If fc Is Nothing Then
						fc = New FCRecord(standard, version, faceImageType, imageBuffer)
					Else
						fc.FaceImages.Add(faceImageType, imageBuffer)
					End If
				End Using
			Next i

			If fc IsNot Nothing Then
				File.WriteAllBytes(args(0), fc.Save().ToArray())

				Console.WriteLine("FCRecord saved to {0}", args(0))
			Else
				Console.WriteLine("No images were added to FCRecord")
			End If

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		Finally
			If fc IsNot Nothing Then
				fc.Dispose()
			End If
		End Try
	End Function
End Class
