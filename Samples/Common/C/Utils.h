#ifndef SAMPLE_UTILS_H_INCLUDED
#define SAMPLE_UTILS_H_INCLUDED

#ifdef N_APPLE_FRAMEWORKS
	#include <NCore/NCore.h>
#else
	#include <Core/NDefs.h>
#endif

// system headers
#ifndef N_WINDOWS
	#ifndef _GNU_SOURCE
		#define _GNU_SOURCE
	#endif
#endif

#ifndef N_APPLE_FRAMEWORKS
	#include <Core/NTypes.h>
#endif

#if defined(N_PRODUCT_LIB)
	#ifdef N_APPLE_FRAMEWORKS
		#include <NDevices/NDevices.h>
	#else
		#include <NDevices.h>
	#endif
	#include <NNet/NInferenceEngineManager.h>
#endif

#ifdef N_CPP
extern "C"
{
#endif

#if defined(N_PRODUCT_LIB)

#if defined(N_PRODUCT_FINGERS_ONLY)
	#define N_PRODUCT_HAS_FINGERS
	#define N_PRODUCT_HAS_FINGERS_OR_PALMS
	#define N_PRODUCT_HAS_F_SCANNERS
#elif defined(N_PRODUCT_FACES_ONLY)
	#define N_PRODUCT_HAS_FACES
	#define N_PRODUCT_HAS_CAMERAS
#elif defined(N_PRODUCT_IRISES_ONLY)
	#define N_PRODUCT_HAS_IRISES
	#define N_PRODUCT_HAS_IRIS_SCANNERS
#elif defined(N_PRODUCT_PALMS_ONLY)
	#define N_PRODUCT_HAS_PALMS
	#define N_PRODUCT_HAS_FINGERS_OR_PALMS
	#define N_PRODUCT_HAS_F_SCANNERS
#elif defined(N_PRODUCT_VOICES_ONLY)
	#define N_PRODUCT_HAS_VOICES
	#define N_PRODUCT_HAS_MICROPHONES
#else
	#define N_PRODUCT_HAS_FINGERS
	#define N_PRODUCT_HAS_FACES
	#define N_PRODUCT_HAS_IRISES
	#define N_PRODUCT_HAS_PALMS
	#define N_PRODUCT_HAS_VOICES
	#define N_PRODUCT_HAS_FINGERS_OR_PALMS
	#define N_PRODUCT_HAS_MULTI_MODAL
	#define N_PRODUCT_HAS_F_SCANNERS
	#define N_PRODUCT_HAS_IRIS_SCANNERS
	#define N_PRODUCT_HAS_CAMERAS
	#define N_PRODUCT_HAS_MICROPHONES
	#define N_PRODUCT_HAS_MULTI_MODAL_DEVICES
#endif

#if defined(N_MAC)

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <libgen.h>

#define SET_DEVICE_PLUGINS_PATH(res)\
	{\
		CFURLRef pfkURL = NULL;\
		NAChar szDirName[PATH_MAX] = { 0, };\
		HNPluginManager hPluginManager = NULL;\
		pfkURL = CFBundleCopyPrivateFrameworksURL(CFBundleGetMainBundle());\
		if (!CFURLGetFileSystemRepresentation(pfkURL, true, (UInt8 *)szDirName, PATH_MAX))\
			res = N_E_FAILED;\
		CFRelease(pfkURL);\
		res = NDeviceManagerGetPluginManager(&hPluginManager);\
		if (NSucceeded(res))\
		{\
			res = NPluginManagerSetPluginSearchPathA(hPluginManager, szDirName);\
			res = NObjectUnref(hPluginManager);\
		}\
	}

#else

#define SET_DEVICE_PLUGINS_PATH(res)

#endif

N_DECLARE_PLUGIN_MODULE(NdmMedia)

N_DECLARE_PLUGIN_MODULE(NdmAkiyama)
N_DECLARE_PLUGIN_MODULE(NdmCanonEds)
N_DECLARE_PLUGIN_MODULE(NdmCisco)
N_DECLARE_PLUGIN_MODULE(NdmFujifilm)
N_DECLARE_PLUGIN_MODULE(NdmMobotix)
N_DECLARE_PLUGIN_MODULE(NdmMobotixThermal)
N_DECLARE_PLUGIN_MODULE(NdmNikonMaid)

N_DECLARE_PLUGIN_MODULE(NdmAbilma)
N_DECLARE_PLUGIN_MODULE(NdmAratekTrustFinger)
N_DECLARE_PLUGIN_MODULE(NdmArhFps)
N_DECLARE_PLUGIN_MODULE(NdmBioca)
N_DECLARE_PLUGIN_MODULE(NdmBioId)
N_DECLARE_PLUGIN_MODULE(NdmBiometrika)
N_DECLARE_PLUGIN_MODULE(NdmBlueFin)
N_DECLARE_PLUGIN_MODULE(NdmCogent)
N_DECLARE_PLUGIN_MODULE(NdmCrossMatch)
N_DECLARE_PLUGIN_MODULE(NdmCrossMatchLScan)
N_DECLARE_PLUGIN_MODULE(NdmDermalog)
N_DECLARE_PLUGIN_MODULE(NdmDigitalPersonaUareU)
N_DECLARE_PLUGIN_MODULE(NdmDigitalPersonaUareUOneTouch)
N_DECLARE_PLUGIN_MODULE(NdmFutronic)
N_DECLARE_PLUGIN_MODULE(NdmFutronicEthernetFam)
N_DECLARE_PLUGIN_MODULE(NdmGreenBit)
N_DECLARE_PLUGIN_MODULE(NdmHFSecurity)
N_DECLARE_PLUGIN_MODULE(NdmHongda)
N_DECLARE_PLUGIN_MODULE(NdmId3Certis)
N_DECLARE_PLUGIN_MODULE(NdmIdentix)
N_DECLARE_PLUGIN_MODULE(NdmImdA2)
N_DECLARE_PLUGIN_MODULE(NdmImdFps)
N_DECLARE_PLUGIN_MODULE(NdmIntec)
N_DECLARE_PLUGIN_MODULE(NdmIntegratedBiometricsIBScanUltimate)
N_DECLARE_PLUGIN_MODULE(NdmJenetric)
N_DECLARE_PLUGIN_MODULE(NdmKoehlke)
N_DECLARE_PLUGIN_MODULE(NdmLumidigm)
N_DECLARE_PLUGIN_MODULE(NdmMiaxis)
N_DECLARE_PLUGIN_MODULE(NdmNeuBio)
N_DECLARE_PLUGIN_MODULE(NdmNextBiometricsNB)
N_DECLARE_PLUGIN_MODULE(NdmNitgen)
N_DECLARE_PLUGIN_MODULE(NdmNitgenNBioScan)
N_DECLARE_PLUGIN_MODULE(NdmNitgenNScan)
N_DECLARE_PLUGIN_MODULE(NdmSecuGen)
N_DECLARE_PLUGIN_MODULE(NdmStartek)
N_DECLARE_PLUGIN_MODULE(NdmSupremaBioMini)
N_DECLARE_PLUGIN_MODULE(NdmSupremaRealScan)
N_DECLARE_PLUGIN_MODULE(NdmTenBio)
N_DECLARE_PLUGIN_MODULE(NdmTSTBiometrics)
N_DECLARE_PLUGIN_MODULE(NdmUnionCommunity)
N_DECLARE_PLUGIN_MODULE(NdmUpek)
N_DECLARE_PLUGIN_MODULE(NdmZKSGroup)
N_DECLARE_PLUGIN_MODULE(NdmZKSoftware)
N_DECLARE_PLUGIN_MODULE(NdmZKTeco)

N_DECLARE_PLUGIN_MODULE(NdmCmiTechIris)
N_DECLARE_PLUGIN_MODULE(NdmCrossMatchIScan)
N_DECLARE_PLUGIN_MODULE(NdmCrossMatchIScan3)
N_DECLARE_PLUGIN_MODULE(NdmIriTechIriMagic)
N_DECLARE_PLUGIN_MODULE(NdmIriTechIriShield)
N_DECLARE_PLUGIN_MODULE(NdmUBKey)
N_DECLARE_PLUGIN_MODULE(NdmVideology)

N_DECLARE_PLUGIN_MODULE(NdmVistaImaging)
N_DECLARE_PLUGIN_MODULE(NdmIrisId)

N_DECLARE_PLUGIN_MODULE(NdmSample)

#define ADD_PLUGIN(res, managerName, moduleName, szPath) \
	{\
		HNPluginManager hPluginManager = NULL;\
		HNPluginModule hModule = NULL;\
		HNPlugin hPlugin = NULL;\
		if (NSucceeded(res)) res = managerName##GetPluginManager(&hPluginManager);\
		if (NSucceeded(res)) res = N_MODULE_OF(moduleName)(&hModule);\
		if (NSucceeded(res))\
		{\
			res = NPluginManagerAddPlugin(hPluginManager, hModule, szPath, &hPlugin);\
			if (NSucceeded(res)) res = NObjectUnref(hPlugin);\
			res = NObjectUnref(hModule);\
		}\
		if (hPluginManager) res = NObjectUnref(hPluginManager);\
	}\

#define ADD_NDM_PLUGIN(res, moduleName, szFolder) \
	{\
		ADD_PLUGIN(res, NDeviceManager, Ndm##moduleName, szFolder N_T("/Ndm") N_STRINGIZE(moduleName));\
	}

#define ADD_MEDIA_PLUGIN(res) \
	{\
		ADD_PLUGIN(res, NDeviceManager, NdmMedia, NULL);\
	}

#define ADD_SAMPLE_PLUGIN(res) \
	{\
		ADD_PLUGIN(res, NDeviceManager, NdmSample, NULL);\
	}

#if defined(N_WINDOWS) && !defined(N_64)

#define ADD_CAMERA_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Akiyama, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, CanonEds, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Cisco, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Fujifilm, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Mobotix, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, MobotixThermal, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, NikonMaid, N_T("Cameras"));\
	}

#define ADD_F_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Abilma, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, AratekTrustFinger, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ArhFps, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Bioca, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, BioId, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Biometrika, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, HFSecurity, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, BlueFin, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Cogent, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, CrossMatch, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, CrossMatchLScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Dermalog, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, DigitalPersonaUareU, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, DigitalPersonaUareUOneTouch, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Futronic, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, FutronicEthernetFam, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, GreenBit, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Hongda, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Id3Certis, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Identix, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ImdA2, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ImdFps, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Intec, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, IntegratedBiometricsIBScanUltimate, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Jenetric, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Koehlke, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Lumidigm, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Miaxis, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NeuBio, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NextBiometricsNB, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Nitgen, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NitgenNBioScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NitgenNScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SecuGen, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Startek, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaBioMini, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaRealScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, TenBio, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, TSTBiometrics, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, UnionCommunity, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Upek, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ZKSGroup, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ZKSoftware, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ZKTeco, N_T("FScanners"));\
	}

