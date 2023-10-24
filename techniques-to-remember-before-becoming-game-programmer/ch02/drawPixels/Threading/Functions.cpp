#include <windows.h>
#undef min
#undef max

#include "GameLib.h"
#include "Threading/Functions.h"

namespace GameLib{
namespace Threading{

void sleep( int milliSeconds ){
	Sleep( milliSeconds );
}

unsigned getCurrentThreadId(){
	return GetCurrentThreadId();
}

} //namespace Threading
} //namespace GameLib
