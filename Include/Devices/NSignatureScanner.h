#include <Devices/NBiometricDevice.h>

#ifndef N_SIGNATURE_SCANNER_H_INCLUDED
#define N_SIGNATURE_SCANNER_H_INCLUDED

#include <Images/NImage.h>
#include <Biometrics/NAAttributes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NSignatureScanner, NBiometricDevice)

typedef NResult (N_CALLBACK NSignatureScannerPreviewCallback)(HNSignatureScanner hDevice, HNImage hImage, NBiometricStatus * pStatus, const HNAAttributes * arhObjects, NInt objectCount, void * pParam);
N_DECLARE_TYPE(NSignatureScannerPreviewCallback)

#ifdef N_CPP
}
#endif

#endif // !N_SIGNATURE_SCANNER_H_INCLUDED
