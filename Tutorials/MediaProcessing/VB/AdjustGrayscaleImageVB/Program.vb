Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Images
Imports Neurotec.Images.Processing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [image] [brightness] [contrast] [output image]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "example: {0} c:\image.png 0.3 0.5 c:\result.png", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 4 Then
			Return Usage()
		End If

		Try
			Dim brightness As Double = Double.Parse(args(1))
			Dim contrast As Double = Double.Parse(args(2))

			' Open image
			Dim image As NImage = NImage.FromFile(args(0))

			' Convert to grayscale
			Dim grayscaleImage As NImage = NImage.FromImage(NPixelFormat.Grayscale8U, 0, image)

			' Adjust brightness and contrast
			Dim result As NImage = Ngip.AdjustBrightnessContrast(grayscaleImage, brightness, contrast)
			result.Save(args(3))
			Console.WriteLine("Result image saved to ""{0}""", args(3))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
