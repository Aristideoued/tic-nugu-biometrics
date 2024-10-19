Imports Microsoft.VisualBasic
Imports System

Imports Neurotec.Biometrics
Imports Neurotec.Devices
Imports Neurotec.Licensing

Friend Class Program
	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const license As String = "IrisExtractor"
		'Const license As String = "IrisClient"
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

		Try
			' Obtain license
			If (Not NLicense.Obtain("/local", 5000, license)) Then
				Throw New ApplicationException(String.Format("Could not obtain license: {0}", license))
			End If

			Using deviceManager = New NDeviceManager With {.DeviceTypes = NDeviceType.IrisScanner, .AutoPlug = True}
				deviceManager.Initialize()
				Console.WriteLine("Device manager created. found scanners: {0}", deviceManager.Devices.Count)

				For Each scanner As NIrisScanner In deviceManager.Devices
					Console.Write("Found scanner {0}", scanner.DisplayName)

					Console.Write(vbTab & "Capturing right iris: ")
					Using rightIrisBiometric = New NIris()
						rightIrisBiometric.Position = NEPosition.Right
						Dim biometricStatus = scanner.Capture(rightIrisBiometric, -1)
						If biometricStatus <> NBiometricStatus.Ok Then
							Console.WriteLine("Failed to capture from scanner, status: {0}", biometricStatus)
							Continue For
						End If
						Dim filename As String = String.Format("{0}_iris_right.jpg", scanner.DisplayName)
						rightIrisBiometric.Image.Save(filename)
						Console.WriteLine("Done")
					End Using

					Console.Write(vbTab & "Capturing left eye: ")
					Using leftIrisBiometric = New NIris()
						leftIrisBiometric.Position = NEPosition.Left
						Dim biometricStatus = scanner.Capture(leftIrisBiometric, -1)
						If biometricStatus <> NBiometricStatus.Ok Then
							Console.WriteLine("Failed to capture from scanner, status: {0}", biometricStatus)
							Continue For
						End If
						Dim filename As String = String.Format("{0}_iris_left.jpg", scanner.DisplayName)
						leftIrisBiometric.Image.Save(filename)
						Console.WriteLine("Done")
					End Using
				Next scanner
			End Using
			Console.WriteLine("Done")

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
