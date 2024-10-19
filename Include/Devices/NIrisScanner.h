#include <Devices/NBiometricDevice.h>

#ifndef N_IRIS_SCANNER_H_INCLUDED
#define N_IRIS_SCANNER_H_INCLUDED

#include <Images/NImage.h>
#include <Biometrics/NEAttributes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NIrisScanner, NBiometricDevice)

typedef NResult (N_CALLBACK NIrisScannerPreviewCallback)(HNIrisScanner hDevice, HNImage hImage, NBiometricStatus * pStatus, const HNEAttributes * arhObjects, NInt objectCount, void * pParam);
N_DECLARE_TYPE(NIrisScannerPreviewCallback)

NResult N_API NIrisScannerGetSupportedPositions(HNIrisScanner hDevice, NEPosition * arValue, NInt valueLength);

#ifdef N_CPP
}
#endif

#endif // !N_IRIS_SCANNER_H_INCLUDED
