#ifndef TAPE_H
#define TAPE_H

class Tape
{
    char* mTape;
    int mSize;
    int mOffset;

    // Symbol that represents an empty character
    static const char emptyChar = 'E';

public:
    Tape();

    // pInitPos is the index that represents the initial position of Head
    // pInit is the length of pText
    void setText(const char* pText, int pSize, int pInitPos = 0);

    // Makes Tape infinite by automatically expanding mTape
    // Indices are calculated using the offset (therefore they never change)
    //
    // e.g. Consider the following code
    // Tape tape("11*111", 6, 0);
    // tape[-2] = '*'; // mTape == "*E11*111", mOffset == 2
    // tape[0] = '*'; // mTape == "*E*1*111" (mTape[0 + 2])
    char& operator [] (int pIndex);

    // returns the current state of tape as text
    const char* getText();

    // returns the number of characters from first non-empty
    // to last non-empty character
    int getSize() const;

    // TODO: Remove this
    int getOffset() const;

    // TODO: implement these
    bool isEmpty() const;
    void clear();

private:
    void shrinkToFit(int &pIndex);
};

#endif // TAPE_H
