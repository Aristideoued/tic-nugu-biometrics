#ifndef N_LICENSE_MANAGER_HPP_INCLUDED
#define N_LICENSE_MANAGER_HPP_INCLUDED

#include <Core/NObject.hpp>
#include <Licensing/NLicenseProductInfo.hpp>
#include <Licensing/NLicManDongle.hpp>

namespace Neurotec { namespace Licensing
{
#include <Licensing/NLicenseManager.h>
}}

#undef N_LIC_MAN_MAX_SERIAL_LENGTH
#undef N_LIC_MAN_MAX_LICENSE_LENGTH

namespace Neurotec { namespace Licensing
{
const NInt N_LIC_MAN_MAX_SERIAL_LENGTH = 39;
const NInt N_LIC_MAN_MAX_LICENSE_LENGTH = 6400;

class NLicenseManager
{
	N_DECLARE_STATIC_OBJECT_CLASS(NLicenseManager)

public:
	static void Initialize()
	{
		NCheck(NLicManInitialize());
	}

	static NString GenerateSerial(NUInt productId, NInt sequenceNumber, NInt * pDistributorId)
	{
		HNString handle;
		NCheck(NLicManGenerateSerialN(productId, sequenceNumber, pDistributorId, &handle));
		return NString(handle, true);
	}

	static NString GenerateSerial(const NLicManDongle & dongle, NUInt productId, NInt sequenceNumber, NInt * pDistributorId)
	{
		HNString handle;
		NCheck(NLicManGenerateSerialExN(dongle.GetHandle(), productId, sequenceNumber, pDistributorId, &handle));
		return NString(handle, true);
	}

	static NString GenerateLicense(const NStringWrapper & id, NInt * pSequenceNumber, NUInt * pProductId)
	{
		HNString handle;
		NCheck(NLicManGenerateLicenseN(id.GetHandle(), pSequenceNumber, pProductId, &handle));
		return NString(handle, true);
	}

	static NString GenerateLicense(const NLicManDongle & dongle, const NStringWrapper & id, NInt * pSequenceNumber, NUInt * pProductId)
	{
		HNString handle;
		NCheck(NLicManGenerateLicenseExN(dongle.GetHandle(), id.GetHandle(), pSequenceNumber, pProductId, &handle));
		return NString(handle, true);
	}

	static void GetLicenseData(const NStringWrapper & id, NInt * pSequenceNumber, NUInt * pProductId, NInt * pDistributorId)
	{
		NCheck(NLicManGetLicenseDataN(id.GetHandle(), pSequenceNumber, pProductId, pDistributorId));
	}

	static void GetLicenseData(const NLicManDongle & dongle, const NStringWrapper & id, NInt * pSequenceNumber, NUInt * pProductId, NInt * pDistributorId)
	{
		NCheck(NLicManGetLicenseDataExN(dongle.GetHandle(), id.GetHandle(), pSequenceNumber, pProductId, pDistributorId));
	}

	static NArrayWrapper<NLicManDongle> GetDongles()
	{
		HNLicManDongle * arhDongles = NULL; NInt count = 0;
		NCheck(NLicManGetDongles(&arhDongles, &count));
		return NArrayWrapper<NLicManDongle>(arhDongles, count);
	}

	static NLicManDongleUpdateTicketInfo GetUpdateTicketInfo(const NStringWrapper & ticketNumber)
	{
		HNLicManDongleUpdateTicketInfo handle;
		NCheck(NLicManGetUpdateTicketInfoN(ticketNumber.GetHandle(), &handle));
		return NObject::FromHandle<NLicManDongleUpdateTicketInfo>(handle);
	}

	static NArrayWrapper<NUInt> GetProductIds()
	{
		NInt count = NLicManGetProductIds(NULL);
		NCheck(count);
		NArrayWrapper<NUInt> result(count);
		NCheck(NLicManGetProductIds(result.GetPtr()));
		return result;
	}

	static bool IsLicenseTypeSupported(NUInt productId, NLicenseType licenseType)
	{
		NBool isSupported;
		NCheck(NLicManIsLicenseTypeSupported(productId, licenseType, &isSupported));
		return isSupported != NFalse;
	}

	static NString GetShortProductName(const NLicenseProductInfo & productInfo)
	{
		HNString handle;
		NCheck(NLicManGetShortProductNameForProductInfoN(productInfo.GetHandle(), &handle));
		return NString(handle, true);
	}

	static NString GetShortProductName(NUInt productId, NLicenseType type)
	{
		HNString handle;
		NCheck(NLicManGetShortProductNameN(productId, type, &handle));
		return NString(handle, true);
	}

	static NString GetLongProductName(const NLicenseProductInfo & productInfo)
	{
		HNString handle;
		NCheck(NLicManGetLongProductNameForProductInfoN(productInfo.GetHandle(), &handle));
		return NString(handle, true);
	}

	static NString GetLongProductName(NUInt productId, NLicenseType type)
	{
		HNString handle;
		NCheck(NLicManGetLongProductNameN(productId, type, &handle));
		return NString(handle, true);
	}

	static bool GetTrialMode()
	{
		NBool value;
		NCheck(NLicManGetTrialMode(&value));
		return value != 0;
	}

	static void SetTrialMode(bool value)
	{
		NCheck(NLicManSetTrialMode(value));
	}

	static NString GetWritableStoragePath()
	{
		HNString handle;
		NCheck(NLicManGetWritableStoragePath(&handle));
		return NString(handle, true);
	}

	static void SetWritableStoragePath(const NStringWrapper & value)
	{
		NCheck(NLicManSetWritableStoragePathN(value.GetHandle()));
	}

	static bool GetUseHttps()
	{
		NBool value;
		NCheck(NLicManGetUseHttps(&value));
		return value != 0;
	}

	static void SetUseHttps(bool value)
	{
		NCheck(NLicManSetUseHttps(value));
	}

	static NString GetProxyHost()
	{
		HNString handle;
		NCheck(NLicManGetProxyHost(&handle));
		return NString(handle, true);
	}

	static void SetProxyHost(const NStringWrapper & value)
	{
		NCheck(NLicManSetProxyHostN(value.GetHandle()));
	}

	static NInt GetProxyPort()
	{
		NInt value;
		NCheck(NLicManGetProxyPort(&value));
		return value;
	}

	static void SetProxyPort(NInt value)
	{
		NCheck(NLicManSetProxyPort(value));
	}

	static NString GetProxyUsername()
	{
		HNString handle;
		NCheck(NLicManGetProxyUsername(&handle));
		return NString(handle, true);
	}

	static void SetProxyUsername(const NStringWrapper & value)
	{
		NCheck(NLicManSetProxyUsernameN(value.GetHandle()));
	}

	static NString GetProxyPassword()
	{
		HNString handle;
		NCheck(NLicManGetProxyPassword(&handle));
		return NString(handle, true);
	}

	static void SetProxyPassword(const NStringWrapper & value)
	{
		NCheck(NLicManSetProxyPasswordN(value.GetHandle()));
	}

	static NString GetClientId()
	{
		HNString handle;
		NCheck(NLicManGetClientId(&handle));
		return NString(handle, true);
	}

	static void SetClientId(const NStringWrapper & value)
	{
		NCheck(NLicManSetClientIdN(value.GetHandle()));
	}
};

}}

#endif // !N_LICENSE_MANAGER_HPP_INCLUDED
