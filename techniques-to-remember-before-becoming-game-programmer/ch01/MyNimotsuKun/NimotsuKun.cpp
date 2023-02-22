#include <iostream>
#include <thread>

using std::cin;
using std::cout;
using std::endl;

static char board[] =
"########\n"
"# .. p #\n"
"# oo   #\n"
"#      #\n"
"########";
static int width = 8 + 1; // plus 1 for line feed
static char command = ' ';
static int row = 5;
static int col = 1;

void getInput()
{
	cout << "a:left s:right w:up z:down. command?" << endl;
	cin >> command;
}

bool isWin()
{
	for (int i = 0; board[i]; ++i) {
		if (board[i] == 'o') return false;
	}

	return true;
}

void draw()
{
	cout << board << endl;
}

char getBlock(int col, int row)
{
	int index = col * width + row;
	return board[index];
}

void setBlock(int col, int row, char c)
{
	int index = col * width + row;
	board[index] = c;
}

inline void updatePersonCoord(int xDelta, int yDelta)
{
	col += xDelta;
	row += yDelta;
}

void move(int xDelta, int yDelta)
{
	auto p = getBlock(col, row);
	auto c = getBlock(col + xDelta, row + yDelta);
	if (c == ' ' || c == '.') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col + xDelta, row + yDelta, c == ' ' ? 'p' : 'P');
		updatePersonCoord(xDelta, yDelta);
	} else if (c == 'o' || c == 'O') {
		auto c2 = getBlock(col + 2 * xDelta, row + 2 * yDelta);
		if (c2 == ' ' || c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col + xDelta, row + yDelta, c == 'o' ? 'p' : 'P');
			setBlock(col + 2 * xDelta, row + 2 * yDelta, c2 == ' ' ? 'o' : 'O');
			updatePersonCoord(xDelta, yDelta);
		}
	}
}

void moveLeft()
{
	move(0, -1);
}

void moveRight()
{
	move(0, 1);
}

void moveUp()
{
	move(-1, 0);
}

void moveDown()
{
	move(1, 0);
}

void updateGame()
{
	switch (command) {
	case 'a':
		moveLeft();
		break;
	case 's':
		moveRight();
		break;
	case 'w':
		moveUp();
		break;
	case 'z':
		moveDown();
		break;
	}
}

void pause()
{
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	draw();
	while (!isWin()) {
		getInput();
		updateGame();
		draw();
	}

	cout << "Congratulation's! you won." << endl;
	pause();
}
