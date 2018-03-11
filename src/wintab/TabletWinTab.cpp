#include "TabletWinTab.h"

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

// Set to 1 to get more debug output
#define VERBOSE_DEBUG 0

//??? Because we'll look up functions from the DLL, don't prototype them 
//#define NOWTFUNCTIONS
#include <wintab.h>

void setupTabletWinTab(TabletData &tablet)
{
    pfWTInfo( WTI_DEFCONTEXT, CTX_MSGBASE, &ms_msgBase );
    ms_msgFilterHook = SetWindowsHookEx( WH_GETMESSAGE, msgProcFilter, nullptr, GetCurrentThreadId() );
    if( ms_msgFilterHook == nullptr ) {
      printf("COuldn't hook");
      //FormatMessage(GetLastError()
    }
}

void destroyTabletWinTab()
{
  UnhookWindowsHookEx( ms_msgFilterHook );
  ms_msgFilterHook = nullptr;
}