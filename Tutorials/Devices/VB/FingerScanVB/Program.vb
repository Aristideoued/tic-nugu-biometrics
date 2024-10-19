Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Biometrics
Imports Neurotec.Devices
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [imageCount]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Console.WriteLine(vbTab & "imageCount - count of fingerprint images to be scanned")
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

		Const license As String = "FingerExtractor"
		'Const license As String = "FingerClient"
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

			Dim imageCount As Integer = Integer.Parse(args(0))
			If imageCount = 0 Then
				Console.WriteLine("No frames will be captured as frame count is not specified")
			End If

			Using deviceManager = New NDeviceManager With {.DeviceTypes = NDeviceType.FingerScanner, .AutoPlug = True}
				deviceManager.Initialize()
				Console.WriteLine("Device manager created. found scanners: {0}", deviceManager.Devices.Count)

				For Each scanner As NFScanner In deviceManager.Devices
					Console.WriteLine("Found scanner {0}, capturing fingerprints", scanner.DisplayName)

					For i As Integer = 0 To imageCount - 1
						Console.Write(vbTab & "Image {0} of {1}. please put your fingerprint on scanner:", i + 1, imageCount)
						Dim filename As String = String.Format("{0}_{1:d4}.jpg", scanner.DisplayName, i)
						Using biometric = New NFinger()
							biometric.Position = NFPosition.Unknown
							Dim biometricStatus = scanner.Capture(biometric, -1)
							If biometricStatus <> NBiometricStatus.Ok Then
								Console.WriteLine("Failed to capture from scanner, status: {0}", biometricStatus)
								Continue For
							End If
							biometric.Image.Save(filename)
							Console.WriteLine("Image captured")
						End Using
					Next i
				Next scanner
				Console.WriteLine("Done")
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
