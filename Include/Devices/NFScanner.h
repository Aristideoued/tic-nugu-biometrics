#include <Devices/NBiometricDevice.h>

#ifndef NF_SCANNER_H_INCLUDED
#define NF_SCANNER_H_INCLUDED

#include <Geometry/NGeometry.h>
#include <Images/NImage.h>
#include <Biometrics/NFAttributes.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NFScanner, NBiometricDevice)

typedef NResult (N_CALLBACK NFScannerPreviewCallback)(HNFScanner hDevice, HNImage hImage, NBiometricStatus * pStatus, const HNFAttributes * arhObjects, NInt objectCount, void * pParam);
N_DECLARE_TYPE(NFScannerPreviewCallback)

NResult N_API NFScannerGetSupportedImpressionTypes(HNFScanner hDevice, NFImpressionType * arValue, NInt valueLength);
NResult N_API NFScannerGetSupportedPositions(HNFScanner hDevice, NFPosition * arValue, NInt valueLength);

#ifdef N_CPP
}
#endif

#endif // !NF_SCANNER_H_INCLUDED
