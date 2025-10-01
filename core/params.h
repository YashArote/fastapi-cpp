#pragma once
#include <string>
#include <optional>

// ---------------- Param Parsers ----------------
template <typename T>
T parse_param(const std::string &s);

template <>
inline int parse_param<int>(const std::string &s) { return std::stoi(s); }
template <>
inline float parse_param<float>(const std::string &s) { return std::stof(s); }
template <>
inline double parse_param<double>(const std::string &s) { return std::stod(s); }
template <>
inline std::string parse_param<std::string>(const std::string &s) { return s; }

// ---------------- Metadata Wrappers ----------------
template <typename T>
struct Path
{
    using type = T;
};
template <typename T>
struct Body
{
    using type = T;
};
