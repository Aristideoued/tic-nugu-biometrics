Imports Neurotec.Licensing
Imports Microsoft.VisualBasic
Imports System
Imports System.IO

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [serial file name] [id file name]", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 2 Then
			Return Usage()
		End If

		Try
			' Load serial file (generated using LicenseManager API or provided either by Neurotechnology or its distributor) 
			Dim serial As String = File.ReadAllText(args(0))

			' Either point to correct place for id_gen.exe, or pass NULL or use method without idGenPath parameter in order to search id_gen.exe in current folder 
			Dim id As String = NLicense.GenerateId(serial)

			' Write generated id to file 
			File.WriteAllText(args(1), id)

			Console.WriteLine("id saved to file {0}, it can now be activated using LicenseActivation tutorial, web page, etc.", args(1))
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
