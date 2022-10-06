#pragma once

#include <string>
#include <optional>
#include <tuple>
#include <type_traits>
#include <regex>
#include <utility>
#include <string>


///////////////////////////////
////////General Utility////////
///////////////////////////////

template<class Class>
std::string classToString() {
	std::regex reg("\\w+\\s+([\\w\\W]+)");
	std::smatch match;
	std::string str = typeid(Class).name();
	std::regex_search(str, match, reg);

	return match[1].str();
}



///////////////////////////////
////////Template Utility///////
///////////////////////////////

//Create a tuple with type "n" number of "Type" types.

template<size_t n, class Type, class... Types>
struct _UniformTuple {
	using tuple = typename _UniformTuple<n - 1, Type, Type, Types...>::tuple;
};

template<class Type, class... Types>
struct _UniformTuple<0, Type, Types...> {
	using tuple = std::tuple<Types...>;
};

template<size_t n, class Type>
struct UniformTuple {
	using tuple = typename _UniformTuple<n, Type>::tuple;
};





//Create a tuple with parameters passed into get() function and fill the remaining parameters of the tuple with non-type "defaultValue".

template<size_t n, class TupleType, class DefaultType, DefaultType defaultValue>
struct _DefaultTuple {
public:
	template<class... Types>
	inline static TupleType get(Types... values) {
		return _DefaultTuple<n - 1, TupleType, DefaultType, defaultValue>::get(values..., defaultValue);
	}
};

template<class DefaultType, class TupleType, DefaultType defaultValue>
struct _DefaultTuple<0, TupleType, DefaultType, defaultValue> {
public:
	template<class... Types>
	inline static TupleType get(Types... values) {
		return std::make_tuple<Types...>(std::move(values)...);
	}
};

template<size_t n, class DefaultType, DefaultType defaultValue>
struct DefaultTuple {
public:
	template<class... Types>
	inline static UniformTuple<n, DefaultType>::tuple get(Types&&... values) {
		return _DefaultTuple<n - sizeof...(Types), typename UniformTuple<n, DefaultType>::tuple, DefaultType, defaultValue>::get(std::forward<Types>(values)...);
	}
};




template<size_t n, class ReturnTuple, class DefaultType, DefaultType defaultValue>
struct _DefaultTupleFromTuple {
public:
	template<class ArgTuple, class... Parameters>
	inline static ReturnTuple unpack(ArgTuple tuple, Parameters... variables) {
		//DefaultType test = getTupleElement<n>(tuple);
		//UniformTuple<std::tuple_size_v<ArgTuple>, DefaultType>
		return _DefaultTupleFromTuple<n - 1, ReturnTuple, DefaultType, defaultValue>::unpack(tuple, std::get<n>(tuple), variables...);
		//return UniformTuple<5, const char*>::tuple();
	}
};

template<class ReturnTuple, class DefaultType, DefaultType defaultValue>
struct _DefaultTupleFromTuple<0, ReturnTuple, DefaultType, defaultValue> {
public:
	template<class ArgTuple, class... Parameters>
	inline static ReturnTuple unpack(ArgTuple tuple, Parameters... variables) {
		return DefaultTuple<std::tuple_size_v<ReturnTuple>, DefaultType, defaultValue>::get(std::get<0>(tuple), variables...);
		//return UniformTuple<5, const char*>::tuple();
	}
};

template<class ReturnTuple, class DefaultType, DefaultType defaultValue>
struct _DefaultTupleFromTuple<-1, ReturnTuple, DefaultType, defaultValue> {
public:
	template<class ArgTuple, class... Parameters>
	inline static ReturnTuple unpack(ArgTuple tuple, Parameters... variables) {
		return DefaultTuple<std::tuple_size_v<ReturnTuple>, DefaultType, defaultValue>::get(variables...);
		//return UniformTuple<5, const char*>::tuple();
	}
};

template<class ReturnTuple, class DefaultType, DefaultType defaultValue>
struct DefaultTupleFromTuple {
public:
	template<class ArgTuple>
	inline static ReturnTuple unpack(ArgTuple tuple) {
		return _DefaultTupleFromTuple<std::tuple_size_v<ArgTuple> -1, ReturnTuple, DefaultType, defaultValue>::unpack(tuple);
	}
};





template<class Function>
struct _GetClassFromFunctionPointer {};

template<class TClass, class TReturnType, class... TParameters>
struct _GetClassFromFunctionPointer<TReturnType(TClass::*)(TParameters...)> {
	using Class = TClass;
	using ReturnType = TReturnType;
	using Parameters = std::tuple<TParameters...>;
};

template<class TClass, class TReturnType, class... TParameters>
struct _GetClassFromFunctionPointer<TReturnType(TClass::*)(TParameters...) const> {
	using Class = TClass;
	using ReturnType = TReturnType;
	using Parameters = std::tuple<TParameters...>;
};

template<auto function>
using GetClassFromFunctionPointer = _GetClassFromFunctionPointer<decltype(function)>::Class;


template<class Function>
struct _GetClassWithConstFromFunctionPointer {};

template<class TClass, class TReturnType, class... TParameters>
struct _GetClassWithConstFromFunctionPointer<TReturnType(TClass::*)(TParameters...)> {
	using Class = TClass;
	using ReturnType = TReturnType;
	using Parameters = std::tuple<TParameters...>;
};

template<class TClass, class TReturnType, class... TParameters>
struct _GetClassWithConstFromFunctionPointer<TReturnType(TClass::*)(TParameters...) const> {
	using Class = const TClass;
	using ReturnType = TReturnType;
	using Parameters = std::tuple<TParameters...>;
};

template<auto function>
using GetClassWithConstFromFunctionPointer = _GetClassWithConstFromFunctionPointer<decltype(function)>::Class;