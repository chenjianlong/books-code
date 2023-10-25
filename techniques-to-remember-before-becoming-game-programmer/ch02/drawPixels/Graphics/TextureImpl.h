#ifndef INCLUDED_GAMELIB_GRAPHICS_TEXTUREIMPL_H
#define INCLUDED_GAMELIB_GRAPHICS_TEXTUREIMPL_H

#include "FileIO/Manager.h"
#include "FileIO/InFile.h"
#include "Base/Impl/ReferenceType.h"
#include "PseudoXml/Element.h"
#include "PseudoXml/Attribute.h"
#include "Base/RefString.h"
#include <string>

namespace GameLib{
using namespace std;
using namespace GameLib::PseudoXml;
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

	void write( const char* filename ){
		Extension ext = getExtension( filename );
		switch ( ext ){
			case EXT_TGA: writeTga( filename ); break;
			case EXT_DDS: writeDds( filename ); break;
			default: ASSERT( 0 ); break;
		}
	}
	static void writeTga( const char* filename, int width, int height, int pitch, const unsigned* src, bool alpha ){
		static const char* footerString = "TRUEVISION-XFILE.";
		const int footerStringLength = static_cast< int >( strlen( footerString ) );
		char pixelSize = ( alpha ) ? 4 : 3;
		int fileSize = width * height * pixelSize;
		fileSize += 18; //标头
		fileSize += ( 8 + footerStringLength + 1 ); //footer
		char* data = NEW char[ fileSize ];
		//用0填充标题
		for ( int i = 0; i < 18; ++i ){
			data[ i ] = 0;
		}
		unsigned char* dst = reinterpret_cast< unsigned char* >( data );
		dst[ 0x0 ] = 0; //ID字段长度
		dst[ 0x1 ] = 0; //调色板存在
		dst[ 0x2 ] = 2; //RGB24bit
		dst[ 0x3 ] = 0; //调色板偏移量？
		dst[ 0x4 ] = 0; //调色板偏移量？
		dst[ 0x5 ] = 0; //调色板数？
		dst[ 0x6 ] = 0; //调色板数？
		dst[ 0x7 ] = 0; //调色板位深度？
		dst[ 0x8 ] = 0; //X offset (lower)
		dst[ 0x9 ] = 0; //X offset (upper)
		dst[ 0xa ] = 0; //Y offset (lower)
		dst[ 0xb ] = 0; //Y offset (upper)
		dst[ 0xc ] = static_cast< char >( width & 0xff ); //width (lower)
		dst[ 0xd ] = static_cast< char >( ( width & 0xff00 ) >> 8 ); //width (lower)
		dst[ 0xe ] = static_cast< char >( height & 0xff ); //width (lower)
		dst[ 0xf ] = static_cast< char >( ( height & 0xff00 ) >> 8 ); //width (lower)
		dst[ 0x10 ] = pixelSize * 8; //色深
		dst[ 0x11 ] = 0x20 + ( ( alpha ) ? 8 : 0 ); //

		//里面
		dst += 0x12;
		if ( alpha ){
			for ( int y = 0; y < height; ++y ){
				for ( int x = 0; x < width; ++x ){
					unsigned char* d = dst + 4 * x;
					unsigned s = src[ x ];
					d[ 0 ] = static_cast< unsigned char >( ( s & 0x000000ff ) >> 0 ); //B
					d[ 1 ] = static_cast< unsigned char >( ( s & 0x0000ff00 ) >> 8 ); //G
					d[ 2 ] = static_cast< unsigned char >( ( s & 0x00ff0000 ) >> 16 ); //R
					d[ 3 ] = static_cast< unsigned char >( ( s & 0xff000000 ) >> 24 ); //A
				}
				dst += width * 4;
				src += pitch / 4;
			}
		}else{
			for ( int y = 0; y < height; ++y ){
				for ( int x = 0; x < width; ++x ){
					unsigned char* d = dst + 3 * x;
					unsigned s = src[ x ];
					d[ 0 ] = static_cast< unsigned char >( ( s & 0x000000ff ) >> 0 ); //B
					d[ 1 ] = static_cast< unsigned char >( ( s & 0x0000ff00 ) >> 8 ); //G
					d[ 2 ] = static_cast< unsigned char >( ( s & 0x00ff0000 ) >> 16 ); //R
				}
				dst += width * 3;
				src += pitch / 4;
			}
		}
		//写footer
		//8字节零
		for ( int i = 0; i < 8; ++i ){	
			dst[ i ] = 0;
		}
		dst += 8;
		for ( int i = 0; i < footerStringLength; ++i ){
			dst[ i ] = footerString[ i ];
		}
		dst[ footerStringLength ] = '\0';

		//写
		FileIO::Manager().write( filename, data, fileSize );
		SAFE_DELETE_ARRAY( data );
	}
	void writeTga( const char* filename ){
		unsigned* b;
		int pitch;
		lock( &b, &pitch, 0 );
		writeTga( filename, mWidth, mHeight, pitch, b, true );
		unlock( 0 );
	}
	static void writeDds( const char* filename, int width, int height, int pitch, const unsigned* src, bool alpha ){
		int fileSize = width * height * 4 + 128;
		char* data = NEW char[ fileSize ];
		//用0填充标题
		for ( int i = 0; i < 128; ++i ){
			data[ i ] = 0;
		}
		unsigned char* dst = reinterpret_cast< unsigned char* >( data );
		//只是编写用二进制编辑器看到的DDS内容，却不知道其含义
		dst[ 0x0 ] = 'D';
		dst[ 0x1 ] = 'D';
		dst[ 0x2 ] = 'S';
		dst[ 0x3 ] = ' ';
		dst[ 0x4 ] = 0x7c; //结构体大小124
		dst[ 0x8 ] = 0x7; //flags
		dst[ 0x9 ] = 0x10; //flags
		dst[ 0xc ] = static_cast< char >( height & 0xff );
		dst[ 0xd ] = static_cast< char >( ( height & 0xff00 ) >> 8 );
		dst[ 0x10 ] = static_cast< char >( width & 0xff );
		dst[ 0x11 ] = static_cast< char >( ( width & 0xff00 ) >> 8 );
		dst[ 0x4c ] = 0x20; //DDPIXELFORMAT的尺寸32
		dst[ 0x50 ] = 0x41; //flags
		dst[ 0x58 ] = 0x20; //32bit
		dst[ 0x5e ] = 0xff; //Rmask
		dst[ 0x61 ] = 0xff; //Gmask
		dst[ 0x64 ] = 0xff; //Bmask
		dst[ 0x6b ] = 0xff; //Amask
		dst[ 0x6c ] = 0x2; //caps
		dst[ 0x6d ] = 0x10; //caps

		dst += 128;
		if ( alpha ){
			for ( int y = 0; y < height; ++y ){
				for ( int x = 0; x < width; ++x ){
					unsigned char* d = dst + 4 * x;
					unsigned s = src[ x ];
					d[ 0 ] = static_cast< unsigned char >( ( s & 0x000000ff ) >> 0 ); //B
					d[ 1 ] = static_cast< unsigned char >( ( s & 0x0000ff00 ) >> 8 ); //G
					d[ 2 ] = static_cast< unsigned char >( ( s & 0x00ff0000 ) >> 16 ); //R
					d[ 3 ] = static_cast< unsigned char >( ( s & 0xff000000 ) >> 24 ); //A
				}
				dst += width * 4;
				src += pitch / 4;
			}
		}else{
			for ( int y = 0; y < height; ++y ){
				for ( int x = 0; x < width; ++x ){
					unsigned char* d = dst + 4 * x;
					unsigned s = src[ x ];
					d[ 0 ] = static_cast< unsigned char >( ( s & 0x000000ff ) >> 0 ); //B
					d[ 1 ] = static_cast< unsigned char >( ( s & 0x0000ff00 ) >> 8 ); //G
					d[ 2 ] = static_cast< unsigned char >( ( s & 0x00ff0000 ) >> 16 ); //R
					d[ 3 ] = 0xff;
				}
				dst += width * 4;
				src += pitch / 4;
			}
		}
		//写
		FileIO::Manager().write( filename, data, fileSize );
		SAFE_DELETE_ARRAY( data );
	}
	void writeDds( const char* filename ){
		unsigned* b;
		int pitch;
		lock( &b, &pitch, 0 );
		writeDds( filename, mWidth, mHeight, pitch, b, true );
		unlock( 0 );
	}
	///将数据写入文件的函数。Pitch数量大体是height*4，但不一定。
	static void write( const char* filename, int width, int height, int pitch, const unsigned* data ){
		Extension ext = getExtension( filename );
		if ( ext == EXT_DDS ){
			writeDds( filename, width, height, pitch, data, false );
		}else{
			writeTga( filename, width, height, pitch, data, false );
		}
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
	FileIO::InFile mFile;
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
