#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <array>


#include <sqlite3.h>

class DebugYourselfDatabase
{
public:


	DebugYourselfDatabase() :
		databaseInstance(sqlite3_open("DebugYourselfDatabase.db", &database))
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
	
private:

	sqlite3* database;
	intmax_t databaseInstance;

	std::string schema;
};


template<class... SchemaTypes>
class DebugYourselfDatabaseTable
{
public:
	struct Types {
		struct SQLite {
		public:
			using INTEGER = intmax_t;
			using REAL = double_t;
			using TEXT = const char*;
			using BLOB = void*;
		};
	};

	template<class... SchemaNames>
	DebugYourselfDatabaseTable(DebugYourselfDatabase* database, std::string tableName, SchemaNames... names) :
		database(database)
	{
		char* error;
		intmax_t rc = 0;
		const std::string schema = concatenateParameterPack(names...);

		sqlite3_exec(*database, "PRAGMA synchronous=OFF", nullptr, nullptr, &error);
		sqlite3_exec(*database, "PRAGMA count_changes=OFF", nullptr, nullptr, &error);
		sqlite3_exec(*database, "PRAGMA journal_mode=MEMORY", nullptr, nullptr, &error);
		sqlite3_exec(*database, "PRAGMA temp_store=MEMORY", nullptr, nullptr, &error);


		//CREATE TABLE
		std::string tableList = ((std::string(names) + " " + std::string(getSQLType<SchemaTypes>()) + ",") + ...);
		tableList.pop_back();

		std::string sql = "CREATE TABLE " + tableName + " (ID INT PRIMARY KEY NOT NULL, " + tableList + ");";
		rc |= sqlite3_exec(*database, sql.c_str(), nullptr, 0, &error);

		//CREATE AND START TRANSACTION
		std::string qs = "?,";
		for (size_t i = 0; i < sizeof...(SchemaNames); i++) {
			qs += "?,";
		}
		qs.pop_back();

		command = "INSERT INTO " + tableName + " (ID," + schema + ") VALUES(" + qs + "); ";

		begin();
	}

	void add(SchemaTypes... entry) {
		statementCount++;
		if(statementCount > 32766){
			push();
			statementCount = 0;
			begin();
		}
		bind(std::make_integer_sequence<intmax_t, sizeof...(SchemaTypes) + 1>{}, id, std::forward<SchemaTypes>(entry)...);
		id++;
		sqlite3_step(statement);
		sqlite3_reset(statement);
	}

	void push() {
		char* error;
		intmax_t rc = sqlite3_exec(*database, "END TRANSACTION", nullptr, nullptr, &error); // <<< START HERE ERROR NEEDS TO BE A MEMBER VARIABLE, SWITCH IN CONSTRUCTOR TOO.
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << error << std::endl;
			sqlite3_free(error);
		}
		sqlite3_finalize(statement);
	}

private:

	void begin() {
		int rc = 0;
		char* error;
		sqlite3_exec(*database, "BEGIN TRANSACTION", nullptr, nullptr, &error);
		rc |= sqlite3_prepare_v2(*database, command.c_str(), -1, &statement, nullptr);

		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << error << std::endl;
			sqlite3_free(error);
		}
	}

	template<class SQLType>
	constexpr const char* getSQLType() {
		if (std::is_same_v<Types::SQLite::INTEGER, SQLType>) { return "INT"; };
		if (std::is_same_v<Types::SQLite::REAL, SQLType>) { return "REAL"; };
		if (std::is_same_v<Types::SQLite::TEXT, SQLType>) { return "TEXT"; };
		if (std::is_same_v<Types::SQLite::BLOB, SQLType>) { return "BLOB"; };
	}

	std::string convertEntryData(Types::SQLite::INTEGER var) { return std::to_string(var); }
	std::string convertEntryData(Types::SQLite::REAL var) { return std::to_string(var); }
	std::string convertEntryData(Types::SQLite::TEXT var) { return std::string(var); }
	std::string convertEntryData(Types::SQLite::BLOB var) { return std::to_string(reinterpret_cast<intmax_t>(var)); }

	template<class... Types, intmax_t... indices>
	void bind(std::integer_sequence<intmax_t, indices...>, Types... values) {
		(_bind(values, indices + 1), ...);
	}

	void _bind(Types::SQLite::INTEGER value, intmax_t location) {sqlite3_bind_int64(statement, location, value); }
	void _bind(Types::SQLite::REAL value, intmax_t location) { sqlite3_bind_double(statement, location, value); }
	void _bind(Types::SQLite::TEXT value, intmax_t location) { sqlite3_bind_text(statement, location, value, -1, SQLITE_TRANSIENT); }
	void _bind(Types::SQLite::BLOB value, intmax_t location) {
		size_t e = *reinterpret_cast<size_t*>(value);
		sqlite3_bind_blob64(statement, location, value, 8, SQLITE_TRANSIENT);
		int a = 1;
	}

	template<class... ParameterPack>
	std::string concatenateParameterPack(ParameterPack... params) {
		std::string returnValue = std::string(((std::string(params) + ",") + ...));
		returnValue.pop_back();
		return returnValue;
	}

	DebugYourselfDatabase* database;

	sqlite3_stmt* statement;
	size_t statementCount = 0;
	Types::SQLite::INTEGER id = 0;

	std::string command;
};

