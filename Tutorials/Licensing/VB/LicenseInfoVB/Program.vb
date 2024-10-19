Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [license file name]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 1 Then
			Return Usage()
		End If

		Try
			Dim licenseInfo As NLicenseInfo = NLicense.GetLicenseInfoOnline(File.ReadAllText(args(0)))
			Console.WriteLine("Specified license information:")
			Console.WriteLine(Constants.vbTab & "Type: {0}", licenseInfo.Type)
			Console.WriteLine(Constants.vbTab & "Source type: {0}", licenseInfo.SourceType)
			Console.WriteLine(Constants.vbTab & "Distributor id: {0}", licenseInfo.DistributorId)
			Console.WriteLine(Constants.vbTab & "Sequence number: {0}", licenseInfo.SequenceNumber)
			Console.WriteLine(Constants.vbTab & "License id: {0}", licenseInfo.LicenseId)
			Console.WriteLine(Constants.vbTab & "Products:")
			Dim licenses() As NLicenseProductInfo = licenseInfo.GetLicenses()
			For Each license As NLicenseProductInfo In licenses
				Console.WriteLine(Constants.vbTab + Constants.vbTab & "{0} OS: {1}, Count: {2}", NLicenseManager.GetShortProductName(license.Id, license.LicenseType), license.OSFamily, license.LicenseCount)
			Next license

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
