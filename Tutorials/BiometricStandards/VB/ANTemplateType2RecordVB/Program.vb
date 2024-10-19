Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Biometrics.Standards
Imports Neurotec.Licensing
Imports Neurotec.IO

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ANTemplate] [Tot] [Dai] [Ori] [Tcn] [Encoding]", TutorialUtils.GetAssemblyName())
		Console.WriteLine("")
		Console.WriteLine(Constants.vbTab & "[ANTemplate] - filename for ANTemplate.")
		Console.WriteLine(Constants.vbTab & "[Tot] - specifies type of transaction.")
		Console.WriteLine(Constants.vbTab & "[Dai] - specifies destination agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Ori] - specifies originating agency identifier.")
		Console.WriteLine(Constants.vbTab & "[Tcn] - specifies transaction control number.")
		Console.WriteLine(Constants.vbTab & "[Encoding] - specifies ANTemplate encoding type.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "0 - Traditional binary encoding.")
		Console.WriteLine(Constants.vbTab + Constants.vbTab & "1 - NIEM-conformant XML encoding.")
		Console.WriteLine("")

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 6 Then
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

			Dim tot As String = args(1)	' type of transaction
			Dim dai As String = args(2)	' destination agency identifier
			Dim ori As String = args(3)	' originating agency identifier
			Dim tcn As String = args(4)	' transaction control number
			Dim enc As String = args(5)	' encoding type

			If (tot.Length < 3) OrElse (tot.Length > 4) Then
				Console.WriteLine("Tot parameter should be 3 or 4 characters length.")
				Return -1
			End If

			Dim encoding As BdifEncodingType = If((enc = "1"), BdifEncodingType.Xml, BdifEncodingType.Traditional)

			Dim nameFieldNumber As Integer = 18	'exemplary field number for subject's name and surname
			Dim nameFieldValue As String = "name, surname"	'exemplary subject's name and surname
			Dim placeOfBirthFieldNumber As Integer = 20	'exemplary field number for subject's place of birth
			Dim placeOfBirthFieldValue As String = "UK"	'exemplary subject's place of birth
			Dim dateOfBirthFieldNumber As Integer = 22	'exemplary field number for subject's date of birth
			Dim dateOfBirthFieldValue As String = "19700131"	'exemplary subject's date of birth
			Dim genderFieldNumber As Integer = 24	'exemplary field number for subject's gender
			Dim genderFieldValue As String = "M"	'exemplary subject's gender

			Using template = New ANTemplate(ANTemplate.VersionCurrent, tot, dai, ori, tcn, 0)

				Dim record As ANType2Record = template.Records.AddType2()

				' Adds fields for "traditional" binary encoding
				If encoding = BdifEncodingType.Traditional Then
					record.Fields.Add(nameFieldNumber, nameFieldValue)
					record.Fields.Add(placeOfBirthFieldNumber, placeOfBirthFieldValue)
					record.Fields.Add(dateOfBirthFieldNumber, dateOfBirthFieldValue)
					record.Fields.Add(genderFieldNumber, genderFieldValue)
				Else	' Adds fields for NIEM-conformant XML encoding
					record.Fields.Add(nameFieldNumber, "PersonName", nameFieldValue)
					record.Fields.Add(placeOfBirthFieldNumber, "PersonBirthPlaceCode", placeOfBirthFieldValue)
					record.Fields.Add(dateOfBirthFieldNumber, "PersonBirthDate", dateOfBirthFieldValue)
					record.Fields.Add(genderFieldNumber, "PersonSexCode", genderFieldValue)
				End If
				' Store ANTemplate object with type 2 record in file
				template.Save(args(0), encoding)
			End Using
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try

	End Function
End Class
