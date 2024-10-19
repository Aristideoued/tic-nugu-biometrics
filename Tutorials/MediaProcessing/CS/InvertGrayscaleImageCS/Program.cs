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
			Console.WriteLine("\t{0} [image] [output image]", TutorialUtils.GetAssemblyName());
			Console.WriteLine("\t[image] - image to invert");
			Console.WriteLine("\t[output image] - inverted image");
			Console.WriteLine();
			return 1;
		}

		static int Main(string[] args)
		{
			TutorialUtils.PrintTutorialHeader(args);
			if (args.Length < 2)
			{
				return Usage();
			}

			try
			{
				// Open image
				NImage image = NImage.FromFile(args[0]);

				// Convert to grayscale image
				var grayscaleImage = NImage.FromImage(NPixelFormat.Grayscale8U, 0, image);

				// Invert image
				NImage result = Ngip.Invert(grayscaleImage);
				result.Save(args[1]);
				Console.WriteLine("Inverted image saved to \"{0}\"", args[1]);

				return 0;
			}
			catch (Exception ex)
			{
				return TutorialUtils.PrintException(ex);
			}
		}
	}
}
