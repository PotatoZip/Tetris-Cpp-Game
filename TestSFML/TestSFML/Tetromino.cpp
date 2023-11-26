#include <vector>
#include "WallKick.cpp"
#include "Values.cpp"

using namespace std;

class Tetromino {

//Wall kick object
WallKick wallKick;

private:

	unsigned char rotation;
	unsigned char shape;
	vector<Position> minos;

public:

	// Constructor
	Tetromino(unsigned char tshape, const vector<vector<unsigned char>> tmatrix) :

		rotation(0),
		shape(tshape),
		minos(getTetromino(tshape, columns / 2, 1))
	{}

	//Vector of tetrominos
	vector<Position> getTetromino(unsigned char tshape, unsigned char tx, unsigned char ty) {
		vector<Position> tetromino(4);

		// Here I have all tetrominos positions
		switch (tshape) {
			// L shape
		case 0: {
			tetromino[0] = { 0,0 };
			tetromino[1] = { 1,0 };
			tetromino[2] = { -1,-1 };
			tetromino[3] = { -1,0 };
			break;
		}
			// I shape
		case 1: {
			tetromino[0] = { 1,-1 };
			tetromino[1] = { 0,-1 };
			tetromino[2] = { -1,-1 };
			tetromino[3] = { -2,-1 };
			break;
		}
			// J shape
		case 2: {
			tetromino[0] = { 0,0 };
			tetromino[1] = { 1,0 };
			tetromino[2] = { 1,-1 };
			tetromino[3] = { -1,0 };
			break;
		}
			// O shape
		case 3: {
			tetromino[0] = { 0,0 };
			tetromino[1] = { 0,-1 };
			tetromino[2] = { -1,-1 };
			tetromino[3] = { -1,0 };
			break;
		}
			// Z shape
		case 4: {
			tetromino[0] = { 0,0 };
			tetromino[1] = { 1,-1 };
			tetromino[2] = { 0,-1 };
			tetromino[3] = { -1,0 };
			break;
		}
			// T shape
		case 5: {
			tetromino[0] = { 0,0 };
			tetromino[1] = { 1,0 };
			tetromino[2] = { 0,-1 };
			tetromino[3] = { -1,0 };
			break;
		}
			// S shape
		case 6: {
			tetromino[0] = { 0,0 };
			tetromino[1] = { 1,0 };
			tetromino[2] = { 0,-1 };
			tetromino[3] = { -1,-1 };
		}
		}

		for (Position& mino : tetromino) {
			mino.x += tx;
			mino.y += ty;
		}

		return tetromino;
	}

	// Getter of shape
	unsigned char getShape() {
		return shape;
	}

	// Moving down
	bool moveDown(const vector<vector<unsigned char>>& tmatrix) {
		//Checking weather moving down is possible or not
		for (Position& mino : minos) {
			//Moving from matrix
			if (1 + mino.y == rows) {
				return 0;
			}
			//Hitting another tetromino
			if(tmatrix[mino.x][1 + mino.y] > 0) {
				return 0;
			}
		}
		//Moving tetromino down
		for (Position& mino : minos) {
			mino.y++;
		}

		return 1;
	}

	//Moving left
	void moveLeft(const vector<vector<unsigned char>>& tmatrix) {
		//Checking weather moving left is possible or not
		for (Position& mino : minos) {
			if (mino.x - 1 < 0) {
				return;
			}

			if (mino.y < 0) {
				continue;
			}
			else if (tmatrix[mino.x - 1][mino.y] > 0) {
				return;
			}
		}
		// Moving tetromino left
		for (Position& mino : minos) {
			mino.x--;
		}
	}

	// Moving right
	void moveRight(const vector<vector<unsigned char>>& tmatrix) {
		//Checking weather moving right is possible or not
		for (Position& mino : minos) {
			if (1 + mino.x == columns) {
				return;
			}

			if (mino.y < 0) {
				continue;
			}
			else if (tmatrix[1 + mino.x][mino.y] > 0) {
				return;
			}
		}
		// Moving tetromino right
		for (Position& mino : minos) {
			mino.x++;
		}
	}

