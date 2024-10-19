Imports Microsoft.VisualBasic
Imports System
Imports System.IO
Imports Neurotec.Licensing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [lic file name] (optional: [id file name])", TutorialUtils.GetAssemblyName())
		Console.WriteLine("NOTE: Please always deactivate license on the same computer it was activated on!")
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length <> 1 Then
			Return Usage()
		End If

		Try
			' Load license file 
			Dim license As String = File.ReadAllText(args(0))

			' First check our intentions 
			Console.WriteLine("WARNING: deactivating a license will make" & vbLf & "it and product(for which it was generated) disabled on current pc. Continue? (y/n)")
			If Chr(Console.Read) <> "y"c Then
				Console.WriteLine("not generating")
				Return 0
			End If

			Try
				' Either point to correct place for id_gen.exe, or pass NULL or use method without idGenPath parameter in order to search id_gen.exe in current folder 
				' Do the deactivation 
				NLicense.DeactivateOnline(license)

				Console.WriteLine("online deactivation succeeded. you can now use serial number again")
			Catch ex As Exception
				Console.WriteLine("online deactivation failed. reason: {0}", ex.Message)
				Console.WriteLine("generating deactivation id, which you can send to support@neurotechnology.com for manual deactivation")
				If args.Length <> 2 Then
					Console.WriteLine("missing deactivation id argument, please specify it")
					Return Usage()
				End If
				Dim id As String = NLicense.GenerateDeactivationIdForLicense(license)
				' Write generated deactivation id to file 
				File.WriteAllText(args(1), id)

				Console.WriteLine("deactivation id saved to file {0}. please send it to support@neurotechnology.com to complete deactivation process", args(1))
			End Try
			
			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
