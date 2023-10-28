#ifndef INCLUDED_GAMELIB_GRAPHICS_TEXTUREIMPL_H
#define INCLUDED_GAMELIB_GRAPHICS_TEXTUREIMPL_H

#include "Base/Impl/ReferenceType.h"
#include <string>

namespace GameLib{
using namespace std;
namespace Graphics{

class Texture::Impl : public ReferenceType{
public:
	enum Extension{
		EXT_TGA,
		EXT_DDS,
		EXT_UNKNOWN,
	};
	Impl( int w, int h, bool createMipChain, IDirect3DDevice9* device ) :
    mDxObject( 0 ),
	mDxDevice( device ),
	mIsError( false ),
	mWidth( 0 ),
	mHeight( 0 ),
	mOriginalWidth( w ),
	mOriginalHeight( h ),
	mExtension( EXT_UNKNOWN ){
		createDxObject( w, h, createMipChain );
	}
	~Impl(){
		if ( mDxObject ){ //如果有错误，则为0
			mDxObject->Release();
			mDxObject = 0;
		}
		mDxDevice = 0;
	}
	void lock( unsigned** b, int* pitch, int mipLevel ){
		D3DLOCKED_RECT rect;
		HRESULT hr = mDxObject->LockRect( mipLevel, &rect, NULL, 0 );
		ASSERT( hr != D3DERR_INVALIDCALL && "LockRect : INVALID CALL" );
		ASSERT( hr != D3DERR_WASSTILLDRAWING && "LockRect : WAS STILL DRAWING" );
		*b = static_cast< unsigned* >( rect.pBits );
		*pitch = rect.Pitch;
	}
	void lock( unsigned** b, int* pitch, int x, int y, int w, int h, int mipLevel ){
		D3DLOCKED_RECT rect;
		RECT range;
		range.left = x;
		range.top = y;
		range.right = x + w;
		range.bottom = y + h;
		HRESULT hr = mDxObject->LockRect( mipLevel, &rect, &range, 0 );
		ASSERT( hr != D3DERR_INVALIDCALL && "LockRect : INVALID CALL" );
		ASSERT( hr != D3DERR_WASSTILLDRAWING && "LockRect : WAS STILL DRAWING" );
		*b = static_cast< unsigned* >( rect.pBits );
		*pitch = rect.Pitch;
	}
	static Extension getExtension( const char* filename ){
		int l = static_cast< int >( strlen( filename ) );
		Array< char > name( l );
		for ( int i = 0; i < l; ++i ){
			name[ i ] = static_cast< char >( tolower( filename[ i ] ) );
		}
		Extension r = EXT_UNKNOWN;
		if ( 
				( name[ l - 4 ] == '.' ) &&
				( name[ l - 3 ] == 't' ) &&
				( name[ l - 2 ] == 'g' ) &&
				( name[ l - 1 ] == 'a' ) ){
			r = EXT_TGA;
		}else if ( 
				( name[ l - 4 ] == '.' ) &&
				( name[ l - 3 ] == 'd' ) &&
				( name[ l - 2 ] == 'd' ) &&
				( name[ l - 1 ] == 's' ) ){
			r = EXT_DDS;
		}
		return r;
	}

