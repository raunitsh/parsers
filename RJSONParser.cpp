#include "RJSONParser.hpp"

RJSONParser::RJSONParser (RLoader* pLoader, RJSONLexer* pLexer)
{
    vLoader = pLoader;
    vLexer = pLexer;
}

RJSONParser::~RJSONParser ()
{
    
}

bool
RJSONParser::Parse ()
{
        eJSONTokenType curr_token = InternalGetCurrTokenType ();

    if (curr_token == JSON_UNKNOWN)
    {
        return false;
    }

    if (curr_token == JSON_EOF)
    {
        return true;
    }

    // Must have an object at root level
    if (curr_token != JSON_LBRACE)
    {
        return false;
    }

    InternalParseObject ();

    return true;
}

eJSONTokenType
RJSONParser::InternalGetCurrTokenType ()
{
        int c;
        char ch;

    c = vLoader->ReadByteAndAdvance ();

    if (c == EOF)
    {
        return JSON_EOF;
    }

    ch = (char) c;

    // if (!gTokenFromLiteral.contains (ch))
    // {
    //     return JSON_UNKNOWN;
    // }

    // return gTokenFromLiteral [ch];
    return JSON_EOF;
}   

bool
RJSONParser::InternalParseObject ()
{

}

bool
RJSONParser::InternalParseObjectMembers ()
{

}