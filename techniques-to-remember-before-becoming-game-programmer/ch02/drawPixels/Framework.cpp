#include "GameLib.h"
#include "WindowCreator/WindowCreator.h"
#include "FileIO/Manager.h"
#include "Graphics/Manager.h"
#include "Graphics/Texture.h"
#include "Math/Vector2.h"
#include "Scene/Font.h"
#include "Threading/Functions.h"
#include "Threading/Manager.h"

#include "Framework.h"
#include "FontTextureGenerated.h"

#include <string>
using namespace std;

namespace GameLib{

namespace { //匿名

class Impl{
public:
	Impl() :
	mWidth( 320 ),
	mHeight( 240 ),
	mFullScreen( false ),
	mFullScreenForbidden( true ),
	mVSync( false ),
	mAntiAlias( false ),
	mTitle( "A GameLib Framework Application" ),
	mArchiveNames( 0 ),
	mArchiveNumber( 0 ),
	mLoadMode( FileIO::Manager::MODE_DIRECT_FIRST ),
	mPreviousFrameInterval( 0 ),
	mFrameRate( 0 ),
	mEndRequested( false ),
	mStarted( false ){
		//cout初始化
		cout.begin();
		//帧历史记录重置
		unsigned t = time();
		for ( int i = 0; i < TIME_HISTORY_SIZE; ++i ){
			mTimeHistory[ i ] = t;
		}

		mVideoMemoryWithPadding.setSize( mWidth * ( mHeight + 2 ) );
		//0初始化
		for ( int i = 0; i < mWidth * ( mHeight + 2 ); ++i ){
			mVideoMemoryWithPadding[ i ] = 0;
		}
		for ( int i = 0; i < mWidth; ++i ){
			mVideoMemoryWithPadding[ i ] = MAGIC_NUMBER;
			mVideoMemoryWithPadding[ mWidth * ( mHeight + 1 ) + i ] = MAGIC_NUMBER;
		}
	}
	~Impl(){
		if ( mArchiveNames ){
			SAFE_DELETE_ARRAY( mArchiveNames );
		}
		Graphics::Manager::destroy();
		FileIO::Manager::destroy();
		Threading::Manager::destroy();
		//cout结束
		cout.end();
	}
	void start( void* windowHandle ){
		//线程系统初始化
		Threading::Manager::create( 0 );
		//初始化文件加载器
		if ( mArchiveNumber > 0 ){
			Array< const char* > names( mArchiveNumber );
			for ( int i = 0; i < mArchiveNumber; ++i ){
				names[ i ] = mArchiveNames[ i ].c_str();
			}
			FileIO::Manager::create( &names[ 0 ], mArchiveNumber, mLoadMode );
			//丢弃，因为不需要归档名称数组
			SAFE_DELETE_ARRAY( mArchiveNames );
			mArchiveNumber = 0;
		}else{
			FileIO::Manager::create();
		}
		//初始化绘制
		Graphics::Manager::create( windowHandle, mWidth * 2, mHeight * 2, mFullScreen, mVSync, mAntiAlias );
		//绘制文字
		//ASCII表（ASCII（126-32 + 1 = 95个字符+ 63个字符，158个字符
		Array< Scene::Font::BitmapChar > chars( 158 );
		//ASCII部分填充
		int pos = 0;
		for ( int i = 0x20; i <= 0x7E; ++i ){
			Scene::Font::BitmapChar& c = chars[ pos ];
			c.mCode = static_cast< unsigned short >( i );
			c.mX = static_cast< unsigned short >( ( i % 16 ) * 8 );
			c.mY = static_cast< unsigned short >( ( i / 16 ) * 16 );
			c.mTexturePage = 0;
			c.mWidth = 8;
			c.mHeight = 16;
			++pos;
		}
		//半角假名部分
		for ( int i = 0xA1; i <= 0xDF; ++i ){
			Scene::Font::BitmapChar& c = chars[ pos ];
			c.mCode = static_cast< unsigned short >( i );
			c.mX = static_cast< unsigned short >( ( i % 16 ) * 8 );
			c.mY = static_cast< unsigned short >( ( i / 16 ) * 16 );
			c.mTexturePage = 0;
			c.mWidth = 8;
			c.mHeight = 16;
			++pos;
		}

		ASSERT( pos == 158 );
		int textureSize = sizeof( gFontTga );
		const char* fontDataArray[ 1 ];
		fontDataArray[ 0 ] = gFontTga;
//2D图层
		m2dTexture = Graphics::Texture::create( mWidth, mHeight, false );
		Graphics::Manager().setTextureFilter( Graphics::TEXTURE_FILTER_POINT );

		mStarted = true;
	}
	unsigned time() const {
		return WindowCreator().time();
	}
	void preUpdate(){
		//帧时间更新
		unsigned currentTime = time();
		mPreviousFrameInterval = currentTime - mTimeHistory[ TIME_HISTORY_SIZE - 1 ];
		unsigned frameIntervalSum = currentTime - mTimeHistory[ 0 ];
		mFrameRate = TIME_HISTORY_SIZE * 1000 / frameIntervalSum;
		//更新历史
		for ( int i = 0; i < TIME_HISTORY_SIZE - 1; ++i ){
			mTimeHistory[ i ] = mTimeHistory[ i + 1 ]; 
		}
		mTimeHistory[ TIME_HISTORY_SIZE - 1 ] = currentTime;

		Graphics::Manager().beginDraw();
		float pointerScale;
		Vector2 pointerOffset;
		Graphics::Manager().getPointerModifier( &pointerScale, &pointerOffset );
	}
	void postUpdate(){
		//----2D处理
		//检查销毁
		for ( int i = 0; i < mWidth; ++i ){
			ASSERT( mVideoMemoryWithPadding[ i ] == MAGIC_NUMBER && "VRAM RANGE ERROR!" );
			ASSERT( mVideoMemoryWithPadding[ mWidth * ( mHeight + 1 ) + i ] == MAGIC_NUMBER && "VRAM RANGE ERROR!" );
		}
		//复制VRAM
		unsigned* dst;
		int pitch;
		m2dTexture.lock( &dst, &pitch );
		const unsigned* src = &mVideoMemoryWithPadding[ mWidth ];
		for ( int y = 0; y < mHeight; ++y ){			
			for ( int x = 0; x < mWidth; ++x ){
				dst[ x ] = 0xff000000 | src[ x ]; //强制alpha ff
			}
			src += mWidth;
			dst += pitch / 4;
		}
		src = 0; //使用终止
		m2dTexture.unlock( &dst );
		Graphics::Manager().blendToScreen( m2dTexture );
		Graphics::Manager().endDraw();
	}
	//示例类库
	Array< unsigned > mVideoMemoryWithPadding;
	Graphics::Texture m2dTexture;
	static const unsigned MAGIC_NUMBER = 0x12345678;


