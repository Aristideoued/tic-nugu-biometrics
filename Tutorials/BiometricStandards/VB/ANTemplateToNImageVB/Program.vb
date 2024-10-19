Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Images
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ANTemplate]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[ATemplate] - filename of ANTemplate.")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 1 Then
			Return Usage()
		End If

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const licenses As String = "FingerClient,PalmClient,FaceClient,IrisClient"
		'Const licenses As String = "FingerFastExtractor,PalmClient,FaceFastExtractor,IrisFastExtractor"

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

		Dim anyMatchingComponent = False
		Try
			' Obtain licenses
			For Each license As String In licenses.Split(","c)
				If NLicense.Obtain("/local", 5000, license) Then
					Console.WriteLine("Obtained license: {0}", license)
					anyMatchingComponent = True
				End If
			Next license
			If (Not anyMatchingComponent) Then
				Throw New NotActivatedException("Could not obtain any matching license")
			End If

			Using anTemplate = New ANTemplate(args(0))
				If (Not anTemplate.IsValidated) Then
					Throw New Exception("ANSI/NIST template is not valid")
				End If
				For i As Integer = 0 To anTemplate.Records.Count - 1
					Dim record As ANRecord = anTemplate.Records(i)
					Dim image As NImage = Nothing
					Dim number As Integer = record.RecordType.Number
					If number >= 3 AndAlso number <= 8 AndAlso number <> 7 Then
						image = (CType(record, ANImageBinaryRecord)).ToNImage()
					ElseIf number >= 10 AndAlso number <= 17 Then
						image = (CType(record, ANImageAsciiBinaryRecord)).ToNImage()
					End If

					If image IsNot Nothing Then
						Dim fileName As String = String.Format("record{0}_type{1}.jpg", i + 1, number)
						image.Save(fileName)
						image.Dispose()
						Console.WriteLine("Image saved to {0}", fileName)
					End If
				Next i
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
