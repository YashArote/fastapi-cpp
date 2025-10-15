#pragma once
#include <string>
#include <optional>


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
template<>
inline bool parse_param<bool>(const std::string &s) { return s == "true"; }
template<>
inline std::optional<int> parse_param<std::optional<int>>(const std::string &s) { return s.empty() ? std::nullopt : std::make_optional(std::stoi(s)); }
template<>
inline std::optional<float> parse_param<std::optional<float>>(const std::string &s) { return s.empty() ? std::nullopt : std::make_optional(std::stof(s)); }
template<>
inline std::optional<double> parse_param<std::optional<double>>(const std::string &s) { return s.empty() ? std::nullopt : std::make_optional(std::stod(s)); }
template<>
inline std::optional<std::string> parse_param<std::optional<std::string>>(const std::string &s) { return s.empty() ? std::nullopt : std::make_optional(s); }
template<>
inline std::optional<bool> parse_param<std::optional<bool>>(const std::string &s) { return s.empty() ? std::nullopt : std::make_optional(s == "true"); }


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
