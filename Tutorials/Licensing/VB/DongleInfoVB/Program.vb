Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Licensing

Friend Class Program
	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		Try

			Dim dongles() As NLicManDongle = NLicenseManager.GetDongles()

			If dongles.Length = 0 Then
				Console.WriteLine("no dongles found")
				Return -1
			End If

			For Each dongle In dongles
				Console.WriteLine("=== Dongle Id: {0} ===" & vbLf, dongle.DistributorId)
				Dim licenses() As NLicenseProductInfo = dongle.GetLicenses()
				For Each license As NLicenseProductInfo In licenses
					Console.WriteLine("{0} OS: {1}, Count: {2}", NLicenseManager.GetShortProductName(license.Id, license.LicenseType), license.OSFamily, license.LicenseCount)
				Next license
			Next

			Console.WriteLine("no more dongles found")

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
