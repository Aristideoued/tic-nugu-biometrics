#include <Devices/NBiometricDevice.hpp>

#ifndef N_SIGNATURE_SCANNER_HPP_INCLUDED
#define N_SIGNATURE_SCANNER_HPP_INCLUDED

#include <Images/NImage.hpp>
#include <Biometrics/NAAttributes.hpp>
namespace Neurotec { namespace Devices
{
using ::Neurotec::Images::HNImage;
using ::Neurotec::Biometrics::HNAAttributes;
using ::Neurotec::Biometrics::NBiometricType;
using ::Neurotec::Biometrics::NBiometricStatus;
#include <Devices/NSignatureScanner.h>
}}

namespace Neurotec { namespace Devices
{

class NSignatureScanner : public NBiometricDevice
{
	N_DECLARE_OBJECT_CLASS(NSignatureScanner, NBiometricDevice)
};

}}

#endif // !N_SIGNATURE_SCANNER_HPP_INCLUDED
