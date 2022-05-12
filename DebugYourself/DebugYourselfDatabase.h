#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <array>
#include <regex>
#include <optional>


#include <sqlite3.h>

#include "Utility.h"

class DebugYourselfDatabase
{
public:


	DebugYourselfDatabase(std::string fileName) :
		databaseInstance(sqlite3_open(fileName.c_str(), &database))
	{
		if (databaseInstance != 0) {
			std::cerr << "Could not create database!" << std::endl;
		}
	}

	~DebugYourselfDatabase() {
		sqlite3_close(database);
	}

	operator sqlite3* () {
		return database;
	}

	void checkError(int rc, char* error) {
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << error << std::endl;
			sqlite3_free(error);
		}
	}

	void startTransaction() {
		if (sqlite3_get_autocommit(database)) {
			int rc = 0;
			char* error;
			rc = sqlite3_exec(database, "BEGIN TRANSACTION", nullptr, nullptr, &error);

			checkError(rc, error);
		}
	}

	void endTransaction() {
		if (!sqlite3_get_autocommit(database)) {
			int rc = 0;
			char* error;
			rc = sqlite3_exec(database, "END TRANSACTION", nullptr, nullptr, &error);

			checkError(rc, error);
		}
	}
	
	
private:

	sqlite3* database;
	intmax_t databaseInstance;

	std::string schema;
};


template<class... Args>
struct Constraints {};

struct SQL {
public:
	struct Types {
	public:
		using INTEGER = intmax_t;
		using REAL = double_t;
		using TEXT = const char*;
		using BLOB = void*;
	};
	struct ColumnConstraints {
	public:
		template<class SQLType> struct PrimaryKey {
		public:
			PrimaryKey(SQLType value) : value(value) {}
			operator SQLType() {
				return value;
			}
		private:
			SQLType value;
		};
	};
	struct TableConstraints {
	public:
		struct ForeignKey {
		public:
			ForeignKey(std::string column, std::string table_reference, std::string column_reference) :
				column(column),
				table_reference(table_reference),
				column_reference(column_reference)
			{}

			const std::string column;
			const std::string table_reference;
			const std::string column_reference;
		};
	};
};

template<class... SchemaTypes>
class DebugYourselfDatabaseTable
{
public:
	

	template<class T>
	struct Test {};

	struct SchemaFormat {
		SchemaFormat(std::string column, std::string entry) : column(column), entry(entry) {}

		std::string column;
		std::string entry;
	};

	template<class SchemaType>
	struct SchemaFormatter {};

	template<> struct SchemaFormatter<typename SQL::Types::INTEGER> { public: static SchemaFormat generate(std::string name) { return SchemaFormat(name, name + " INT"); } };
	template<> struct SchemaFormatter<typename SQL::Types::REAL> { public: static SchemaFormat generate(std::string name) { return  SchemaFormat(name, name + " REAL"); } };
	template<> struct SchemaFormatter<typename SQL::Types::TEXT> { public: static SchemaFormat generate(std::string name) { return SchemaFormat(name, name + " TEXT"); } };
	template<> struct SchemaFormatter<typename SQL::Types::BLOB> { public: static SchemaFormat generate(std::string name) { return SchemaFormat(name, name + " BLOB"); } };
	
	template<class SQLType> struct SchemaFormatter<typename SQL::ColumnConstraints::template PrimaryKey<SQLType>> {
	public:
		static SchemaFormat generate(std::string name) {
			SchemaFormat format = SchemaFormatter<SQLType>::generate(name);

			format.entry += " PRIMARY KEY";
			format.column = name;
			return format;
		}
	};

	template<> struct SchemaFormatter<typename SQL::TableConstraints::ForeignKey> {
	public:
		static SchemaFormat generate(typename SQL::TableConstraints::ForeignKey key) {
			return SchemaFormat(
				key.column,
				"FOREIGN KEY(" + key.column + ") REFERENCES " + key.table_reference + "(" + key.column_reference + ")");
		}
	};
	


