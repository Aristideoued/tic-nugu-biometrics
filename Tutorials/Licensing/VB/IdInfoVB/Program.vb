Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [id file name]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 1 Then
			Return Usage()
		End If

		Try
			Dim id As String = File.ReadAllText(args(0))
			Dim sequenceNumber, distributorId As Integer
			Dim productId As UInteger
			NLicenseManager.GetLicenseData(id, sequenceNumber, productId, distributorId)

			Console.WriteLine("sequence number: {0}", sequenceNumber)
			Console.WriteLine("distributor id: {0}", distributorId)
			Console.WriteLine("product: {0}", NLicenseManager.GetShortProductName(productId, NLicenseType.SingleComputer))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class

