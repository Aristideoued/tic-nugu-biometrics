#ifndef N_INFERENCE_ENGINE_MANAGER_HPP_INCLUDED
#define N_INFERENCE_ENGINE_MANAGER_HPP_INCLUDED

#include <Core/NObject.hpp>
#include <Core/NString.hpp>
#include <Core/NError.hpp>
#include <Plugins/NPluginManager.hpp>
namespace Neurotec { namespace InferenceEngines
{
using ::Neurotec::HNModule;
using ::Neurotec::Plugins::HNPlugin;
using ::Neurotec::Plugins::HNPluginModule;
using ::Neurotec::Plugins::HNPluginManager;
#include <NNet/NInferenceEngineManager.h>
}}

namespace Neurotec { namespace InferenceEngines
{
#undef NIEM_ADD_STATIC
#define NIEM_ADD_STATIC(ieName) \
	{\
		::Neurotec::HNModule hModule;\
		::Neurotec::NCheck(::Neurotec::InferenceEngines::Niem##ieName##ModuleOf(&hModule));\
		::Neurotec::Plugins::NPluginModule pluginModule = ::Neurotec::Plugins::NPluginModule(hModule, true);\
		::Neurotec::Plugins::NPluginManager pluginManager = ::Neurotec::InferenceEngines::NInferenceEngineManager::GetPluginManager();\
		pluginManager.GetPlugins().Add(pluginModule, N_T("InferenceEngines/Niem") N_STRINGIZE(ieName));\
	}

class NInferenceEngineManager : public NObject
{
	N_DECLARE_OBJECT_CLASS(NInferenceEngineManager, NObject)

private:
	static HNInferenceEngineManager Create()
	{
		HNInferenceEngineManager handle;
		NCheck(NInferenceEngineManagerCreate(&handle));
		return handle;
	}

public:
	static ::Neurotec::Plugins::NPluginManager GetPluginManager()
	{
		return GetObject< ::Neurotec::Plugins::NPluginManager>(NInferenceEngineManagerGetPluginManager, true);
	}

	NInferenceEngineManager()
		: NObject(Create(), true)
	{
	}

	void Initialize()
	{
		NCheck(NInferenceEngineManagerInitialize(GetHandle()));
	}

	bool IsInitialized()
	{
		NBool value;
		NCheck(NInferenceEngineManagerIsInitialized(GetHandle(), &value));
		return value != 0;
	}

	bool GetAutoPlug()
	{
		NBool value;
		NCheck(NInferenceEngineManagerGetAutoPlug(GetHandle(), &value));
		return value != 0;
	}

	void SetAutoPlug(bool value)
	{
		NCheck(NInferenceEngineManagerSetAutoPlug(GetHandle(), value ? NTrue : NFalse));
	}

	::Neurotec::Plugins::NPlugin GetPluginByName(NStringWrapper names, bool checkIsAvailable, bool checkIsBatchedSupported)
	{
		::Neurotec::Plugins::HNPlugin hPlugin;
		NCheck(NInferenceEngineManagerGetPluginByName(names.GetHandle(), checkIsAvailable ? NTrue : NFalse ,
			checkIsBatchedSupported ? NTrue : NFalse, NULL, &hPlugin));
		return FromHandle<::Neurotec::Plugins::NPlugin>(hPlugin, true);
	}
};

}}

#endif // !N_INFERENCE_ENGINE_MANAGER_HPP_INCLUDED
