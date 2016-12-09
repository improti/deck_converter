# deck_converter

This program converts decks into the format used by XMage. 
It can also automatically convert all standard land cards
of those decks to use a specific edition to match the users 
preferences.

## Notes and Limitations

The program uses a database extracted from the database used 
by XMage. This is currently not included, therefore you cannot 
use this program atm :(

At the moment you will need to define things before compilation
in the Defines.h:
* the path to the directory with the images available to you, 
  so you the program can determine what alternatives you have.
* the path to the database.
* The edition you want to use for lands. Not setting this
  will crash the program.

## Usage

deck_converter <in-file>

... where <in-file> is the file to convert.

