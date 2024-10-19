Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Images
Imports Neurotec.Images.Processing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [image] [output image] [red brightness] [red contrast] [green brightness] [green contrast] [blue brightness] [blue contrast]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "example: {0} c:\input.bmp c:\result.bmp 0.5 0.5 0.2 0.3 1 0.9", TutorialUtils.GetAssemblyName())
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 8 Then
			Return Usage()
		End If

		Try
			Dim redBrightness As Double = Double.Parse(args(2))
			Dim redContrast As Double = Double.Parse(args(3))
			Dim greenBrightness As Double = Double.Parse(args(4))
			Dim greenContrast As Double = Double.Parse(args(5))
			Dim blueBrightness As Double = Double.Parse(args(6))
			Dim blueContrast As Double = Double.Parse(args(7))

			' Open image
			Dim image As NImage = NImage.FromFile(args(0))

			' Covert image to rgb
			Dim rgbImage As NImage = NImage.FromImage(NPixelFormat.Rgb8U, 0, image)

			' Adjust brightness and contrast
			Dim result As NImage = Nrgbip.AdjustBrightnessContrast(rgbImage, redBrightness, redContrast, greenBrightness, greenContrast, blueBrightness, blueContrast)
			result.Save(args(1))
			Console.WriteLine("Result image saved to ""{0}""", args(1))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
