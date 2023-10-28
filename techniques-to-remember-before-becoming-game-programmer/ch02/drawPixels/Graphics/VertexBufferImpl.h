#ifndef INCLUDED_GAMELIB_GRAPHICS_VERTEXBUFFERIMPL_H
#define INCLUDED_GAMELIB_GRAPHICS_VERTEXBUFFERIMPL_H

#include "Graphics/Vertex.h"
#include "Base/Impl/ReferenceType.h"
#include "Base/RefString.h"

namespace GameLib{
namespace Graphics{

class VertexBuffer::Impl : public ReferenceType{
public:
	Impl( int vertexNumber, IDirect3DDevice9* device ) : 
	mDxObject( 0 ),
	mVertexNumber( vertexNumber ),
	mName( 0 ){
		createDxObject( device );
	}
	~Impl(){
		mDxObject->Release();
		mDxObject = 0;
		SAFE_DELETE_ARRAY( mName );
	}
	void createDxObject( IDirect3DDevice9* device ){
		HRESULT hr;
		hr = device->CreateVertexBuffer( 
			mVertexNumber * sizeof( Vertex ), 
			0,
			0,
			D3DPOOL_MANAGED, 
			&mDxObject, 
			NULL );
		if ( FAILED( hr ) ){
			ASSERT( hr != D3DERR_INVALIDCALL && "CreateVertexBuffer : INVALID CALL" );
			ASSERT( hr != D3DERR_OUTOFVIDEOMEMORY && "CreateVertexBuffer : OUT OF VIDEO MEMORY" );
			ASSERT( hr != E_OUTOFMEMORY && "CreateVertexBuffer : E OUT OF MEMORY" );
			ASSERT( 0 && "CreateVertexBuffer : unknown error" );
		}
	}
	Vertex* lock(){
		void* r = 0;
		mDxObject->Lock( 0, 0, &r, 0 );
		return static_cast< Vertex* >( r );
	}
	void unlock(){
		mDxObject->Unlock();
	}
	IDirect3DVertexBuffer9* mDxObject;
	int mVertexNumber;
	char* mName;
private:
	void operator=( const Impl& ); //禁止
};

} //namespace Graphics
} //namespace GameLib

#endif
