#pragma once


#include <string>
#include <optional>
#include <tuple>
#include <type_traits>
#include <regex>
#include <utility>
#include <string>
#include <algorithm>
#include <chrono>
#include <ratio>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "Utility.h"
#include "TemplateUtility.h"

#include "DebugYourselfDatabase.h"

namespace dy {

#ifdef _DEBUG
	constexpr bool CONFIGURATION_STATE = true;
#else
	constexpr bool CONFIGURATION_STATE = false;
#endif

	template<bool enable>
	using EnableGuard = std::enable_if_t<enable>;


	class ReleaseDebugYourself {
public:

	ReleaseDebugYourself() {}

	template<auto... functionPointers>
	using MemberFunctionPointerHeadClass = _GetClassFromFunctionPointer<std::tuple_element_t<0, std::tuple<decltype(functionPointers)...>>>::Class;

	template<auto... functionPointers>
	struct ClassFunctionRegister {
	public:
		template<class... Parameters> ClassFunctionRegister(Parameters... names){};
		template<class... Parameters> ClassFunctionRegister(std::tuple<Parameters...> names){};

		template<size_t n> void getFunctionPointer() {}
		template<size_t n> void getFunctionName() {}

		static void getClassName() {}
	};

	template<class ObjectType, class... Types>
	struct ObjectVariableRegister {
	public:

		ObjectVariableRegister(){};
		template<class... Parameters> ObjectVariableRegister(ObjectType* object, std::tuple<Types*...> variables){};
		template<class... Parameters> ObjectVariableRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables){};
		template<class... Parameters> ObjectVariableRegister(ObjectType* object, std::tuple<Types*...> variables, std::tuple<Parameters...> names){};
		template<class... Parameters> ObjectVariableRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables, std::tuple<Parameters...> names){};

		ObjectVariableRegister(const ObjectVariableRegister& other){};
		ObjectVariableRegister(ObjectVariableRegister&& other){}

		void operator=(const ObjectVariableRegister& other) {}
		void operator=(ObjectVariableRegister&& other) {}

