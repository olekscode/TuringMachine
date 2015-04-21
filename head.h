#ifndef HEAD_H
#define HEAD_H

#include "exception.h"
class Head
{
    char *mCurrSymbol;

public:
    Head() = default;

    void moveTo(char *pSymbol);

    char read() const;
    void write(char pChar);
};

#endif // HEAD_H
