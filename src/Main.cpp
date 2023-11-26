#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tetromino.cpp"
#include "Values.cpp"

using namespace sf;
using namespace std;
using namespace chrono;

int main() {

	//Necessary values
	bool gameOver{ 0 };															 //Checking weather game is over or not
	bool rotatePressed{ 0 };													 //Checking weather A or D is pressed or not
	unsigned lag{ 0 };															 //For time ilusion
	unsigned linesCleared{ 0 };													 //Count of cleared lines
	unsigned char currentSpeed = fallingSpeed;									 //Speed of tetromino
	unsigned char moveTimer{ 0 };												 //Time of tetromino moving
	unsigned char nextShape{};												     //Just next shape
	unsigned char softDropTime{ 0 };											 //Time of tetromino soft drop
	unsigned char fallTimer{ 0 };													 //Time of tetromino falling
	unsigned char clearEffectTimer{ 0 };											 //Time of row clearing
	vector<bool> clearLines(rows, 0);                                            //Store information whether a row should be cleared or not (All rows are set to 0 defaulty)
	vector<vector<unsigned char>> matrix(columns, vector<unsigned char>(rows));  //Just matrix of rows and columns

	// Vector of SFML Colors
	vector<Color> cellColor = {
		Color(55,55,55),     //Grey
		Color(0,225,0),      //Green
		Color(0,0,255),      //Blue
		Color(255,0,0),      //Red
		Color(255,255,0),    //Yellow
		Color(255,0,255),    //Magenta
		Color(0,255,255),    //Cyan
		Color(0,0,0),        //Black
		Color(255,255,255)   //White
	};

	//Random number generator
	random_device randomDevice;
	default_random_engine randomEngine(randomDevice());
	uniform_int_distribution<unsigned short> shapeDistribution(0, 6);
	nextShape = static_cast<unsigned char>(shapeDistribution(randomEngine));

	//Tetromino object
	Tetromino tetromino(static_cast<unsigned char>(shapeDistribution(randomEngine)), matrix);

	//Generates Tetris window
	Event event;
	RenderWindow window(VideoMode(cellPixels * columns * screenResizing, cellPixels * rows * screenResizing), "Tetris", Style::Close); //Window render
	window.setView(View(FloatRect(0, 0, cellPixels * columns, cellPixels * rows)));                                                   //Resizing of window

	//Time counting
	time_point<steady_clock> previosTime;
	previosTime = steady_clock::now();

	//Infinite loop to run game
	while (window.isOpen()) {
		//Count difference between frames
		unsigned deltaTime = duration_cast<chrono::microseconds>(steady_clock::now() - previosTime).count();
		lag += deltaTime;
		previosTime += chrono::microseconds(deltaTime);

		while (lag >= frameTime) {
			lag -= frameTime;

			while (window.pollEvent(event)) {
				switch (event.type) {
					// Game closed
				case Event::Closed: {
					window.close();
					break;
				}
								  // Key pressed
				case Event::KeyReleased:
					switch (event.key.code) {
					case Keyboard::A: {
						rotatePressed = 0;
						break;
					}
					case Keyboard::D: {
						rotatePressed = 0;
						break;
					}
					case Keyboard::Down: {
						softDropTime = 0;
						break;
					}
					case Keyboard::Left: {
						moveTimer = 0;
						break;
					}
					case Keyboard::Right: {
						moveTimer = 0;
					}
					}
				}
			}

			if (clearEffectTimer == 0) {
				if (gameOver == 0) {
					if (rotatePressed == 0) {
						if (Keyboard::isKeyPressed(Keyboard::A) == 1) {
							rotatePressed = 1;
							tetromino.rotate(0, matrix);
						}
						else if (Keyboard::isKeyPressed(Keyboard::D) == 1) {
							rotatePressed = 1;
							tetromino.rotate(1, matrix);
						}
					}

					if (moveTimer == 0) {
						if (Keyboard::isKeyPressed(Keyboard::Left) == 1) {
							moveTimer = 1;
							tetromino.moveLeft(matrix);
						}
						else if (Keyboard::isKeyPressed(Keyboard::Right) == 1) {
							moveTimer = 1;
							tetromino.moveRight(matrix);
						}
					}
					else {
						moveTimer = (1 + moveTimer) % moveSpeed;
					}

					if (softDropTime == 0) {
						if (Keyboard::isKeyPressed(Keyboard::Down) == 1) {
							if (tetromino.moveDown(matrix) == 1) {
								fallTimer = 0;
								softDropTime = 1;
							}
						}
					}
					else {
						softDropTime = (1 + softDropTime) % softDrop;
					}

					if (fallingSpeed == fallTimer) {
						// Checking wheather we can move down or not
						if (tetromino.moveDown(matrix) == 0) {
							// Add tetromino to matrix
							tetromino.updateMatrix(matrix);

							// In this loop we are checking wheather we should clear a row or not
							for (unsigned char a = 0; a < rows; a++) {
								// Let's suppose that we need to clear it
								bool clearLine = 1;

								// And now we check 
								for (unsigned char b = 0; b < columns; b++) {
									//Checking all cells in the row
									if (matrix[b][a] == 0) {
										clearLine = 0;
										break;
									}
								}

								//If we have to clear a row
								if (clearLine == 1) {
									//Setting time for clearing effect
									clearEffectTimer = clearEffectDuration;

									//Row that must be cleared
									clearLines[a] = 1;

									//Score increse
									linesCleared++;
								}
							}

							//If the effect timer is over
							if (clearEffectTimer == 0) {
								//Decide if the game is over or not based on the return value of the reset function
								//Yes I know I could use "!" but it looks ugly and I hate using it!
								gameOver = 0 == tetromino.reset(nextShape, matrix);

								//Generate the next shape
								nextShape = static_cast<unsigned char>(shapeDistribution(randomEngine));
							}
						}

						//Restart the fall timer
						fallTimer = 0;
					}
					else {
						//Increment the fall timer
						fallTimer++;
					}
				}
				//Restarting game
				else if (Keyboard::isKeyPressed(sf::Keyboard::Enter) == 1) {
					//Reseting values
					gameOver = 0;
					rotatePressed = 0;
					linesCleared = 0;
					currentSpeed = fallingSpeed;
					fallTimer = 0;
					moveTimer = 0;
					softDropTime = 0;

					//Matrix clear
					for (vector<unsigned char>& a : matrix)
					{
						fill(a.begin(), a.end(), 0);
					}
				}
			}

			else {
				//Decrement the effect timer
				clearEffectTimer--;

				//If the effect timer is between 1 and -1
				if (0 == clearEffectTimer) {
					//Loop through each row
					for (unsigned char a = 0; a < rows; a++) {
						//If the row should be cleared
						if (clearLines[a] == 1) {
							//Loop through each cell in the row
							for (unsigned char b = 0; b < columns; b++) {
								//Set the cell to 0 (empty) (the absence of existence)
								matrix[b][a] = 0;

								//Swap the row with the rows above
								for (unsigned char c = a; 0 < c; c--) {
									matrix[b][c] = matrix[b][c - 1];
									matrix[b][c - 1] = 0;
								}
							}
						}
					}

					//I already explained this earlier and I don't wanna do it again
					gameOver = 0 == tetromino.reset(nextShape, matrix);

					nextShape = static_cast<unsigned char>(shapeDistribution(randomEngine));

					//Clear the clear lines array
					fill(clearLines.begin(), clearLines.end(), 0);
				}
			}
			//Drawing
			if (frameTime > lag) {

				unsigned char clearCellSize = static_cast<unsigned char>(2 * round(0.5f * cellPixels * (clearEffectTimer / static_cast<float>(clearEffectDuration))));

				//Object to draw cell
				RectangleShape cell(Vector2f(cellPixels - 1, cellPixels - 1));

				//First we have to clear everything from last frame
				window.clear();

				//Draw matrix
				for (float a = 0; a < columns; a++) {
					for (float b = 0; b < rows; b++) {
						//If the cell is clear
						if (clearLines[b] == 0) {
							cell.setPosition(static_cast<float>(cellPixels * a), static_cast<float>(cellPixels * b));

							//Turns everything into red
							if (gameOver == 1 && matrix[a][b] > 0) {
								cell.setFillColor(cellColor[3]);
							}
							//Set color of found tetromino
							else {
								cell.setFillColor(cellColor[matrix[a][b]]);
							}
							window.draw(cell);
						}
					}
				}

				cell.setFillColor(cellColor[3]);

				if (gameOver == 0) {
					cell.setFillColor(cellColor[1 + tetromino.getShape()]);
				}

				for (Position& mino : tetromino.getMinos()) {
					cell.setPosition(static_cast<float>(cellPixels * mino.x), static_cast<float>(cellPixels * mino.y));
					window.draw(cell);
				}

				cell.setFillColor(cellColor[1 + nextShape]);
				cell.setSize(sf::Vector2f(cellPixels - 1, cellPixels - 1));

				window.display();
			}
		}
	}

	return 0;
}
