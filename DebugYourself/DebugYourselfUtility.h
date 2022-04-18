#pragma once

#include <type_traits>
#include <tuple>
#include "Utility.h"

template<class... Args>
	requires (std::conjunction_v<std::is_pointer<Args>...>)
std::tuple<Args...> V(Args... pointers) {
	return std::tuple<Args...>(pointers...);
};

template<class... Args>
	requires (std::conjunction_v<std::is_same<const char*, Args>...>)
std::tuple<Args...> N(Args... names) {
	return std::tuple<Args...>(names...);
};