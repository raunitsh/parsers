#pragma once

struct RJSONValue
{
    ~RJSONValue ();

    eRJSONValueType          uType;
    RString*                 uStringVal  = nullptr;
    double                   uNumVal     = 0.0;
    bool                     uBoolVal    = false;
    RJSONObject*             uObjVal     = nullptr;
    RJSONArray*              uArrayVal   = nullptr;
};

inline RJSONValue::~RJSONValue ()
{
    if (uObjVal)    delete uObjVal;
    if (uArrayVal)  delete uArrayVal;
    if (uStringVal) delete uStringVal;
}