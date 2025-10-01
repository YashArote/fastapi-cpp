#pragma once
#include "json.hpp"

#define MODEL(Type, ...) \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, __VA_ARGS__)

// optional validation hook
struct Validatable
{
    virtual void validate() const {}
};
