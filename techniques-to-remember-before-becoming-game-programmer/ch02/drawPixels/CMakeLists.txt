cmake_minimum_required(VERSION 3.15)
project(drawPixels)

include_directories(
	${CMAKE_SOURCE_DIR}
)

add_executable(drawPixels WIN32
	Framework.h
	Framework.cpp
	main.cpp
	Base/Conversion.h
	Base/Conversion.cpp
	Base/DebugStream.h
	Base/DebugStream.cpp
	Base/Halt.cpp
	Base/MemoryManager.h
	Base/MemoryManager.cpp
	Base/OStringStream.h
	Base/OStringStream.cpp
	Base/RefString.h
	Base/RefString.cpp
	Graphics/Manager.h
	Graphics/Manager.cpp
	Graphics/Texture.h
	Graphics/Texture.cpp
	Graphics/VertexBuffer.h
	Graphics/VertexBuffer.cpp
	Math/Functions.h
	Math/Functions.cpp
	Math/Random.h
	Math/Random.cpp
	Math/Matrix33.h
	Math/Matrix33.cpp
	Math/Matrix34.h
	Math/Matrix34.cpp
	Math/Matrix44.h
	Math/Matrix44.cpp
	Math/Vector2.h
	Math/Vector2.cpp
	Math/Vector3.h
	Math/Vector3.cpp
	Math/Vector4.h
	Math/Vector4.cpp
	Threading/Event.h
	Threading/Event.cpp
	Threading/Functions.h
	Threading/Functions.cpp
	Threading/Semaphore.h
	Threading/Semaphore.cpp
	Threading/Thread.h
	Threading/Thread.cpp
	Threading/Manager.h
	Threading/Manager.cpp
	Threading/Mutex.h
	Threading/Mutex.cpp
	WindowCreator/WindowCreator.h
	WindowCreator/WindowCreator.cpp
)

target_link_libraries(drawPixels d3d9 winmm DSound dinput8 dxguid)
