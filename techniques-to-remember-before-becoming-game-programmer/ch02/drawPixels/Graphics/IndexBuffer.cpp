﻿#include <d3d9.h>
#undef min
#undef max

#include "GameLib.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/IndexBufferImpl.h"
#include "Graphics/ManagerImpl.h"

namespace GameLib{
namespace Graphics{

IndexBuffer IndexBuffer::create( PseudoXml::ConstElement e ){
	IndexBuffer r;
	r.mImpl = NEW Impl( e, gManagerImpl->dxDevice() );
	return r;
}

IndexBuffer IndexBuffer::create( int indexNumber ){
	IndexBuffer r;
	r.mImpl = NEW Impl( indexNumber, gManagerImpl->dxDevice() );
	return r;
}

unsigned short* IndexBuffer::lock(){
	ASSERT( mImpl && "Graphics::IndexBuffer : This is empty object." );
	return mImpl->lock();
}

void IndexBuffer::unlock( unsigned short** p ){
	//TODO：调试时，请记住锁返回的指针，并在此处进行处理。
	ASSERT( *p && "Graphics::IndexBuffer : give LOCKED pointer." );
	ASSERT( mImpl && "Graphics::IndexBuffer : This is empty object." );
	mImpl->unlock();
	*p = 0;
}

IndexBuffer::IndexBuffer( const Impl* ) : mImpl( 0 ){
}

const char* IndexBuffer::name() const {
	return mImpl->mName;
}

int IndexBuffer::indexNumber() const {
	return mImpl->mIndexNumber;
}

#define TYPE IndexBuffer
#include "Base/Impl/ReferenceTypeTemplate.h"

} //namespace Graphics
} //namespace GameLib
