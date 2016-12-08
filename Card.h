#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card
{
public:
    Card(string name, string expansion, string number);
    ~Card();
    
    const string& GetExpansion() const
    {
        return expansion;
    }
    const string& GetName() const
    {
        return name;
    }
    const string& GetNumber() const
    {
        return number;
    }

private:
    string name;
    string expansion;
    string number;
    

};

#endif // CARD_H
