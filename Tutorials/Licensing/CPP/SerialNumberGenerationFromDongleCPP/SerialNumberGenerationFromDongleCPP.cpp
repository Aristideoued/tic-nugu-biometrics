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
using namespace Neurotec::IO;
using namespace Neurotec::Licensing;

const NChar title[] = N_T("SerialNumberGenerationFromDongle");
const NChar description[] = N_T("Demonstrates serial number generation for given sequence number and product id");
const NChar version[] = N_T("13.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2024 Neurotechnology");

static int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [sequence number] [product id]" << endl;
	cout << "product name : id:" << endl;
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
		NInt sequenceNumber = atoi(argv[1]);
		NUInt productId = atoi(argv[2]);
		NInt distributorId;
		NString serialNumber = NLicenseManager::GenerateSerial(productId, sequenceNumber, &distributorId);
		cout << "Serial number: " << serialNumber << endl;
		cout << "Distributor id: " << distributorId << endl;
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
