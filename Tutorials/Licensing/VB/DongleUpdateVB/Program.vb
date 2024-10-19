Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(Constants.vbTab & "{0} [ticket number]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 1 Then
			Return Usage()
		End If

		Try
			Dim ticket As NLicManDongleUpdateTicketInfo = NLicenseManager.GetUpdateTicketInfo(args(0))
			Console.WriteLine("ticket: {0}, status: {1}, issue date: {2:yyyy-MM-dd HH:mm:ss}", ticket.Number, ticket.Status, ticket.IssueDate)
			If ticket.DongleDistributorId <> 0 AndAlso ticket.DongleHardwareId <> 0 Then
				Console.WriteLine("ticket assigned to dongle: {0} (hardware id: {1:X})", ticket.DongleDistributorId, ticket.DongleHardwareId)
			End If
			For Each license As NLicenseProductInfo In ticket.GetLicenses()
				Console.WriteLine("{0} OS: {1}, Count: {2}", NLicenseManager.GetShortProductName(license.Id, license.LicenseType), license.OSFamily, license.LicenseCount)
			Next license
			If ticket.Status <> NLicManDongleUpdateTicketStatus.Enabled Then
				Console.WriteLine("Specified ticket can not be used as ticket status is: {0}", ticket.Status)
				Return -1
			End If

			Dim foundDongle As NLicManDongle = Nothing

			Dim dongles() As NLicManDongle = NLicenseManager.GetDongles()

			For Each dongle In dongles
				If ticket.DongleDistributorId <> 0 AndAlso ticket.DongleHardwareId <> 0 Then
					If dongle.DistributorId = ticket.DongleDistributorId AndAlso dongle.HardwareId = ticket.DongleHardwareId Then
						foundDongle = dongle
						Exit For
					End If
				Else
					foundDongle = dongle
				End If
			Next

			If foundDongle Is Nothing Then
				Console.WriteLine("No dongles found (that could be used)")
				Return -1
			End If

			' Apply the dongle update
			foundDongle.UpdateOnline(ticket)

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
