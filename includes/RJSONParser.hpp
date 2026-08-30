#pragma once

// #include <unordered_map>
#include "RFileUtilsLib.hpp"

#include <vector>

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

struct RJSONValue;
struct RJSONObject;
struct RJSONMember;

struct RJSONObject
{
    std::vector<RJSONMember*> uMembers;
};

struct RJSONArray 
{
    std::vector<RJSONValue*> uElements;
};

struct RJSONValue
{
    eRJSONValueType          uType;
    RString*                 uStringVal  = nullptr;
    double                   uNumVal     = 0.0;
    bool                     uBoolVal    = false;
    RJSONObject*             uObjVal     = nullptr;
    RJSONArray*              uArrayVal   = nullptr;

    ~RJSONValue ()
    {
        if (uObjVal)
        {
            delete uObjVal;
        }

        if (uArrayVal)
        {
            delete uArrayVal;
        } 

        if (uStringVal)
        {
            delete uStringVal;
        }
    }
};

struct RJSONMember
{
    RString*                uKey = nullptr;
    RJSONValue*             uValue = nullptr;

    ~RJSONMember ()
    {
        if (uValue)
        {
            delete uValue;
        }

        if (uKey)
        {
            delete uKey;
        }
    }
};

class RJSONParser {

public:

                        RJSONParser                 (RLoader * pLoader);
                        ~RJSONParser                ();

    bool                Parse                       ();
    const RJSONObject*  GetJSONObject               ();        

private:

    void                InternalReadAndAdvance      ();
    RJSONObject*        InternalParseObject         ();
    bool                InternalParseObjectMembers  (RJSONObject* pObj);
    void                InternalSkipWhiteSpaces     (int& pC);
    void                InternalParseObjectMember   (RJSONObject* pObj);
    RJSONValue*         InternalParsemMemberValue   ();
    RString*            InternalParseString         ();
    double              InternalParseNumber         ();

    RLoader*            vLoader;
    char                vToken;
    eJSONTokenType      vTokenType;
    RJSONObject*        vRootObj;
};