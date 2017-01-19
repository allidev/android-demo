#pragma once

#include <functional>

// Don't understand what this is for.
// It seems that this declaration is needed for
// the next class template definition
template <typename T>
class CallbackHelper;

template <typename Ret, typename... Params>
class CallbackHelper<Ret(Params...)>
{
public:
	static std::function<Ret(Params...)> func;
	template <typename... Args>
	static Ret callback(Args... args)
	{
		return func(args...);
	}
};

// Initialize the static member.
template <typename Ret, typename... Params>
std::function<Ret(Params...)> CallbackHelper<Ret(Params...)>::func;
