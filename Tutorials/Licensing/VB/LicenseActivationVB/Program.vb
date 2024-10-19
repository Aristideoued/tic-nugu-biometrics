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
			' Load id file (it can be generated using IdGeneration tutorial or ActivationWizardDotNet 
			Dim id As String = File.ReadAllText(args(0))

			' Generate license for specified id 
			Dim license As String = NLicense.ActivateOnline(id)

			' Write license to file 
			File.WriteAllText(args(1), license)

			Console.WriteLine("license saved to file {0}", args(1))
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