	template<class... SchemaNames>
	DebugYourselfDatabaseTable(DebugYourselfDatabase* database, std::string tableName, SchemaNames... names) :
		database(database),
		schemaFormat({ SchemaFormatter<SchemaTypes>::generate(names)... }),
		tableName(tableName),
		add(this)
	{
		char* error;
		//const std::string schema = concatenateParameterPack(names...);

		sqlite3_exec(*database, "PRAGMA synchronous=OFF", nullptr, nullptr, &error);
		sqlite3_exec(*database, "PRAGMA count_changes=OFF", nullptr, nullptr, &error);
		sqlite3_exec(*database, "PRAGMA journal_mode=MEMORY", nullptr, nullptr, &error);
		sqlite3_exec(*database, "PRAGMA temp_store=MEMORY", nullptr, nullptr, &error);

		std::string schema;
		std::string tableList;
		for (size_t i = 0; i < sizeof...(SchemaTypes); i++) {
			
			schema += schemaFormat.at(i).column + ", ";
			tableList += schemaFormat.at(i).entry + ", ";
		}
		schema.erase(schema.size() - 2, 2);
		tableList.erase(tableList.size() - 2, 2);

		std::string sql = "CREATE TABLE " + tableName + " (" + tableList + ");";
		rc |= sqlite3_exec(*database, sql.c_str(), nullptr, 0, &error);

		//CREATE AND START TRANSACTION
		std::string qs = "";
		for (size_t i = 0; i < sizeof...(SchemaNames); i++) {
			qs += "?,";
		}
		qs.pop_back();

		command = "INSERT INTO " + tableName + " (" + schema + ") VALUES(" + qs + "); ";

		rc |= sqlite3_prepare_v2(*database, command.c_str(), -1, &statement, nullptr);
		//database->startTransaction();
	}

	/*
	template<size_t n, class Tuple>
	struct InvertParameterPack {};

	template<size_t n, class Type, class... Types>
	struct InvertParameterPack<n, std::tuple<Type, Types...>> {
	public:
		using Tuple = InvertParameterPack<n - 1, std::tuple<Types..., Type>>::Tuple;
	};

	template<class Type, class... Types>
	struct InvertParameterPack <0, std::tuple<Type, Types...>> {
	public:
		using Tuple = std::tuple<Types..., Type>;
	};

	template<class Tuple>
	struct StripTableConstraints {};

	template<class... Types>
	struct StripTableConstraints<std::tuple<SQL::TableConstraints::ForeignKey, Types...>> {
	public:
		using Tuple = StripTableConstraints<std::tuple<Types...>>::Tuple;
	};

	template<class... Types>
	struct StripTableConstraints<std::tuple<Types...>> {
	public:
		using Tuple = std::tuple<Types...>;
	};
	*/

	/*
	template<class... Types>
	struct DeleteTableConstraints {
		//using Tuple = std::tuple<std::enable_if_t<!std::is_same_v<Types, SQL::TableConstraints::ForeignKey>, Types>...>;
	};

	template<class... Types>
	struct DeleteTableConstraints<std::enable_if_t<!std::is_same_v<Types, SQL::TableConstraints::ForeignKey>, Types>...> {
	public:
		using Tuple = std::tuple<Types...>;
	};
	*/

	template<typename...Ts>
	using tuple_cat_t = decltype(std::tuple_cat(std::declval<Ts>()...));

	template<typename T, typename...Ts>
	using remove_t = tuple_cat_t<
		typename std::conditional<
		std::is_same<T, Ts>::value,
		std::tuple<>,
		std::tuple<Ts>
		>::type...
	>;

	template<class Tuple>
	struct _add {};

