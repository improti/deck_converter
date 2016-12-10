#include <iostream>
#include <sstream>
#include <fstream>
#include <DeckUtils.h>
#include <Mdb.h>
#include <Defines.h>



int main(int argc, char** argv)
{
    // https://www.c-plusplus.net/forum/155621-full
    string deckname;
    Mdb mdb;
#ifdef RELEASE
    // check for parameters and exit if none supplied
    if (!argv[1]) {
    	std::cerr << "ERROR: No parameters supplied, terminating.";
    	return(-1);
    }
    std::cout << "Converting: " << argv[1] << " ...\n";
    deckname = argv[1];
#else
    deckname = DEBUGDECK;
#endif
#ifdef CONVERT
    DeckUtils::convert_deck(deckname);
#endif

    // 80.000
/*
    std::ifstream in("/home/zaq/build/xmage_c/Balance.full.jpg", std::ifstream::ate | std::ifstream::binary);
    cout << in.tellg() << "\n";
    std::ifstream in2("/home/zaq/build/xmage_c/Arachnoid.full.jpg", std::ifstream::ate | std::ifstream::binary);
    cout << in2.tellg() << "\n";
    
    std:list<string> liste = mdb.getExpansionList(); 
    char a;
    
    for(std::list<string>::iterator it = liste.begin();it != liste.end();++it){
        cout << (*it) << " :"; 
        
    }
     
      */
/* #ifdef RELEASE
    if(argc < 3) {
        ss.str("");
        ss << argv[1];
        DeckUtils::saveDeck(ss.str().substr(0,ss.str().length()-4).append("_c.dck"),deck);
    } else
        DeckUtils::saveDeck(argv[2], deck);
#else
    std::cout << deck.toString();
    DeckUtils::saveDeck("test.dck", deck);
#endif
 */
    return 0;
}
