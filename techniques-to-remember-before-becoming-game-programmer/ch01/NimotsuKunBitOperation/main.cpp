﻿#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//函数声明
void readFile( char** buffer, int* size, const char* filename );

//二维数组类
//不知道读者是否熟悉模板的用法？如果不熟悉可能需要学习一下相关基础
//类定义中出现了T，具体使用时根据需要会被替换成int或者bool等具体类型
template< class T > class Array2D{
public:
	Array2D() : mArray( 0 ){}
	~Array2D(){
		delete[] mArray;
		mArray = 0;  //为安全起见，把指针值设为0
	}
	void setSize( int size0, int size1 ){
		mSize0 = size0;
		mSize1 = size1;
		mArray = new T[ size0 * size1 ];
	}
	T& operator()( int index0, int index1 ){
		return mArray[ index1 * mSize0 + index0 ];
	}
	const T& operator()( int index0, int index1 ) const {
		return mArray[ index1 * mSize0 + index0 ];
	}
private:
	T* mArray;
	int mSize0;
	int mSize1;
};

//状态类
class State{
public:
	State( const char* stageData, int size );
	void update( char input );
	void draw() const;
	bool hasCleared() const;
private:
	enum Object{
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,
		OBJ_UNKNOWN,

		OBJ_GOAL_FLAG = ( 1 << 7 ), //终点标记位
	};
	void setSize( const char* stageData, int size );

	int mWidth;
	int mHeight;
	Array2D< unsigned char > mObjects; //由于位运算的需要，这里使用unsigned char类型。
};

int main( int argc, char** argv ){
	const char* filename = "stageData.txt";
	if ( argc >= 2 ){
		filename = argv[ 1 ];
	}
	char* stageData;
	int fileSize;
	readFile( &stageData, &fileSize, filename );
	if ( !stageData ){
		cout << "stage file could not be read." << endl;
		return 1;
	}
	State* state = new State( stageData, fileSize );

	//主循环
	while ( true ){
		//首先绘制
		state->draw();
		//通关检测
		if ( state->hasCleared() ){
			break; //通关检测
		}
		//提示如何操作
		cout << "a:left s:right w:up z:down. command?" << endl; //操作说明
		char input;
		cin >> input;
		//刷新
		state->update( input ); 	
	}
	//打印通关祝贺的信息
	cout << "Congratulation's! you won." << endl;
	//析构
	delete[] stageData;
	stageData = 0;

	//无限循环（ctrl-C中断）
	while ( true ){
		;
	}
	return 0;
}

//---------------------下面是函数定义--------------

void readFile( char** buffer, int* size, const char* filename ){
	ifstream in( filename );
	if ( !in ){
		*buffer = 0;
		*size = 0;
	}else{
		in.seekg( 0, ifstream::end );
		*size = static_cast< int >( in.tellg() );
		in.seekg( 0, ifstream::beg );
		*buffer = new char[ *size ];
		in.read( *buffer, *size );
	}
}

State::State( const char* stageData, int size ){	
	//确保容量
	setSize( stageData, size );
	//确保空间
	mObjects.setSize( mWidth, mHeight );
	//预设初始值
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			mObjects( x, y ) = OBJ_WALL; //多余部分都设置为墙壁
		}
	}
	int x = 0;
	int y = 0;
	for ( int i = 0; i < size; ++i ){
		unsigned char t;
		switch ( stageData[ i ] ){
			case '#': t = OBJ_WALL; break;
			case ' ': t = OBJ_SPACE; break;
			case 'o': t = OBJ_BLOCK; break;
			case 'O': t = OBJ_BLOCK | OBJ_GOAL_FLAG; break;
			case '.': t = OBJ_SPACE | OBJ_GOAL_FLAG; break;
			case 'p': t = OBJ_MAN; break;
			case 'P': t = OBJ_MAN | OBJ_GOAL_FLAG; break;
			case '\n': x = 0; ++y; t = OBJ_UNKNOWN; break; //换行处理
			default: t = OBJ_UNKNOWN; break;
		}
		if ( t != OBJ_UNKNOWN ){ //这个if处理的意义在如果遇到未定义的元素值就跳过它
			mObjects( x, y ) = t; //写入
			++x;
		}
	}
}

