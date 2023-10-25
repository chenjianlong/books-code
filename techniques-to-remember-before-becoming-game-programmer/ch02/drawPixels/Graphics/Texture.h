#ifndef INCLUDED_GAMELIB_GRAPHICS_TEXTURE_H
#define INCLUDED_GAMELIB_GRAPHICS_TEXTURE_H

namespace GameLib{
namespace PseudoXml{
	class ConstElement;
}
namespace Graphics{

class Texture{
public:
	//空的纹理
	static Texture create( int width, int height, bool createMipChain );

	///是否发生读取错误？
	bool isError() const;

	///写入函数
	void lock( unsigned** address, int* pitch, int mipLevel = 0 );
	///部分写入函数
	void lock( 
		unsigned** address, 
		int* pitch, 
		int x,
		int y,
		int width,
		int height,
		int mipLevel = 0 );
	void unlock( unsigned** address, int mipLevel = 0 );
	//获取信息
	int width() const;
	int height() const;
	///转换为2的n次幂之前的原始宽度
	int originalWidth() const;
	///转换为2的n次幂之前的原始高度
	int originalHeight() const;
	int mipmapNumber() const;

	//用户不会意识到的函数
	Texture();
	Texture( const Texture& );
	~Texture();
	operator void*() const;
	Texture& operator=( const Texture& );
	void release();
	bool operator==( const Texture& ) const;
	bool operator!=( const Texture& ) const;
	bool operator<( const Texture& ) const;

	class Impl;
	Texture( const Impl* );
private:
	friend class Manager;
	Impl* mImpl;
};

} //namespace Graphics
} //namespace GameLib

#endif
