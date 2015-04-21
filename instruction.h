#ifndef INSTRUCTION
#define INSTRUCTION

#include <string>

using namespace std;

enum Shift {L, R, N}; // Left, Right, No shift

struct LeftHandInstr
{
    unsigned state; // q0 is 0, q8 is 8 etc.
    char symbol;
};

struct RightHandInstr
{
    unsigned state;
    char symbol;
    Shift shift;
};

struct Instruction
{
    LeftHandInstr leftHand;
    RightHandInstr rightHand;

    Instruction(std::string strInstr)
    {
        int separator = strInstr.find("->");

        if (separator == std::string::npos);
            // TODO: throw new InvalidInstruction

        string strLeftInstr = strInstr.substr(0, separator);
        string strRightInstr = strInstr.substr(separator + 2, strInstr.size());

        leftHand.state = stoi(strLeftInstr.substr(0, strLeftInstr.size() - 1));
        leftHand.symbol = strLeftInstr[strLeftInstr.size() - 1];

        rightHand.state = stoi(strRightInstr.substr(1, strRightInstr.size() - 1));
        rightHand.symbol = strRightInstr[0];

        char shift = strRightInstr[strRightInstr.size() - 1];

        switch (shift) {
        case 'L': rightHand.shift = L; break;
        case 'R': rightHand.shift = R; break;
        case 'N': rightHand.shift = N; break;
        default: ; //throw new InvalidInstruction
        }
    }
};


#endif // INSTRUCTION