#define ADD_IRIS_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, CmiTechIris, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, CrossMatchIScan, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, CrossMatchIScan3, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, IriTechIriMagic, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, IriTechIriShield, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, UBKey, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, Videology, N_T("IrisScanners"));\
	}

#define ADD_MULTI_MODAL_DEVICE_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, IrisId, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, VistaImaging, N_T("MultiModalDevices"));\
	}

#elif defined(N_WINDOWS) && defined(N_64)

#define ADD_CAMERA_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Akiyama, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, CanonEds, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Cisco, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Mobotix, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, MobotixThermal, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, NikonMaid, N_T("Cameras"));\
	}

#define ADD_F_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Abilma, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, AratekTrustFinger, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ArhFps, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Biometrika, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, HFSecurity, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, BlueFin, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, CrossMatchLScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Dermalog, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, DigitalPersonaUareU, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, DigitalPersonaUareUOneTouch, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Futronic, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, FutronicEthernetFam, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, GreenBit, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Id3Certis, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, IntegratedBiometricsIBScanUltimate, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Jenetric, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Lumidigm, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NeuBio, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NextBiometricsNB, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Nitgen, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NitgenNBioScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NitgenNScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SecuGen, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Startek, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaBioMini, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaRealScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Upek, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ZKSoftware, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ZKTeco, N_T("FScanners"));\
	}

