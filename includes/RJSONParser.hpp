#pragma once

// #include <unordered_map>
#include "RCppUtilsLib.hpp"
#include "RFileUtilsLib.hpp"

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
    JSON_NULL
};

// std::unordered_map<RString, eJSONTokenType> gGetTokenFromLiteral = {
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

                RJSONParser     (RLoader * pLoader);
                ~RJSONParser    ();

    bool        Parse           ();


private:

    RLoader*    vLoader;
};