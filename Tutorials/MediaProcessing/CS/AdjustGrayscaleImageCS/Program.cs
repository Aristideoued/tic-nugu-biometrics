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
			Console.WriteLine("\t{0} [image] [brightness] [contrast] [output image]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\texample: {0} c:\\image.png 0.3 0.5 c:\\result.png", TutorialUtils.GetAssemblyName());
			Console.WriteLine();
			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);

			if (args.Length < 4)
			{
				return Usage();
			}

			try
			{
				double brightness = double.Parse(args[1]);
				double contrast = double.Parse(args[2]);

				// Open image
				NImage image = NImage.FromFile(args[0]);

				// Convert to grayscale
				var grayscaleImage = NImage.FromImage(NPixelFormat.Grayscale8U, 0, image);

				// Adjust brightness and contrast
				NImage result = Ngip.AdjustBrightnessContrast(grayscaleImage, brightness, contrast);
				result.Save(args[3]);
				Console.WriteLine("Result image saved to \"{0}\"", args[3]);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
