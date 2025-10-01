#pragma once
#include "params.h"
#include "router.h"
#include "request.h"

template <typename Param>
auto resolve_arg(const Request &req, const Router::Values &values, size_t index)
{
    using T = typename Param::type;

    if constexpr (std::is_same_v<Param, Path<T>>)
    {
        return parse_param<T>(values[index]); // return raw T
    }
    else if constexpr (std::is_same_v<Param, Body<T>>)
    {
        if (!req.json_body)
            throw std::runtime_error("Missing JSON body");
        return req.json_body->get<T>(); // validated via model
    }
}

template <typename Func, typename... Params, std::size_t... I>
Response call_with_params(Func f,
                          const Request &req,
                          const Router::Values &values,
                          std::index_sequence<I...>)
{
    return f(resolve_arg<Params>(req, values, I)...);
}

template <typename... Params, typename Func>
Router::Handler make_handler(Func f)
{
    return [f](const Request &req, const Router::Values &values) -> Response
    {
        try
        {
            return call_with_params<Func, Params...>(
                f, req, values, std::index_sequence_for<Params...>{});
        }
        catch (const std::exception &e)
        {
            return Response(std::string("Validation Error: ") + e.what(), "text/plain");
        }
        catch (...)
        {
            return Response("Unknown Error", "text/plain");
        }
    };
}
