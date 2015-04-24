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

// TODO: consider storing the initial position of head together with the instructions.
//       Still, they are inseparable.
void TuringMachine::setTape(string pText, int pInitPos)
{
    mTape = new Tape(pText, pInitPos);
    mHead->move(mTape->getInit());
    mProcessingUnit = new ProcessingUnit(mHead, mTape, &mInstructions);
}

void TuringMachine::run()
{
    ofstream ofs("log.txt");

    // TODO: dynamically set the final state
    while (mProcessingUnit->getState() != FINAL_STATE) {
        mProcessingUnit->step();

        string output = to_string(mProcessingUnit->getState()) + '\t'
                + mTape->toStringWithCarriage(mHead->getCurrCell());

        ofs << output << endl;
    }

    ofs.close();
}

string TuringMachine::showTape() const
{
    return mTape->toString();
}
