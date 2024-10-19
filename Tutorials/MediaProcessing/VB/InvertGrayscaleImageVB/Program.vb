Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Images
Imports Neurotec.Images.Processing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [image] [output image]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "[image] - image to invert")
		Console.WriteLine(vbTab & "[output image] - inverted image")
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)
		If args.Length < 2 Then
			Return Usage()
		End If

		Try
			' Open image
			Dim image As NImage = NImage.FromFile(args(0))

			' Convert to grayscale image
			Dim grayscaleImage As NImage = NImage.FromImage(NPixelFormat.Grayscale8U, 0, image)

			' Invert image
			Dim result As NImage = Ngip.Invert(grayscaleImage)
			result.Save(args(1))
			Console.WriteLine("Inverted image saved to ""{0}""", args(1))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
