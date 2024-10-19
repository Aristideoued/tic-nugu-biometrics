Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [id file name] [lic file name]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()

		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 2 Then
			Return Usage()
		End If

		Try
			Dim id As String = File.ReadAllText(args(0))
			Console.Write("WARNING: generating a license will decrease license count" & vbLf & "for a specific product in a dongle by 1. Continue? (y/n)")
			If CStr(Console.Read()) <> "y"c Then
				Console.WriteLine("not generating")
				Return 0
			End If

			Dim sequenceNumber As Integer
			Dim productId As UInteger
			Dim license As String = NLicenseManager.GenerateLicense(id, sequenceNumber, productId)
			File.WriteAllText(args(1), license)
			Console.WriteLine("license saved to file {0}", args(1))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
