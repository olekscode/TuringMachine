#include "tape.h"

TapeCell::TapeCell(char pValue)
    : value(pValue) {}

// Could be shortened a bit
// Could be optimized
// TODO: Check if pText is not empty (consider the posibility
//       of creating empty tapes)
Tape::Tape(string pText, int pInitPos)
{
    // if the initial position of head is after the last non-empty cell
    if (pInitPos >= (int) pText.size()) {
        initCell = new TapeCell(BLANC_SYMBOL);
        TapeCell* curr = initCell;

        // the tail of list
        curr->next = new TapeCell('\0');
        curr->next->prev = curr;

        if (pText.size() != 0) {
            // write BLANK_SYMBOL into every cell from the initial head position
            // to the last non-empty character
            for (int i = pInitPos - 1; i >= (int) pText.size(); --i) {
                curr->prev = new TapeCell(BLANC_SYMBOL);
                curr->prev->next = curr;
                curr = curr->prev;
            }
        }

        // write the text
        for (int i = (int) pText.size() - 1; i >= 0; --i) {
            curr->prev = new TapeCell(pText[i]);
            curr->prev->next = curr;
            curr = curr->prev;
        }

        // the head of list
        curr->prev = new TapeCell('\0');
        curr->prev->next = curr;
    }
    // if the initial position of head is before the first non-empty cell
    else if (pInitPos < 0) {
        initCell = new TapeCell(BLANC_SYMBOL);
        TapeCell* curr = initCell;

        // the head of list
        curr->prev = new TapeCell('\0');
        curr->prev->next = curr;

        if (pText.size() != 0) {
            // write BLANK_SYMBOL into every cell from the initial head position
            // to the first non-empty character
            for (int i = pInitPos + 1; i < 0; ++i) {
                curr->next = new TapeCell(BLANC_SYMBOL);
                curr->next->prev = curr;
                curr = curr->next;
            }
        }

        // write the text
        for (int i = 0; i < (int) pText.size(); ++i) {
            curr->next = new TapeCell(pText[i]);
            curr->next->prev = curr;
            curr = curr->next;
        }

        // the tail of list
        curr->next = new TapeCell('\0');
        curr->next->prev = curr;
    }
    // if the initial position of head is between
    // the first and the last non-empty cells
    else {
        initCell = new TapeCell(pText[pInitPos]);

        TapeCell* curr = initCell;

        // write the text from the initial head position to the first
        // non-empty character
        for (int i = pInitPos - 1; i >= 0; --i) {
            curr->prev = new TapeCell(pText[i]);
            curr->prev->next = curr;
            curr = curr->prev;
        }

        // the head of list
        curr->prev = new TapeCell('\0');
        curr->prev->next = curr;

        curr = initCell;

        // write the text from the initial head position to the last
        // non-empty character
        for (int i = pInitPos + 1; i < (int) pText.size(); ++i) {
            curr->next = new TapeCell(pText[i]);
            curr->next->prev = curr;
            curr = curr->next;
        }

        // the tail of list
        curr->next = new TapeCell('\0');
        curr->next->prev = curr;
    }
}

Tape::~Tape()
{
    // need to reach the first non-empty cell
    TapeCell* curr = initCell->prev;

    while (curr->value != '\0') {
        curr = curr->prev;
    }

    // now delete all the succeding cells
    curr = curr->next;
    delete curr->prev;

    while (curr->value != '\0') {
        curr = curr->next;
        delete curr->prev;
    }

    delete curr;
}

TapeCell* Tape::getInit() const
{
    return initCell;
}

TapeCell* Tape::getRight(TapeCell *pCurr)
{
    // if the head is being moved from the first/last empty cell, it should be deleted
    // e.g. this is fine: 1[1]1.*.1.1.1, [E]1.1.*.1.1.1
    //      but this isn't: E[1]1.*.1.1.1
    if (pCurr->prev->value == '\0' && pCurr->value == BLANC_SYMBOL) {
        delete pCurr->prev;
        pCurr->prev = nullptr;
        pCurr->value = '\0';

        if (initCell == pCurr) {
            initCell = initCell->next;
        }
    }

    pCurr = pCurr->next;

    // expanding the tape
    if (pCurr->value == '\0') {
        pCurr->value = BLANC_SYMBOL;
        pCurr->next = new TapeCell('\0');
        pCurr->next->prev = pCurr;
    }

    return pCurr;
}

TapeCell* Tape::getLeft(TapeCell *pCurr)
{
    // if the head is being moved from the first/last empty cell, it should be deleted
    // e.g. this is fine: 1[1]1.*.1.1.1, [E]1.1.*.1.1.1
    //      but this isn't: E[1]1.*.1.1.1
    if (pCurr->next->value == '\0' && pCurr->value == BLANC_SYMBOL) {
        delete pCurr->next;
        pCurr->next = nullptr;
        pCurr->value = '\0';

        if (initCell == pCurr) {
            initCell = initCell->prev;
        }
    }

    pCurr = pCurr->prev;

    // expanding the tape
    if (pCurr->value == '\0') {
        pCurr->value = BLANC_SYMBOL;
        pCurr->prev = new TapeCell('\0');
        pCurr->prev->next = pCurr;
    }

    return pCurr;
}

string Tape::toString() const
{
    // need to reach the first non-empty cell
    TapeCell* curr = initCell->prev;

    while (curr->value != '\0') {
        curr = curr->prev;
    }

    curr = curr->next;

    string text = "";

    while (curr->value != '\0') {
        text += curr->value;
        curr = curr->next;
    }

    return text;
}

string Tape::toStringWithCarriage(TapeCell *pCurr) const
{
    // need to reach the first non-empty cell
    TapeCell* curr = initCell->prev;

    while (curr->value != '\0') {
        curr = curr->prev;
    }

    curr = curr->next;

    string text = "";

    while (curr != pCurr) {
        if (curr->value == '\0') {
            // throw sth
        }

        text += '.';
        text += curr->value;
        curr = curr->next;
    }

    text += string("[") + curr->value + ']';
    curr = curr->next;

    while (curr->value != '\0') {
        text += curr->value;
        text += '.';
        curr = curr->next;
    }

    return text;
}

bool Tape::isEmpty() const
{
    return initCell->value == BLANC_SYMBOL
        && initCell->prev->value == '\0'
        && initCell->next->value == '\0';
}

void Tape::clear()
{
    // need to reach the first non-empty cell
    TapeCell* curr = initCell->prev;

    while (curr->value != '\0') {
        curr = curr->prev;
    }

    curr = curr->next;
    initCell = curr;
    initCell->value = BLANC_SYMBOL;

    // to delete everything we're leaving behind
    if (curr->next->value != '\0') {
        curr = curr->next->next;

        do {
            delete curr->prev;
            curr = curr->next;
        } while (curr->value != '\0');

        delete curr->prev;
        initCell->next = curr;
    }
}
