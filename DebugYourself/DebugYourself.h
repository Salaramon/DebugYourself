//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////`,~*~^.^~*~^.^~*~§ TABLE OF CONTENT §~*~^.^~*~^.^~*~,´//////
//////                                                      //////
//////   100. Includes                                      //////
//////   200. External Tools                                //////
//////   300. Release Mode                                  //////
//////      ~400. Registers                                 //////
//////      ~500. Binders                                   //////
//////      ~600. Database Aliases                          //////
//////      ~700. Inbuilt Publishing Filters                //////
//////      ~800. Debug Linker                              //////
//////   1000. Debug Mode                                   //////
//////       ~1000. Registers                               //////
//////           ~1000. Class Register                      //////
//////           ~1200. Object Register                     //////
//////           ~1500. Function Register                   //////
//////           ~1600. Variable Register                   //////
//////       ~1800. Binders                                 //////
//////           ~1800. Class Binder                        //////
//////           ~2000. Object Binder                       //////
//////           ~2400. Function Binder                     //////
//////           ~2600. Variable Binder                     //////
//////       ~2900. Inbuilt Publishing Filters              //////
//////       ~3100. Database Aliases                        //////
//////       ~3300. Debug Linker                            //////
//////            ~3500. Debug Calls                        //////
//////   4600. Controllers                                  //////
//////                                                      //////
//////`,~*~^.^~*~^.^~*~^.^~*~^.^§§^.^~*~^.^~*~^.^~*~^.^~*~,´//////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////




























































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


		///////////////////////////
		////////API Utility////////
		///////////////////////////

		inline static std::chrono::time_point<std::chrono::steady_clock> launchTimeStamp = std::chrono::steady_clock::now();



		template<auto... functionPointers>
		using MemberFunctionPointerHeadClass = _GetClassFromFunctionPointer<std::tuple_element_t<0, std::tuple<decltype(functionPointers)...>>>::Class;


		template<class... Args>
			requires (std::conjunction_v<std::is_pointer<Args>...>)
		static std::tuple<Args...> V(Args... pointers) {
			return std::tuple<Args...>(pointers...);
		};

		template<class... Args>
			requires (std::conjunction_v<std::is_same<const char*, Args>...>)
		static std::tuple<Args...> N(Args... names) {
			return std::tuple<Args...>(names...);
		};


		template<class...>
		struct OverloadSelector;

		template<class R, class... Args>
		struct OverloadSelector<R(Args...)> {
		private:
			template<R(*F)(Args...)>
			struct _Get {
				inline static constexpr auto FP = F;
			};

		public:
			template<R(*F)(Args...)>
			inline static constexpr auto Get = _Get<F>::FP;
		};

		template<class C, class R, class... Args>
		struct OverloadSelector<C, R(Args...)> {
		private:
			template<R(C::* F)(Args...)>
			struct _Get {
				inline static constexpr auto FP = F;
			};

		public:
			template<R(C::* F)(Args...)>
			inline static constexpr auto Get = _Get<F>::FP;
		};















































































		///////////////////////////////////////
		////////Class Function Register////////
		///////////////////////////////////////

		template<auto... functionPointers>
		//requires std::conjunction_v<
		//		std::is_same<MemberFunctionPointerHeadClass<functionPointers...>, MemberFunctionPointerHeadClass<functionPointers>>...>
		struct ClassRegister {
		public:
			template<class... Parameters>
			ClassRegister(Parameters... names) {};

			template<class... Parameters>
			ClassRegister(std::tuple<Parameters...> names) {};
		};























































		///////////////////////////////////////
		////////Object Variable Register///////
		///////////////////////////////////////

		template<class ObjectType, class... Types>
		struct ObjectRegister {
		public:

			ObjectRegister() {};

			template<class... Parameters>
			ObjectRegister(ObjectType* object, std::tuple<Types*...> variables) {};

			template<class... Parameters>
			ObjectRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables) {};

			template<class... Parameters>
			ObjectRegister(ObjectType* object, std::tuple<Types*...> variables, std::tuple<Parameters...> names) {};

			template<class... Parameters>
			ObjectRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables, std::tuple<Parameters...> names) {};

			ObjectRegister(const ObjectRegister& other) {};

			ObjectRegister(ObjectRegister&& other) {}
		};

































































































































		////////////////////////////////////////
		////////Global Function Register////////
		////////////////////////////////////////

		template<auto... functionPointers>
		struct FunctionRegister {
		public:
			template<class... Parameters>
			FunctionRegister(Parameters... names) {};

			template<class... Parameters>
			FunctionRegister(std::tuple<Parameters...> names) {};
		};
































































		////////////////////////////////////////////
		////////Fundamental Variable Register///////
		////////////////////////////////////////////

		template<class... Types>
		struct VariableRegister {
		public:

			VariableRegister(){};

			template<class... Parameters>
			VariableRegister(std::tuple<Types*...> variables) {};

			template<class... Parameters>
			VariableRegister(std::tuple<Types*...> variables, std::tuple<Parameters...> names) {};

			VariableRegister(const VariableRegister& other) {};
		};



		template<class T>
		struct Tuplify {
			using type = int;
		};

		template<template<class...> class Template, class... Args>
		struct Tuplify<Template<Args...>> {
		public:
			using type = std::tuple<Args...>;
		};

		template<class T1, class T2>
		struct TemplateIsSame {
		public:
			inline static constexpr bool value = false;
		};

		template<template<class...> class Template, class... Args1, class... Args2>
		struct TemplateIsSame<Template<Args1...>, Template<Args2...>> {
		public:
			inline static constexpr bool value = true;
		};

		template<class T1, class T2>
		inline static constexpr bool TemplateIsSame_v = TemplateIsSame<T1, T2>::value;

		template<class T>
		using Tuplify_t = Tuplify<T>::type;


		template<class Type, class Tuple>
		struct TypeIsInTuple {};

		template<class Type, class... Args>
		struct TypeIsInTuple<Type, std::tuple<Args...>> {
			inline static constexpr bool value = std::disjunction_v<std::is_same<Type, Args>...>;
		};


		template<class Tuple, class ResultTuple = std::tuple<>>
		struct UniqueTuple {};

		template<class T, class... Args, class ResultTuple>
		struct UniqueTuple<std::tuple<T, Args...>, ResultTuple> {
			using type = std::conditional_t<
				TypeIsInTuple<T, ResultTuple>::value,
				UniqueTuple<std::tuple<Args...>, ResultTuple>,
				UniqueTuple<std::tuple<Args...>, typename std::_Tuple_cat1<ResultTuple, std::tuple<T>>::type>
			>::type;
		};

		template<class T, class ResultTuple>
		struct UniqueTuple<std::tuple<T>, ResultTuple> {
			using type = std::conditional_t<
				TypeIsInTuple<T, ResultTuple>::value,
				ResultTuple,
				typename std::_Tuple_cat1<ResultTuple, std::tuple<T>>::type
			>;
		};





























































		template<class... Registers>
		struct ClassBinder {
		public:

			ClassBinder() {}
			ClassBinder(Registers... registers) {}
		
		};















































































		template<class... Registers>
		struct ObjectBinder {
			ObjectBinder() {}
			ObjectBinder(Registers&...) {}
		};




















































































		template<class... Registers>
		struct FunctionBinder {
		public:
			FunctionBinder(Registers... registers) {}
		};























































































		template<class... Registers>
		struct VariableBinder {
			
			VariableBinder() {}
			VariableBinder(Registers...) {}

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
			static DebugYourselfDatabase database("log/DebugYourselfDatabase-" + oss.str() + ".db");

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
		struct PtrUnion {
			union Union
			{
				decltype(fPointer) f;
				uintmax_t buf;
			};
		};

		template<auto fPointer, class R, class T, class... Args>
		struct PtrUnion<fPointer, R(T::*)(Args...)> {
			union Union
			{
				R(T::* f)(Args...);
				uintmax_t buf;
			};
		};

		template<auto fPointer, class R, class... Args>
		struct PtrUnion<fPointer, R(*)(Args...)> {
			union Union
			{
				R(*f)(Args...);
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

		struct AlwaysFalse : public LoggingCondition {
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

				return false;
			};
		};

		template<class Condition = AlwaysFalse>
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
					taglist.erase(taglist.size() - 1, 2);
					taglist += "}";

					std::cout <<
						"Class_Name" << "\t" <<
						"Object_Name" << "\t" <<
						"Function_Name" << "\t" <<
						"Variable_Name" << "\t" <<
						"Time" << "\n" <<
						(class_name ? class_name : "") << "\t" <<
						(object_name ? object_name : "") << "\t" <<
						(function_name ? function_name : "") << "\t" <<
						(variable_name ? variable_name : "") << "\t" <<
						time << "\n" <<
						message << "\n" << "\n\n";
				}
			}
		};

		using No_CB = ClassBinder<ClassRegister<nullptr>>;
		using No_OB = ObjectBinder<ObjectRegister<std::nullptr_t>>;
		using No_FB = FunctionBinder<FunctionRegister<nullptr>>;
		using No_VB = VariableBinder<VariableRegister<std::nullptr_t>>;























































































		static void enablePublish() {}

		static void disablePublish() {}



		template<class CB, class OB, class FB, class VB, class Publish = AlwaysTrue, class PreAction = DirectLogger<>>
		struct Dependencies {
		public:


			struct DBTags {
				inline static const char* GLOBAL = "#GLOBAL";
				inline static const char* NULLVAR = "#NULL";
				inline static const char* UNKNOWN = "#UNKNOWN";
			};



			template<auto functionPointer, class Type = decltype(functionPointer)>
			struct GetNames {
			public:
				template<class Variable> static const char* variableName(Variable* v) {
					return nullptr;
				}
				inline static const char* functionName() {
					return FB::template getFunctionName<functionPointer>();
				}
				inline static std::string className() {
					return classToString<Type>();
				}
			};

			template<auto functionPointer, class R, class C, class... Args>
			struct GetNames<functionPointer, R(C::*)(Args...)> {
			public:
				inline static const char* functionName() {
					return CB::template getFunctionName<functionPointer>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return OB::getVariableName(v);
				}
				inline static const char* className() {
					return CB::template getClassName<functionPointer>();
				}
			};

			template<auto functionPointer, class R, class... Args>
			struct GetNames<functionPointer, R(*)(Args...)> {
			public:
				inline static const char* className = DBTags::GLOBAL;
				inline static const char* functionName() {
					return FB::template getFunctionName<functionPointer>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return VB::getVariableName(v);
				}
			};

			template<auto functionPointer, class R, class C, class... Args>
			struct GetNames<functionPointer, R(C::*)(Args...) const> {
			public:
				inline static const char* functionName() {
					return CB::template getFunctionName<functionPointer>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return OB::getVariableName(v);
				}
				inline static const char* className() {
					return CB::template getClassName<functionPointer>();
				}
			};

			template<>
			struct GetNames<nullptr, std::nullptr_t> {
			public:
				inline static const char* className = DBTags::GLOBAL;
				inline static const char* functionName() {
					FB::template getFunctionName<nullptr>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return VB::getVariableName(v);
				}
			};




























































			struct Class {
			public:
				template<auto functionPointer, class... Args>
				static void debug(Args...) {}
				template<class... Args>
				static void debug(Args...) {}
			};

			struct Static {
				template<auto functionPointer, class... Args>
				static void debug(Args...) {}
				template<class... Args>
				static void debug(Args...) {}
			};

			struct Global {
				template<auto functionPointer, class... Args>
				static void debug(Args...) {}
				template<class... Args>
				static void debug(Args...) {}
			};

			struct Constructor {
			public:
				template<class... Args>
				static void debug(Args...) {}
			};

			struct Special {
			public:

				struct Static {
					template<auto functionPointer, class... Args>
					static void debug(Args...) {}
				};

				struct Global {
					template<auto functionPointer, class... Args>
					static void debug(Args...) {}
				};
			};

			struct Assemblers {
			public:

				struct Class {
				public:
					template<auto functionPointer, class... Args>
					static void debug(Args...) {}

				};

				struct Global {
					template<auto functionPointer, class... Args>
					static void debug(Args...) {}
					template<class... Args>
					static void debug(Args...) {}

				};

				struct Constructor {
				public:
					template<class... Args>
					static void debug(Args...) {}
				};

				struct Special {
				public:
					template<auto functionPointer, class... Args>
					static void debug(Args...) {}
				};
			};

		};

	};
















































































































	class DebugDebugYourself {
	public:

		DebugDebugYourself() {}


		///////////////////////////
		////////API Utility////////
		///////////////////////////

		inline static std::chrono::time_point<std::chrono::steady_clock> launchTimeStamp = std::chrono::steady_clock::now();



		template<auto... functionPointers>
		using MemberFunctionPointerHeadClass = _GetClassFromFunctionPointer<std::tuple_element_t<0, std::tuple<decltype(functionPointers)...>>>::Class;


		template<class... Args>
			requires (std::conjunction_v<std::is_pointer<Args>...>)
		static std::tuple<Args...> V(Args... pointers) {
			return std::tuple<Args...>(pointers...);
		};

		template<class... Args>
			requires (std::conjunction_v<std::is_same<const char*, Args>...>)
		static std::tuple<Args...> N(Args... names) {
			return std::tuple<Args...>(names...);
		};


		template<class...>
		struct OverloadSelector;

		template<class R, class... Args>
		struct OverloadSelector<R(Args...)> {
		private:
			template<R(*F)(Args...)>
			struct _Get {
				inline static constexpr auto FP = F;
			};

		public:
			template<R(*F)(Args...)>
			inline static constexpr auto Get = _Get<F>::FP;
		};

		template<class C, class R, class... Args>
		struct OverloadSelector<C, R(Args...)> {
		private:
			template<R(C::* F)(Args...)>
			struct _Get {
				inline static constexpr auto FP = F;
			};

		public:
			template<R(C::* F)(Args...)>
			inline static constexpr auto Get = _Get<F>::FP;
		};















































































		///////////////////////////////////////
		////////Class Function Register////////
		///////////////////////////////////////

		template<auto... functionPointers>
		//requires std::conjunction_v<
		//		std::is_same<MemberFunctionPointerHeadClass<functionPointers...>, MemberFunctionPointerHeadClass<functionPointers>>...>
		struct ClassRegister {
		public:
			template<class... Parameters>
				requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			ClassRegister(Parameters... names) :
				associatedFunctions(functionPointers...),
				associatedFunctionNames(DefaultTuple<sizeof...(functionPointers), const char*, nullptr>::get(names...))
			{};

			template<class... Parameters>
				requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			ClassRegister(std::tuple<Parameters...> names) :
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
		struct ObjectRegister {
		public:

			ObjectRegister() :
				associatedObject(nullptr),
				associatedVariables(std::tuple<Types*...>()),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),
				objectName(nullptr),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};

			template<class... Parameters>
			//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			ObjectRegister(ObjectType* object, std::tuple<Types*...> variables) :
				associatedObject(object),
				associatedVariables(variables),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),
				objectName(nullptr),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};

			template<class... Parameters>
			//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			ObjectRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables) :
				associatedObject(object),
				associatedVariables(variables),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),
				objectName(objectName),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};

			template<class... Parameters>
			//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			ObjectRegister(ObjectType* object, std::tuple<Types*...> variables, std::tuple<Parameters...> names) :
				associatedObject(object),
				associatedVariables(variables),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(names)),
				objectName(nullptr),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};

			template<class... Parameters>
			//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			ObjectRegister(ObjectType* object, const char* objectName, std::tuple<Types*...> variables, std::tuple<Parameters...> names) :
				associatedObject(object),
				associatedVariables(variables),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(names)),
				objectName(objectName),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};


			//Copy constructor
			ObjectRegister(const ObjectRegister& other) :
				associatedObject(other.associatedObject),
				associatedVariables(other.associatedVariables),
				associatedVariableNames(other.associatedVariableNames),
				objectName(other.objectName),

				timeStamp(other.timeStamp),
				instanceID(++instanceCount)
			{};

			ObjectRegister(ObjectRegister&& other) :
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

			~ObjectRegister() {
				cleanBinder(reinterpret_cast<void*>(associatedObject));
			}


			ObjectRegister& operator=(const ObjectRegister& other) {
				associatedObject = other.associatedObject;
				associatedVariables = other.associatedVariables;
				associatedVariableNames = other.associatedVariableNames;
				objectName = other.objectName;

				timeStamp = other.timeStamp;
				instanceID = ++instanceCount;

				return *this;
			}

			ObjectRegister& operator=(ObjectRegister&& other) {
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

			std::function<void(void*)> cleanBinder = [](void*) {};
		};

































































































































		////////////////////////////////////////
		////////Global Function Register////////
		////////////////////////////////////////

		template<auto... functionPointers>
		struct FunctionRegister {
		public:
			template<class... Parameters>
				requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			FunctionRegister(Parameters... names) :
				associatedFunctions(functionPointers...),
				associatedFunctionNames(DefaultTuple<sizeof...(functionPointers), const char*, nullptr>::get(names...))
			{};

			template<class... Parameters>
				requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			FunctionRegister(std::tuple<Parameters...> names) :
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
		struct VariableRegister {
		public:

			VariableRegister() :
				associatedVariables(std::tuple<Types*...>()),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};

			template<class... Parameters>
			//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			VariableRegister(std::tuple<Types*...> variables) :
				associatedVariables(variables),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(std::tuple<>())),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};

			template<class... Parameters>
			//requires (sizeof...(Parameters) <= sizeof...(functionPointers) && std::conjunction_v<std::is_same<char const*, Parameters>...>)
			VariableRegister(std::tuple<Types*...> variables, std::tuple<Parameters...> names) :
				associatedVariables(variables),
				associatedVariableNames(DefaultTupleFromTuple<UniformTuple<sizeof...(Types), const char*>::tuple, const char*, nullptr>::unpack(names)),

				timeStamp(std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count()),
				instanceID(++instanceCount)
			{};


			//Copy constructor
			VariableRegister(const VariableRegister& other) :
				associatedVariables(other.associatedVariables),
				associatedVariableNames(other.associatedVariableNames),

				timeStamp(other.timeStamp),
				instanceID(other.instanceID)
			{};


			VariableRegister& operator=(const VariableRegister& other) {
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



		template<class T>
		struct Tuplify {
			using type = int;
		};

		template<template<class...> class Template, class... Args>
		struct Tuplify<Template<Args...>> {
		public:
			using type = std::tuple<Args...>;
		};

		template<class T1, class T2>
		struct TemplateIsSame {
		public:
			inline static constexpr bool value = false;
		};

		template<template<class...> class Template, class... Args1, class... Args2>
		struct TemplateIsSame<Template<Args1...>, Template<Args2...>> {
		public:
			inline static constexpr bool value = true;
		};

		template<class T1, class T2>
		inline static constexpr bool TemplateIsSame_v = TemplateIsSame<T1, T2>::value;

		template<class T>
		using Tuplify_t = Tuplify<T>::type;


		template<class Type, class Tuple>
		struct TypeIsInTuple {};

		template<class Type, class... Args>
		struct TypeIsInTuple<Type, std::tuple<Args...>> {
			inline static constexpr bool value = std::disjunction_v<std::is_same<Type, Args>...>;
		};


		template<class Tuple, class ResultTuple = std::tuple<>>
		struct UniqueTuple {};

		template<class T, class... Args, class ResultTuple>
		struct UniqueTuple<std::tuple<T, Args...>, ResultTuple> {
			using type = std::conditional_t<
				TypeIsInTuple<T, ResultTuple>::value,
				UniqueTuple<std::tuple<Args...>, ResultTuple>,
				UniqueTuple<std::tuple<Args...>, typename std::_Tuple_cat1<ResultTuple, std::tuple<T>>::type>
			>::type;
		};

		template<class T, class ResultTuple>
		struct UniqueTuple<std::tuple<T>, ResultTuple> {
			using type = std::conditional_t<
				TypeIsInTuple<T, ResultTuple>::value,
				ResultTuple,
				typename std::_Tuple_cat1<ResultTuple, std::tuple<T>>::type
			>;
		};





























































		template<class... Registers>
		struct ClassBinder {
		public:
			using RegisterCollection = std::_Tuple_cat1<std::conditional_t<TemplateIsSame_v<ClassBinder<>, Registers>, Tuplify_t<Registers>, std::tuple<Registers>>...>::type;

			template<class T>
			struct TupleFromRB {};

			template<class... Args>
			struct TupleFromRB<ClassBinder<Args...>> {
			public:
				static std::tuple<Args...> get(ClassBinder<Args...> reg) {
					return reg.binder;
				}
			};

			template<auto... fps>
			struct TupleFromRB<ClassRegister<fps...>> {
			public:
				static std::tuple<ClassRegister<fps...>> get(ClassRegister<fps...> reg) {
					return std::tuple(reg);
				}
			};

			ClassBinder() {}
			ClassBinder(Registers... registers) {
				ClassBinder<Registers...>::binder = std::tuple_cat(TupleFromRB<Registers>::get(registers)...);
			}
			inline static RegisterCollection binder;
			static void use(Registers... registers) {
				ClassBinder<Registers...>::binder = std::tuple_cat(TupleFromRB<Registers>::get(registers)...);
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
			struct _0_GetFunctionIndexFromRegister<n, functionP, ClassRegister<functionPHead, functionPs...>> {
			public:
				inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : _1_GetFunctionIndexFromRegister<n + 1, functionP, functionPs...>::index;
			};

			template<size_t n, auto functionP, auto functionPHead>
			struct _0_GetFunctionIndexFromRegister<n, functionP, ClassRegister<functionPHead>> {
			public:
				inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : -1;
			};

			template<auto functionP, class CFR>
			inline static constexpr size_t GetFunctionIndexFromRegister = _0_GetFunctionIndexFromRegister<0, functionP, CFR>::index;


			template<auto function, class Tuple>
			struct _GetRegisterFromFunction {};

			template<auto function, class T, class... Args>
			struct _GetRegisterFromFunction<function, std::tuple<T, Args...>> {
			public:
				using Class = std::conditional_t<std::is_same_v<GetClassFromFunctionPointer<function>, typename T::AssociatedClass>, T, typename _GetRegisterFromFunction<function, std::tuple<Args...>>::Class>;
			};

			template<auto function, class T>
			struct _GetRegisterFromFunction<function, std::tuple<T>> {
			public:
				using Class = std::conditional_t<std::is_same_v<GetClassFromFunctionPointer<function>, typename T::AssociatedClass>, T, void>;
			};

			template<auto function>
			using GetRegisterFromFunction = _GetRegisterFromFunction<function, RegisterCollection>::Class;


			template<class TClass, class Tuple>
			struct _GetRegisterFromClass {};

			template<class TClass, class T, class... Args>
			struct _GetRegisterFromClass<TClass, std::tuple<T, Args...>> {
			public:
				using Class = std::conditional_t<std::is_same_v<TClass, typename T::AssociatedClass>, T, typename _GetRegisterFromClass<TClass, std::tuple<Args...>>::Class>;
			};

			template<class TClass, class T>
			struct _GetRegisterFromClass<TClass, std::tuple<T>> {
			public:
				using Class = std::conditional_t<std::is_same_v<TClass, typename T::AssociatedClass>, T, void>;
			};

			template<class TClass>
			using GetRegisterFromClass = _GetRegisterFromClass<TClass, RegisterCollection>::Class;


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

			template<class Class>
			static const char* getClassName() {
				return GetRegisterFromClass<Class>::getClassName();
			}

		};















































































		template<class... Registers>
		struct ObjectBinder {
			using _RegisterCollection = std::_Tuple_cat1<std::conditional_t<TemplateIsSame_v<ObjectBinder<>, Registers>, Tuplify_t<Registers>, std::tuple<Registers>>...>::type;
			using RegisterCollection = UniqueTuple<_RegisterCollection>::type;

			template<class T>
			using Container = std::unordered_map<void*, T*>;

			template<class Tuple>
			struct MakeBinderOfTuple {};


			template<class... Args>
			struct MakeBinderOfTuple<std::tuple<Args...>> {
				using type = std::tuple<Container<Args>...>;
			};

			ObjectBinder() {}
			ObjectBinder(Registers&...) {}

			template<class Register>
			struct _GetObjectTypeFromRegister {};

			template<class ObjectType, class... Args>
			struct _GetObjectTypeFromRegister<ObjectRegister<ObjectType, Args...>> {
				using Type = ObjectType;
			};

			template<class Register>
			using GetObjectTypeFromRegister = _GetObjectTypeFromRegister<Register>;

			inline static MakeBinderOfTuple<RegisterCollection>::type binder;

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

			template<class FullContainer>
			static void cleanBinder(void* address) {
				std::get<FullContainer>(binder).erase(address);
			}

			template<class T>
			struct TupleFromRB {};

			template<class ObjectType, class... Types>
			struct TupleFromRB<Container<ObjectRegister<ObjectType, Types...>>> {
			public:
				using RegType = Container<ObjectRegister<ObjectType, Types...>>;
				static void get(RegType& reg) {
					RegType& binderElement = std::get<RegType>(binder);
					binderElement.insert(reg.begin(), reg.end());
					for (auto it = reg.begin(); it != reg.end(); it++) {
						it->second->cleanBinder = [&](void* address) { cleanBinder<RegType>(address); };
						binderElement.insert({ reinterpret_cast<void*>(it->second->associatedObject), it->second });
					}
				}
			};

			template<class... Args>
			struct TupleFromRB<std::tuple<Container<Args>...>> {
			public:
				static void get(std::tuple<Container<Args>...>& regTuple) {
					(TupleFromRB<Container<Args>>::get(std::get<Container<Args>>(regTuple)), ...);
				}
			};

			template<class ObjectType, class... Types>
			struct TupleFromRB<ObjectRegister<ObjectType, Types...>> {
			public:
				using RegType = ObjectRegister<ObjectType, Types...>;
				static void get(RegType& reg) {
					reg.cleanBinder = [&](void* address) { cleanBinder<Container<RegType>>(address); };
					std::get<Container<RegType>>(binder).emplace(reinterpret_cast<void*>(reg.associatedObject), &reg);
				}
			};

			template<class... Args>
			struct TupleFromRB<ObjectBinder<Args...>> {
			public:
				static void get(ObjectBinder<Args...>& reg) {
					TupleFromRB<decltype(reg.binder)>::get(reg.binder);
				}
			};


			template<class... Register>
			static void add(Register&... reg) {
				(TupleFromRB<Register>::get(reg), ...);
			}


			template<size_t n, class PointerType, class RegisterVector>
			static auto getRegisterIndexFromPointer(PointerType* pointer, RegisterVector& registerVector) {

				for (auto it = registerVector.begin(); it != registerVector.end(); it++) {
					if ((pointer == it->second->getVariablePointer<n>())) {
						return it;
					}
				}

				return registerVector.end();
			}

			template<class RegisterVector>
			struct _GetPointerTypeFromRegisterVector {};

			template<class Register>
			struct _GetPointerTypeFromRegisterVector<Container<Register>> {
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

					auto it = getRegisterIndexFromPointer<n>(pointer, registerVector);
					return (it != registerVector.end()) ?
						it->second->getVariableName<n>() :
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

					auto it = getRegisterIndexFromPointer<0>(pointer, registerVector);
					return (it != registerVector.end()) ?
						it->second->getVariableName<0>() :
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

			template<>
			struct VariableNameFromTuple<-1> {
				template<class PointerType, class RegisterVector>
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
				return VariableName<std::tuple_size_v<RegisterCollection> -1>::get(variableAddress);

			}


			template<size_t n, class Type, class Tuple>
			struct _GetParameterPackIndex {};

			template<size_t n, class Type, class T, class... Args>
			struct _GetParameterPackIndex<n, Type, std::tuple<T, Args...>> {
				inline static constexpr size_t index = std::is_same_v<Type, T> ? n : _GetParameterPackIndex<n + 1, Type, std::tuple<Args...>>::index;
			};

			template<size_t n, class Type, class T>
			struct _GetParameterPackIndex<n, Type, std::tuple<T>> {
				inline static constexpr size_t index = std::is_same_v<Type, T> ? n : -1;
			};

			template<class Type, class Tuple>
			inline static constexpr size_t GetParameterPackIndex = _GetParameterPackIndex<0, Type, Tuple>::index;

			template<class ObjectType, size_t index>
			struct _GetObjectName {
			public:
				static const char* get(ObjectType* objectAddress) {
					constexpr auto& reg = std::get<index>(binder);

					auto it = reg.find(reinterpret_cast<void*>(objectAddress));
					if (it != reg.end()) {
						return it->second->getObjectName();
					}

					return nullptr;
				}
			};

			template<class ObjectType>
			struct _GetObjectName<ObjectType, -1> {
			public:
				static const char* get(ObjectType* objectAddress) {
					return nullptr;
				}
			};


			template<class ObjectType>
			static const char* getObjectName(ObjectType* objectAddress) {
				return _GetObjectName<ObjectType, GetParameterPackIndex<ObjectType, RegisterCollection>>::get(objectAddress);

			}




			template<size_t n, class Variable, class RegMap>
			struct GetVariable {
				static intmax_t get(Variable* variable, RegMap& regMap) {
					for (auto it = regMap.begin(); it != regMap.end(); it++) {
						if (it->second->getVariablePointer<n> == variable) {
							return reinterpret_cast<intmax_t>(it->second->getObject());
						}
					}

					return GetVariable<n - 1, Variable, RegMap>::get(variable, regMap);
				}
			};

			template<class Variable, class RegMap>
			struct GetVariable<0, Variable, RegMap> {
				static intmax_t get(Variable* variable, RegMap& regMap) {
					for (auto it = regMap.begin(); it != regMap.end(); it++) {
						if (it->second->getVariablePointer<0> == variable) {
							return reinterpret_cast<intmax_t>(it->second->getObject());
						}
					}

					return -1;
				}
			};

			template<size_t n, class Variable>
			struct GetObject {
				static intmax_t get(Variable* variable) {
					constexpr size_t varNr = std::tuple_element_t<n, RegisterCollection>::getNumberOfVariables();
					auto& regMap = std::get<n>(binder);

					intmax_t objAddress = GetVariable<varNr, Variable, std::tuple_element_t<n, RegisterCollection>>::get(variable, regMap);
					if (objAddress != -1) {
						return objAddress;
					}

					return GetObject<n - 1, Variable>::get(variable);

				}
			};

			template<class Variable>
			struct GetObject<0, Variable> {
				static intmax_t get(Variable* variable) {
					constexpr size_t varNr = std::tuple_element_t<0, RegisterCollection>::getNumberOfVariables();
					auto& regMap = std::get<0>(binder);

					intmax_t objAddress = GetVariable<varNr, Variable, std::tuple_element_t<0, RegisterCollection>>::get(variable, regMap);
					if (objAddress != -1) {
						return objAddress;
					}

					return -1;

				}
			};



			template<class Variable>
			static intmax_t getObject(Variable* variable) {
				return GetObject<std::tuple_size_v<RegisterCollection>, Variable>::get(variable);
			}


			template<class ObjectType, size_t index>
			struct _GetInstanceTime {
			public:
				static long double get(ObjectType* objectAddress) {
					constexpr auto& reg = std::get<index>(binder);

					auto it = reg.find(reinterpret_cast<void*>(objectAddress));
					if (it != reg.end()) {
						return it->second->getInstanceTime();
					}

					return -1;
				}
			};

			template<class ObjectType>
			struct _GetInstanceTime<ObjectType, -1> {
			public:
				static long double get(ObjectType* objectAddress) {
					return -1;
				}
			};

			template<class ObjectType>
			static long double getInstanceTime(ObjectType* objectAddress) {
				return _GetInstanceTime<ObjectType, GetParameterPackIndex<ObjectType, RegisterCollection>>::get(objectAddress);
			}
		};




















































































		template<class... Registers>
		struct FunctionBinder {
		public:
			using RegisterCollection = std::_Tuple_cat1<std::conditional_t<TemplateIsSame_v<FunctionBinder<>, Registers>, Tuplify_t<Registers>, std::tuple<Registers>>...>::type;

			template<class T>
			struct TupleFromRB {};

			template<class... Args>
			struct TupleFromRB<FunctionBinder<Args...>> {
			public:
				static std::tuple<Args...> get(FunctionBinder<Args...> reg) {
					return reg.binder;
				}
			};

			template<auto... fps>
			struct TupleFromRB<FunctionRegister<fps...>> {
			public:
				static std::tuple<FunctionRegister<fps...>> get(FunctionRegister<fps...> reg) {
					return std::tuple(reg);
				}
			};

			template<class R, class... Args, R(*fps...)(Args...)>
			struct TupleFromRB<FunctionRegister<fps...>> {
			public:
				static std::tuple<FunctionRegister<fps...>> get(FunctionRegister<fps...> reg) {
					return std::tuple(reg);
				}
			};


			FunctionBinder(Registers... registers) {
				FunctionBinder<Registers...>::binder = std::tuple_cat(TupleFromRB<Registers>::get(registers)...);
			}
			inline static RegisterCollection binder;
			static void use(Registers... registers) {
				FunctionBinder<Registers...>::binder = std::tuple_cat(TupleFromRB<Registers>::get(registers)...);
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
			struct _0_GetFunctionIndexFromRegister<n, functionP, FunctionRegister<functionPHead, functionPs...>> {
			public:
				inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : _1_GetFunctionIndexFromRegister<n + 1, functionP, functionPs...>::index;
			};

			template<size_t n, auto functionP, auto functionPHead>
			struct _0_GetFunctionIndexFromRegister<n, functionP, FunctionRegister<functionPHead>> {
			public:
				inline static constexpr size_t index = CompareFunctionPointers<functionP, functionPHead> ? n : -1;
			};

			template<auto functionP, class CFR>
			inline static constexpr size_t GetFunctionIndexFromRegister = _0_GetFunctionIndexFromRegister<0, functionP, CFR>::index;


			template<auto functionP, class T, class... Args>
			struct _GetFunctionIndexFromBinderRegisters {
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


			template<size_t n, auto function>
			struct GetFunction {
				static const char* get() {
					return std::get<GetFunctionTypeFromBinderRegisters<function>>(binder).getFunctionName<n>();
				}
			};

			template<auto function>
			struct GetFunction<-1, function> {
				static const char* get() {
					return nullptr;
				}
			};


			template<auto function>
			static const char* getFunctionName() {
				return GetFunction<GetFunctionIndexFromBinderRegisters<function>, function>::get();
			}
		};























































































		template<class... Registers>
		struct VariableBinder {
			using _RegisterCollection = std::_Tuple_cat1<std::conditional_t<TemplateIsSame_v<VariableBinder<>, Registers>, Tuplify_t<Registers>, std::tuple<Registers>>...>::type;
			using RegisterCollection = UniqueTuple<_RegisterCollection>::type;


			template<class Tuple>
			struct MakeBinderOfTuple {};


			template<class... Args>
			struct MakeBinderOfTuple<std::tuple<Args...>> {
				using type = std::tuple<std::vector<Args*>...>;
			};


			VariableBinder() {}
			VariableBinder(Registers...) {}

			inline static MakeBinderOfTuple<RegisterCollection>::type binder;


			template<class T>
			struct TupleFromRB {};



			template<class... Types>
			struct TupleFromRB<std::vector<VariableRegister<Types...>*>> {
			public:
				using RegType = std::vector<VariableRegister<Types...>*>;
				static void get(RegType& reg) {
					RegType& binderElement = std::get<RegType>(binder);
					binderElement.insert(binderElement.end(), reg.begin(), reg.end());
				}
			};

			template<class... Args>
			struct TupleFromRB<std::tuple<std::vector<Args*>...>> {
			public:
				static void get(std::tuple<std::vector<Args*>...>& regTuple) {
					(TupleFromRB<std::vector<Args*>>::get(std::get<std::vector<Args*>>(regTuple)), ...);
				}
			};

			template<class... Types>
			struct TupleFromRB<VariableRegister<Types...>> {
			public:
				using RegType = VariableRegister<Types...>;
				static void get(RegType& reg) {
					std::get<std::vector<RegType*>>(binder).emplace_back(&reg);
				}
			};

			template<class... Args>
			struct TupleFromRB<VariableBinder<Args...>> {
			public:
				static void get(VariableBinder<Args...>& reg) {
					TupleFromRB<decltype(reg.binder)>::get(reg.binder);
				}
			};


			template<class... Register>
			static void add(Register&... reg) {
				(TupleFromRB<Register>::get(reg), ...);
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
			struct _GetPointerTypeFromRegisterVector<std::vector<Register*>> {
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
			static DebugYourselfDatabase database("log/DebugYourselfDatabase-" + oss.str() + ".db");

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
		struct PtrUnion {
			union Union
			{
				decltype(fPointer) f;
				uintmax_t buf;
			};
		};

		template<auto fPointer, class R, class T, class... Args>
		struct PtrUnion<fPointer, R(T::*)(Args...)> {
			union Union
			{
				R(T::* f)(Args...);
				uintmax_t buf;
			};
		};

		template<auto fPointer, class R, class... Args>
		struct PtrUnion<fPointer, R(*)(Args...)> {
			union Union
			{
				R(*f)(Args...);
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

		struct AlwaysFalse : public LoggingCondition {
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

				return false;
			};
		};

		template<class Condition = AlwaysFalse>
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
					taglist.erase(taglist.size() - 1, 2);
					taglist += "}";

					std::cout <<
						"Class_Name" << "\t" <<
						"Object_Name" << "\t" <<
						"Function_Name" << "\t" <<
						"Variable_Name" << "\t" <<
						"Time" << "\n" <<
						(class_name ? class_name : "") << "\t" <<
						(object_name ? object_name : "") << "\t" <<
						(function_name ? function_name : "") << "\t" <<
						(variable_name ? variable_name : "") << "\t" <<
						time << "\n" <<
						message << "\n" << "\n\n";
				}
			}
		};

		using No_CB = ClassBinder<ClassRegister<nullptr>>;
		using No_OB = ObjectBinder<ObjectRegister<std::nullptr_t>>;
		using No_FB = FunctionBinder<FunctionRegister<nullptr>>;
		using No_VB = VariableBinder<VariableRegister<std::nullptr_t>>;





















































































		inline static bool publishToggle = true;

		static void enablePublish() {
			publishToggle = true;
		}

		static void disablePublish() {
			publishToggle = false;
		}



		template<class CB, class OB, class FB, class VB, class Publish = AlwaysTrue, class PreAction = DirectLogger<>>
		struct Dependencies {
		public:


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

				if (publishToggle && Publish()(
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
					)) {

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
			}



			template<auto functionPointer, class Type = decltype(functionPointer)>
			struct GetNames {
			public:
				template<class Variable> static const char* variableName(Variable* v) {
					return nullptr;
				}
				inline static const char* functionName() {
					return FB::template getFunctionName<functionPointer>();
				}
				inline static std::string className() {
					return classToString<Type>();
				}
			};

			template<auto functionPointer, class R, class C, class... Args>
			struct GetNames<functionPointer, R(C::*)(Args...)> {
			public:
				inline static const char* functionName() {
					return CB::template getFunctionName<functionPointer>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return OB::getVariableName(v);
				}
				inline static const char* className() {
					return CB::template getClassName<functionPointer>();
				}
			};

			template<auto functionPointer, class R, class... Args>
			struct GetNames<functionPointer, R(*)(Args...)> {
			public:
				inline static const char* className = DBTags::GLOBAL;
				inline static const char* functionName() {
					return FB::template getFunctionName<functionPointer>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return VB::getVariableName(v);
				}
			};

			template<auto functionPointer, class R, class C, class... Args>
			struct GetNames<functionPointer, R(C::*)(Args...) const> {
			public:
				inline static const char* functionName() {
					return CB::template getFunctionName<functionPointer>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return OB::getVariableName(v);
				}
				inline static const char* className() {
					return CB::template getClassName<functionPointer>();
				}
			};

			template<>
			struct GetNames<nullptr, std::nullptr_t> {
			public:
				inline static const char* className = DBTags::GLOBAL;
				inline static const char* functionName() {
					FB::template getFunctionName<nullptr>();
				}
				template<class Variable> static const char* variableName(Variable* v) {
					return VB::getVariableName(v);
				}
			};

			//template<auto functionPointer> inline static const char* GetClassName_v = GetNames<functionPointer>::className;

			//template<auto functionPointer> inline static const char* GetNames<functionPointer>::functionName() = GetNames<functionPointer>::functionName;

			//Does not work because lambdas cannot be resolved in compile time for some reason... i think...
			/*
			template<auto functionPointer> inline static constexpr auto GetVariableName_f = []<class Variable>(Variable* var) -> const char* {
				return GetNames<functionPointer>::className;
			};
			*/































































			struct Class {
			public:
				//FV \w object
				template<auto functionPointer, class Variable>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer, class Variable>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}
				template<auto functionPointer, class Variable>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer, class Variable>
				static void debug(const GetClassWithConstFromFunctionPointer<functionPointer>* object, const Variable* variable, const std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}

				//F \w object
				template<auto functionPointer>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}
				template<auto functionPointer>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer>
				static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}

				//FV \w object
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition(object, variable, rank, tags, message)) {
						debug<functionPointer, Variable>(object, variable, rank, tags, message);
					}
				}
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug<functionPointer, Variable>(object, variable, rank, message);
					}
				}
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<functionPointer, Variable>(object, variable, tags, message);
					}
				}
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, std::string message) {
					if (condition()) {
						debug<functionPointer, Variable>(object, variable, message);
					}
				}

				//FV \w object
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<functionPointer>(object, rank, tags, message);
					}
				}
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<functionPointer>(object, tags, message);
					}
				}
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug<functionPointer>(object, rank, message);
					}
				}
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, std::string message) {
					if (condition()) {
						debug<functionPointer>(object, message);
					}
				}

			};

			struct Static {
				//F \wo object
				template<auto functionPointer>
				static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer>
				static void debug(SQLTypes::INTEGER rank, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}
				template<auto functionPointer>
				static void debug(std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer>
				static void debug(std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}

				//
				static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						nullptr,
						nullptr,
						0,
						-1,
						nullptr,
						0,
						nullptr,
						0,
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
						0,
						-1,
						nullptr,
						0,
						nullptr,
						0,
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
						0,
						-1,
						nullptr,
						0,
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
						nullptr,
						nullptr,
						0,
						-1,
						nullptr,
						0,
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						{}
					);
				}

				//C FV \wo object
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<functionPointer>(rank, tags, message);
					}
				}
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug<functionPointer>(rank, message);
					}
				}
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<functionPointer>(tags, message);
					}
				}
				template<auto functionPointer>
				static void debug(std::function<bool()> condition, std::string message) {
					if (condition()) {
						debug<functionPointer>(message);
					}
				}

				//C
				static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug(rank, tags, message);
					}
				}
				static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug(rank, message);
					}
				}
				static void debug(std::function<bool()> condition, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug(tags, message);
					}
				}
				static void debug(std::function<bool()> condition, std::string message) {
					if (condition()) {
						debug(message);
					}
				}
			};

			struct Global {
				//FV \wo object
				template<auto functionPointer, class Variable>
				static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer, class Variable>
				static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}
				template<auto functionPointer, class Variable>
				static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<auto functionPointer, class Variable>
				static void debug(Variable* variable, std::string message) {

					publish(
						GetNames<functionPointer>::className(),
						nullptr,
						0,
						-1,
						GetNames<functionPointer>::functionName(),
						extractFunctionPointerAsInteger<functionPointer>(),
						GetNames<functionPointer>::variableName(variable),
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}

				//V
				template<class Variable>
				static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					const char* variable_name = OB::getObjectName(variable);
					SQLTypes::INTEGER object = OB::getObject(variable);
					variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

					publish(
						nullptr,
						nullptr,
						0,
						OB::getInstanceTime(reinterpret_cast<void*>(object)),
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<class Variable>
				static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {

					publish(
						nullptr,
						nullptr,
						0,
						-1,
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}
				template<class Variable>
				static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						nullptr,
						nullptr,
						0,
						-1,
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<class Variable>
				static void debug(Variable* variable, std::string message) {

					publish(
						nullptr,
						nullptr,
						0,
						-1,
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}

				//FV \wo object
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition(variable, rank, tags, message)) {
						debug<functionPointer, Variable>(variable, rank, tags, message);
					}
				}
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug<functionPointer, Variable>(variable, rank, message);
					}
				}
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<functionPointer, Variable>(variable, tags, message);
					}
				}
				template<auto functionPointer, class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, std::string message) {
					if (condition()) {
						debug<functionPointer, Variable>(variable, message);
					}
				}

				//C V
				template<class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug(variable, rank, tags, message);
					}
				}
				template<class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug(variable, rank, message);
					}
				}
				template<class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug(variable, tags, message);
					}
				}
				template<class Variable>
				static void debug(std::function<bool()> condition, Variable* variable, std::string message) {
					if (condition()) {
						debug(variable, message);
					}
				}
			};

			struct Constructor {
			public:
				//
				template<class Class>
				static void debug(Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						0,
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);
				}
				template<class Class>
				static void debug(Class* object, SQLTypes::INTEGER rank, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						0,
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						{}
					);
				}
				template<class Class>
				static void debug(Class* object, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);
				}
				template<class Class>
				static void debug(Class* object, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						0,
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						{}
					);
				}

				//V
				template<class Class, class Variable>
				static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

					const char* variable_name = OB::getObjectName(variable);
					SQLTypes::INTEGER object = OB::getObject(variable);
					variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<class Class, class Variable>
				static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						rank,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}
				template<class Class, class Variable>
				static void debug(Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						tags
					);

				}
				template<class Class, class Variable>
				static void debug(Class* object, Variable* variable, std::string message) {

					publish(
						GetNames<nullptr, Class>::className().c_str(),
						OB::getObjectName(object),
						reinterpret_cast<SQLTypes::INTEGER>(object),
						OB::getInstanceTime(object),
						nullptr,
						0,
						nullptr,
						reinterpret_cast<SQLTypes::INTEGER>(variable),
						0,
						std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
						message.c_str(),
						std::vector<SQLTypes::TEXT>()
					);

				}

				//C V
				template<class Class, class Variable>
				static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<Class>(object, variable, rank, tags, message);
					}
				}
				template<class Class, class Variable>
				static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug<Class>(object, variable, rank, message);
					}
				}
				template<class Class, class Variable>
				static void debug(std::function<bool()> condition, Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<Class>(object, variable, tags, message);
					}
				}
				template<class Class, class Variable>
				static void debug(std::function<bool()> condition, Class* object, Variable* variable, std::string message) {
					if (condition()) {
						debug<Class>(object, variable, message);
					}
				}

				//C
				template<class Class>
				static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<Class>(object, rank, tags, message);
					}
				}
				template<class Class>
				static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, std::string message) {
					if (condition()) {
						debug<Class>(object, rank, message);
					}
				}
				template<class Class>
				static void debug(std::function<bool()> condition, Class* object, std::vector<SQLTypes::TEXT> tags, std::string message) {
					if (condition()) {
						debug<Class>(object, tags, message);
					}
				}
				template<class Class>
				static void debug(std::function<bool()> condition, Class* object, std::string message) {
					if (condition()) {
						debug<Class>(object, message);
					}
				}
			};

			struct Special {
			public:

				struct Static {
					//
					template<auto functionPointer, class Class>
					static void debug(Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class Class>
					static void debug(Class* object, SQLTypes::INTEGER rank, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<auto functionPointer, class Class>
					static void debug(Class* object, std::vector<SQLTypes::TEXT> tags, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class Class>
					static void debug(Class* object, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//V
					template<auto functionPointer, class Class, class Variable>
					static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

						const char* variable_name = OB::getObjectName(variable);
						SQLTypes::INTEGER object = OB::getObject(variable);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(Class* object, Variable* variable, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}

					//C V
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(object, variable, rank, tags, message);
						}
					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(object, variable, rank, message);
						}
					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(object, variable, tags, message);
						}
					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(object, variable, message);
						}
					}

					//C
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(object, rank, tags, message);
						}
					}
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(object, rank, message);
						}
					}
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, Class* object, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(object, tags, message);
						}
					}
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, Class* object, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(object, message);
						}
					}

				};

				struct Global {
					//
					template<auto functionPointer, class Class>
					static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class Class>
					static void debug(SQLTypes::INTEGER rank, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<auto functionPointer, class Class>
					static void debug(std::vector<SQLTypes::TEXT> tags, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class Class>
					static void debug(std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//V
					template<auto functionPointer, class Class, class Variable>
					static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {

						const char* variable_name = OB::getObjectName(variable);
						SQLTypes::INTEGER object = OB::getObject(variable);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(Variable* variable, SQLTypes::INTEGER rank, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(Variable* variable, std::string message) {

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							nullptr,
							0,
							-1,
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}

					//C V
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(variable, rank, tags, message);
						}
					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(variable, rank, message);
						}
					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Variable* variable, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(variable, tags, message);
						}
					}
					template<auto functionPointer, class Class, class Variable>
					static void debug(std::function<bool()> condition, Variable* variable, std::string message) {
						if (condition()) {
							debug<functionPointer, Class, Variable>(variable, message);
						}
					}

					//C
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(rank, tags, message);
						}
					}
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(rank, message);
						}
					}
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, std::vector<SQLTypes::TEXT> tags, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(tags, message);
						}
					}
					template<auto functionPointer, class Class>
					static void debug(std::function<bool()> condition, std::string message) {
						if (condition()) {
							debug<functionPointer, Class>(message);
						}
					}

				};
			};

			struct Assemblers {
			public:

				struct Class {
				public:

					//FV \w object
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							OB::getVariableName(variable),
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							OB::getVariableName(variable),
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);

					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							OB::getVariableName(variable),
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							OB::getVariableName(variable),
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);

					}

					//F \w object
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							object,
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							object,
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							object,
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(GetClassWithConstFromFunctionPointer<functionPointer>* object, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							OB::getObjectName(object),
							object,
							OB::getInstanceTime(object),
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//C FV \w object
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(object, variable, rank, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(object, variable, rank, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(object, variable, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Variable* variable, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(object, variable, message);
						}
					}

					//C F \w object
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(object, rank, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(object, rank, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(object, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, GetClassWithConstFromFunctionPointer<functionPointer>* object, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(object, message);
						}
					}

				};

				struct Global {
					//V
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							nullptr,
							nullptr,
							object,
							OB::getInstanceTime(objectPointer),
							nullptr,
							0,
							variable_name,
							variable,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							nullptr,
							nullptr,
							object,
							OB::getInstanceTime(objectPointer),
							nullptr,
							0,
							variable_name,
							variable,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							nullptr,
							nullptr,
							object,
							OB::getInstanceTime(objectPointer),
							nullptr,
							0,
							variable_name,
							variable,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							nullptr,
							nullptr,
							object,
							OB::getInstanceTime(objectPointer),
							nullptr,
							0,
							variable_name,
							variable,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//
					template<class MessageAssembler, class... Args>
					static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							nullptr,
							nullptr,
							0,
							-1,
							nullptr,
							0,
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<class MessageAssembler, class... Args>
					static void debug(SQLTypes::INTEGER rank, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							nullptr,
							nullptr,
							0,
							-1,
							nullptr,
							0,
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<class MessageAssembler, class... Args>
					static void debug(std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							nullptr,
							nullptr,
							0,
							-1,
							nullptr,
							0,
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<class MessageAssembler, class... Args>
					static void debug(Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							nullptr,
							nullptr,
							0,
							-1,
							nullptr,
							0,
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//FV \wo object
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							DBTags::GLOBAL,
							DBTags::NULLVAR,
							object,
							OB::getInstanceTime(objectPointer),
							FB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							variable_name,
							variable,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, SQLTypes::INTEGER rank, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							DBTags::GLOBAL,
							DBTags::NULLVAR,
							object,
							OB::getInstanceTime(objectPointer),
							FB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							variable_name,
							variable,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							DBTags::GLOBAL,
							DBTags::NULLVAR,
							object,
							OB::getInstanceTime(objectPointer),
							FB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							variable_name,
							variable,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(Variable* variable, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						auto objectPointer = OB::getObject(variable);
						SQLTypes::INTEGER object = static_cast<SQLTypes::INTEGER>(objectPointer);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							DBTags::GLOBAL,
							DBTags::NULLVAR,
							object,
							OB::getInstanceTime(objectPointer),
							FB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							variable_name,
							variable,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//F \wo object
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							nullptr,
							0,
							-1,
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(SQLTypes::INTEGER rank, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							nullptr,
							0,
							-1,
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::vector<SQLTypes::TEXT> tags, Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							nullptr,
							0,
							-1,
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(Args... args) {

						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						publish(
							CB::template getClassName<functionPointer>(),
							nullptr,
							0,
							-1,
							CB::template getFunctionName<functionPointer>(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//C FV \wo object
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(variable, rank, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(variable, rank, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(variable, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Variable, Args...>(variable, message);
						}
					}

					//C F \wo object
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(rank, tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(rank, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(tags, message);
						}
					}
					template<auto functionPointer, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<functionPointer, MessageAssembler, Args...>(message);
						}
					}

					//C V
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Variable, Args...>(variable, rank, tags, message);
						}
					}
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Variable, Args...>(variable, rank, message);
						}
					}
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Variable, Args...>(variable, tags, message);
						}
					}
					template<class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Variable* variable, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Variable, Args...>(variable, message);
						}
					}

					//C
					template<class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Args...>(rank, tags, message);
						}
					}
					template<class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Args...>(rank, message);
						}
					}
					template<class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Args...>(tags, message);
						}
					}
					template<class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						if (condition()) {
							debug<MessageAssembler, Args...>(message);
						}
					}

				};

				struct Constructor {
				public:
					//
					template<class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//V
					template<class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));

						const char* variable_name = OB::getObjectName(variable);
						SQLTypes::INTEGER object = OB::getObject(variable);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}
					template<class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							nullptr,
							0,
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}

					//V
					template<class Class, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Variable, Args...>(object, variable, rank, tags, args...);
						}
					}
					template<class Class, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Variable, Args...>(object, variable, rank, args...);
						}
					}
					template<class Class, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Variable, Args...>(object, variable, tags, args...);
						}
					}
					template<class Class, class MessageAssembler, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Variable, Args...>(object, variable, args...);
						}
					}

					//
					template<class Class, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Args...>(object, rank, tags, args...);
						}
					}
					template<class Class, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Args...>(object, rank, args...);
						}
					}
					template<class Class, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, Class* object, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Args...>(object, tags, args...);
						}
					}
					template<class Class, class MessageAssembler, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Args... args) {
						if (condition()) {
							debug<Class, MessageAssembler, Args...>(object, args...);
						}
					}
				};

				struct Special {
				public:
					//
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);
					}
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(Class* object, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							0,
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							{}
						);
					}

					//V
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						const char* variable_name = OB::getObjectName(variable);
						SQLTypes::INTEGER object = OB::getObject(variable);
						variable_name = variable_name != nullptr ? variable_name : VB::getVariableName();

						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							rank,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							tags
						);

					}
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(Class* object, Variable* variable, Args... args) {
						std::string message = std::apply(MessageAssembler(), std::tuple<Args...>(args...));
						publish(
							GetNames<nullptr, Class>::className().c_str(),
							OB::getObjectName(object),
							reinterpret_cast<SQLTypes::INTEGER>(object),
							OB::getInstanceTime(object),
							GetNames<functionPointer>::functionName(),
							extractFunctionPointerAsInteger<functionPointer>(),
							nullptr,
							reinterpret_cast<SQLTypes::INTEGER>(variable),
							0,
							std::chrono::duration<long double>((std::chrono::steady_clock::now() - DebugDebugYourself::launchTimeStamp)).count(),
							message.c_str(),
							std::vector<SQLTypes::TEXT>()
						);

					}

					//C V
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Variable, Args...>(object, variable, rank, tags, args...);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, SQLTypes::INTEGER rank, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Variable, Args...>(object, variable, rank, args...);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Variable, Args...>(object, variable, tags, args...);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Class, class Variable, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Variable* variable, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Variable, Args...>(object, variable, args...);
						}
					}

					//C
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Args...>(object, rank, tags, args...);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(std::function<bool()> condition, Class* object, SQLTypes::INTEGER rank, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Args...>(object, rank, args...);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(std::function<bool()> condition, Class* object, std::vector<SQLTypes::TEXT> tags, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Args...>(object, tags, args...);
						}
					}
					template<auto functionPointer, class MessageAssembler, class Class, class... Args>
					static void debug(std::function<bool()> condition, Class* object, Args... args) {
						if (condition()) {
							debug<functionPointer, MessageAssembler, Class, Args...>(object, args...);
						}
					}
				};
			};

		};

	};




























































































	template<bool enable>
	using DebugYourself = std::conditional_t<enable, DebugDebugYourself, ReleaseDebugYourself>;

};