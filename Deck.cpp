#include "Deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
}

void Deck::setName(std::string name)
{
    this->name = name;
}
void Deck::addCard(Card* card, int n, std::string praefix)
{
    if (kartenliste.count(card->GetName()) > 0) {
        kartenliste[card->GetName()].count += n;
    } else {
        _card* newcard = new _card();
        newcard->card = card;
        newcard->count = n;
        newcard->praefix = praefix;
        kartenliste[card->GetName()] = *newcard;
    }
}
std::string Deck::toString()
{
    std::stringstream ss;
    ss << this->name << "\n";
    for (std::map<string, _card>::iterator it = kartenliste.begin(); it != kartenliste.end(); ++it) {
        ss << (it->second).praefix << std::to_string((it->second).count) << " [" << ((it->second).card)->GetExpansion()
           << ":" << ((it->second).card)->GetNumber() << "] " << ((it->second).card)->GetName() << "\n";
    }
    return ss.str();
}
std::list<Card*> Deck::getCardlist()
{
    list<Card*> l;
    for (std::map<string, _card>::iterator it = kartenliste.begin(); it != kartenliste.end(); ++it)
        l.push_front(it->second.card);
    return l;
}
void Deck::replaceCard(Card* card)
{
    // delete (kartenliste[card->GetName()]).card;
    (kartenliste[card->GetName()]).card = card;
}