#define ADD_IRIS_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, CmiTechIris, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, CrossMatchIScan3, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, IriTechIriShield, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, Videology, N_T("IrisScanners"));\
	}

#define ADD_MULTI_MODAL_DEVICE_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, IrisId, N_T("IrisScanners"));\
		ADD_NDM_PLUGIN(res, VistaImaging, N_T("MultiModalDevices"));\
	}

#elif defined(N_LINUX) && !defined(N_64)

#define ADD_CAMERA_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Cisco, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Mobotix, N_T("Cameras"));\
	}

#define ADD_F_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Abilma, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ArhFps, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, BlueFin, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Dermalog, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Futronic, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, FutronicEthernetFam, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, GreenBit, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, IntegratedBiometricsIBScanUltimate, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Lumidigm, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NextBiometricsNB, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Nitgen, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaBioMini, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaRealScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Upek, N_T("FScanners"));\
	}

#define ADD_IRIS_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, IriTechIriShield, N_T("IrisScanners"));\
	}

#define ADD_MULTI_MODAL_DEVICE_PLUGINS(res) \
	{\
	}

#elif defined(N_LINUX) && defined(N_64)

#define ADD_CAMERA_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Cisco, N_T("Cameras"));\
		ADD_NDM_PLUGIN(res, Mobotix, N_T("Cameras"));\
	}

