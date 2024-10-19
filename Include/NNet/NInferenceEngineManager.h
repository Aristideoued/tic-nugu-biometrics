#ifndef N_INFERENCE_ENGINE_MANAGER_H_INCLUDED
#define N_INFERENCE_ENGINE_MANAGER_H_INCLUDED

#include <Core/NObject.h>
#include <Core/NString.h>
#include <Core/NError.h>
#include <Plugins/NPluginManager.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NInferenceEngineManager, NObject)

NResult N_API NInferenceEngineManagerCreate(HNInferenceEngineManager * phInferenceEngineManager);
NResult N_API NInferenceEngineManagerGetPluginManager(HNPluginManager * phValue);
NResult N_API NInferenceEngineManagerGetPluginByName(HNString hNames, NBool checkIsAvailable, NBool checkIsBatchedSupported, HNError *phLastError, HNPlugin * phValue);
NResult N_API NInferenceEngineManagerGetFailedPluginDiagnostic(HNString * phMessage);

NResult N_API NInferenceEngineManagerInitialize(HNInferenceEngineManager hInferenceEngineManager);
NResult N_API NInferenceEngineManagerIsInitialized(HNInferenceEngineManager hInferenceEngineManager, NBool * pValue);
NResult N_API NInferenceEngineManagerGetAutoPlug(HNInferenceEngineManager hInferenceEngineManager, NBool * pValue);
NResult N_API NInferenceEngineManagerSetAutoPlug(HNInferenceEngineManager hInferenceEngineManager, NBool value);


N_DECLARE_MODULE(NiemBlas)
N_DECLARE_MODULE(NiemFingerNet)
N_DECLARE_MODULE(NiemIntelIe)
N_DECLARE_MODULE(NiemMnn)
N_DECLARE_MODULE(NiemTensorRt)

#define NIEM_ADD_STATIC_VARS \
	HNPluginModule NIEM_ADD_STATIC_hModule = NULL;\
	HNPlugin NIEM_ADD_STATIC_hPlugin = NULL;\
	HNPluginManager NIEM_ADD_STATIC_hPluginManager = NULL;

#define NIEM_ADD_STATIC_FREE \
	N_CHECK(NObjectSet(NULL, &NIEM_ADD_STATIC_hModule));\
	N_CHECK(NObjectSet(NULL, &NIEM_ADD_STATIC_hPlugin));\
	N_CHECK(NObjectSet(NULL, &NIEM_ADD_STATIC_hPluginManager));

#define NIEM_ADD_STATIC(ieName) \
{\
	N_CHECK(N_MODULE_OF(Niem##ieName)(&NIEM_ADD_STATIC_hModule));\
	N_CHECK(NInferenceEngineManagerGetPluginManager(&NIEM_ADD_STATIC_hPluginManager));\
	N_CHECK(NPluginManagerAddPlugin(NIEM_ADD_STATIC_hPluginManager, NIEM_ADD_STATIC_hModule,\
		N_T("InferenceEngines/Niem") N_STRINGIZE(ieName), &NIEM_ADD_STATIC_hPlugin));\
	NIEM_ADD_STATIC_FREE\
}

#if defined(N_X64) && (defined(N_WINDOWS) || defined(N_LINUX))
	#define NIEM_ADD_STATIC_ALL \
	{\
		NIEM_ADD_STATIC(Blas)\
		NIEM_ADD_STATIC(FingerNet)\
		NIEM_ADD_STATIC(IntelIe)\
	}
#elif defined(N_ARM_FAMILY) || defined(N_IOS) || defined(N_MAC)
	#define NIEM_ADD_STATIC_ALL \
	{\
		NIEM_ADD_STATIC(Blas)\
		NIEM_ADD_STATIC(FingerNet)\
		NIEM_ADD_STATIC(Mnn)\
	}
#else
	#define NIEM_ADD_STATIC_ALL \
	{\
		NIEM_ADD_STATIC(Blas)\
		NIEM_ADD_STATIC(FingerNet)\
	}
#endif

#ifdef N_CPP
}
#endif

#endif // !N_INFERENCE_ENGINE_MANAGER_H_INCLUDED
