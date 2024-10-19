using System;
using Neurotec.Images;
using Neurotec.Images.Processing;

namespace Neurotec.Tutorials
{
	class Program
	{
		static int Usage()
		{
			Console.WriteLine("usage:");
			Console.WriteLine("\t{0} [image] [width] [height] [output image] [interpolation mode]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t[image] - image to scale");
			Console.WriteLine("\t[width] - scaled image width");
			Console.WriteLine("\t[height] - scaled image height");
			Console.WriteLine("\t[output image] - scaled image");
			Console.WriteLine("\t[interpolation mode] - (optional) interpolation mode to use: 0 - nearest neighbour, 1 - bilinear");
			Console.WriteLine();
			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if(args.Length < 4)
			{
				return Usage();
			}

			try
			{
				uint dstWidth = uint.Parse(args[1]);
				uint dstHeight = uint.Parse(args[2]);
				var mode = Neurotec.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
				if (args.Length >= 5 && args[4] == "1")
					mode = Neurotec.Drawing.Drawing2D.InterpolationMode.Bilinear;

				// Open image
				NImage image = NImage.FromFile(args[0]);

				// Convert image to grayscale
				NImage grayscaleImage = NImage.FromImage(NPixelFormat.Grayscale8U, 0, image);

				// Scale image
				NImage result = Ngip.Scale(grayscaleImage, dstWidth, dstHeight, mode);
				result.Save(args[3]);
				Console.WriteLine("Scaled image saved to \"{0}\"", args[3]);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