	int mWidth;
	int mHeight;
	bool mFullScreen;
	bool mFullScreenForbidden;
	bool mVSync;
	bool mAntiAlias;
	string mTitle;
	string* mArchiveNames;
	int mArchiveNumber;
	FileIO::Manager::AccessMode mLoadMode;
	static const int TIME_HISTORY_SIZE = 60;
	unsigned mTimeHistory[ TIME_HISTORY_SIZE ];
	int mPreviousFrameInterval;
	int mFrameRate;
	bool mEndRequested;
	bool mStarted;
};

Impl* gImpl = 0;

} //namespace{}

Framework::Framework(){
	//不允许来自其他线程的调用
	ASSERT( WindowCreator::isMainThread() && "you must call from MAIN thread" );
}

void Framework::create(){
	ASSERT( !gImpl );
	gImpl = NEW Impl();
}

void Framework::destroy(){
	SAFE_DELETE( gImpl );
}

Framework Framework::instance(){
	return Framework();
}

void Framework::start( void* windowHandle ){
	gImpl->start( windowHandle );
}

void Framework::preUpdate(){
	gImpl->preUpdate();
}

void Framework::postUpdate(){
	gImpl->postUpdate();
}

int Framework::width() const {
	return gImpl->mWidth;
}

int Framework::height() const {
	return gImpl->mHeight;
}
/*
const char* Framework::getTitle() const {
	return gImpl->mTitle.c_str();
}

bool Framework::isFullScreen() const {
	return gImpl->mFullScreen;
}

bool Framework::isFullScreenForbidden() const {
	return gImpl->mFullScreenForbidden;
}
*/
void Framework::requestEnd(){
	gImpl->mEndRequested = true;
}

bool Framework::isEndRequested() const {
	return gImpl->mEndRequested;
}

//示例类库使用的函数
unsigned* Framework::videoMemory(){
	return &gImpl->mVideoMemoryWithPadding[ gImpl->mWidth ];
}


//WindowProcedure的用户封装函数
void WindowCreator::configure( Configuration* config ){
	Framework::create();
	//用户设定
	Framework f;
//	Framework::Configuration fwConfig;
//	f.configure( &fwConfig );
	config->setWidth( f.width() * 2 );
	config->setHeight( f.height() * 2 );
	config->setTitle( "2D Graphics1 samples" );
	config->enableFullScreen( false );
	config->forbidFullScreen( true );
}

void WindowCreator::update(){
	WindowCreator wc;
	Graphics::Manager gm;
	Framework f;
	//根据WindowCreator的状态执行各种操作
	bool sleepFlag = false;
	//最小化后则休眠
	if ( wc.isMinimized() ){
		sleepFlag = true;
	}
	if ( !sleepFlag ){
		f.preUpdate();
	}
	//检查结束命令是否来自上游（例如x按钮）
	if ( isEndRequested() ){ //收到后则将终止命令发送到Framework
		f.requestEnd();
	}
	if ( sleepFlag ){
		Threading::sleep( 50 ); //睡50ms
	}else{
		f.update();
		f.postUpdate();
	}
	//结束判断
	if ( f.isEndRequested() ){
		Framework::destroy();
		end(); //让上游知道
	}
}

void WindowCreator::start( void* windowHandle ){
	Framework().start( windowHandle );
}


//StandardInput
StandardInput cin;

StandardInput::StandardInput() : mPrevEnterOn( false ){
}

//这里直接调用Windows功能
#include <windows.h>
StandardInput& StandardInput::operator>>( char& a ){
	a = '\0'; //初始值
	bool entered = false;
	while ( true ){ //无限循环
		//空格
		if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 ){
			a = ' ';
			entered = true;
		}
		//0-9
		for ( char i = '0'; i <= '9'; ++i ){
			if ( GetAsyncKeyState( i ) & 0x8000 ){
				a = i;
				entered = true;
			}
		}
		//a-z
		for ( char i = 'A'; i <= 'Z'; ++i ){
			if ( GetAsyncKeyState( i ) & 0x8000 ){
				if ( GetAsyncKeyState( VK_SHIFT ) & 0x8000 ){
					a = i;
				}else{
					a = 'a' + ( i - 'A' );
				}
				entered = true;
			}
		}
		bool enterOn = ( ( GetAsyncKeyState( VK_RETURN ) & 0x8000 ) != 0 );
		if ( entered && enterOn && !mPrevEnterOn ){
			mPrevEnterOn = enterOn;
			break;
		}
		//如果收到终止请求则退出
		bool alt = ( ( GetAsyncKeyState( VK_MENU ) & 0x8000 ) != 0 );
		bool f4 = ( ( GetAsyncKeyState( VK_F4 ) & 0x8000 ) != 0 );
		if ( alt && f4 ){
			Framework().requestEnd();
			break;
		}
		mPrevEnterOn = enterOn;
	}
	return *this;
}

} //namespace GameLib
