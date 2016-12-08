#include "Card.h"

Card::~Card()
{
}

Card::Card(string name, string expansion, string number)
{
    this->name = name;
    this->expansion = expansion;
    this->number = number;
}
