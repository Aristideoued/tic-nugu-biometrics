#ifndef N_EXIT_EVENT_HPP_INCLUDED
#define N_EXIT_EVENT_HPP_INCLUDED

#include <Core/NObject.hpp>
namespace Neurotec {namespace Threading {
#include <Threading/NExitEvent.h>
}}


namespace Neurotec { namespace Threading
{
class NExitEvent
{
	N_DECLARE_STATIC_OBJECT_CLASS(NExitEvent)

public:
	static NType NExitEventNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(NExitEvent), true);
	}

	static void Register()
	{
		NCheck(NExitEventRegister());
	}

	static void WaitFor()
	{
		NCheck(NExitEventWaitFor());
	}
};

}}

#endif // !N_EXIT_EVENT_HPP_INCLUDED
