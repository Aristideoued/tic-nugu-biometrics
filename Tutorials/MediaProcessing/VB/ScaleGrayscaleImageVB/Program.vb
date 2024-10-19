Imports Microsoft.VisualBasic
Imports System
Imports Neurotec.Images
Imports Neurotec.Images.Processing

Friend Class Program
	Private Shared Function Usage() As Integer
		Console.WriteLine("usage:")
		Console.WriteLine(vbTab & "{0} [image] [width] [height] [output image] [interpolation mode]", TutorialUtils.GetAssemblyName())
		Console.WriteLine(vbTab & "[image] - image to scale")
		Console.WriteLine(vbTab & "[width] - scaled image width")
		Console.WriteLine(vbTab & "[height] - scaled image height")
		Console.WriteLine(vbTab & "[output image] - scaled image")
		Console.WriteLine(vbTab & "[interpolation mode] - (optional) interpolation mode to use: 0 - nearest neighbour, 1 - bilinear")
		Console.WriteLine()
		Return 1
	End Function

	Shared Function Main(ByVal args() As String) As Integer
		TutorialUtils.PrintTutorialHeader(args)

		If args.Length < 4 Then
			Return Usage()
		End If

		Try
			Dim dstWidth As UInteger = UInteger.Parse(args(1))
			Dim dstHeight As UInteger = UInteger.Parse(args(2))
			Dim mode As Neurotec.Drawing.Drawing2D.InterpolationMode = Neurotec.Drawing.Drawing2D.InterpolationMode.NearestNeighbor
			If args.Length >= 5 AndAlso args(4) = "1" Then
				mode = Neurotec.Drawing.Drawing2D.InterpolationMode.Bilinear
			End If

			' Open image
			Dim image As NImage = NImage.FromFile(args(0))

			' Convert image to grayscale
			Dim grayscaleImage As NImage = NImage.FromImage(NPixelFormat.Grayscale8U, 0, image)

			' Scale image
			Dim result As NImage = Ngip.Scale(grayscaleImage, dstWidth, dstHeight, mode)
			result.Save(args(3))
			Console.WriteLine("Scaled image saved to ""{0}""", args(3))

			Return 0
		Catch ex As Exception
			Return TutorialUtils.PrintException(ex)
		End Try
	End Function
End Class
