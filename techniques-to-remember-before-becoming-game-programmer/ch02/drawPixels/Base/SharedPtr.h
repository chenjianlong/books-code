#ifndef INCLUDED_GAMELIB_SHAREDPTR_H
#define INCLUDED_GAMELIB_SHAREDPTR_H

namespace GameLib{

template< class T > class SharedPtr{
public:
	SharedPtr();
	SharedPtr( T* p );
	SharedPtr( const SharedPtr< T >& p );
	~SharedPtr();
	SharedPtr& operator=( T* p );
	SharedPtr& operator=( const SharedPtr< T >& p );
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
	operator void*() const;
private:
	struct Reference{
		Reference( T* p );
		~Reference();
		void increment();
		int decrement();

		T* mPointer;
		unsigned mCount;
	};
	Reference* mReference;
};

//const版本
template< class T > class ConstSharedPtr{
public:
	ConstSharedPtr();
	ConstSharedPtr( const SharedPtr< T >& );
	~ConstSharedPtr();
	ConstSharedPtr& operator=( const SharedPtr< T >& );
	const T& operator*() const;
	const T* operator->() const;
	operator void*() const;
private:
	SharedPtr< T > mPointer;
};

} //namespace GameLib
#include "Base/Impl/SharedPtrImpl.h"

#endif
