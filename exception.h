#ifndef EXCEPTION
#define EXCEPTION

class Exception
{
public:
    virtual const char* what()
    {
        return "Exception caught.";
    }
};

class HeadException : public Exception
{
public:
    virtual const char* what()
    {
        return "Head exception caught.";
    }
};

class TapeException : public Exception
{
public:
    virtual const char* what()
    {
        return "Tape exception caught.";
    }
};

class ProcessingUnitException : public Exception
{
public:
    virtual const char* what()
    {
        return "Processing Unit exception caught.";
    }
};

class HeadPositionUndefined : public HeadException
{
public:
    const char* what()
    {
        return "Can't read nor write, position of head is not defined";
    }
};

#endif // EXCEPTION

