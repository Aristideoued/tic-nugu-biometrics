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
			Console.WriteLine("\t{0} [image] [output image] [red brightness] [red contrast] [green brightness] [green contrast] [blue brightness] [blue contrast]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\texample: {0} c:\\input.bmp c:\\result.bmp 0.5 0.5 0.2 0.3 1 0.9", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 8)
			{
				return Usage();
			}

			try
			{
				double redBrightness = double.Parse(args[2]);
				double redContrast = double.Parse(args[3]);
				double greenBrightness = double.Parse(args[4]);
				double greenContrast = double.Parse(args[5]);
				double blueBrightness = double.Parse(args[6]);
				double blueContrast = double.Parse(args[7]);

				// Open image
				NImage image = NImage.FromFile(args[0]);

				// Covert image to rgb
				var rgbImage = NImage.FromImage(NPixelFormat.Rgb8U, 0, image);

				// Adjust brightness and contrast
				NImage result = Nrgbip.AdjustBrightnessContrast(rgbImage, redBrightness, redContrast, greenBrightness, greenContrast, blueBrightness, blueContrast);
				result.Save(args[1]);
				Console.WriteLine("Result image saved to \"{0}\"", args[1]);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
