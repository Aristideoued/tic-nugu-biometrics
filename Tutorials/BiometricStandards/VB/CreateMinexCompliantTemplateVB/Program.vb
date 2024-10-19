Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports System.Collections.Generic
Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing
Imports Neurotec.IO

Friend Class Program
	Private Const Components As String = "Biometrics.FingerExtraction,Biometrics.FingerQualityAssessmentBase,Biometrics.Standards.FingerTemplates"

	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [image] [template]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[image]    - image filename to extract.")
		Console.WriteLine(Constants.vbTab & "[template] - FMRecord to store extracted features.")
		Console.WriteLine()
		Console.WriteLine("example:")
		Console.WriteLine(Constants.vbTab & "{0} image.jpg fmrecord.FMRecord", TutorialUtils.GetAssemblyName())

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

			Using biometricEngine = New NBiometricEngine()
				Using subject = New NSubject()
					Using finger = New NFinger()

						Dim imageFileName As String = args(0)
						Dim outputFileName As String = args(1)

						finger.FileName = args(0)
						subject.Fingers.Add(finger)
						biometricEngine.FingersExtractionScenario = NExtractionScenario.Minex

						Dim task As NBiometricTask = biometricEngine.CreateTask((NBiometricOperations.CreateTemplate Or NBiometricOperations.AssessQuality), subject)
						biometricEngine.PerformTask(task)
						Dim biometricStatus As NBiometricStatus = task.Status

						If biometricStatus = NBiometricStatus.Ok Then
							Console.WriteLine("ANSI template extracted.")

							' Save FMRecord 
							Dim storedFmRecord As Byte() = subject.GetTemplateBuffer(CbeffBiometricOrganizations.IncitsTCM1Biometrics,
								CbeffBdbFormatIdentifiers.IncitsTCM1BiometricsFingerMinutiaeU,
								FMRecord.VersionAnsi20).ToArray()
							File.WriteAllBytes(outputFileName, storedFmRecord)

						Else
							Console.WriteLine("Template extraction failed!")
							Console.WriteLine("Biometric status, {0}", biometricStatus)
							If task.Error IsNot Nothing Then
								Return TutorialUtils.PrintException(task.Error)
							End If
							Return -1
						End If
					End Using
				End Using
			End Using

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
