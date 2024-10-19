Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Licensing
Imports Neurotec.Media
Imports Neurotec.Images

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [source] [frameCount] <optional: is url>", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Console.WriteLine(vbTab & "source - filename or url frames should be captured from")
		Console.WriteLine(vbTab & "frameCount - number of sound buffers to capture from specified filename or url")
		Console.WriteLine(vbTab & "is url - specifies that passed source parameter is url (value: 1) or filename (value: 0)")
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 2 Then
			Return Usage()
		End If

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const license As String = "FaceExtractor"
		'Const license As String = "FaceClient"
		'Const license As String = "FaceFastExtractor"
		'Const license As String = "SentiVeillance"
		'Const license As String = "SentiMask"

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
				Throw New NotActivatedException(String.Format("Could not obtain license: {0}", license))
			End If

			Dim uri As String = args(0)
			Dim isUrl As Boolean = False
			Dim frameCount As Integer = Integer.Parse(args(1))
			If frameCount = 0 Then
				Console.WriteLine("No frames will be captured as frame count is not specified")
			End If

			If args.Length > 2 Then
				isUrl = args(2) = "1"
			End If

			' create media source
			Using mediaSource As NMediaSource = IIf((isUrl), NMediaSource.FromUrl(uri), NMediaSource.FromFile(uri))
				Console.WriteLine("Display name: {0}", mediaSource.DisplayName)

				Using mediaReader As New NMediaReader(mediaSource, NMediaType.Video, True, Nothing)
					ReadFrames(mediaReader, frameCount)
				End Using
			End Using
			Console.WriteLine("Done")
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function

	Private Shared Sub DumpMediaFormat(ByVal mediaFormat As NMediaFormat)
		If mediaFormat Is Nothing Then
			Throw New ArgumentNullException("mediaFormat")
		End If

		Select Case mediaFormat.MediaType
			Case NMediaType.Video
				Dim videoFormat As NVideoFormat = CType(mediaFormat, NVideoFormat)
				Console.WriteLine("Video format .. {0}x{1} @ {2}/{3} (interlace: {4}, aspect ratio: {5}/{6})", videoFormat.Width, videoFormat.Height, videoFormat.FrameRate.Numerator, videoFormat.FrameRate.Denominator, videoFormat.InterlaceMode, videoFormat.PixelAspectRatio.Numerator, videoFormat.PixelAspectRatio.Denominator)
			Case NMediaType.Audio
				Dim audioFormat As NAudioFormat = CType(mediaFormat, NAudioFormat)
				Console.WriteLine("Audio format .. channels: {0}, samples/second: {1}, bits/channel: {2}", audioFormat.ChannelCount, audioFormat.SampleRate, audioFormat.BitsPerChannel)
			Case Else
				Throw New ArgumentException("Unknown media type specified in format!")
		End Select
	End Sub

	Private Shared Sub ReadFrames(ByVal mediaReader As NMediaReader, ByVal frameCount As Integer)
		Dim mediaSource As NMediaSource = mediaReader.Source

		Console.WriteLine("Media length: {0}", mediaReader.Length)

		Dim mediaFormats() As NMediaFormat = mediaSource.GetFormats(NMediaType.Video)
		If mediaFormats Is Nothing Then
			Console.WriteLine("Formats are not yet available (should be available after media reader is started")
		Else
			Console.WriteLine("Format count: {0}", mediaFormats.Length)
			For i As Integer = 0 To mediaFormats.Length - 1
				Console.Write("[{0}] ", i)
				DumpMediaFormat(mediaFormats(i))
			Next i
		End If

		Dim currentMediaFormat As NMediaFormat = mediaSource.GetCurrentFormat(NMediaType.Video)
		If currentMediaFormat IsNot Nothing Then
			Console.WriteLine("Current media format:")
			DumpMediaFormat(currentMediaFormat)

			If mediaFormats IsNot Nothing Then
				Console.WriteLine("Set the last supported format (optional) ... ")
				mediaSource.SetCurrentFormat(NMediaType.Video, mediaFormats(mediaFormats.Length - 1))
			End If
		Else
			Console.WriteLine("Current media format is not yet available (will be available after media reader start)")
		End If

		Console.Write("Starting capture ... ")
		mediaReader.Start()
		Console.WriteLine("Capture started")

		Try
			currentMediaFormat = mediaSource.GetCurrentFormat(NMediaType.Video)
			If currentMediaFormat Is Nothing Then
				Throw New Exception("Current media format is not set even after media reader start!")
			End If
			Console.WriteLine("Capturing with format: ")
			DumpMediaFormat(currentMediaFormat)

			For i As Integer = 0 To frameCount - 1
				Dim timeSpan, duration As TimeSpan

				Using image As NImage = mediaReader.ReadVideoSample(timeSpan, duration)
					If image Is Nothing Then ' end of stream
						Return
					End If

					Dim filename As String = String.Format("{0:d4}.jpg", i)
					image.Save(filename)

					Console.WriteLine("[{0} {1}] {2}", timeSpan, duration, filename)
				End Using
			Next i
		Finally
			mediaReader.Stop()
		End Try
	End Sub
End Class
