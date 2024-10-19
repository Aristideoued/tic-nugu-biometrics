Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Images
Imports Neurotec.Licensing
Imports Neurotec.IO

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ANTemplate] [Encoding] [Finger NImage] [Face NImage] [Iris NImage]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[ANTemplate] - filename for ANTemplate.")
		Console.WriteLine(Constants.vbTab & "[Encoding] - specifies ANTemplate encoding type.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - Traditional binary encoding.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - NIEM-conformant XML encoding.")
		Console.WriteLine(Constants.vbTab & "[Finger NImage]  - filename with finger image file.")
		Console.WriteLine(Constants.vbTab & "[Face NImage]    - filename with face image file (optional).")
		Console.WriteLine(Constants.vbTab & "[Iris NImage]    - filename with finger image file (optional).")
		Console.WriteLine("")

		Return 1
	End Function

	Private Shared Sub ANTemplateGetRecordType2(ByVal antemplate As ANTemplate, ByVal encoding As BdifEncodingType)
		Dim nameFieldNumber As Integer = 18
		Dim placeOfBirthFieldNumber As Integer = 20
		Dim dateOfBirthFieldNumber As Integer = 22
		Dim genderFieldNumber As Integer = 24

		Try
			Dim record As ANType2Record = antemplate.Records.AddType2()
			' Adds fields for "traditional" binary encoding
			If encoding = BdifEncodingType.Traditional Then
				record.Fields.Add(nameFieldNumber, "name, surname")
				record.Fields.Add(placeOfBirthFieldNumber, "UK")
				record.Fields.Add(dateOfBirthFieldNumber, "19700131")
				record.Fields.Add(genderFieldNumber, "M")
			Else    ' Adds fields for NIEM-conformant XML encoding
				record.Fields.Add(nameFieldNumber, "PersonName", "name, surname")
				record.Fields.Add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", "UK")
				record.Fields.Add(dateOfBirthFieldNumber, "PersonBirthDate", "19700131")
				record.Fields.Add(genderFieldNumber, "PersonSexCode", "M")
			End If
		Catch e1 As Exception
			Throw
		End Try
	End Sub

	Private Shared Sub ANTemplateGetRecordType10(ByVal antemplate As ANTemplate, ByVal fileNameIn As String, ByVal src As String)
		Try
			Using imageBuffer = NFile.ReadAllBytes(fileNameIn)
				Dim imt As ANImageType = ANImageType.Face
				Dim record As ANType10Record = antemplate.Records.AddType10(imt, src, imageBuffer)
			End Using
		Catch e1 As Exception
			Throw
		End Try
	End Sub

	Private Shared Sub ANTemplateGetRecordType14(ByVal antemplate As ANTemplate, ByVal fileNameIn As String, ByVal src As String)
		Try
			Using imageBuffer = NFile.ReadAllBytes(fileNameIn)
				Dim record As ANType14Record = antemplate.Records.AddType14(src, imageBuffer)
			End Using
		Catch e1 As Exception
			Throw
		End Try
	End Sub

	Private Shared Sub ANTemplateGetRecordType17(ByVal antemplate As ANTemplate, ByVal fileNameIn As String, ByVal src As String)
		Try
			Using imageBuffer = NFile.ReadAllBytes(fileNameIn)
				Dim record As ANType17Record = antemplate.Records.AddType17(src, imageBuffer)
			End Using
		Catch e1 As Exception
			Throw
		End Try
	End Sub

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 3 Then
			Return Usage()
		End If

		'=========================================================================
		' CHOOSE LICENCES !!!
		'=========================================================================
		' ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
		' If you are using a TRIAL version - choose any of them.

		Const licenses As String = "FingerClient,FaceClient,IrisClient"
		'Const licenses As String = "FingerFastExtractor,FaceFastExtractor,IrisFastExtractor"

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

		Dim fileNameOut As String = args(0)
		Dim encoding As BdifEncodingType = If((args(1) = "1"), BdifEncodingType.Xml, BdifEncodingType.Traditional)
		Dim fingerFileNameIn As String = args(2)
		Dim faceFileNameIn As String = If(args.Length > 3, args(3), "")
		Dim irisFileNameIn As String = If(args.Length > 4, args(4), "")

		Try
			' Obtain licenses
			If (Not NLicense.Obtain("/local", 5000, licenses)) Then
				Throw New ApplicationException(String.Format("Could not obtain licenses: {0}", licenses))
			End If

			Dim tot As String = "TransactionType"
			Dim dai As String = "DestinationAgencyId"
			Dim ori As String = "OriginatingAgencyId"
			Dim tcn As String = "Transaction1"
			Dim src As String = "SourceAgencyName"
			Dim version As NVersion = ANTemplate.VersionCurrent

			Using antemplate As New ANTemplate(version, tot, dai, ori, tcn, 0)
				ANTemplateGetRecordType2(antemplate, encoding)

				ANTemplateGetRecordType14(antemplate, fingerFileNameIn, src)
				If faceFileNameIn.Length > 0 Then
					ANTemplateGetRecordType10(antemplate, faceFileNameIn, src)
				End If
				If irisFileNameIn.Length > 0 Then
					ANTemplateGetRecordType17(antemplate, irisFileNameIn, src)
				End If

				antemplate.Save(fileNameOut, encoding)
				Console.WriteLine("Template saved to {0}", fileNameOut)
				Return 0
			End Using
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
