#ifndef N_EXIT_EVENT_H_INCLUDED
#define N_EXIT_EVENT_H_INCLUDED

#include <Core/NObject.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_STATIC_OBJECT_TYPE(NExitEvent)

NResult N_API NExitEventRegister(void);
NResult N_API NExitEventWaitFor(void);

#ifdef N_CPP
}
#endif

#endif // !N_EXIT_EVENT_H_INCLUDED
