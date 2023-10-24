#include "Framework.h"

namespace GameLib{
	void Framework::update(){
		unsigned* vram = videoMemory();
		static unsigned i;
		vram[ i ] += i * 100;
		i += 9973; //max prime number less than 10,000
		i %= ( width() * height() );
	}
}
