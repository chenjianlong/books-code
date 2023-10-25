#include <d3d9.h>
#undef max
#undef min

#include "GameLib.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureImpl.h"
#include "Graphics/ManagerImpl.h"

namespace GameLib{
namespace Graphics{

Texture Texture::create( int w, int h, bool createMipChain ){
	Texture r;
	r.mImpl = NEW Texture::Impl( w, h, createMipChain, gManagerImpl->dxDevice() );
	return r;
}

void Texture::lock( unsigned** b, int* pitch, int mipLevel ){
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	mImpl->lock( b, pitch, mipLevel );
}

void Texture::lock( 
unsigned** b, 
int* pitch,
int x,
int y,
int w,
int h,
int mipLevel ){
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	mImpl->lock( b, pitch, x, y, w, h, mipLevel );
}

void Texture::unlock( unsigned** p, int mipLevel ){
	ASSERT( *p && "Graphics::Texture : give LOCKED pointer." );
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	mImpl->unlock( mipLevel );
	*p = 0;
}

bool Texture::isError() const {
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	return mImpl->isError();
}

int Texture::width() const {
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	return mImpl->width();
}

int Texture::height() const {
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	return mImpl->height();
}

int Texture::originalWidth() const {
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	return mImpl->originalWidth();
}

int Texture::originalHeight() const {
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	return mImpl->originalHeight();
}

int Texture::mipmapNumber() const {
	ASSERT( mImpl && "Graphics::Texture : This is empty object." );
	return Impl::mipmapNumber( mImpl->mWidth, mImpl->mHeight );
}

Texture::Texture( const Impl* ) : mImpl( 0 ){ //自动生成
}

bool Texture::operator<( const Texture& o ) const {
	return ( mImpl < o.mImpl );
}

#define TYPE Texture
#include "Base/Impl/ReferenceTypeTemplate.h"

} //namespace Graphics
} //namespace GameLib
