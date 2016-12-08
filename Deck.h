#ifndef DECK_H
#define DECK_H

#include<Card.h>
#include<string>
#include<sstream>
#include<map>
#include<list>


class Deck
{
public:
    Deck();
    
    void addCard(Card *card,int n,std::string praefix);
    
    void replaceCard(Card *card);
    
    void removeCard(Card *card);
    
    void setName(std::string name);
    
    std::string toString();
    
    std::list<Card*> getCardlist();
    
    ~Deck();


private: 

struct _card {
    int count;
    Card *card;
    std::string praefix;
}; 

std::string name;

std::map<string,_card> kartenliste;



};

#endif // DECK_H
