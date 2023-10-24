#ifndef INCLUDED_GAMELIB_GRAPHICS_VERTEX_H
#define INCLUDED_GAMELIB_GRAPHICS_VERTEX_H

#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace GameLib{
using namespace Math;
namespace Graphics{

class Vertex{
public:
	Vector4 mPosition; //位置
	Vector3 mNormal; //法线
	unsigned mColor; //顶点颜色
	Vector2 mUv; //纹理坐标
};

} //namespace Graphics
} //namespace GameLib

#endif
