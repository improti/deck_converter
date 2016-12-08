#ifndef DECKIO_H
#define DECKIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Deck.h>
#include <Card.h>
#include <istream>
#include <Defines.h>



class DeckUtils
{
public:
    static Deck loadDeck(std::string filename);
    static Deck loadDecktxt(std::string filename);
    static void saveDeck(std::string filename, Deck deck);
    static streampos checkForPic(std::string name, std::string expansion);
    static void convert_deck(std::string name);
   

private:
    DeckUtils();
    ~DeckUtils();
     static bool getline(std::stringstream *buffer, std::string *contents);
};

#endif // DECKIO_H
