Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Images
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [filename]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Console.WriteLine(vbTab & "filename - image filename.")
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 1 Then
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
			' Obtain license (optional)
			If (Not NLicense.Obtain("/local", 5000, license)) Then
					Console.WriteLine("Could not obtain license: {0}", license)
			End If

			' Create NImage with info from file
			Using image = NImage.FromFile(args(0))
				' Get image format
				Dim format As NImageFormat = image.Info.Format

				' Print info common to all formats
				Console.WriteLine("Format: {0}", format.Name)

				' Print format specific info.
				If NImageFormat.Jpeg2K.Equals(format) Then
					Dim info As Jpeg2KInfo = CType(image.Info, Jpeg2KInfo)
					Console.WriteLine("Profile: {0}", info.Profile)
					Console.WriteLine("Compression ratio: {0}", info.Ratio)
				ElseIf NImageFormat.Jpeg.Equals(format) Then
					Dim info As JpegInfo = CType(image.Info, JpegInfo)
					Console.WriteLine("Lossless: {0}", info.IsLossless)
					Console.WriteLine("Quality: {0}", info.Quality)
				ElseIf NImageFormat.Png.Equals(format) Then
					Dim info As PngInfo = CType(image.Info, PngInfo)
					Console.WriteLine("Compression level: {0}", info.CompressionLevel)
				ElseIf NImageFormat.Wsq.Equals(format) Then
					Dim info As WsqInfo = CType(image.Info, WsqInfo)
					Console.WriteLine("Bit rate: {0}", info.BitRate)
					Console.WriteLine("Implementation number: {0}", info.ImplementationNumber)
				End If
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
