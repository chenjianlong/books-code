#include <d3d9.h>
#undef min
#undef max

#include "GameLib.h"
#include "Graphics/Manager.h"
#include "WindowCreator/WindowCreator.h"

#include "ManagerImpl.h"

namespace GameLib{
using namespace Math;
namespace Graphics{

ManagerImpl* gManagerImpl = 0;

Manager::Manager(){
	//不允许来自其他线程的调用
	ASSERT( WindowCreator::isMainThread() && "you must call from MAIN thread" );
}

void Manager::create( 
void* hwnd, 
int w, 
int h,
bool fullScreen,
bool vSync,
bool antiAlias ){
	STRONG_ASSERT( !gManagerImpl );
	gManagerImpl = NEW ManagerImpl( 
		static_cast< HWND >( hwnd ), 
		w, 
		h,
		fullScreen,
		vSync,
		antiAlias );
}

void Manager::destroy(){
	SAFE_DELETE( gManagerImpl );
}

void Manager::beginDraw(){
	gManagerImpl->beginDraw();
}

void Manager::endDraw(){
	gManagerImpl->endDraw();
}

void Manager::setTextureFilter( TextureFilter tf ){
	gManagerImpl->setTextureFilter( tf );
}

void Manager::blendToScreen( Texture t ){
	gManagerImpl->blendToScreen( t.mImpl );
}

int Manager::width() const { 
	return gManagerImpl->mWidth;
}

int Manager::height() const {
	return gManagerImpl->mHeight;
}
 
void Manager::getPointerModifier( float* scale, Vector2* offset ) const {
	gManagerImpl->getPointerModifier( scale, offset );
}

} //namespace Graphics
} //namespace GameLib
