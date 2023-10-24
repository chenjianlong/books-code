#ifndef INCLUDED_GAMELIB_AUTOPTR_H
#define INCLUDED_GAMELIB_AUTOPTR_H

namespace GameLib{

template< class T > class AutoPtr{
public:
	AutoPtr( T* p = 0 );
	~AutoPtr();
	//如果内部有任何内容，则立即删除（使用此选项，可以在任何时候将其删除为0）
	AutoPtr& operator=( T* p );
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
	operator void*() const; //可以编写if（p）{
private:
	void operator=( AutoPtr< T >& ); //禁止赋值。管理的转移很难理解。
	AutoPtr( AutoPtr< T >& ); //复制构造函数也是禁止的。管理的转移不容易理解。

	T* mPointer;
};

} //namespace GameLib
#include "Base/Impl/AutoPtrImpl.h"

#endif
