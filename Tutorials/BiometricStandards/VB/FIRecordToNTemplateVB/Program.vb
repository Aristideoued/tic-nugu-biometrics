Imports System
Imports System.IO

Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Client
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing
Imports Microsoft.VisualBasic

Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage: {0} [FIRecord] [NTemplate]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "[FIRecord]  - input FIRecord")
		Console.WriteLine(vbTab & "[NTemplate] - output NTemplate")

		Return 1
	End Function

	Shared Function Main(ByVal args As String()) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 2 Then
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
			' Obtain license
			If (Not NLicense.Obtain("/local", 5000, license)) Then
				Throw New ApplicationException(String.Format("Could not obtain license: {0}", license))
			End If

			Using biometricClient = New NBiometricClient()
				Using subject = New NSubject()
					Dim fiRec As FIRecord

					' Read FIRecord from file
					Dim fiRecordData As Byte() = File.ReadAllBytes(args(0))

					' Create FIRecord
					fiRec = New FIRecord(fiRecordData, BdifStandard.Iso)

					' Read all images from FIRecord
					For Each fv As FirFingerView In fiRec.FingerViews
						Dim finger As NFinger = New NFinger()
						finger.Image = fv.ToNImage()
						subject.Fingers.Add(finger)
					Next

					' Set finger template size (large is recommended for enrolment to database) (optional)
					biometricClient.FingersTemplateSize = NTemplateSize.Large

					' Create template from added finger image(s)
					Dim status = biometricClient.CreateTemplate(subject)
					Console.WriteLine(If(status = NBiometricStatus.Ok, "Template extracted", [String].Format("Extraction failed: {0}", status)))

					' Save template to file
					If status = NBiometricStatus.Ok Then
						File.WriteAllBytes(args(1), subject.GetTemplateBuffer().ToArray())
						Console.WriteLine("Template saved successfully")
					End If
				End Using
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
