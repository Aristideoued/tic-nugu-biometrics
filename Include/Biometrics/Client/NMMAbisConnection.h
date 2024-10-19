#ifndef N_MMABIS_CONNECTION_H_INCLUDED
#define N_MMABIS_CONNECTION_H_INCLUDED

#include <Biometrics/Client/NRemoteBiometricConnection.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NMMAbisConnection, NRemoteBiometricConnection)

NResult N_API NMMAbisConnectionCreateN(HNString hAddress, HNString hUsername, HNString hPassword, HNMMAbisConnection * phConnection);
#ifndef N_NO_ANSI_FUNC
NResult N_API NMMAbisConnectionCreateA(const NAChar * szAddress, const NAChar * szUsername, const NAChar * szPassword, HNMMAbisConnection * phConnection);
#endif
#ifndef N_NO_UNICODE
NResult N_API NMMAbisConnectionCreateW(const NWChar * szAddress, const NWChar * szUsername, const NWChar * szPassword, HNMMAbisConnection * phConnection);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NMMAbisConnectionCreate(const NChar * szAddress, const NChar * szUsername, const NChar * szPassword, NMMAbisConnection * phConnection);
#endif
#define NMMAbisConnectionCreate N_FUNC_AW(NMMAbisConnectionCreate)

NResult N_API NMMAbisConnectionGetAddress(HNMMAbisConnection hConnection, HNString * phValue);
NResult N_API NMMAbisConnectionSetAddressN(HNMMAbisConnection hConnection, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API NMMAbisConnectionSetAddressA(HNMMAbisConnection hConnection, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API NMMAbisConnectionSetAddressW(HNMMAbisConnection hConnection, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NMMAbisConnectionSetAddress(HNMMAbisConnection hConnection, const NChar * szValue);
#endif
#define NMMAbisConnectionSetAddress N_FUNC_AW(NMMAbisConnectionSetAddress)

NResult N_API NMMAbisConnectionGetUsername(HNMMAbisConnection hConnection, HNString * phValue);
NResult N_API NMMAbisConnectionSetUsernameN(HNMMAbisConnection hConnection, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API NMMAbisConnectionSetUsernameA(HNMMAbisConnection hConnection, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API NMMAbisConnectionSetUsernameW(HNMMAbisConnection hConnection, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NMMAbisConnectionSetUsername(HNMMAbisConnection hConnection, const NChar * szValue);
#endif
#define NMMAbisConnectionSetUsername N_FUNC_AW(NMMAbisConnectionSetUsername)

NResult N_API NMMAbisConnectionGetPassword(HNMMAbisConnection hConnection, HNString * phValue);
NResult N_API NMMAbisConnectionSetPasswordN(HNMMAbisConnection hConnection, HNString hValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API NMMAbisConnectionSetPasswordA(HNMMAbisConnection hConnection, const NAChar * szValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API NMMAbisConnectionSetPasswordW(HNMMAbisConnection hConnection, const NWChar * szValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NMMAbisConnectionSetPassword(HNMMAbisConnection hConnection, const NChar * szValue);
#endif
#define NMMAbisConnectionSetPassword N_FUNC_AW(NMMAbisConnectionSetPassword)

#ifdef N_CPP
}
#endif

#endif // !N_MMABIS_CONNECTION_H_INCLUDED
