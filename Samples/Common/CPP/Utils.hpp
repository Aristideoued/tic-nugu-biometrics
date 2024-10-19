#ifndef SAMPLE_UTILS_HPP_INCLUDED
#define SAMPLE_UTILS_HPP_INCLUDED

#include <cmath>
#include <algorithm>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
#else
	#include <NCore.hpp>
#endif

#if defined(N_PRODUCT_LIB)
	#ifdef N_APPLE_FRAMEWORKS
		#include <NDevices/NDevices.hpp>
	#else
		#include <NDevices.hpp>
	#endif
	#include <NNet/NInferenceEngineManager.hpp>
#endif

#define SAMPLES_FAR_LOG_RATIO 12.0

namespace Neurotec { namespace Samples
{
	using namespace Neurotec::Plugins;
	#include <Utils.h>
	class Utils
	{
	public:
		static double MatchingThresholdToFAR(int th)
		{
			if (th < 0) th = 0;
			return pow(10.0, -th / SAMPLES_FAR_LOG_RATIO);
		}

		static int FARToMatchingThreshold(double f)
		{
			if (f > 1) f = 1;
			else if (f <= 0.0) f = 1E-100;
			return (int)wxRound(-log10(f) * SAMPLES_FAR_LOG_RATIO);
		}

		static wxString MatchingThresholdToFARString(int matchingThreshold)
		{
			NDouble value = MatchingThresholdToFAR(matchingThreshold) * 100.0;
			wxString stringValue = wxString::Format(wxT("%.9f"), value);

			int trailingCount = 0;
			int position = (int)stringValue.Length() - 1;

			while (position >= 0 && stringValue[position] == wxT('0'))
			{
				trailingCount++;
				position--;
			}

			if (position >= 0 && !wxIsdigit(stringValue[position]))
			{
				trailingCount++;
				position--;
			}

			stringValue.RemoveLast(trailingCount);
			stringValue.Append(wxT("%"));
			stringValue.Replace(wxT(","), wxT("."));
			return stringValue;
		}

		static int FARStringToMatchingThreshold(const wxString& farString)
		{
			double value;
			try
			{
				value = NTypes::DoubleParse(farString, "f%");
			}
			catch (NError & /*ex*/)
			{
				return -1;
			}
			return FARToMatchingThreshold(value);
		}

		static wxString MatchingThresholdToString(int value)
		{
			double p = -value / 12.0;
			wxString stringValue = wxString::Format(wxString::Format("%%0.%df%%%%", std::max(0, (int)std::ceil(-p) - 2)), std::pow(10, p) * 100);
			stringValue.Replace(wxT(","), wxT("."));
			return stringValue;
		}

		static int MatchingThresholdFromString(const wxString& value)
		{
			double dValue;
			try
			{
				dValue = NTypes::DoubleParse(value, "f%");
			}
			catch (NError & /*ex*/)
			{
				return -1;
			}
			double p = std::log10(std::max<double>(std::numeric_limits<double>::epsilon(), std::min<double>(1, dValue)));
			return std::max(0, (int)std::ceil(-12 * p ));
		}
	};
}}

#endif // SAMPLE_UTILS_HPP_INCLUDED
