#include "DeckUtils.h"
#include "ctype.h"
#include <Mdb.h>

DeckUtils::DeckUtils()
{
}

DeckUtils::~DeckUtils()
{
}

bool DeckUtils::getline(std::stringstream *buffer, std::string *contents)
{
    while(!(*buffer).eof()) {
        std::getline(*buffer, *contents);
        if((*contents).find("LAYOUT",0)&&(*contents).find("//",0)&&(*contents).find("AUTHOR:",0)&&(*contents).find("#",0)&&((*contents).length() > 1)) break;
    }
    return !(*buffer).eof();
}

void DeckUtils::saveDeck(std::string filename, Deck deck)
{
    std::ofstream ofs(filename.c_str(), std::ofstream::out);
    ofs << deck.toString();
    ofs.close();
}

Deck DeckUtils::loadDeck(std::string filename)
{
    Deck* deck = new Deck();
    std::ifstream in(filename.c_str(),std::ifstream::in);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string contents;

    while (DeckUtils::getline(&buffer,&contents)) {

        if(!contents.find("NAME:",0)) deck->setName(contents);
        else {
            string s1;
            string name, expansion, number;
            string pf = "";
            int pos, ccount;

            if (!(contents.find("SB:", 0))) {
                contents.erase(0, 4);
                pf = "SB: ";
            }
            pos = contents.find(" ");
            ccount = std::stoi(contents.substr(0, pos));
            contents.erase(0, pos + 1);
            pos = contents.find(" ");
            s1 = contents.substr(0, pos);
            contents.erase(0, pos + 1);
            if(!isspace(contents.at(contents.length()-1)))
                name = contents.substr(0, contents.length());
            else
                name = contents.substr(0, contents.length()-1);
            pos = s1.find(":");
            expansion = s1.substr(1, pos - 1);
            number = s1.substr(pos + 1, s1.length() - pos - 2);

            Card* card = new Card(name, expansion, number);
            deck->addCard(card, ccount, pf);
        }
    }

    in.close();
    return *deck;
}

Deck DeckUtils::loadDecktxt(std::string filename)
{
    Deck* deck = new Deck();
    std::ifstream in(filename.c_str(),std::ifstream::in);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string contents;
    
    filename = filename.erase(filename.length()-4, filename.length());
    filename = filename.erase(0,filename.find_last_of("/")+1);

    while (DeckUtils::getline(&buffer,&contents)) {
            string s1;
            string name="", expansion="", number="";
            string pf = "";
            int pos; 
            int ccount;
            pos = contents.find("\t");
            if(pos ==-1) pos = contents.find(" ");
            ccount = std::stoi(contents.substr(0, pos));
            contents.erase(0, pos + 1);
            if(!isspace(contents.at(contents.length()-1)))
                name = contents.substr(0, contents.length());
            else
                name = contents.substr(0, contents.length()-1);
            if(name == filename) pf = "SB: ";
            
            Card* card = new Card(name, expansion, number);
            deck->addCard(card, ccount, pf);
    }

    in.close();
    return *deck;
}

streampos DeckUtils::checkForPic(string name, string expansion)
{
    std::stringstream ss;
    
    if((name.find("//") != std::string::npos))
        name.replace(name.find("//"),2,"-");
    ss << PICTURE_DIRECTORY << expansion << "/" << name << ".full.jpg";
    std::ifstream in(ss.str(), std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


void DeckUtils::convert_deck(std::string name)
{
    Mdb mdb;
    Deck deck;
    if(name.find(".txt") != std::string::npos)
        deck = DeckUtils::loadDecktxt(name);
    else
        deck = DeckUtils::loadDeck(name);
    list<Card*> l = deck.getCardlist();
    std::stringstream ss;
    for (std::list<Card*>::iterator it = l.begin(); it != l.end(); ++it) {
        if ((*it)->GetName() == "Island" || (*it)->GetName() == "Plains" || (*it)->GetName() == "Swamp" ||
            (*it)->GetName() == "Mountain" || (*it)->GetName() == "Forest")
            	deck.replaceCard(new Card((*it)->GetName(), LANDEDITION,mdb.getCardNumber((*it)->GetName(),LANDEDITION)));
        else {
            std::multimap<std::string,std::string> mmap = mdb.getExpansionNumber((*it)->GetName());
            std::string expansion,number;
            std::stringstream exps;
            int p_size = 0;
            exps.str("");

            for(std::multimap<std::string,std::string>::iterator it_mmap = mmap.begin(); it_mmap != mmap.end(); ++it_mmap ) {
                exps << (*it_mmap).first << " ";
                int ti = DeckUtils::checkForPic((*it)->GetName(),(*it_mmap).first);
                if (ti > p_size) {
                    expansion = (*it_mmap).first;
                    number = (*it_mmap).second;
                    p_size = ti;
                }
            }
            if(p_size > 0) deck.replaceCard(new Card((*it)->GetName(),expansion,number));
            else{
                if(exps.str().length() == 0)
                    std::cout << "Karte \"" << (*it)->GetName() << "\" ist nicht implementiert.\n";
                else
                    std::cout << "Kein Bild gefunden für: " << (*it)->GetName() << " - Expansionen: " << exps.str() << "\n";
            }
        }
        ss.str("");
    }
    DeckUtils::saveDeck(name.substr(0,name.length()-4).append("_c.dck"),deck);
#ifndef RELEASE
    std::cout << deck.toString();
#endif
}
