
Imports Neurotec.Licensing
Imports Microsoft.VisualBasic
Imports System

Imports Neurotec.Devices
Imports Neurotec.Sound

Friend Class Program

	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [bufferCount]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Console.WriteLine(vbTab & "bufferCount - number of sound buffers to capture from each microphone to current directory")
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

		Const license As String = "VoiceExtractor"
		'Const license As String = "VoiceClient"
		'Const license As String = "VoiceFastExtractor"

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

			Dim bufferCount As Integer = Integer.Parse(args(0))
			If bufferCount = 0 Then
				Console.WriteLine("No sound buffers will be captured as sound buffer count is not specified")
			End If

			Using deviceManager = New NDeviceManager With {.DeviceTypes = NDeviceType.Microphone, .AutoPlug = True}
				deviceManager.Initialize()
				Console.WriteLine("Device manager created. found microphones: {0}", deviceManager.Devices.Count)

				For Each microphone As NMicrophone In deviceManager.Devices
					Console.Write("Found microphone {0}", microphone.DisplayName)

					microphone.StartCapturing()

					If bufferCount > 0 Then
						Console.WriteLine(", capturing")
						For i As Integer = 0 To bufferCount - 1
							Using soundSample As NSoundBuffer = microphone.GetSoundSample()
								Console.WriteLine("Sample buffer received. sample rate: {0}, sample length: {1}", soundSample.SampleRate, soundSample.Length)
							End Using
							Console.Write(" ... ")
						Next i
						Console.Write(" Done")
						Console.WriteLine()
					End If
					microphone.StopCapturing()
				Next microphone
			End Using
			Console.WriteLine("Done")

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
