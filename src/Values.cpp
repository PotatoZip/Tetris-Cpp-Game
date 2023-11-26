#pragma once

// Windows values
const unsigned char columns{10};
const unsigned char rows{20};
const unsigned char cellPixels{9};
const unsigned char screenResizing{ 5 };

//Other values
const unsigned short frameTime{ 20000 };
const unsigned char fallingSpeed{32};
const unsigned char moveSpeed{4};
const unsigned char softDrop{4};
const unsigned char clearEffectDuration{8};
const unsigned char linesToIncreseSpeed{1};

// Structure to create vector of coordinates
struct Position {
	char x;
	char y;
};
