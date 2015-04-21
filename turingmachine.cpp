#include "turingmachine.h"

TuringMachine::TuringMachine()
{
    mHead = new Head();
    mTape = new Tape();
    mProcessingUnit = new ProcessingUnit(mHead, mTape, &mInstructions);
}

TuringMachine::~TuringMachine()
{
    delete mHead;
    delete mTape;
    delete mProcessingUnit;
}

void TuringMachine::loadInstructionsFromFile(string pPath)
{
    ifstream ifs(pPath);

    if (!ifs) {
        // TODO: throw an Exception
    }

    string lineBuff;

    while (!ifs.eof()) {
        getline(ifs, lineBuff);

        if (lineBuff != "")
            mInstructions.push_back(Instruction(lineBuff));
    }

    ifs.close();
}

void TuringMachine::setTape(string pText)
{
    mTape->setText(pText.c_str(), pText.size());
    // TODO: set initial position
    mHead->moveTo(&(*mTape)[0]);
}

void TuringMachine::run()
{
    ofstream ofs("log.txt");

    // TODO: set final state
    while (mProcessingUnit->getState() != 100) {
        mProcessingUnit->step();

        string output = to_string(mProcessingUnit->getState()) + '\t';
        string currTape = mTape->getText();

        for (int i = 0; i < currTape.size(); ++i) {
            if (i == mProcessingUnit->getCurrHeadPosition() + mTape->getOffset()) {
                output += '[';
            }
            else if (i == mProcessingUnit->getCurrHeadPosition() + mTape->getOffset() + 1) {
                output += ']';
            }
            else {
                output += ' ';
            }

            output += currTape[i];
        }
        if (mProcessingUnit->getCurrHeadPosition() + mTape->getOffset() == currTape.size() - 1) {
            output += ']';
        }

        ofs << output << endl;
    }

    ofs.close();
}

string TuringMachine::showTape() const
{
    return mTape->getText();
}
