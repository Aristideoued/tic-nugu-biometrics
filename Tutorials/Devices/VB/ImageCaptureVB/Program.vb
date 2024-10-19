Imports Neurotec.Licensing
Imports Microsoft.VisualBasic
Imports System

Imports Neurotec.Images
Imports Neurotec.Devices

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [frameCount]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Console.WriteLine(vbTab & "frameCount - number of frames to capture from each camera to current directory.")
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

		Const license As String = "FaceExtractor"
		'Const license As String = "FaceClient"
		'Const license As String = "FaceFastExtractor"
		'Const license As String = "SentiVeillance"

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

			Dim frameCount As Integer = Integer.Parse(args(0))
			If frameCount = 0 Then
				Console.WriteLine("No frames will be captured as frame count is not specified")
			End If

			Using deviceManager = New NDeviceManager With {.DeviceTypes = NDeviceType.Camera, .AutoPlug = True}
				deviceManager.Initialize()
				Console.WriteLine("Device manager created. found cameras: {0}", deviceManager.Devices.Count)

				For Each camera As NCamera In deviceManager.Devices
					Console.Write("Found camera {0}", camera.DisplayName)

					camera.StartCapturing()

					If frameCount > 0 Then
						Console.Write(", capturing")
						For i As Integer = 0 To frameCount - 1
							Dim filename As String = String.Format("{0}_{1:d4}.jpg", camera.DisplayName, i)
							Using image As NImage = camera.GetFrame()
								image.Save(filename)
							End Using
							Console.Write(".")
						Next i
						Console.Write(" Done")
						Console.WriteLine()
					End If
					camera.StopCapturing()
				Next camera
			End Using
			Console.WriteLine("Done")
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
