#pragma once
#include "nlohmann/json.hpp"

#define MODEL(Type, ...) \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, __VA_ARGS__)

struct Validatable
{
    virtual void validate() const {}
};