#define ADD_F_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Abilma, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, ArhFps, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, BlueFin, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Futronic, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, FutronicEthernetFam, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, GreenBit, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, IntegratedBiometricsIBScanUltimate, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Lumidigm, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NextBiometricsNB, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Nitgen, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaBioMini, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, SupremaRealScan, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Upek, N_T("FScanners"));\
	}

#define ADD_IRIS_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, IriTechIriShield, N_T("IrisScanners"));\
	}

#define ADD_MULTI_MODAL_DEVICE_PLUGINS(res) \
	{\
	}

#elif defined(N_MAC) && !defined(N_64)

#define ADD_CAMERA_PLUGINS(res) \
	{\
	}

#define ADD_F_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Abilma, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Futronic, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, FutronicEthernetFam, N_T("FScanners"));\
	}

#define ADD_IRIS_SCANNER_PLUGINS(res) \
	{\
	}

#define ADD_MULTI_MODAL_DEVICE_PLUGINS(res) \
	{\
	}

#elif defined(N_MAC) && defined(N_64)

#define ADD_CAMERA_PLUGINS(res) \
	{\
	}

#define ADD_F_SCANNER_PLUGINS(res) \
	{\
		ADD_NDM_PLUGIN(res, Abilma, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, Futronic, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, FutronicEthernetFam, N_T("FScanners"));\
		ADD_NDM_PLUGIN(res, NextBiometricsNB, N_T("FScanners"));\
	}

#define ADD_IRIS_SCANNER_PLUGINS(res) \
	{\
	}

#define ADD_MULTI_MODAL_DEVICE_PLUGINS(res) \
	{\
	}

#endif

#endif

#ifdef N_CPP
}
#endif

#endif // SAMPLE_UTILS_H_INCLUDED
