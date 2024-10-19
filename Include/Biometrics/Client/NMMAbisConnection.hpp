#include <Biometrics/Client/NRemoteBiometricConnection.hpp>

#ifndef N_MMABIS_CONNECTION_HPP_INCLUDED
#define N_MMABIS_CONNECTION_HPP_INCLUDED

namespace Neurotec { namespace Biometrics { namespace Client
{
#include <Biometrics/Client/NMMAbisConnection.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Client
{

class NMMAbisConnection : public NRemoteBiometricConnection
{
	N_DECLARE_OBJECT_CLASS(NMMAbisConnection, NRemoteBiometricConnection)

private:
	static HNMMAbisConnection Create(const NStringWrapper & address, const NStringWrapper & username, const NStringWrapper & password)
	{
		HNMMAbisConnection handle;
		NCheck(NMMAbisConnectionCreateN(address.GetHandle(), username.GetHandle(), password.GetHandle(), &handle));
		return handle;
	}

public:
	NMMAbisConnection(const NStringWrapper & address, const NStringWrapper & username, const NStringWrapper & password)
		: NRemoteBiometricConnection(Create(address, username, password), true)
	{
	}

	NString GetAddress() const
	{
		return GetString(NMMAbisConnectionGetAddress);
	}

	void SetAddress(const NStringWrapper & value)
	{
		SetString(NMMAbisConnectionSetAddressN, value);
	}

	NString GetUsername() const
	{
		return GetString(NMMAbisConnectionGetUsername);
	}

	void SetUsername(const NStringWrapper & value)
	{
		SetString(NMMAbisConnectionSetUsernameN, value);
	}

	NString GetPassword() const
	{
		return GetString(NMMAbisConnectionGetPassword);
	}

	void SetPassword(const NStringWrapper & value)
	{
		SetString(NMMAbisConnectionSetPasswordN, value);
	}
};

}}}

#endif // !N_MMABIS_CONNECTION_HPP_INCLUDED
