#ifndef ALTTAPE
#define ALTTAPE

#include <string>
#include <QDebug>

using namespace std;

class TapeCell
{
public:
    char value;
    TapeCell* next;
    TapeCell* prev;

    TapeCell(char pValue);
};

class Tape
{
    TapeCell* initCell;

    static const char BLANC_SYMBOL = 'E';

public:
    Tape(string pText = "", int pInitPos = 0);
    ~Tape();

    TapeCell* getInit() const;

    TapeCell* getRight(TapeCell* pCurr);
    TapeCell* getLeft(TapeCell* pCurr);

    string toString() const;
    string toStringWithCarriage(TapeCell* pCurr) const;

    bool isEmpty() const;
    void clear();
};

#endif // ALTTAPE

