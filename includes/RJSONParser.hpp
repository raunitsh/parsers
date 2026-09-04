#pragma once

#include "RFileUtilsLib.hpp"

#include <vector>

struct RJSONValue;
struct RJSONObject;
struct RJSONMember;
struct RJSONArray;

#include "RJSONTypes.hpp"
#include "RJSONObject.hpp"
#include "RJSONValue.hpp"
#include "RJSONArray.hpp"

class RJSONParser {

public:

                        RJSONParser                 (RLoader * pLoader);
                        ~RJSONParser                ();

    bool                Parse                       ();
    const RJSONObject*  GetJSONObject               ();        

private:

    void                InternalReadAndAdvance      (bool pSkipSpaces = true);
    RJSONObject*        InternalParseObject         ();
    bool                InternalParseObjectMembers  (RJSONObject* pObj);
    void                InternalSkipWhiteSpaces     (int& pC);
    void                InternalParseObjectMember   (RJSONObject* pObj);
    RJSONValue*         InternalParseMemberValue    ();
    RString*            InternalParseString         ();
    double              InternalParseNumber         ();

    RLoader*            vLoader;
    char                vToken;
    eJSONTokenType      vTokenType;
    RJSONObject*        vRootObj;
};