		template<size_t n> void getVariablePointer() {}
		template<size_t n> void getVariableName() {}
		void getObject() {}
		void getObjectName() {}
		void getInstanceTime() {}
		static void getNumberOfVariables() {}
	};

	template<auto... functionPointers>
	struct GlobalFunctionRegister {
	public:
		template<class... Parameters> GlobalFunctionRegister(Parameters... names){};
		template<class... Parameters> GlobalFunctionRegister(std::tuple<Parameters...> names){};

		template<size_t n> void getFunctionPointer() {}
		template<size_t n> void getFunctionName() {}
	};

	template<class... Types>
	struct FundamentalVariableRegister {
	public:

		FundamentalVariableRegister() {};
		template<class... Parameters> FundamentalVariableRegister(std::tuple<Types*...> variables) {};
		template<class... Parameters> FundamentalVariableRegister(std::tuple<Types*...> variables, std::tuple<Parameters...> names){};

		FundamentalVariableRegister(const FundamentalVariableRegister& other){};

		void operator=(const FundamentalVariableRegister& other) {}
		template<size_t n> void getVariablePointer() {}
		template<size_t n> void getVariableName() {}
		static void getNumberOfVariables() {}
	};

	template<class... Registers>
	struct ClassFunctionRegisterBinder {
	public:
		ClassFunctionRegisterBinder() {}
		ClassFunctionRegisterBinder(Registers... registers) {}

		static void use(const ClassFunctionRegisterBinder<Registers...>& binder) {}

		template<auto function> static void getFunctionName() {}
		template<auto function> static void getClassName() {}
	};


	template<class... Registers>
	struct ObjectVariableRegisterBinder {

		ObjectVariableRegisterBinder() {}
		ObjectVariableRegisterBinder(Registers...) {}

		template<class... Register> static void add(Register&... reg) {}
		template<size_t n, class PointerType, class RegisterVector> static void getRegisterIndexFromPointer(PointerType* pointer, RegisterVector& registerVector) {}

		template<class VariableType> static void getVariableName(VariableType* variableAddress) {}
		template<class ObjectType> static void getObjectName(ObjectType* objectAddress) {}
		template<class ObjectType> static void getInstanceTime(ObjectType* objectAddress) {}
	};


	template<class... Registers>
	struct GlobalFunctionRegisterBinder {
		GlobalFunctionRegisterBinder(Registers... registers) {}

		static void use(const GlobalFunctionRegisterBinder<Registers...>& binder) {}
		template<auto function> static void getFunctionName() {}
	};


	template<class... Registers>
	struct FundamentalVariableRegisterBinder {

		FundamentalVariableRegisterBinder(Registers...) {}

		template<class... Register> static void add(Register&... reg) {}

		template<size_t n, class PointerType, class RegisterVector> static void getRegisterIndexFromPointer(PointerType* pointer, RegisterVector& registerVector) {}

		template<class VariableType> static void getVariableName(VariableType* variableAddress) {}

	};


	using SQLTypes = SQL::Types;
	using SQLCConst = SQL::ColumnConstraints;
	using SQLTConst = SQL::TableConstraints;
	using MainTableType = DebugYourselfDatabaseTable<
		SQLCConst::PrimaryKey<SQLTypes::INTEGER>,
		SQLTypes::TEXT,
		SQLTypes::TEXT,
		SQLTypes::INTEGER,
		SQLTypes::REAL,
		SQLTypes::TEXT,
		SQLTypes::INTEGER,
		SQLTypes::TEXT,
		SQLTypes::INTEGER,
		SQLTypes::INTEGER,
		SQLTypes::REAL,
		SQLTypes::TEXT>;

	using TagsTableType = DebugYourselfDatabaseTable<
		SQLCConst::PrimaryKey<SQLTypes::INTEGER>,
		SQLTypes::TEXT>;

	using MainTable_TagsType = DebugYourselfDatabaseTable
		<SQLTypes::INTEGER, SQLTypes::INTEGER, SQLTConst::ForeignKey, SQLTConst::ForeignKey>;

	struct LoggingDatabase {
	public:
		LoggingDatabase(MainTableType& main, TagsTableType& tags, MainTable_TagsType& main_tags){}
	};

	static void getLoggingDatabase() {}

	static void end() {}

	template<auto fp> static intmax_t extractFunctionPointerAsInteger() {}

	struct LoggingAction {
		virtual void operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) = 0;
	};

	struct LoggingCondition {
		virtual bool operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) = 0;
	};

	struct AlwaysTrue {
		void operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) {
		};
	};

	template<class Condition = AlwaysTrue>
	struct DirectLogger {
		void operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) {}
	};

	template<class CFRB, class OVRB, class GFRB, class FVRB, class PreAction = DirectLogger<>>
	struct Dependencies {

		template<auto functionPointer, class Variable> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer> static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer> static void debug(SQLTypes::INTEGER rank, std::string message) {}
		template<class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {}

		static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		static void debug(SQLTypes::INTEGER rank, std::string message) {}
		static void debug(std::vector<SQLTypes::TEXT> tags, std::string message) {}
		static void debug(std::string message) {}


		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {}

		template<class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, Args... args) {}
		template<class MessageAssembler, class... Args> static void debug(std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args> static void debug(Args... args) {}




		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::string message) {}
		template<class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}

		template<class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::string message) {}
		template<class Func> static void debug(std::function<Func> condition, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Func> static void debug(std::function<Func> condition, std::string message) {}

		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}

		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, Args... args) {}
		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Args... args) {}

	};

};
	

	class DebugDebugYourself {
public:

	DebugDebugYourself() {}



	///////////////////////////
	////////API Utility////////
	///////////////////////////

	inline static std::chrono::time_point<std::chrono::steady_clock> launchTimeStamp = std::chrono::steady_clock::now();


	///////////////////////////////////////
	////////Class Function Register////////
	///////////////////////////////////////


	template<auto... functionPointers>
	using MemberFunctionPointerHeadClass = _GetClassFromFunctionPointer<std::tuple_element_t<0, std::tuple<decltype(functionPointers)...>>>::Class;

	template<auto... functionPointers>
	//requires std::conjunction_v<
	//		std::is_same<MemberFunctionPointerHeadClass<functionPointers...>, MemberFunctionPointerHeadClass<functionPointers>>...>
	struct ClassFunctionRegister {
	public:
		template<class... Parameters>
			requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		ClassFunctionRegister(Parameters... names) :
			associatedFunctions(functionPointers...),
			associatedFunctionNames(DefaultTuple<sizeof...(functionPointers), const char*, nullptr>::get(names...))
		{};

		template<class... Parameters>
			requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		ClassFunctionRegister(std::tuple<Parameters...> names) :
			associatedFunctions(functionPointers...),
			associatedFunctionNames(DefaultTupleFromTuple<UniformTuple<sizeof...(functionPointers), const char*>::tuple, const char*, nullptr>::unpack(names))
		{};

		template<size_t n>
		constexpr auto getFunctionPointer() {
			return std::get<n>(associatedFunctions);
		}

		template<size_t n>
		constexpr const char* getFunctionName() {
			return std::get<n>(associatedFunctionNames);
		}

		static const char* getClassName() {
			return className.c_str();
		}


		using AssociatedClass = MemberFunctionPointerHeadClass<functionPointers...>;
		std::tuple<decltype(functionPointers)...> associatedFunctions;
		UniformTuple<sizeof...(functionPointers), const char*>::tuple associatedFunctionNames;
		inline static std::string className = classToString<AssociatedClass>();

		long double timeStamp = std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count();
	};


	///////////////////////////////////////
	////////Object Variable Register///////
	///////////////////////////////////////

	template<class ObjectType, class... Types>
	struct ObjectVariableRegister {
	public:

		ObjectVariableRegister() :
			associatedObject(nullptr),
			associatedVariables(std::tuple<Types*...>()),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),
			objectName(nullptr),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};

		template<class... Parameters>
		//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		ObjectVariableRegister(ObjectType* object, std::tuple<Types*...> variables) :
			associatedObject(object),
			associatedVariables(variables),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),
			objectName(nullptr),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};

		template<class... Parameters>
		//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		ObjectVariableRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables) :
			associatedObject(object),
			associatedVariables(variables),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),
			objectName(objectName),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};

		template<class... Parameters>
		//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		ObjectVariableRegister(ObjectType* object, std::tuple<Types*...> variables, std::tuple<Parameters...> names) :
			associatedObject(object),
			associatedVariables(variables),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(names)),
			objectName(nullptr),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};

		template<class... Parameters>
		//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		ObjectVariableRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables, std::tuple<Parameters...> names) :
			associatedObject(object),
			associatedVariables(variables),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(names)),
			objectName(objectName),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};


		//Copy constructor
		ObjectVariableRegister(const ObjectVariableRegister& other) :
			associatedObject(other.associatedObject),
			associatedVariables(other.associatedVariables),
			associatedVariableNames(other.associatedVariableNames),
			objectName(other.objectName),

			timeStamp(other.timeStamp),
			instanceID(++instanceCount)
		{};

		ObjectVariableRegister(ObjectVariableRegister&& other) :
			associatedObject(std::move(other.associatedObject)),
			associatedVariables(std::move(other.associatedVariables)),
			associatedVariableNames(std::move(other.associatedVariableNames)),
			objectName(std::move(other.objectName)),

			timeStamp(std::move(other.timeStamp)),
			instanceID(std::move(other.instanceID))
		{
			other.associatedObject = nullptr;
			other.associatedVariables = std::tuple<Types*...>();
			other.associatedVariableNames = DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>());
			other.objectName = nullptr;

			other.timeStamp = std::chrono::duration_values<long double>::zero();
			other.instanceID = 0;
		}


		ObjectVariableRegister& operator=(const ObjectVariableRegister& other) {
			associatedObject = other.associatedObject;
			associatedVariables = other.associatedVariables;
			associatedVariableNames = other.associatedVariableNames;
			objectName = other.objectName;

			timeStamp = other.timeStamp;
			instanceID = ++instanceCount;

			return *this;
		}

		ObjectVariableRegister& operator=(ObjectVariableRegister&& other) {
			associatedObject = other.associatedObject;
			associatedVariables = other.associatedVariables;
			associatedVariableNames = other.associatedVariableNames;
			objectName = other.objectName;

			timeStamp = other.timeStamp;
			instanceID = other.instanceID;

			other.associatedObject = nullptr;
			other.associatedVariables = std::tuple<Types*...>();
			other.associatedVariableNames = DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>());
			other.objectName = nullptr;

			other.timeStamp = std::chrono::duration_values<long double>::zero();
			other.instanceID = 0;

			return *this;
		}

		template<size_t n>
		const auto getVariablePointer() {
			return std::get<n>(associatedVariables);
		}

		template<size_t n>
		const char* getVariableName() {
			return std::get<n>(associatedVariableNames);
		}

		ObjectType* getObject() {
			return associatedObject;
		}

		const char* getObjectName() {
			return objectName;
		}

		long double getInstanceTime() {
			return timeStamp;
		}

		static constexpr size_t getNumberOfVariables() {
			return sizeof...(Types);
		}

		using AssociatedClass = ObjectType;
		ObjectType* associatedObject;
		std::tuple<Types*...> associatedVariables;
		UniformTuple<sizeof...(Types), const char*>::tuple associatedVariableNames;
		const char* objectName;

		long double timeStamp;
		inline static size_t instanceCount = 0;
		size_t instanceID;
	};


	////////////////////////////////////////
	////////Global Function Register////////
	////////////////////////////////////////

	template<auto... functionPointers>
	struct GlobalFunctionRegister {
	public:
		template<class... Parameters>
			requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		GlobalFunctionRegister(Parameters... names) :
			associatedFunctions(functionPointers...),
			associatedFunctionNames(DefaultTuple<sizeof...(functionPointers), const char*, nullptr>::get(names...))
		{};

		template<class... Parameters>
			requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		GlobalFunctionRegister(std::tuple<Parameters...> names) :
			associatedFunctions(functionPointers...),
			associatedFunctionNames(DefaultTupleFromTuple<UniformTuple<sizeof...(functionPointers), const char*>::tuple, const char*, nullptr>::unpack(names))
		{};

		template<size_t n>
		auto getFunctionPointer() {
			return std::get<n>(associatedFunctions);
		}

		template<size_t n>
		const char* getFunctionName() {
			return std::get<n>(associatedFunctionNames);
		}

		std::tuple<decltype(functionPointers)...> associatedFunctions;
		UniformTuple<sizeof...(functionPointers), const char*>::tuple associatedFunctionNames;

		long double timeStamp = std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count();
	};


	////////////////////////////////////////////
	////////Fundamental Variable Register///////
	////////////////////////////////////////////

	template<class... Types>
	struct FundamentalVariableRegister {
	public:

		FundamentalVariableRegister() :
			associatedVariables(std::tuple<Types*...>()),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};

		template<class... Parameters>
		//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		FundamentalVariableRegister(std::tuple<Types*...> variables) :
			associatedVariables(variables),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};

		template<class... Parameters>
		//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
		FundamentalVariableRegister(std::tuple<Types*...> variables, std::tuple<Parameters...> names) :
			associatedVariables(variables),
			associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(names)),

			timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
			instanceID(++instanceCount)
		{};


		//Copy constructor
		FundamentalVariableRegister(const FundamentalVariableRegister& other) :
			associatedVariables(other.associatedVariables),
			associatedVariableNames(other.associatedVariableNames),

			timeStamp(other.timeStamp),
			instanceID(other.instanceID)
		{};


		FundamentalVariableRegister& operator=(const FundamentalVariableRegister& other) {
			associatedVariables = other.associatedVariables;
			associatedVariableNames = other.associatedVariableNames;

			timeStamp = other.timeStamp;

			return *this;
		}

		template<size_t n>
		auto getVariablePointer() {
			return std::get<n>(associatedVariables);
		}

		template<size_t n>
		const char* getVariableName() {
			return std::get<n>(associatedVariableNames);
		}

		static constexpr size_t getNumberOfVariables() {
			return sizeof...(Types);
		}

		std::tuple<Types*...> associatedVariables;
		UniformTuple<sizeof...(Types), const char*>::tuple associatedVariableNames;

		long double timeStamp;
		inline static size_t instanceCount = 0;
		const size_t instanceID;
	};

	template<class... Registers>
	struct ClassFunctionRegisterBinder {
	public:
		ClassFunctionRegisterBinder() {}
		ClassFunctionRegisterBinder(Registers... registers) : internalBinder(registers...) {}
		std::tuple<Registers...> internalBinder;
		inline static std::tuple<Registers...> binder;
		static void use(const ClassFunctionRegisterBinder<Registers...>& binder) {
			ClassFunctionRegisterBinder<Registers...>::binder = binder.internalBinder;
		}

		template<auto function1, auto function2>
		inline static constexpr bool FunctionIsSameType = std::is_same_v<decltype(function1), decltype(function2)>;


		template<auto function1, auto function2, class Enable = void>
		struct _CompareFunctionPointers {};

		template<auto function1, auto function2>
		struct _CompareFunctionPointers<function1, function2, std::enable_if_t<FunctionIsSameType<function1, function2>>> {
		public:
			inline static constexpr bool value = (function1 == function2);
		};

		template<auto function1, auto function2>
		struct _CompareFunctionPointers<function1, function2, std::enable_if_t<!FunctionIsSameType<function1, function2>>> {
		public:
			inline static constexpr bool value = false;
		};

		template<auto function1, auto function2>
		inline static constexpr bool CompareFunctionPointers = _CompareFunctionPointers<function1, function2>::value;



		template<size_t n, auto functionP, auto functionPHead, auto... functionPs>
		struct _1_GetFunctionIndexFromRegister {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : _1_GetFunctionIndexFromRegister<n + 1, functionP, functionPs...>::index;
		};

		template<size_t n, auto functionP, auto functionPHead>
		struct _1_GetFunctionIndexFromRegister<n, functionP, functionPHead> {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : -1;
		};


		template<size_t n, auto functionP, class CFR>
		struct _0_GetFunctionIndexFromRegister {};

		template<size_t n, auto functionP, auto functionPHead, auto... functionPs>
		struct _0_GetFunctionIndexFromRegister<n, functionP, ClassFunctionRegister<functionPHead, functionPs...>> {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : _1_GetFunctionIndexFromRegister<n + 1, functionP, functionPs...>::index;
		};

		template<size_t n, auto functionP, auto functionPHead>
		struct _0_GetFunctionIndexFromRegister<n, functionP, ClassFunctionRegister<functionPHead>> {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : -1;
		};

		template<auto functionP, class CFR>
		inline static constexpr size_t GetFunctionIndexFromRegister = _0_GetFunctionIndexFromRegister<0, functionP, CFR>::index;

		template<auto function, class T, class... Args>
		struct _GetRegisterFromFunction {
		public:
			using Class = std::conditional_t<std::is_same_v<GetClassFromFunctionPointer<function>, typename T::AssociatedClass>, T, typename _GetRegisterFromFunction<function, Args...>::Class>;
		};

		template<auto function, class T>
		struct _GetRegisterFromFunction<function, T> {
		public:
			using Class = std::conditional_t<std::is_same_v<GetClassFromFunctionPointer<function>, typename T::AssociatedClass>, T, void>;
		};

		template<auto function>
		using GetRegisterFromFunction = _GetRegisterFromFunction<function, Registers...>::Class;

		template<auto function>
		inline static constexpr size_t GetFunctionIndex = GetFunctionIndexFromRegister<function, GetRegisterFromFunction<function>>;

		template<auto function>
		static const char* getFunctionName() {
			constexpr size_t index = GetFunctionIndexFromRegister<function, GetRegisterFromFunction<function>>;
			return std::get<GetRegisterFromFunction<function>>(binder).getFunctionName<index>();
		}

		template<auto function>
		static const char* getClassName() {
			return GetRegisterFromFunction<function>::getClassName();
		}

	};


	template<class... Registers>
	struct ObjectVariableRegisterBinder {

		ObjectVariableRegisterBinder() {}
		ObjectVariableRegisterBinder(Registers...) {}

		template<class Register>
		struct _GetObjectTypeFromRegister {};

		template<class ObjectType, class... Args>
		struct _GetObjectTypeFromRegister<ObjectVariableRegister<ObjectType, Args...>> {
			using Type = ObjectType;
		};

		template<class Register>
		using GetObjectTypeFromRegister = _GetObjectTypeFromRegister<Register>;

		inline static std::tuple<std::vector<std::unique_ptr<Registers>>...> binder;

		template<class Register>
		struct _GetRegisterVariablesMapTuple {};

		template<class... Types>
		struct _GetRegisterVariablesMapTuple<std::tuple<Types...>> {
			using Type = std::tuple<std::unordered_map<Types*, size_t>...>;
		};

		template<class Register>
		using GetRegisterVariablesMapTuple = _GetRegisterVariablesMapTuple<Register>::Type;


		//inline static std::tuple<GetRegisterVariablesMapTuple<Registers>...> objectLookup;

		//static void _add(GetObjectTypeFromRegister<Registers>* objectPointer, Registers reg)

		template<class... Register>
		static void add(Register&... reg) {
			(std::get<std::vector<std::unique_ptr<Register>>>(binder).emplace_back(std::make_unique<Register>(reg)), ...);

			//Consider implementing map lookup 
			//std::get<Register>(objectLookup)
		}

		template<size_t n, class PointerType, class RegisterVector>
		static size_t getRegisterIndexFromPointer(PointerType* pointer, RegisterVector& registerVector) {
			for (size_t i = 0; i < registerVector.size(); i++) {
				if ((pointer == registerVector.at(i)->getVariablePointer<n>())) {
					return i;
				}
			}

			return -1;
		}

		template<class RegisterVector>
		struct _GetPointerTypeFromRegisterVector {};

		template<class Register>
		struct _GetPointerTypeFromRegisterVector<std::vector<std::unique_ptr<Register>>> {
			using Type = decltype(Register::associatedVariables);
		};

		template<class RegisterVector>
		using GetPointerTypeFromRegisterVector = typename _GetPointerTypeFromRegisterVector<RegisterVector>::Type;

		template<size_t n>
		struct VariableNameFromTuple {

			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				std::is_same_v<PointerType*,
				std::tuple_element_t<n, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {

				size_t index = getRegisterIndexFromPointer<n>(pointer, registerVector);
				return (index != static_cast<size_t>(-1)) ?
					registerVector.at(index)->getVariableName<n>() :
					VariableNameFromTuple<n - 1>::get(pointer, registerVector);
			}

			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				!std::is_same_v<PointerType*,
				std::tuple_element_t<n, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {
				return VariableNameFromTuple<n - 1>::get(pointer, registerVector);
			}
		};

		template<>
		struct VariableNameFromTuple<0> {
			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				std::is_same_v<PointerType*,
				std::tuple_element_t<0, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {
				size_t index = getRegisterIndexFromPointer<0>(pointer, registerVector);
				return (index != static_cast<size_t>(-1)) ?
					registerVector.at(index)->getVariableName<0>() :
					nullptr;
			}

			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				!std::is_same_v<PointerType*,
				std::tuple_element_t<0, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {
				return nullptr;
			}
		};

		template<size_t n>
		struct VariableName {
			template<class PointerType>
			static const char* get(PointerType* pointer) {
				const char* name = VariableNameFromTuple<std::tuple_size_v<
					GetPointerTypeFromRegisterVector<
					std::tuple_element_t<n, decltype(binder)>>> -1>::get(
						pointer, std::get<n>(binder));
				return (nullptr != name ? name : VariableName<n - 1>::get(pointer));
			}
		};

		template<>
		struct VariableName<0> {
			template<class PointerType>
			static const char* get(PointerType* pointer) {
				const char* name = VariableNameFromTuple<std::tuple_size_v<
					GetPointerTypeFromRegisterVector<
					std::tuple_element_t<0, decltype(binder)>>> -1>::get(
						pointer, std::get<0>(binder));
				return (nullptr != name ? name : nullptr);
			}
		};

		template<class VariableType>
		static const char* getVariableName(VariableType* variableAddress) {
			return VariableName<sizeof...(Registers) - 1>::get(variableAddress);

		}

		template<size_t n, class Type, class T, class... Args>
		struct _GetParameterPackIndex {
			inline static constexpr size_t index = std::is_same_v<Type, T> ? n : _GetParameterPackIndex<n + 1, Type, Args...>::index;
		};

		template<size_t n, class Type, class T>
		struct _GetParameterPackIndex<n, Type, T> {
			inline static constexpr size_t index = std::is_same_v<Type, T> ? n : -1;
		};

		template<class Type, class... Args>
		inline static constexpr size_t GetParameterPackIndex = _GetParameterPackIndex<0, Type, Args...>::index;

		template<class ObjectType>
		static const char* getObjectName(ObjectType* objectAddress) {
			constexpr auto& reg = std::get<GetParameterPackIndex<ObjectType, typename Registers::AssociatedClass...>>(binder);

			for (size_t i = 0; i < reg.size(); i++) {
				if (reg.at(i)->getObject() == objectAddress) {
					return reg.at(i)->getObjectName();
				}
			}

			return nullptr;

		}

		
		

		template<size_t n>
		struct VariableInRegister {
		public:
			template<class VariablePointer, class RegisterVector>
			bool exists(VariablePointer* pointer, RegisterVector& vector) {
				size_t index = getRegisterIndexFromPointer<n>(pointer, vector);
				return (index != -1) ? true : VariableInRegister<n - 1>::exists(pointer, vector);
			}
		};

		template<>
		struct VariableInRegister<0> {
		public:
			template<class VariablePointer, class RegisterVector>
			bool exists(VariablePointer* pointer, RegisterVector& vector) {
				size_t index = getRegisterIndexFromPointer<n>(pointer, vector);
				return (index != -1) ? true : false;
			}
		};


		struct bb {
			template<class VariablePointer>
			void a(VariablePointer* pointer){
				VariableInRegister<Register::getVarSize()>::exists(pointer, vector)
			}
		};

		template<class VariableType, class Register>
		struct VariableTypeComp {};

		template<class VariableType, template<class...> class Template, class T, class... Args>
		struct VariableTypeComp<VariableType, Template<T, Args...>> {
			inline constexpr bool value = stl::TypeExists_v<T, std::tuple<Args...>>;
		};

		
		//Needs to be implemented sometime.
		template<class VariableType>
		static auto getObject(VariableType* type) {
			//using FilteredRegisters = stl::ConditionalFilter_t<VariableTypeComp, VariableType, std::tuple<Registers...>>;
			
		}


		template<class ObjectType>
		static long double getInstanceTime(ObjectType* objectAddress) {
			constexpr auto& reg = std::get<GetParameterPackIndex<ObjectType, typename Registers::AssociatedClass...>>(binder);

			for (size_t i = 0; i < reg.size(); i++) {
				if (reg.at(i)->getObject() == objectAddress) {
					return reg.at(i)->getInstanceTime();
				}
			}

			return -1;

		}
	};


	template<class... Registers>
	struct GlobalFunctionRegisterBinder {
		GlobalFunctionRegisterBinder(Registers... registers) : internalBinder(registers...) {}
		std::tuple<Registers...> internalBinder;
		inline static std::tuple<Registers...> binder;
		static void use(const GlobalFunctionRegisterBinder<Registers...>& binder) {
			GlobalFunctionRegisterBinder<Registers...>::binder = binder.internalBinder;
		}

		template<auto function1, auto function2>
		inline static constexpr bool FunctionIsSameType = std::is_same_v<decltype(function1), decltype(function2)>;


		template<auto function1, auto function2, class Enable = void>
		struct _CompareFunctionPointers {};

		template<auto function1, auto function2>
		struct _CompareFunctionPointers<function1, function2, std::enable_if_t<FunctionIsSameType<function1, function2>>> {
		public:
			inline static constexpr bool value = (function1 == function2);
		};

		template<auto function1, auto function2>
		struct _CompareFunctionPointers<function1, function2, std::enable_if_t<!FunctionIsSameType<function1, function2>>> {
		public:
			inline static constexpr bool value = false;
		};

		template<auto function1, auto function2>
		inline static constexpr bool CompareFunctionPointers = _CompareFunctionPointers<function1, function2>::value;



		template<size_t n, auto functionP, auto functionPHead, auto... functionPs>
		struct _1_GetFunctionIndexFromRegister {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : _1_GetFunctionIndexFromRegister<n + 1, functionP, functionPs...>::index;
		};

		template<size_t n, auto functionP, auto functionPHead>
		struct _1_GetFunctionIndexFromRegister<n, functionP, functionPHead> {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : -1;
		};


		template<size_t n, auto functionP, class CFR>
		struct _0_GetFunctionIndexFromRegister {};

		template<size_t n, auto functionP, auto functionPHead, auto... functionPs>
		struct _0_GetFunctionIndexFromRegister<n, functionP, GlobalFunctionRegister<functionPHead, functionPs...>> {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : _1_GetFunctionIndexFromRegister<n + 1, functionP, functionPs...>::index;
		};

		template<size_t n, auto functionP, auto functionPHead>
		struct _0_GetFunctionIndexFromRegister<n, functionP, GlobalFunctionRegister<functionPHead>> {
		public:
			inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : -1;
		};

		template<auto functionP, class CFR>
		inline static constexpr size_t GetFunctionIndexFromRegister = _0_GetFunctionIndexFromRegister<0, functionP, CFR>::index;


		template<auto functionP, class... Args>
		struct _GetFunctionIndexFromBinderRegisters {};

		template<auto functionP, class T, class... Args>
		struct _GetFunctionIndexFromBinderRegisters<functionP, T, Args...> {
		public:
			using Type = std::conditional_t<(GetFunctionIndexFromRegister<functionP, T> != -1), T, typename _GetFunctionIndexFromBinderRegisters<functionP, Args...>::Type>;
			inline static constexpr size_t index = (GetFunctionIndexFromRegister<functionP, T> != -1) ? GetFunctionIndexFromRegister<functionP, T> : _GetFunctionIndexFromBinderRegisters<functionP, Args...>::index;
		};

		template<auto functionP, class T>
		struct _GetFunctionIndexFromBinderRegisters<functionP, T> {
		public:
			using Type = std::conditional_t<(GetFunctionIndexFromRegister<functionP, T> != -1), T, void>;
			inline static constexpr size_t index = (GetFunctionIndexFromRegister<functionP, T> != -1) ? GetFunctionIndexFromRegister<functionP, T> : -1;
		};

		template<auto functionP>
		inline static constexpr size_t GetFunctionIndexFromBinderRegisters = _GetFunctionIndexFromBinderRegisters<functionP, Registers...>::index;

		template<auto functionP>
		using GetFunctionTypeFromBinderRegisters = typename _GetFunctionIndexFromBinderRegisters<functionP, Registers...>::Type;

		template<auto function>
		static const char* getFunctionName() {
			constexpr size_t index = GetFunctionIndexFromBinderRegisters<function>;
			return std::get<GetFunctionTypeFromBinderRegisters<function>>(binder).getFunctionName<index>();
		}
	};


	template<class... Registers>
	struct FundamentalVariableRegisterBinder {

		FundamentalVariableRegisterBinder(Registers...) {}

		inline static std::tuple<std::vector<std::unique_ptr<Registers>>...> binder;


		template<class... Register>
		static void add(Register&... reg) {
			(std::get<std::vector<std::unique_ptr<Register>>>(binder).emplace_back(std::make_unique<Register>(reg)), ...);

			//Consider implementing map lookup 
			//std::get<Register>(objectLookup)
		}

		template<size_t n, class PointerType, class RegisterVector>
		static size_t getRegisterIndexFromPointer(PointerType* pointer, RegisterVector& registerVector) {
			for (size_t i = 0; i < registerVector.size(); i++) {
				if ((pointer == registerVector.at(i)->getVariablePointer<n>())) {
					return i;
				}
			}

			return -1;
		}

		template<class RegisterVector>
		struct _GetPointerTypeFromRegisterVector {};

		template<class Register>
		struct _GetPointerTypeFromRegisterVector<std::vector<std::unique_ptr<Register>>> {
			using Type = decltype(Register::associatedVariables);
		};

		template<class RegisterVector>
		using GetPointerTypeFromRegisterVector = typename _GetPointerTypeFromRegisterVector<RegisterVector>::Type;

		template<size_t n>
		struct VariableNameFromTuple {

			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				std::is_same_v<PointerType*,
				std::tuple_element_t<n, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {

				size_t index = getRegisterIndexFromPointer<n>(pointer, registerVector);
				return (index != static_cast<size_t>(-1)) ?
					registerVector.at(index)->getVariableName<n>() :
					VariableNameFromTuple<n - 1>::get(pointer, registerVector);
			}

			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				!std::is_same_v<PointerType*,
				std::tuple_element_t<n, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {
				return VariableNameFromTuple<n - 1>::get(pointer, registerVector);
			}
		};

		template<>
		struct VariableNameFromTuple<0> {
			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				std::is_same_v<PointerType*,
				std::tuple_element_t<0, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {
				size_t index = getRegisterIndexFromPointer<n>(pointer, registerVector);
				return (index != static_cast<size_t>(-1)) ?
					registerVector.at(index)->getVariableName<0>() :
					nullptr;
			}

			template<class PointerType, class RegisterVector,
				std::enable_if_t<
				!std::is_same_v<PointerType*,
				std::tuple_element_t<0, GetPointerTypeFromRegisterVector<RegisterVector>>>
			>* = nullptr>
				static const char* get(PointerType* pointer, RegisterVector& registerVector) {
				return nullptr;
			}
		};

		template<size_t n>
		struct VariableName {
			template<class PointerType>
			static const char* get(PointerType* pointer) {
				const char* name = VariableNameFromTuple<std::tuple_size_v<
					GetPointerTypeFromRegisterVector<
					std::tuple_element_t<n, decltype(binder)>>> -1>::get(
						pointer, std::get<n>(binder));
				return (nullptr != name ? name : VariableName<n - 1>::get(pointer));
			}
		};

		template<>
		struct VariableName<0> {
			template<class PointerType>
			static const char* get(PointerType* pointer) {
				const char* name = VariableNameFromTuple<std::tuple_size_v<
					GetPointerTypeFromRegisterVector<
					std::tuple_element_t<0, decltype(binder)>>> -1>::get(
						pointer, std::get<0>(binder));
				return (nullptr != name ? name : nullptr);
			}
		};

		template<class VariableType>
		static const char* getVariableName(VariableType* variableAddress) {
			return VariableName<sizeof...(Registers) - 1>::get(variableAddress);

		}

	};


	using SQLTypes = SQL::Types;
	using SQLCConst = SQL::ColumnConstraints;
	using SQLTConst = SQL::TableConstraints;
	using MainTableType = DebugYourselfDatabaseTable<
		SQLCConst::PrimaryKey<SQLTypes::INTEGER>,
		SQLTypes::TEXT,
		SQLTypes::TEXT,
		SQLTypes::INTEGER,
		SQLTypes::REAL,
		SQLTypes::TEXT,
		SQLTypes::INTEGER,
		SQLTypes::TEXT,
		SQLTypes::INTEGER,
		SQLTypes::INTEGER,
		SQLTypes::REAL,
		SQLTypes::TEXT>;

	using TagsTableType = DebugYourselfDatabaseTable<
		SQLCConst::PrimaryKey<SQLTypes::INTEGER>,
		SQLTypes::TEXT>;

	using MainTable_TagsType = DebugYourselfDatabaseTable
		<SQLTypes::INTEGER, SQLTypes::INTEGER, SQLTConst::ForeignKey, SQLTConst::ForeignKey>;

	struct LoggingDatabase {
	public:
		LoggingDatabase(MainTableType& main, TagsTableType& tags, MainTable_TagsType& main_tags) :
			mainTable(main),
			tagsTable(tags),
			main_tagsTable(main_tags)
		{}
		MainTableType& mainTable;
		TagsTableType& tagsTable;
		MainTable_TagsType& main_tagsTable;
	};

	static LoggingDatabase getLoggingDatabase() {

		auto t = std::time(nullptr);
		tm tm;
		gmtime_s(&tm, &t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y%m%d%H%M%S");
		//"%d-%m-%Y %H-%M-%S"
		static DebugYourselfDatabase database("DebugYourselfDatabase-" + oss.str() + ".db");

		static MainTableType mainTable(&database, "MainTable",
			"ID",
			"Class",
			"ObjectName",
			"Object_Address",
			"Object_Time",
			"Function_Name",
			"Function_Address",
			"Variable_Name",
			"Variable_Address",
			"Rank",
			"Time",
			"Message");

		static TagsTableType tagsTable(&database, "TagsTable",
			"ID",
			"Tag");

		static MainTable_TagsType mainTable_Tags(&database, "MainTable_Tags",
			"MainTable_ID", "TagsTable_ID", SQLTConst::ForeignKey("MainTable_ID", "MainTable", "ID"), SQLTConst::ForeignKey("TagsTable_ID", "TagsTable", "ID"));

		return LoggingDatabase(mainTable, tagsTable, mainTable_Tags);
	}

	static void end() {
		getLoggingDatabase().mainTable.push();
		getLoggingDatabase().tagsTable.push();
		getLoggingDatabase().main_tagsTable.push();

	}

	template<auto fPointer, class FPType = decltype(fPointer)>
	struct PtrUnion {};

	template<auto fPointer, class R, class T, class... Args>
	struct PtrUnion<fPointer, R(T::*)(Args...)> {
		union Union
		{
			R(T::* f)(Args...);
			uintmax_t buf;
		};
	};

	template<auto fp>
	static intmax_t extractFunctionPointerAsInteger() {
		typename PtrUnion<fp>::Union caster;
		caster.f = fp;
		return static_cast<intmax_t>(caster.buf);
	}

	inline static SQLTypes::INTEGER mainTableIndex = 1;
	inline static SQLTypes::INTEGER tagsTableIndex = 1;

	//Implement compile-time debug() tag check.

	inline static std::unordered_map<std::string, SQLTypes::INTEGER> existingTags;

	struct LoggingAction {
		virtual void operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) = 0;
	};

	struct LoggingCondition {
		virtual bool operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) = 0;
	};

	struct AlwaysTrue : public LoggingCondition {
		bool operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) override {

			return true;
		};
	};

	template<class Condition = AlwaysTrue>
	struct DirectLogger : public LoggingAction {
		void operator()(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags) override {

			if (Condition()(
				class_name,
				object_name,
				object,
				objectTime,
				function_name,
				function,
				variable_name,
				variable,
				rank,
				time,
				message,
				tags
				)) {
				std::string taglist = "{";
				for (SQLTypes::TEXT tag : tags) {
					taglist += std::string(tag) + ", ";
				}
				taglist.erase(taglist.size() - 2, 2);
				taglist += "}";

				std::cout <<
					"Class_Name" << "\t" <<
					"Object_Name" << "\t" <<
					"Function_Name" << "\t" <<
					"Variable_Name" << "\t" <<
					"Time" << "\n" <<
					class_name << "\t" <<
					object_name << "\t" <<
					function_name << "\t" <<
					variable_name << "\t" <<
					time << "\n" <<
					message << "\n" << "\n\n";
			}
		}
	};

	template<class CFRB, class OVRB, class GFRB, class FVRB, class PreAction = DirectLogger<>>
	struct Dependencies {
		std::unordered_map<std::string, std::function<void(void)>> debugTagMap;

		void createTag(std::string name, std::function<void(void)> callback) {
			debugTagMap.emplace(name, callback);
		}

		struct DBTags {
			inline static const char* GLOBAL = "#GLOBAL";
			inline static const char* NULLVAR = "#NULL";
			inline static const char* UNKNOWN = "#UNKNOWN";
		};

		static void publish(
			SQLTypes::TEXT class_name,
			SQLTypes::TEXT object_name,
			SQLTypes::INTEGER object,
			SQLTypes::REAL objectTime,
			SQLTypes::TEXT function_name,
			SQLTypes::INTEGER function,
			SQLTypes::TEXT variable_name,
			SQLTypes::INTEGER variable,
			SQLTypes::INTEGER rank,
			SQLTypes::REAL time,
			SQLTypes::TEXT message,
			std::vector<SQLTypes::TEXT> tags)
		{
			PreAction()(
				class_name,
				object_name == nullptr ? DBTags::UNKNOWN : object_name,
				object,
				objectTime,
				function_name == nullptr ? DBTags::UNKNOWN : function_name,
				function,
				variable_name == nullptr ? DBTags::UNKNOWN : variable_name,
				variable,
				rank,
				time,
				message,
				tags
				);


			getLoggingDatabase().mainTable.add(
				mainTableIndex,
				class_name,
				object_name == nullptr ? DBTags::UNKNOWN : object_name,
				object,
				objectTime,
				function_name == nullptr ? DBTags::UNKNOWN : function_name,
				function,
				variable_name == nullptr ? DBTags::UNKNOWN : variable_name,
				variable,
				rank,
				time,
				message);

			for (SQLTypes::TEXT tag : tags) {
				auto it = existingTags.find(tag);
				if (it == existingTags.end()) {
					getLoggingDatabase().tagsTable.add(
						tagsTableIndex,
						tag);
					existingTags.emplace(tag, tagsTableIndex);

					getLoggingDatabase().main_tagsTable.add(
						mainTableIndex,
						tagsTableIndex
					);

					tagsTableIndex++;
				}
				else {
					getLoggingDatabase().main_tagsTable.add(
						mainTableIndex,
						it->second
					);
				}
			}

			mainTableIndex++;
		}


		template<class FunctionType, class OtherType>
		union Union {};

		template<class R, class T, class... Args, class OtherType>
		union Union<R(T::*)(Args...), OtherType>
		{
			R(T::* f)(Args...);
			OtherType buf;
		};

		template<class R, class... Args, class OtherType>
		union Union<R(*)(Args...), OtherType>
		{
			R(*f)(Args...);
			OtherType buf;
		};

		template<class FunctionType>
		struct StripFunctionType {};

		template<class R, class T, class... Args>
		struct StripFunctionType<R(T::*)(Args...)> {
		public:
			template<class To>
			inline static To get(R(T::* f)(Args...)) {
				Union<decltype(f), To> ptr;
				ptr.f = f;

				return static_cast<To>(ptr.buf);
			}
		};

		template<class R, class... Args>
		struct StripFunctionType<R(*)(Args...)> {
		public:
			template<class To>
			inline static To get(R(*f)(Args...)) {
				Union<decltype(f), To> ptr;
				ptr.f = f;

				return static_cast<To>(ptr.buf);
			}
		};


		class FunctionPointer {
		public:
			template<class FP>
			FunctionPointer(FP fp) : ptr(StripFunctionType<FP>::template get<uintmax_t>(fp)) {}

			uintmax_t ptr;
		};

		template<class From>
		struct StripVariableType {

			template<class To>
			static To get(From from) {
				return reinterpret_cast<To>(from);
			}
		};

		struct VariablePointer {
			template<class VP>
			VariablePointer(VP vp) : ptr(StripVariableType<VP>::template get<uintmax_t>(vp)) {}

			uintmax_t ptr;
		};

		template<auto functionPointer, class Type = decltype(functionPointer)>
		struct GetNames {};

		template<auto functionPointer, class R, class C, class... Args>
		struct GetNames<functionPointer, R(C::*)(Args...)> {
		public:
			inline static const char* className = CFRB::template getClassName<functionPointer>();
			inline static const char* functionName = CFRB::template getFunctionName<functionPointer>();
			template<class Variable> static const char* variableName(Variable* v) {
				return OVRB::getVariableName(v);
			}
		};

		template<auto functionPointer, class R, class... Args>
		struct GetNames<functionPointer, R(*)(Args...)> {
		public:
			inline static const char* className = DBTags::GLOBAL;
			inline static const char* functionName = GFRB::template getFunctionName<functionPointer>();
			template<class Variable> static const char* variableName(Variable* v) {
				return FVRB::getVariableName(v);
			}
		};

		template<>
		struct GetNames<nullptr, std::nullptr_t> {
		public:
			inline static const char* className = DBTags::GLOBAL;
			inline static const char* functionName = GFRB::template getFunctionName<functionPointer>();
			template<class Variable> static const char* variableName(Variable* v) {
				return FVRB::getVariableName(v);
			}
		};

		template<auto functionPointer> inline static const char* GetClassName_v = GetNames<functionPointer>::className;

		template<auto functionPointer> inline static const char* GetFunctionName_v = GetNames<functionPointer>::functionName;

		template<auto functionPointer> inline static auto GetVariableName_f = []<class Variable>(Variable * v) -> const char* { return GetNames<functionPointer>::variableName(v); };
		


		template<auto functionPointer, class Variable> struct fv_Debug { public:
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				
				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}

			static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
					{}
				);

			}
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}
			static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}

			static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
			static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
			static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}
			static void debug(Variable* variable, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				);

			}
		};

		template<auto functionPointer> struct f_Debug { public:
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}

			static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}
			static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}

			static void debug(GetClassFromFunctionPointer<functionPointer>* object, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
			static void debug(SQLTypes::INTEGER rank, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
			static void debug(std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}
			static void debug(std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					-1,
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					0,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				);

			}
		};

		template<class Variable> struct v_Debug { public:
			static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

				const char* variable_name = OVRB::getObjectName(variable);
				auto objectPointer = OVRB::getObject(variable);
				SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
				variable_name = variable_name != nullptr ? variable_name : FVRB::getVariableName();

				publish(
					GetClassName_v<functionPointer>,
					nullptr,
					0,
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}

			static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
			static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}

			static void debug(Variable* variable, std::string message) {

				publish(
					GetClassName_v<functionPointer>,
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					GetFunctionName_v<functionPointer>,
					extractFunctionPointerAsInteger<functionPointer>(),
					GetVariableName_f<functionPointer>(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					std::vector<SQLTypes::TEXT>()
				{}
				);

			}
		};

		struct _Debug { public:
			static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(SQLTypes::INTEGER rank, std::string message) {

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
			static void debug(std::vector<SQLTypes::TEXT> tags, std::string message) {

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(std::string message) {

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
		};

		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> struct fvm_Debug { public:
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					CFRB::template getClassName<functionPointer>(),
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					CFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					OVRB::getVariableName(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);

			}
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					CFRB::template getClassName<functionPointer>(),
					OVRB::getObjectName(object),
					reinterpret_cast<SQLTypes::INTEGER>(object),
					OVRB::getInstanceTime(object),
					CFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					OVRB::getVariableName(variable),
					reinterpret_cast<SQLTypes::INTEGER>(variable),
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);

			}
			static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				const char* variable_name = OVRB::getObjectName(variable);
				auto objectPointer = OVRB::getObject(variable);
				SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
				variable_name = variable_name != nullptr ? variable_name : FVRB::getVariableName();

				publish(
					DBTags::GLOBAL,
					DBTags::NULLVAR,
					object,
					OVRB::getInstanceTime(objectPointer),
					GFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					variable_name,
					variable,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				const char* variable_name = OVRB::getObjectName(variable);
				auto objectPointer = OVRB::getObject(variable);
				SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
				variable_name = variable_name != nullptr ? variable_name : FVRB::getVariableName();

				publish(
					DBTags::GLOBAL,
					DBTags::NULLVAR,
					object,
					OVRB::getInstanceTime(objectPointer),
					GFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					variable_name,
					variable,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
		};

		template<auto functionPointer, class MessageAssembler, class... Args> struct fm_Debug { public:
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					CFRB::template getClassName<functionPointer>(),
					OVRB::getObjectName(object),
					object,
					OVRB::getInstanceTime(object),
					CFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					CFRB::template getClassName<functionPointer>(),
					OVRB::getObjectName(object),
					object,
					OVRB::getInstanceTime(object),
					CFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
			static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					CFRB::template getClassName<functionPointer>(),
					nullptr,
					nullptr,
					0,
					CFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(SQLTypes::INTEGER rank, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					CFRB::template getClassName<functionPointer>(),
					nullptr,
					nullptr,
					0,
					CFRB::template getFunctionName<functionPointer>(),
					extractFunctionPointerAsInteger<functionPointer>(),
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
		};

		template<class Variable, class MessageAssembler, class... Args> struct vm_Debug { public:
			static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				const char* variable_name = OVRB::getObjectName(variable);
				auto objectPointer = OVRB::getObject(variable);
				SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
				variable_name = variable_name != nullptr ? variable_name : FVRB::getVariableName();

				publish(
					nullptr,
					nullptr,
					object,
					OVRB::getInstanceTime(objectPointer),
					nullptr,
					nullptr,
					variable_name,
					variable,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				const char* variable_name = OVRB::getObjectName(variable);
				auto objectPointer = OVRB::getObject(variable);
				SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
				variable_name = variable_name != nullptr ? variable_name : FVRB::getVariableName();

				publish(
					nullptr,
					nullptr,
					object,
					OVRB::getInstanceTime(objectPointer),
					nullptr,
					nullptr,
					variable_name,
					variable,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
		};

		template<class MessageAssembler, class... Args> struct m_Debug { public:
			static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(SQLTypes::INTEGER rank, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					rank,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
			static void debug(std::vector<SQLTypes::TEXT> tags, Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					tags
				);
			}
			static void debug(Args... args) {

				std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

				publish(
					nullptr,
					nullptr,
					nullptr,
					0,
					nullptr,
					nullptr,
					nullptr,
					nullptr,
					0,
					std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
					message.c_str(),
					{}
				);
			}
		};

		
		template<auto functionPointer, class Variable, class Func> struct fvc_Debug { public:
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { fv_Debug<functionPointer, Variable>::debug(object, variable, rank, tags, message); }
			}
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
				if (condition()) { fv_Debug<functionPointer, Variable>::debug(object, variable, rank, message); }
			}
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { fv_Debug<functionPointer, Variable>::debug(variable, rank, tags, message); }
			}
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
				if (condition()) { fv_Debug<functionPointer, Variable>::debug(variable, rank, message); }
			}
		};

		template<auto functionPointer, class Func> struct fc_Debug { public:
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { f_Debug<functionPointer>::debug(object, rank, tags, message); }
			}
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {
				if (condition()) { f_Debug<functionPointer>::debug(object, rank, message); }
			}
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { f_Debug<functionPointer>::debug(rank, tags, message); }
			}
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::string message) {
				if (condition()) { f_Debug<functionPointer>::debug(rank, message); }
			}
		};

		template<class Variable, class Func> struct vc_Debug { public:
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { v_Debug<Variable>::debug(variable, rank, tags, message); }
			}
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
				if (condition()) { v_Debug<Variable>::debug(variable, rank, message); }
			}
		};

		template<class Func> struct c_Debug { public:
		public:
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { _Debug::debug(rank, tags, message); }
			}
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::string message) {
				if (condition()) { _Debug::debug(rank, message); }
			}
			static void debug(std::function<Func> condition, std::vector<SQLTypes::TEXT> tags, std::string message) {
				if (condition()) { _Debug::debug(tags, message); }
			}
			static void debug(std::function<Func> condition, std::string message) {
				if (condition()) { _Debug::debug(message); }
			}
		};

		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> struct fvmc_Debug { public:
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) { 
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fvm_Debug<functionPointer,Variable, MessageAssembler, Args...>::debug(object, variable, rank, tags, message); }
			}
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fvm_Debug<functionPointer, Variable, MessageAssembler, Args...>::debug(object, variable, rank, message);
				}
			}
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fvm_Debug<functionPointer, Variable, MessageAssembler, Args...>::debug(variable, rank, tags, message);
				}
			}
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fvm_Debug<functionPointer, Variable, MessageAssembler, Args...>::debug(variable, rank, message);
				}
			}
		};

		template<auto functionPointer, class MessageAssembler, class... Args, class Func> struct fmc_Debug { public:
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fm_Debug<functionPointer, MessageAssembler, Args...>::debug(object, rank, tags, message);
				}
			}
			static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fm_Debug<functionPointer, MessageAssembler, Args...>::debug(object, rank, message);
				}
			}
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fm_Debug<functionPointer, MessageAssembler, Args...>::debug(rank, tags, message);
				}
			}
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					fm_Debug<functionPointer, MessageAssembler, Args...>::debug(rank, message);
				}
			}
		};

		template<class Variable, class MessageAssembler, class... Args, class Func> struct vmc_Debug { public:
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					vm_Debug<Variable, MessageAssembler, Args...>::debug(variable, rank, tags, message);
				}
			}
			static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					vm_Debug<Variable, MessageAssembler, Args...>::debug(variable, rank, message);
				}
			}
		};

		template<class MessageAssembler, class... Args, class Func> struct mc_Debug { public:
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					m_Debug<MessageAssembler, Args...>::debug(rank, tags, message);
				}
			}
			static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					m_Debug<MessageAssembler, Args...>::debug(rank, message);
				}
			}
			static void debug(std::function<Func> condition, std::vector<SQLTypes::TEXT> tags, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					m_Debug<MessageAssembler, Args...>::debug(tags, message);
				}
			}
			static void debug(std::function<Func> condition, Args... args) {
				if (condition()) {
					std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
					m_Debug<MessageAssembler, Args...>::debug(message);
				}
			}
		};
		
		


	};

	
	template<auto function>
	struct DebugFunctionLookup {
	public:
		inline static bool exist = false;
	};

	template<class Variable>
	struct DebugVariableTypeLookup {
	public:
		inline static bool exist = false;
	};

	template<auto functionPointer = nullptr, class Variable = void>
	class DebugLinker {
	public:
		inline static std::function<void(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message)> fPtr = nullptr;
	};

	template<class Variable>
	class DebugLinker<nullptr, Variable> {
	public:

	};

	template<>
	class DebugLinker<nullptr, void> {
		
	};

	class Debug {
		template<auto functionPointer, class Variable> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) { 
			DebugFunctionLookup<functionPointer>::exist 
		}
	};

	
	template<class T = void>
	class BinderLinker {};

	template<class... Args>
	class BinderLinker<ObjectVariableRegister<Args...>> {
	public:
		inline static std::function<void(ObjectVariableRegister<Args...>)> add;
	};

	template<class... Args>
	class BinderLinker<FundamentalVariableRegister<Args...>> {
	public:
		inline static std::function<void(FundamentalVariableRegister<Args...>)> add;
	};

	template<>
	class BinderLinker<void> {
	public:

		template<auto functionPointer, class Variable>
		struct fv_debug {
		public:
			template<class... Params>
			struct store {
			public:
				std::function<void(Params...)> storedFunction;
			};
		};


		
		template<auto functionPointer, class Variable> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer> static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer> static void debug(SQLTypes::INTEGER rank, std::string message) {}
		template<class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Variable> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {}

		static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		static void debug(SQLTypes::INTEGER rank, std::string message) {}
		static void debug(std::vector<SQLTypes::TEXT> tags, std::string message) {}
		static void debug(std::string message) {}


		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args> static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {}

		template<class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args> static void debug(SQLTypes::INTEGER rank, Args... args) {}
		template<class MessageAssembler, class... Args> static void debug(std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args> static void debug(Args... args) {}




		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<auto functionPointer, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::string message) {}
		template<class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Variable, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {}

		template<class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::string message) {}
		template<class Func> static void debug(std::function<Func> condition, std::vector<SQLTypes::TEXT> tags, std::string message) {}
		template<class Func> static void debug(std::function<Func> condition, std::string message) {}

		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, GetClassFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<auto functionPointer, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class Variable, class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {}

		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, SQLTypes::INTEGER rank, Args... args) {}
		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, std::vector<SQLTypes::TEXT> tags, Args... args) {}
		template<class MessageAssembler, class... Args, class Func> static void debug(std::function<Func> condition, Args... args) {}

	};



	template<class CFRs, class OVRs, class GFRs, class FVRs>
	class BinderCollection {};

	template<template<class...> class Container, class... CFRs, class... OVRs, class... GFRs, class... FVRs>
	class BinderCollection<Container<CFRs...>, Container<OVRs...>, Container<GFRs...>, Container<FVRs...>> {
	public:

		inline static ClassFunctionRegisterBinder<CFRs...> CFRB;

		inline static ObjectVariableRegisterBinder<OVRs...> OVRB;

		inline static GlobalFunctionRegisterBinder<GFRs...> GFRB;

		inline static FundamentalVariableRegisterBinder<FVRs...> FVRB;

		template<class Register>
		inline static auto add = [&](Register OVR) { OVRB.add(OVR); };


		template<class PreAction = DirectLogger<>>
		using Logger = Dependencies<decltype(CFRB), decltype(CFRB), decltype(CFRB), decltype(CFRB), PreAction>;

		inline static auto debug = [&](auto... args) { Logger<>::debug(args...); };

		static void Initialize() {
			((BinderLinker<OVRs>::add = add<OVRs>), ...);
			BinderLinker<void>::ldebug = debug;
		}

		


	};

};


	template<bool enable>
	using DebugYourself = std::conditional_t<enable, DebugDebugYourself, ReleaseDebugYourself>;
	
}