#include <TutorialUtils.hpp>

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::IO;

const NChar title[] = N_T("IdGeneration");
const NChar description[] = N_T("Demonstrates how to generate Id from serial number (either generated using LicenseManager API or given by Neurotechnology or distributor)");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

static int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [serial file name] [id file name]" << endl;
	return 1;
}

int main(int argc, NChar *argv[])
{
	OnStart(title, description, version, copyright, argc, argv);

	if (argc != 3)
	{
		return usage();
	}

	try
	{
		NString serial = NFile::ReadAllText(argv[1]);
		NString id = NLicense::GenerateId(serial);
		NFile::WriteAllText(argv[2], id);
		cout << "Id saved to file " << argv[2] << ", it can now be activated using LicenseActivation tutorial, web page, etc.";
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
