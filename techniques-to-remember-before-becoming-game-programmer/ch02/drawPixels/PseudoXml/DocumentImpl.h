#ifndef INCLUDED_GAMELIB_PSEUDOXML_DOCUMENTIMPL_H
#define INCLUDED_GAMELIB_PSEUDOXML_DOCUMENTIMPL_H

#include "FileIO/InFile.h"
#include "FileIO/Manager.h"
#include "Base/Impl/ReferenceType.h"
#include "Base/Pool.h"
#include "Base/OStringStream.h"
#include "Base/IBinaryStream.h"
#include "PseudoXml/Document.h"
#include "PseudoXml/Element.h"
#include "PseudoXml/Attribute.h"

namespace GameLib{
namespace PseudoXml{
using namespace std;

class Document::Impl : public ReferenceType{
public:
	void load( const char* filename ){
		mFile = FileIO::InFile::create( filename );
	}
	bool isError() const {
		return ( mFile && mFile.isError() );
	}
	const char* allocateString( const char* name ){
		return mStringPool.allocate( name, static_cast< int >( strlen( name ) ) + 1 );
	}
	const char* allocateString( const RefString& name ){
		char* p = mStringPool.allocate( name.get(), name.size() + 1 );
		p[ name.size() ] = '\0';
		return p;
	}
	const char* allocateString( const string& name ){
		return mStringPool.allocate( name.c_str(), static_cast< int >( name.size() ) + 1 );
	}
	const char* allocateString( const char* name, int size ){
		char* p = mStringPool.allocate( name, size + 1 );
		p[ size ] = '\0';
		return p;
	}
	//在cpp中定义。避免循环引用
	Impl();
	~Impl();
	Element::Impl* allocateElement( int n );
	Attribute::Impl* allocateAttribute( int n );
	Element::Impl* root();
	bool isReady();
	void build( const char* data, int size );
	void convertToString( string* out ) const;
	void convertToBinary( Array< char >* out ) const;
private:
	Pool< char > mStringPool;
	Pool< Element::Impl > mElementPool;
	Pool< Attribute::Impl > mAttributePool;
	Element::Impl* mRoot;
	FileIO::InFile mFile;
};

} //namespace PseudoXml
} //namespace GameLib

#endif
