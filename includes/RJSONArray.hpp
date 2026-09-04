#pragma once

#include <vector>

struct RJSONArray 
{
    ~RJSONArray ();

    std::vector<RJSONValue*> uElements;
};

inline RJSONArray::~RJSONArray ()
{
    for (RJSONValue* element : uElements)
    {
        if (element) delete element;
    }

    uElements.clear ();
}