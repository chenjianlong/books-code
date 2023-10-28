#ifndef INCLUDED_GAMELIB_GRAPHICS_MANAGER_H
#define INCLUDED_GAMELIB_GRAPHICS_MANAGER_H

#include "Graphics/Enum.h"

namespace GameLib{

namespace Math{
	class Matrix44;
	class Matrix34;
	class Vector2;
	class Vector3;
}
using namespace Math;
	
namespace Graphics{

class Texture;

class Manager{
public:
	Manager();

	void setTextureFilter( TextureFilter );

	///纹理贴到全屏幕
	void blendToScreen( Texture );
	///返回绘图缓冲区的宽度
	int width() const;
	///返回绘图缓冲区的高度
	int height() const;

	//你不需要知道的东西
	static void create( 
		void* windowHandle,
		int width,
		int height,
		bool fullScreen,
		bool vSync,
		bool antiAlias );
	static void destroy();
	void beginDraw();
	void endDraw();
	void getPointerModifier( float* scale, Vector2* offset ) const;
};

} //namespace Graphics
} //namespace GameLib

#endif
