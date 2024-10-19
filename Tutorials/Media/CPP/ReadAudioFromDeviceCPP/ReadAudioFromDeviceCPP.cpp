#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NMedia.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::Media;
using namespace Neurotec::Sound;

const NChar title[] = N_T("ReadAudioFromDevice");
const NChar description[] = N_T("Demonstrates capturing sound from device");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [bufferCount]" << endl << endl;
	cout << "\tbufferCount - number of sound buffers to capture from each device to current directory";
	return 1;
}

static void DumpMediaFormat(const NMediaFormat & mediaFormat)
{
	if (mediaFormat.IsNull()) NThrowException("mediaFormat");
	
	switch (mediaFormat.GetMediaType())
	{
	case nmtVideo:
		{
			NVideoFormat videoFormat = NObjectDynamicCast<NVideoFormat>(mediaFormat);
			cout << "Video format .. " << videoFormat.GetWidth() << "x" << videoFormat.GetHeight() << " @ " << (videoFormat.GetFrameRate()).Numerator << "/"
				 << (videoFormat.GetFrameRate()).Denominator << " (interlace: " << videoFormat.GetInterlaceMode() << ", aspect ratio: "
				 << (videoFormat.GetPixelAspectRatio()).Numerator << "/" << (videoFormat.GetPixelAspectRatio()).Denominator << ")" << endl;
			break;
		}
	case nmtAudio:
		{
			NAudioFormat audioFormat = NObjectDynamicCast<NAudioFormat>(mediaFormat);
			cout << "Audio format .. channels: " << audioFormat.GetChannelCount() << ", samples/second: " << audioFormat.GetSampleRate() << ", bits/channel: "
				 << audioFormat.GetBitsPerChannel() << endl;
			break;
		}
	default:
		{
			NThrowException("Unknown media type specified in format!");
		}
	}
}

static void ReadSoundBuffers(NMediaReader & mediaReader, int bufferCount)
{
	NMediaSource mediaSource = mediaReader.GetSource();
	cout << "Media length: " << mediaReader.GetLength().ToString() << endl;
	NArrayWrapper<NMediaFormat> formats = mediaSource.GetFormats(nmtAudio);
	int formatCount = formats.GetCount();
	cout << "Format count: " << formatCount << endl;
	for (int i = 0; i < formatCount; i++)
	{
		cout << "[" << i << "]" << endl;
		DumpMediaFormat(formats.Get(i));
	}
	NMediaFormat currentMediaFormat = mediaSource.GetCurrentFormat(nmtAudio);
	if (!currentMediaFormat.IsNull())
	{
		cout << "Current media format: ";
		DumpMediaFormat(currentMediaFormat);
		cout << "Set the last supported format (optional) ..." << endl;
		mediaSource.SetCurrentFormat(nmtAudio, formats.Get(formatCount - 1));
		cout << "Format set" << endl;
	}
	else
		cout << "Current media format is not yet available (will be available after media reader start)" << endl;

	cout <<"Starting capture ..." << endl;
	mediaReader.Start();
	cout << "Capture started" << endl;
	currentMediaFormat = mediaSource.GetCurrentFormat(nmtAudio);
	if (currentMediaFormat.IsNull())
		NThrowException("Current media format is not set even after media reader start!");
	cout << "Capturing with format: " << endl;
	DumpMediaFormat(currentMediaFormat);
	for (int i = 0; i < bufferCount; i++)
	{
		NTimeSpan timespan(-1);
		NTimeSpan duration(0);
		NSoundBuffer soundBuffer(NULL);
		soundBuffer = mediaReader.ReadAudioSample(&timespan, &duration);
		if (soundBuffer.IsNull()) break;
		cout << "[" << timespan.GetValue() << " " << duration.GetValue() << "] sample rate: " << soundBuffer.GetSampleRate() << ", sample length: " << soundBuffer.GetLength() << endl;
	}
	mediaReader.Stop();
}

int main(int argc, NChar **argv)
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc < 2)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed licenses is required for unlocking this sample's functionality. Choose a license that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.

	const NString license = N_T("VoiceExtractor");
	//const NString license = N_T("VoiceClient");
	//const NString license = N_T("VoiceFastExtractor");

	//=========================================================================

	//=========================================================================
	// TRIAL MODE
	//=========================================================================
	// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.

	NLicenseManager::SetTrialMode(GetTrialModeFlag());
	cout << "Trial mode: " << NLicenseManager::GetTrialMode() << endl;

	//=========================================================================

	try
	{
		// Obtain license
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), license))
		{
			NThrowException(NString::Format(N_T("Could not obtain license: {S}"), license.GetBuffer())); 
		}

		int bufferCount = atoi(argv[1]);
		if (bufferCount == 0)
			cout << "No sound buffers will be captured as sound buffer count is not specified" << endl;
		
		cout << "Querying connected audio devices ..." << endl;
		cout << "Devices found: " << NMediaSource::EnumDevices(nmtAudio).GetCount() << endl;

		NArrayWrapper<NMediaSource> devices = NMediaSource::EnumDevices(nmtAudio);
		for (int i = 0; i < devices.GetCount(); i++)
		{
			NMediaSource source = devices.Get(i);
			cout << "Found device: " << source.GetDisplayName() << endl;
			NMediaReader mediaReader(source, nmtAudio, true);
			ReadSoundBuffers(mediaReader, bufferCount);
		}
		cout << "Done" << endl;
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
