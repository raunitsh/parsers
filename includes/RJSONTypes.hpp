#pragma once

#include <unordered_map>

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

inline std::unordered_map<char, eJSONTokenType> gTokenFromLiteral = 
{
    {'{',   JSON_LBRACE},
    {'}',   JSON_RBRACE},
    {'[',   JSON_LBRACKET},
    {']',   JSON_RBRACKET},
    {',',   JSON_COMMA},
    {':',   JSON_COLON},
    {'"',   JSON_QUOTE},
    {'f',   JSON_FALSE},
    {'t',   JSON_TRUE},
    {'n',   JSON_NULL},
};

inline std::unordered_map<eJSONTokenType, char> gLiteralFromToken = 
{
    {JSON_LBRACE,   '{',},
    {JSON_RBRACE,   '}',},
    {JSON_LBRACKET, '[',},
    {JSON_RBRACKET, ']',},
    {JSON_COMMA,    ',',},
    {JSON_COLON,    ':',},
    {JSON_QUOTE,    '"'},
};

enum eRJSONValueType 
{
    RJSON_OBJECT_VAL,
    RJSON_ARRAY_VAL,
    RJSON_BOOL_VAL,
    RJSON_NUM_VAL,
    RJSON_STR_VAL,
    RJSON_NULL_VAL
};