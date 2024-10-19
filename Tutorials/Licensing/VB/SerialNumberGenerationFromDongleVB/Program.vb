Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [sequence number] [product id]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Console.WriteLine("product name : id:")
		Dim ids() As UInteger = NLicenseManager.GetProductIds()
		For Each id As UInteger In ids
			Console.WriteLine("{0} : {1}", NLicenseManager.GetShortProductName(id, NLicenseType.SingleComputer), id)
		Next id
		Console.WriteLine()

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 2 Then
			Return Usage()
		End If

		Try
			Dim sequenceNumber As Integer = Integer.Parse(args(0))
			Dim productId As UInteger = UInteger.Parse(args(1))
			Dim distributorId As Integer
			Dim serialNumber As String = NLicenseManager.GenerateSerial(productId, sequenceNumber, distributorId)

			Console.WriteLine("serial number: {0}", serialNumber)
			Console.WriteLine("distributor id: {0}", distributorId)

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
