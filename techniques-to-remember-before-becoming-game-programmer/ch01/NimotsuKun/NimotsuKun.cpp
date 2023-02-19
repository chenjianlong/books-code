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

void moveLeft()
{
	auto p = getBlock(col, row);
	auto c = getBlock(col, row - 1);
	if (c == ' ') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col, row - 1, 'p');
		--row;
	} else if (c == '.') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col, row - 1, 'P');
		--row;
	} else if (c == 'o') {
		auto c2 = getBlock(col, row - 2);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row - 1, 'p');
			setBlock(col, row - 2, 'o');
			--row;
		} else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row - 1, 'p');
			setBlock(col, row - 2, 'O');
			--row;
		}
	} else if (c == 'O') {
		auto c2 = getBlock(col, row - 2);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row - 1, 'P');
			setBlock(col, row - 2, 'o');
			--row;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row - 1, 'P');
			setBlock(col, row - 2, 'O');
			--row;
		}
	}
}

void moveRight()
{
	auto p = getBlock(col, row);
	auto c = getBlock(col, row + 1);
	if (c == ' ') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col, row + 1, 'p');
		++row;
	}
	else if (c == '.') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col, row + 1, 'P');
		++row;
	}
	else if (c == 'o') {
		auto c2 = getBlock(col, row + 2);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row + 1, 'p');
			setBlock(col, row + 2, 'o');
			++row;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row + 1, 'p');
			setBlock(col, row + 2, 'O');
			++row;
		}
	}
	else if (c == 'O') {
		auto c2 = getBlock(col, row + 2);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row + 1, 'P');
			setBlock(col, row + 2, 'o');
			++row;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col, row + 1, 'P');
			setBlock(col, row + 2, 'O');
			++row;
		}
	}
}

void moveUp()
{
	auto p = getBlock(col, row);
	auto c = getBlock(col - 1, row);
	if (c == ' ') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col - 1, row, 'p');
		--col;
	}
	else if (c == '.') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col - 1, row, 'P');
		--col;
	}
	else if (c == 'o') {
		auto c2 = getBlock(col - 2, row);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col - 1, row, 'p');
			setBlock(col - 2, row, 'o');
			--col;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col - 1, row, 'p');
			setBlock(col - 2, row, 'O');
			--col;
		}
	}
	else if (c == 'O') {
		auto c2 = getBlock(col - 2, row);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col - 1, row, 'P');
			setBlock(col - 2, row, 'o');
			--col;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col - 1, row, 'P');
			setBlock(col - 2, row, 'O');
			--col;
		}
	}
}

void moveDown()
{
	auto p = getBlock(col, row);
	auto c = getBlock(col + 1, row);
	if (c == ' ') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col + 1, row, 'p');
		++col;
	}
	else if (c == '.') {
		setBlock(col, row, p == 'P' ? '.' : ' ');
		setBlock(col + 1, row, 'P');
		++col;
	}
	else if (c == 'o') {
		auto c2 = getBlock(col + 2, row);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col + 1, row, 'p');
			setBlock(col + 2, row, 'o');
			++col;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col + 1, row, 'p');
			setBlock(col + 2, row, 'O');
			++col;
		}
	}
	else if (c == 'O') {
		auto c2 = getBlock(col + 2, row);
		if (c2 == ' ') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col + 1, row, 'P');
			setBlock(col + 2, row, 'o');
			++col;
		}
		else if (c2 == '.') {
			setBlock(col, row, p == 'P' ? '.' : ' ');
			setBlock(col + 1, row, 'P');
			setBlock(col + 2, row, 'O');
			++col;
		}
	}
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
