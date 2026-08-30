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
    InternalReadAndAdvance ();

    if (vTokenType != eJSONTokenType::JSON_LBRACE)
    {
        return false;
    }

    vRootObj = InternalParseObject ();

    return true;
}

void
RJSONParser::InternalReadAndAdvance ()
{
        int c;
        char ch;

    c = vLoader->ReadByteAndAdvance ();

    InternalSkipWhiteSpaces (c);

    if (c == EOF)
    {
        vTokenType = eJSONTokenType::JSON_EOF;
        return;
    }

    ch = (char) c;
    vToken = ch;

    if (vToken >= '0' && vToken <= '9')
    {
        vTokenType = eJSONTokenType::JSON_NUMBER;
        return;
    }
    
    if (gTokenFromLiteral.find (ch) == gTokenFromLiteral.end ())
    {
        vTokenType = JSON_UNKNOWN;
        return;
    }

    vTokenType = gTokenFromLiteral [ch];
}   

RJSONObject*
RJSONParser::InternalParseObject ()
{
        RJSONObject* obj = new RJSONObject ();
        bool rc;

    rc = InternalParseObjectMembers (obj);

    if (rc)
        return obj;

    return nullptr;
}

bool
RJSONParser::InternalParseObjectMembers (RJSONObject* pObj)
{
    InternalReadAndAdvance ();

    if (vTokenType != eJSONTokenType::JSON_QUOTE)
    {
        return false;
    }

    while (vToken == gLiteralFromToken [eJSONTokenType::JSON_QUOTE])
    {
        InternalParseObjectMember (pObj);
        
        InternalReadAndAdvance ();
        
        // Comma
        if (vToken == gLiteralFromToken [eJSONTokenType::JSON_COMMA])
        {
            continue;
        }

        if (vToken == gLiteralFromToken [eJSONTokenType::JSON_RBRACE])
        {
            // Obj ended
            return true;
        }
    }

    InternalReadAndAdvance ();

    return vToken == gLiteralFromToken [eJSONTokenType::JSON_RBRACE];
}

void
RJSONParser::InternalParseObjectMember (RJSONObject* pObj)
{
        RJSONMember* kv = new RJSONMember ();

    kv->uKey = InternalParseString ();

    InternalReadAndAdvance ();
    // Colon
    if (vToken != gLiteralFromToken [eJSONTokenType::JSON_COLON])
    {
        return;
    }

    InternalReadAndAdvance ();

    kv->uValue = InternalParsemMemberValue ();

    pObj->uMembers.push_back (kv);
}

RJSONValue*
RJSONParser::InternalParsemMemberValue ()
{
        RJSONValue* val = new RJSONValue ();
    
    if (vTokenType == eJSONTokenType::JSON_QUOTE)
    {
        // String val
        val->uType = eRJSONValueType::RJSON_STR_VAL;
        val->uStringVal = InternalParseString ();
        
        return val;
    }

    if (vTokenType == eJSONTokenType::JSON_NUMBER)
    {
        // num val
        val->uType = eRJSONValueType::RJSON_NUM_VAL;
        val->uNumVal = InternalParseNumber ();

        return val;
    }

    if (vTokenType == eJSONTokenType::JSON_FALSE)
    {
        // bool val
        val->uType = eRJSONValueType::RJSON_BOOL_VAL;
        val->uBoolVal = false;

        return val;
    }

    if (vTokenType == eJSONTokenType::JSON_TRUE)
    {
        // bool val
        val->uType = eRJSONValueType::RJSON_BOOL_VAL;
        val->uBoolVal = true;
        
        return val;
    }

    if (vTokenType == eJSONTokenType::JSON_LBRACE)
    {
        // obj val
        val->uType = eRJSONValueType::RJSON_OBJECT_VAL;
        val->uObjVal = InternalParseObject ();

        return val;
    }

    if (vTokenType == eJSONTokenType::JSON_LBRACKET)
    {
        // array val
        val->uType = eRJSONValueType::RJSON_ARRAY_VAL;
        val->uArrayVal = new RJSONArray ();

        while (vTokenType != eJSONTokenType::JSON_RBRACKET)
        {
            val->uArrayVal->uElements.push_back (InternalParsemMemberValue ());
            
            InternalReadAndAdvance ();

            // if (vToken == gLiteralFromToken [eJSONTokenType::JSON_COMMA])
            // {
            //     continue;
            // }
        }

        return val;
    }

    // todo null
}

RString*
RJSONParser::InternalParseString ()
{
        RString* str = new RString ("");

    do 
    {
        InternalReadAndAdvance ();

        if (vToken != gLiteralFromToken [eJSONTokenType::JSON_QUOTE])
            str->Append (vToken);
    }
    while (vToken != gLiteralFromToken [eJSONTokenType::JSON_QUOTE]);

    return str;
}

double
RJSONParser::InternalParseNumber ()
{
        double res = 0.0;
        double sign = 1.0;
        double fraction = 0.1;

    if (vToken == '-')
    {
        sign = -1.0;
    } 
    else {

        res = (double)(vToken - '0');
    }

    while (true)
    {
        InternalReadAndAdvance ();

        if (vToken >= '0' && vToken <= '9')
        {
            res = (res*10.0) + (vToken - '0');
        }
        else {
            break;
        }
    }

    if (vToken == '.')
    {
        while (true)
        {
            InternalReadAndAdvance ();

            if (vToken >= '0' && vToken <= '9')
            {
                res += (vToken - '0') * fraction;
                fraction *= 0.1; 
            }
            else {
                break;
            }
        }
    }

    InternalReadAndAdvance ();

    return res * sign;
}

void
RJSONParser::InternalSkipWhiteSpaces (int& pC)
{
    while (pC == '\n' || pC == ' ' || pC == '\t' || pC == '\r')
    {
        pC = vLoader->ReadByteAndAdvance ();
    }
}