	template<class... Types>
	struct _add<std::tuple<Types...>> {
	public:
		_add(DebugYourselfDatabaseTable<SchemaTypes...>* table) : 
			table(table)
		{}
		void operator()(Types... entry) {
			table->statementCount++;
			if (sqlite3_get_autocommit(*table->database)) {
				table->reset();
			}
			else if (table->statementCount > 32766) {
				table->push();
				table->reset();
			}
			table->bind(std::make_integer_sequence<intmax_t, sizeof...(Types)>{}, std::forward<Types>(entry)...);
			table->id++;
			sqlite3_step(table->statement);
			sqlite3_reset(table->statement);
		}
	private:
		DebugYourselfDatabaseTable<SchemaTypes...>* table;
		//friend class DebugYourselfDatabaseTable<SchemaTypes...>;
	};

	_add<remove_t<SQL::TableConstraints::ForeignKey, SchemaTypes...>> add;


	void push() {
		database->endTransaction();
		sqlite3_finalize(statement);
	}

private:

	void reset() {
		statementCount = 0;

		rc |= sqlite3_prepare_v2(*database, command.c_str(), -1, &statement, nullptr);
		database->startTransaction();
	}

	std::string convertEntryData(SQL::Types::INTEGER var) { return std::to_string(var); }
	std::string convertEntryData(SQL::Types::REAL var) { return std::to_string(var); }
	std::string convertEntryData(SQL::Types::TEXT var) { return std::string(var); }
	std::string convertEntryData(SQL::Types::BLOB var) { return std::to_string(reinterpret_cast<intmax_t>(var)); }

	template<class... Types, intmax_t... indices>
	void bind(std::integer_sequence<intmax_t, indices...>, Types... values) {
		(_bind(values, indices + 1), ...);
	}

	void _bind(SQL::Types::INTEGER value, intmax_t location) {sqlite3_bind_int64(statement, location, value); }
	void _bind(SQL::Types::REAL value, intmax_t location) { sqlite3_bind_double(statement, location, value); }
	void _bind(SQL::Types::TEXT value, intmax_t location) { sqlite3_bind_text(statement, location, value, -1, SQLITE_TRANSIENT); }
	void _bind(SQL::Types::BLOB value, intmax_t location) {
		size_t e = *reinterpret_cast<size_t*>(value);
		sqlite3_bind_blob64(statement, location, value, 8, SQLITE_TRANSIENT);
		int a = 1;
	}

	template<class SchemaType>
	struct SchemaConcat {};

	template<> struct SchemaConcat<typename SQL::Types::INTEGER> { static std::string get(std::string name) { return name; } };
	template<> struct SchemaConcat<typename SQL::Types::REAL> { static std::string get(std::string name) { return name; } };
	template<> struct SchemaConcat<typename SQL::Types::TEXT> { static std::string get(std::string name) { return name; } };
	template<> struct SchemaConcat<typename SQL::Types::BLOB> { static std::string get(std::string name) { return name; } };

	template<class... STs>
	struct SchemaConcat<DebugYourselfDatabaseTable<STs...>> {
		static std::string get(std::string reference) {
			std::regex getName("REFERENCES\\s+[\\w]+\\((\\w+)\\)");
			std::smatch matches;
			std::regex_search(reference, matches, getName);
			return matches[1].str();
		}
	};

	template<class... ParameterPack>
	std::string concatenateParameterPack(ParameterPack... params) {
		std::string returnValue = ((SchemaConcat<SchemaTypes>::get(params) + ",") + ...);
		returnValue.pop_back();
		return returnValue;
	}

	DebugYourselfDatabase* database;

	sqlite3_stmt* statement;
	size_t statementCount = 0;
	SQL::Types::INTEGER id = 0;

	std::string command;

	std::array<SchemaFormat, sizeof...(SchemaTypes)> schemaFormat;
	std::array<std::string, sizeof...(SchemaTypes)> schemaTypes;
	std::array<std::string, sizeof...(SchemaTypes)> schemaNames;
	std::string tableName;

	int rc = 0;
};

