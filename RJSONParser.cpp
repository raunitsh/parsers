#include "RJSONParser.hpp"

RJSONParser::RJSONParser (RLoader* pLoader)
{
    vLoader = pLoader;
}

RJSONParser::~RJSONParser ()
{
    
}

bool
RJSONParser::Parse ()
{
        int c;
        char ch;
    
    while ((c = vLoader->ReadAndAdvance ()) != EOF)
    {
        ch = (char)c;
        
        putchar (ch);
    }

    return true;
}