Imports Neurotec.IO
Imports Microsoft.VisualBasic
Imports System
Imports System.IO

Imports Neurotec.Biometrics
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ANTemplate] [NTemplate]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[ATemplate] - filename of ANTemplate.")
		Console.WriteLine(Constants.vbTab & "[NTemplate] - filename of NTemplate.")
		Console.WriteLine("")
		Console.WriteLine("examples:")
		Console.WriteLine(Constants.vbTab & "{0} antemplate.data nTemplate.data", TutorialUtils.GetAssemblyName())

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 2 Then
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

			Dim aNTemplateFileName As String = args(0)

			' Creating ANTemplate object from file
			Using anTemplate = New ANTemplate(aNTemplateFileName)
				If (Not anTemplate.IsValidated) Then
					Throw New Exception("ANSI/NIST template is not valid")
				End If
				' Converting ANTemplate object to NTemplate object
				Using nTemplate As NTemplate = anTemplate.ToNTemplate()
					' Packing NTemplate object
					Dim packedNTemplate() As Byte = nTemplate.Save().ToArray()

					' Storing NTemplate object in file
					File.WriteAllBytes(args(1), packedNTemplate)
				End Using
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
