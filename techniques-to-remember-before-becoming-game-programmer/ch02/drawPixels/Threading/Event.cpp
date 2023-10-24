#include <windows.h>
#undef min
#undef max
#include "GameLib.h"
#include "Threading/Event.h"
#include "Base/Impl/ReferenceType.h"

namespace GameLib{
namespace Threading{

class Event::Impl : public ReferenceType{
public:
	Impl( bool f ) : mHandle( 0 ){
		BOOL t = ( f ) ? TRUE : FALSE;
		mHandle = CreateEvent( NULL, TRUE, t, NULL );
	}
	~Impl(){
		CloseHandle( mHandle );
		mHandle = 0;
	}
	HANDLE mHandle;
};

Event Event::create( bool f ){
	Event r;
	r.mImpl = NEW Impl( f );
	return r;
}

void Event::wait() const {
	WaitForSingleObject( mImpl->mHandle, INFINITE );
}

bool Event::isSet() const {
	return ( WaitForSingleObject( mImpl->mHandle, 0 ) == WAIT_OBJECT_0 );
}

void Event::set(){
	SetEvent( mImpl->mHandle );
}

void Event::reset(){
	ResetEvent( mImpl->mHandle );
}

#define TYPE Event
#include "Base/Impl/ReferenceTypeTemplate.h"

} //namespace Threading
} //namespace GameLib
