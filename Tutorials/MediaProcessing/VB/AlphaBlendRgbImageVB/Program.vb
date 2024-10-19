Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Images
Imports Neurotec.Images.Processing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [imageA] [imageB] [alpha] [output image]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "example: {0} c:\image1.bmp c:\image2.bmp 0.5 c:\result.bmp", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "note: images must be of the same width and height")
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)
		If args.Length < 4 Then
			Return Usage()
		End If

		Try
			Dim alpha As Double = Double.Parse(args(2))

			' Open images
			Dim imageA As NImage = NImage.FromFile(args(0))
			Dim imageB As NImage = NImage.FromFile(args(1))

			' Convert images to rgb
			Dim rgbImageA As NImage = NImage.FromImage(NPixelFormat.Rgb8U, 0, imageA)
			Dim rgbImageB As NImage = NImage.FromImage(NPixelFormat.Rgb8U, 0, imageB)

			' Alpha blend
			Dim result As NImage = Nrgbip.AlphaBlend(rgbImageA, rgbImageB, alpha)
			result.Save(args(3))
			Console.WriteLine("Image saved to ""{0}""", args(3))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
