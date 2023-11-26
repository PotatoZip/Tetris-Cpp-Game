#include <vector>
#include "Values.cpp"
using namespace std;

class WallKick {

public:

	//Rotation System based on SRS system using in the current Tetris Guideline
	//Source: https://tetris.fandom.com/wiki/SRS

	vector<Position> getWallKickData(bool Ishape, unsigned char currentRotation, unsigned char nextRotation) {
		
		// If current shape is different from "I"
		if (Ishape == 0) {
			switch (currentRotation) {
			case 0: {
				switch (nextRotation) {
				case 1: {
					return { {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
				}
				case 3: {
					return { {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2} };
				}
				}
			}
			case 1: {
				return { {0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2} };
			}
			case 2: {
				switch (nextRotation) {
				case 1: {
					return { {0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
				}
				case 3: {
					return { {0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2} };
				}
				}
			}
			case 3: {
				return { {0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
			}
			}

			return { {0, 0} };
		}

		// When shape is "I"
		else {
			switch (currentRotation) {
			case 0: {
				switch (nextRotation) {
				case 1: {
					return { {0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2} };
				}
				case 3: {
					return { {0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1} };
				}
				}
			}
			case 1: {
				switch (nextRotation) {
				case 0: {
					return { {0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2} };
				}
				case 2: {
					return { {0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1} };
				}
				}
			}
			case 2: {
				switch (nextRotation) {
				case 1: {
					return { {0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1} };
				}
				case 3: {
					return { {0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2} };
				}
				}
			}
			case 3: {
				switch (nextRotation) {
				case 0: {
					return { {0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1} };
				}
				case 2: {
					return { {0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2} };
				}
				}
			}
			}

			return { {0, 0} };
		}
	}
};