#pragma once

// #include <unordered_map>
#include "RFileUtilsLib.hpp"
#include "RJSONLexer.hpp"

enum eJSONTokenType 
{
    JSON_LBRACE,
    JSON_RBRACE,
    JSON_LBRACKET,
    JSON_RBRACKET,
    JSON_COMMA,
    JSON_COLON,
    JSON_QUOTE,
    JSON_NUMBER,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL,
    JSON_UNKNOWN,
    JSON_EOF
};

// std::unordered_map<RString, eJSONTokenType> gTokenFromLiteral = {
//     {"{",   JSON_LBRACE},
//     {"}",   JSON_RBRACE},
//     {"[",   JSON_LBRACKET},
//     {"]",   JSON_RBRACKET},
//     {",",   JSON_COMMA},
//     {":",   JSON_COLON},
//     {"\"",  JSON_QUOTE},
// };

class RJSONParser {

public:

                    RJSONParser                 (RLoader * pLoader, RJSONLexer* pLexer);
                    ~RJSONParser                ();

    bool            Parse                       ();

private:

    eJSONTokenType  InternalGetCurrTokenType    ();
    bool            InternalParseObject         ();
    bool            InternalParseObjectMembers  ();

    RLoader*        vLoader;
    RJSONLexer*     vLexer;
};