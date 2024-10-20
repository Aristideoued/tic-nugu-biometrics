#ifndef WSQ_HPP_INCLUDED
#define WSQ_HPP_INCLUDED

#include <Images/NImage.hpp>
#include <Images/NistCom.hpp>
namespace Neurotec { namespace Images
{
#include <Images/Wsq.h>
}}

namespace Neurotec { namespace Images
{

#undef WSQ_DEFAULT_BIT_RATE
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN32_X86_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN64_X64_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN32_X86
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN64_X64
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_DEBIAN_I386_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_DEBIAN_AMD64_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_I386
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_AMD64
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_ARM
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_ARM64
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_INTEL_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_INTEL64_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_POWERPC_LEGACY
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_INTEL64
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_ANDROID_ARM
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_ANDROID_ARM64
#undef WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_IOS_ARM64
#undef WSQ_RECOVER_CORRUPT_FILE

const NFloat WSQ_DEFAULT_BIT_RATE = 0.75f;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN32_X86_LEGACY = 10150;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN64_X64_LEGACY = 10151;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN32_X86 = 10158;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_WIN64_X64 = 10157;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_DEBIAN_I386_LEGACY = 10152;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_DEBIAN_AMD64_LEGACY = 10153;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_I386 = 10160;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_AMD64 = 10159;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_ARM = 10166;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_LINUX_ARM64 = 10165;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_INTEL_LEGACY = 10154;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_INTEL64_LEGACY = 10155;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_POWERPC_LEGACY = 10156;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_MACOSX_INTEL64 = 10163;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_ANDROID_ARM = 10161;
const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_ANDROID_ARM64 = 10162;

const NUShort WSQ_IMPLEMENTATION_NEUROTECHNOLOGY_IOS_ARM64 = 10164;

const NUInt WSQ_RECOVER_CORRUPT_FILE = 0x000100000;

class WsqInfo : public NImageInfo
{
	N_DECLARE_OBJECT_CLASS(WsqInfo, NImageInfo)

public:
	NFloat GetBitRate() const
	{
		NFloat value;
		NCheck(WsqInfoGetBitRate(GetHandle(), &value));
		return value;
	}

	void SetBitRate(NFloat value)
	{
		NCheck(WsqInfoSetBitRate(GetHandle(), value));
	}

	NUShort GetImplementationNumber() const
	{
		NUShort value;
		NCheck(WsqInfoGetImplementationNumber(GetHandle(), &value));
		return value;
	}

	bool HasNistCom() const
	{
		NBool value;
		NCheck(WsqInfoHasNistCom(GetHandle(), &value));
		return value != 0;
	}

	void SetHasNistCom(bool value)
	{
		NCheck(WsqInfoSetHasNistCom(GetHandle(), value ? NTrue : NFalse));
	}

	NistCom GetNistCom() const
	{
		HNistCom hValue;
		NCheck(WsqInfoGetNistCom(GetHandle(), &hValue));
		return FromHandle<NistCom>(hValue, true);
	}
};

}}

#endif // !WSQ_HPP_INCLUDED