	void unlock( int mipLevel ){
		mDxObject->UnlockRect( mipLevel );
	}
	bool isError() const {
		return mIsError;
	}
	void createDxObject( int w, int h, bool createMipmaps ){
		int mipLevels = ( createMipmaps ) ? mipmapNumber( w, h ) : 1;
		HRESULT hr;
		hr = mDxDevice->CreateTexture( w, h, mipLevels, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &mDxObject, NULL );
		if ( FAILED( hr ) ){
			ASSERT( hr != D3DERR_INVALIDCALL && "CreateTexture : INVALID CALL" );
			ASSERT( hr != D3DERR_OUTOFVIDEOMEMORY && "CreateTexture : OUT OF VIDEO MEMORY" );
			ASSERT( hr != E_OUTOFMEMORY && "CreateTexture : E OUT OF MEMORY" );
			ASSERT( 0 && "CreateTexture : unknown error" );
		}
		mDxDevice = 0; //在这里结束。
		//成功后赋值
		mWidth = w;
		mHeight = h;
	}
	static int powerOfTwo( int a ){
		ASSERT( a < 0x40000000 ); //如果a大于0x40000000，将发生无限循环。
		int r = 1;
		while ( r < a ){
			r *= 2;
		}
		return r;
	}
	static unsigned getUnsigned( const char* data ){
		const unsigned char* up;
		up = reinterpret_cast< const unsigned char* >( data );
		unsigned r = up[ 0 ];
		r |= ( up[ 1 ] << 8 ); 
		r |= ( up[ 2 ] << 16 ); 
		r |= ( up[ 3 ] << 24 ); 
		return r;
	}
	static unsigned short getUnsignedShort( const char* data ){
		const unsigned char* up;
		up = reinterpret_cast< const unsigned char* >( data );
		unsigned short r = up[ 0 ];
		r |= ( up[ 1 ] << 8 ); 
		return r;
	}
	static unsigned char getUnsignedChar( const char* data ){
		const unsigned char* up;
		up = reinterpret_cast< const unsigned char* >( data );
		return up[ 0 ];
	}

	//递归调用，因为它很麻烦。pitch以DWORD为单位。也就是/4
	void createMipmapChain( const unsigned* src, int srcPitch, int sw, int sh, int level ){
		int dw = sw >> 1;
		int dh = sh >> 1;
		if ( dw == 0 || dh == 0 ){ //变成0
			return;
		}
		unsigned* dstSurface;
		int dstPitch;
		lock( &dstSurface, &dstPitch, level );
		unsigned* dst = dstSurface;
		dstPitch /= 4;
		ASSERT( dstPitch >= dw ); //
		//性能差一点无妨。
		for ( int y = 0; y < dh; ++y ){
			for ( int x = 0; x < dw; ++x ){
				unsigned c0 = src[ ( 2 * x ) ];
				unsigned c1 = src[ ( 2 * x ) + 1 ];
				unsigned c2 = src[ ( 2 * x ) + srcPitch ];
				unsigned c3 = src[ ( 2 * x ) + srcPitch + 1 ];
				int b = ( c0 & 0xff ) + ( c1 & 0xff ) + ( c2 & 0xff ) + ( c3 & 0xff );
				c0 >>= 8; c1 >>= 8; c2 >>= 8; c3 >>= 8;
				int g = ( c0 & 0xff ) + ( c1 & 0xff ) + ( c2 & 0xff ) + ( c3 & 0xff );
				c0 >>= 8; c1 >>= 8; c2 >>= 8; c3 >>= 8;
				int r = ( c0 & 0xff ) + ( c1 & 0xff ) + ( c2 & 0xff ) + ( c3 & 0xff );
				c0 >>= 8; c1 >>= 8; c2 >>= 8; c3 >>= 8;
				int a = ( c0 & 0xff ) + ( c1 & 0xff ) + ( c2 & 0xff ) + ( c3 & 0xff );
				b = ( b + 2 ) >> 2; //+2舍入
				g = ( g + 2 ) >> 2; //+2舍入
				r = ( r + 2 ) >> 2; //+2舍入
				a = ( a + 2 ) >> 2; //+2舍入
				dst[ x ] = b | ( g << 8 ) | ( r << 16 ) | ( a << 24 );
			}
			dst += dstPitch;
			src += srcPitch * 2; //2前进
		}
		unlock( level );
		//递归调用
		createMipmapChain( dstSurface, dstPitch, dw, dh, level + 1 );
	}
	int width() const {
		return mWidth;
	}
	int height() const {
		return mHeight;
	}
	int originalWidth() const {
		return mOriginalWidth;
	}
	int originalHeight() const {
		return mOriginalHeight;
	}
	static int mipmapNumber( int w, int h ){ //当任一个变为1时，就结束。
		int levels = 0;
		while ( w > 0 && h > 0 ){
			w >>= 1;
			h >>= 1;
			++levels;
		}
		return levels;
	}
	IDirect3DTexture9* mDxObject;
	IDirect3DDevice9* mDxDevice;
	bool mIsError;
	int mWidth;
	int mHeight;
	int mOriginalWidth;
	int mOriginalHeight;
	Extension mExtension;
};

} //namespace Graphics
} //namespace GameLib

#endif
