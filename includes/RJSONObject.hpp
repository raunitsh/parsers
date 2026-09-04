#pragma once

#include <unordered_map>

struct RJSONObject
{
    ~RJSONObject ();

    std::unordered_map<RString, RJSONValue*> uMembers;
};

inline RJSONObject::~RJSONObject ()
{
    for (const auto& member : uMembers)
    {
        if (member.second)
        {
            delete member.second;
        }
    }

    uMembers.clear ();
}