	// Updating matrix
	void updateMatrix(vector<vector<unsigned char>>& tmatrix) {
		for (Position& mino : minos) {
			if (mino.y < 0) {
				continue;
			}
			tmatrix[mino.x][mino.y] = 1 + shape;
		}
	}
	
	// Reseting
	bool reset(unsigned char tshape, const vector<vector<unsigned char>>& tmatrix) {

		rotation = 0;
		shape = tshape;
		minos = getTetromino(shape, columns / 2, 1);

		for (Position& mino : minos) {
			if (tmatrix[mino.x][mino.y] > 0) {
				return 0;
			}
		}

		return 1;
	}

	// Getter of minos
	vector<Position> getMinos() {
		return minos;
	}

	// Rotation 
	void rotate(bool tclockwise, const vector<vector<unsigned char>>& tmatrix) {
		// We can't rotate O shape so the function only works if shape != 3
		if (shape != 3) {
			unsigned char nextRotation{};

			vector<Position> currentMinos = minos;

			//Calculating the next rotation state
			if (tclockwise == 0) {
				nextRotation = (3 + rotation) % 4;
			}
			else {
				nextRotation = (1 + rotation) % 4;
			}

			//If it's the I shape
			if (shape == 0) {
				//We find it's center
				float centerX = 0.5f * (minos[1].x + minos[2].x);
				float centerY = 0.5f * (minos[1].y + minos[2].y);

				switch (rotation) {
				case 0: {
					centerY += 0.5f;

					break;
				}
				case 1: {
					centerX -= 0.5f;

					break;
				}
				case 2: {
					centerY -= 0.5f;

					break;
				}
				case 3: {
					centerX += 0.5f;
				}
				}

				//Then we rotate every mino based on the center
				for (Position& mino : minos) {
					//We find the position of the mino relative to the center
					float x = mino.x - centerX;
					float y = mino.y - centerY;

					if (0 == tclockwise) {
						mino.x = static_cast<char>(centerX + y);
						mino.y = static_cast<char>(centerY - x);
					}
					else {
						mino.x = static_cast<char>(centerX - y);
						mino.y = static_cast<char>(centerY + x);
					}
				}
			}

			//For all other shapes
			else {
				//We don't rotate the mino that's located at the center of rotation
				for (unsigned char a = 1; a < minos.size(); a++) {
					//We find the position of the mino relative to the central mino
					char x = minos[a].x - minos[0].x;
					char y = minos[a].y - minos[0].y;

					if (0 == tclockwise) {
						minos[a].x = y + minos[0].x;
						minos[a].y = minos[0].y - x;
					}
					else {
						minos[a].x = minos[0].x - y;
						minos[a].y = x + minos[0].y;
					}
				}
			}

			//We try every vector from the wall kick data
			for (Position& wall_kick : wallKick.getWallKickData(0 == shape, rotation, nextRotation)) {
				bool canTurn = 1;

				for (Position& mino : minos) {
					//Here we're checking every collision that can happen
					if (0 > mino.x + wall_kick.x || columns <= mino.x + wall_kick.x || rows <= mino.y + wall_kick.y) {
						canTurn = 0;

						break;
					}

					if (0 > mino.y + wall_kick.y) {
						continue;
					}
					else if (0 < tmatrix[mino.x + wall_kick.x][mino.y + wall_kick.y]) {
						canTurn = 0;

						break;
					}
				}

				//If we can turn
				if (1 == canTurn) {
					//We turn
					rotation = nextRotation;

					for (Position& mino : minos) {
						mino.x += wall_kick.x;
						mino.y += wall_kick.y;
					}

					return;
				}
			}

			//Since we applied changes to the minos array, we're resetting it when we can't rotate the tetromino
			minos = currentMinos;
		}
	}
};