void State::setSize( const char* stageData, int size ){
	mWidth = mHeight = 0; //初始化
	//当前位置
	int x = 0;
	int y = 0;
	for ( int i = 0; i < size; ++i ){
		switch ( stageData[ i ] ){
			case '#': case ' ': case 'o': case 'O':
			case '.': case 'p': case 'P':
				++x;
				break;
			case '\n': 
				++y;
				//更新最大值
				mWidth = max( mWidth, x );
				mHeight = max( mHeight, y );
				x = 0; 
				break;
		}
	}
}

void State::draw() const {
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			switch ( mObjects( x, y ) ){
				case ( OBJ_SPACE | OBJ_GOAL_FLAG ): cout << '.'; break;
				case ( OBJ_WALL | OBJ_GOAL_FLAG ): cout << '#'; break;
				case ( OBJ_BLOCK | OBJ_GOAL_FLAG ): cout << 'O'; break;
				case ( OBJ_MAN | OBJ_GOAL_FLAG ): cout << 'P'; break;
				case OBJ_SPACE: cout << ' '; break;
				case OBJ_WALL: cout << '#'; break;
				case OBJ_BLOCK: cout << 'o'; break;
				case OBJ_MAN: cout << 'p'; break;
			}
		}
		cout << endl;
	}
}

void State::update( char input ){
	//移动量变换
	int dx = 0;
	int dy = 0;
	switch ( input ){
		case 'a': dx = -1; break; //向左
		case 's': dx = 1; break; //右
		case 'w': dy = -1; break; //上。Y朝下为正
		case 'z': dy = 1; break; //下。
	}
	//使用较短的变量名。这里试着使用了C++中的“引用”。注意要加上const关键字
	const int& w = mWidth;
	const int& h = mHeight;
	Array2D< unsigned char >& o = mObjects;
	//查找小人的坐标
	int x, y;
	x = y = -1; //危险值
	bool found = false;
	for ( y = 0; y < h; ++y ){
		for ( x = 0; x < w; ++x ){
			if ( ( o( x, y ) & ~OBJ_GOAL_FLAG ) == OBJ_MAN ){ //为了提取出终点标志以外的部分于是使用 & ~OBJ_GOAL_FLAG
				found = true;
				break;
			}
		}
		if ( found ){
			break;
		}
	}
	//移动
	//移动后的坐标
	int tx = x + dx;
	int ty = y + dy;
	//检测坐标的极端值。确保值位于合理范围内
	if ( tx < 0 || ty < 0 || tx >= w || ty >= h ){
		return;
	}
	//A.该方向上是空白或者终点。则小人移动
	if ( ( o( tx, ty ) & ~OBJ_GOAL_FLAG ) == OBJ_SPACE ){
		o( tx, ty ) = ( o( tx, ty ) & OBJ_GOAL_FLAG ) | OBJ_MAN; //为了保存终点标志位所以需要这步麻烦的操作。下面的代码也一样
		o( x, y ) = ( o( x, y ) & OBJ_GOAL_FLAG ) | OBJ_SPACE;
	//B.如果该方向上是箱子。并且该方向的下下个格子是空白或者终点，则允许移动
	}else if ( o( tx, ty ) == OBJ_BLOCK ){
		//检测同方向上的下下个格子是否位于合理值范围
		int tx2 = tx + dx;
		int ty2 = ty + dy; 
		if ( tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h ){ //按键无效
			return;
		}
		if ( ( o( tx2, ty2 ) & ~OBJ_GOAL_FLAG ) == OBJ_SPACE ){
			//按顺序替换
			o( tx2, ty2 ) = ( o( tx2, ty2 ) & OBJ_GOAL_FLAG ) | OBJ_BLOCK;
			o( tx, ty ) = ( o( tx, ty ) & OBJ_GOAL_FLAG ) | OBJ_MAN;
			o( x, y ) = ( o( x, y ) & OBJ_GOAL_FLAG ) | OBJ_SPACE;
		}
	}
}

//只要还存在一个goalFlag值为false就不能判定为通关
bool State::hasCleared() const {
	for ( int y = 0; y < mHeight; ++y ){
		for ( int x = 0; x < mWidth; ++x ){
			if ( mObjects( x, y ) == OBJ_BLOCK ){ //没有终点标志的区块
				return false;
			}
		}
	}
	return true;
}

