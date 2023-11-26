# Tetris - C++ Game

This is Tetris game designed and implemented with SFML library that provides a simple graphical user interface. The game uses tetromino system that includes 7 block shapes and define their behaviour.

## Installation

First of all clone this repository to your local pc. Then visit [SFML](https://www.sfml-dev.org/index.php) website and download library (make note that project was created with SFML 2.5.0). Finally you need to paste necessary files in places depending on what environment you will work in (here is some help for visual studio: https://www.youtube.com/watch?v=lFzpkvrscs4). Also you can check TestSFML folder in which I created visual studio project with SFML files.

## Usage

After launching the game it will automatically start running in designed window. The main goal of a player is to arrange falling blocks so they will fit without any gaps on a floor. You can interact with falling blocks with keyboard by using:
<br />
"A" - rotates tetromino by -90 degree <br />
"D" - rotates tetromino by 90 degree <br />
"S" - immediately move tetromino block into the floor <br />
"Page Left" - move tetromino block to the left <br />
"Page Right" - move tetromino block to the right
<br />
If you manage to fill a whole vertical level with blocks it will clear this area meaning you scored points. The game ends if your lying blocks touch a roof of a board. 

## Future development

- Add score display
- Add new levels
- Add menu

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

This project is licensed under the [MIT](https://choosealicense.com/licenses/mit/) license, feel free to use it.