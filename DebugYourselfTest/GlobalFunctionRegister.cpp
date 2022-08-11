
#include "pch.h"

#include <DebugYourself.h>

using DebugYourself = dy::DebugYourself<true>;

namespace ns_Parameters_ {
	void voidFunction(bool, char) {}
	bool boolFunction(void*, char) { return true; }
	char charFunction(void*, bool) { return ' '; }

	DebugYourself::FunctionRegister<
		&voidFunction,
		&boolFunction,
		&charFunction> GFR_No_Naming;

	DebugYourself::FunctionRegister<
		&voidFunction,
		&boolFunction,
		&charFunction> GFR_Partial_Naming("voidFunction");

	DebugYourself::FunctionRegister<
		&voidFunction,
		&boolFunction,
		&charFunction> GFR_Full_Naming(
			"voidFunction",
			"boolFunction",
			"charFunction");
}

namespace ns_tuple_ {
	void voidFunction(bool, char) {}
	bool boolFunction(void*, char) { return true; }
	char charFunction(void*, bool) { return ' '; }

	DebugYourself::FunctionRegister<
		&voidFunction,
		&boolFunction,
		&charFunction> GFR_No_Naming;

	DebugYourself::FunctionRegister<
		&voidFunction,
		&boolFunction,
		&charFunction> GFR_Partial_Naming("voidFunction");

	DebugYourself::FunctionRegister<
		&voidFunction,
		&boolFunction,
		&charFunction> GFR_Full_Naming(
			"voidFunction",
			"boolFunction",
			"charFunction");
}

TEST(GlobalFunctionRegister, _Parameters_) {
	EXPECT_EQ(std::get<0>(ns_Parameters_::GFR_No_Naming.associatedFunctions), &ns_Parameters_::voidFunction);
	EXPECT_EQ(std::get<1>(ns_Parameters_::GFR_No_Naming.associatedFunctions), &ns_Parameters_::boolFunction);
	EXPECT_EQ(std::get<2>(ns_Parameters_::GFR_No_Naming.associatedFunctions), &ns_Parameters_::charFunction);

	EXPECT_STREQ(std::get<0>(ns_Parameters_::GFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<1>(ns_Parameters_::GFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(ns_Parameters_::GFR_No_Naming.associatedFunctionNames), nullptr);

	EXPECT_GT(ns_Parameters_::GFR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(ns_Parameters_::GFR_Partial_Naming.associatedFunctions), &ns_Parameters_::voidFunction);
	EXPECT_EQ(std::get<1>(ns_Parameters_::GFR_Partial_Naming.associatedFunctions), &ns_Parameters_::boolFunction);
	EXPECT_EQ(std::get<2>(ns_Parameters_::GFR_Partial_Naming.associatedFunctions), &ns_Parameters_::charFunction);

	EXPECT_STREQ(std::get<0>(ns_Parameters_::GFR_Partial_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(ns_Parameters_::GFR_Partial_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(ns_Parameters_::GFR_Partial_Naming.associatedFunctionNames), nullptr);

	EXPECT_GT(ns_Parameters_::GFR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(ns_Parameters_::GFR_Full_Naming.associatedFunctions), &ns_Parameters_::voidFunction);
	EXPECT_EQ(std::get<1>(ns_Parameters_::GFR_Full_Naming.associatedFunctions), &ns_Parameters_::boolFunction);
	EXPECT_EQ(std::get<2>(ns_Parameters_::GFR_Full_Naming.associatedFunctions), &ns_Parameters_::charFunction);

	EXPECT_STREQ(std::get<0>(ns_Parameters_::GFR_Full_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(ns_Parameters_::GFR_Full_Naming.associatedFunctionNames), "boolFunction");
	EXPECT_STREQ(std::get<2>(ns_Parameters_::GFR_Full_Naming.associatedFunctionNames), "charFunction");

	EXPECT_GT(ns_Parameters_::GFR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
}
TEST(GlobalFunctionRegister, _tuple_) {
	EXPECT_EQ(std::get<0>(ns_tuple_::GFR_No_Naming.associatedFunctions), &ns_tuple_::voidFunction);
	EXPECT_EQ(std::get<1>(ns_tuple_::GFR_No_Naming.associatedFunctions), &ns_tuple_::boolFunction);
	EXPECT_EQ(std::get<2>(ns_tuple_::GFR_No_Naming.associatedFunctions), &ns_tuple_::charFunction);

	EXPECT_STREQ(std::get<0>(ns_tuple_::GFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<1>(ns_tuple_::GFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(ns_tuple_::GFR_No_Naming.associatedFunctionNames), nullptr);

	EXPECT_GT(ns_tuple_::GFR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(ns_tuple_::GFR_Partial_Naming.associatedFunctions), &ns_tuple_::voidFunction);
	EXPECT_EQ(std::get<1>(ns_tuple_::GFR_Partial_Naming.associatedFunctions), &ns_tuple_::boolFunction);
	EXPECT_EQ(std::get<2>(ns_tuple_::GFR_Partial_Naming.associatedFunctions), &ns_tuple_::charFunction);

	EXPECT_STREQ(std::get<0>(ns_tuple_::GFR_Partial_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(ns_tuple_::GFR_Partial_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(ns_tuple_::GFR_Partial_Naming.associatedFunctionNames), nullptr);

	EXPECT_GT(ns_tuple_::GFR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(ns_tuple_::GFR_Full_Naming.associatedFunctions), &ns_tuple_::voidFunction);
	EXPECT_EQ(std::get<1>(ns_tuple_::GFR_Full_Naming.associatedFunctions), &ns_tuple_::boolFunction);
	EXPECT_EQ(std::get<2>(ns_tuple_::GFR_Full_Naming.associatedFunctions), &ns_tuple_::charFunction);

	EXPECT_STREQ(std::get<0>(ns_tuple_::GFR_Full_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(ns_tuple_::GFR_Full_Naming.associatedFunctionNames), "boolFunction");
	EXPECT_STREQ(std::get<2>(ns_tuple_::GFR_Full_Naming.associatedFunctionNames), "charFunction");

	EXPECT_GT(ns_tuple_::GFR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
}

TEST(GlobalFunctionRegister, getFunctionPointer) {
	EXPECT_EQ(ns_Parameters_::GFR_No_Naming.getFunctionPointer<0>(), &ns_Parameters_::voidFunction);
	EXPECT_EQ(ns_Parameters_::GFR_No_Naming.getFunctionPointer<1>(), &ns_Parameters_::boolFunction);
	EXPECT_EQ(ns_Parameters_::GFR_No_Naming.getFunctionPointer<2>(), &ns_Parameters_::charFunction);

	EXPECT_EQ(ns_Parameters_::GFR_Partial_Naming.getFunctionPointer<0>(), &ns_Parameters_::voidFunction);
	EXPECT_EQ(ns_Parameters_::GFR_Partial_Naming.getFunctionPointer<1>(), &ns_Parameters_::boolFunction);
	EXPECT_EQ(ns_Parameters_::GFR_Partial_Naming.getFunctionPointer<2>(), &ns_Parameters_::charFunction);

	EXPECT_EQ(ns_Parameters_::GFR_Full_Naming.getFunctionPointer<0>(), &ns_Parameters_::voidFunction);
	EXPECT_EQ(ns_Parameters_::GFR_Full_Naming.getFunctionPointer<1>(), &ns_Parameters_::boolFunction);
	EXPECT_EQ(ns_Parameters_::GFR_Full_Naming.getFunctionPointer<2>(), &ns_Parameters_::charFunction);


	EXPECT_EQ(ns_tuple_::GFR_No_Naming.getFunctionPointer<0>(), &ns_tuple_::voidFunction);
	EXPECT_EQ(ns_tuple_::GFR_No_Naming.getFunctionPointer<1>(), &ns_tuple_::boolFunction);
	EXPECT_EQ(ns_tuple_::GFR_No_Naming.getFunctionPointer<2>(), &ns_tuple_::charFunction);

	EXPECT_EQ(ns_tuple_::GFR_Partial_Naming.getFunctionPointer<0>(), &ns_tuple_::voidFunction);
	EXPECT_EQ(ns_tuple_::GFR_Partial_Naming.getFunctionPointer<1>(), &ns_tuple_::boolFunction);
	EXPECT_EQ(ns_tuple_::GFR_Partial_Naming.getFunctionPointer<2>(), &ns_tuple_::charFunction);

	EXPECT_EQ(ns_tuple_::GFR_Full_Naming.getFunctionPointer<0>(), &ns_tuple_::voidFunction);
	EXPECT_EQ(ns_tuple_::GFR_Full_Naming.getFunctionPointer<1>(), &ns_tuple_::boolFunction);
	EXPECT_EQ(ns_tuple_::GFR_Full_Naming.getFunctionPointer<2>(), &ns_tuple_::charFunction);
}

TEST(GlobalFunctionRegister, getFunctionName) {
	EXPECT_STREQ(ns_Parameters_::GFR_No_Naming.getFunctionName<0>(), nullptr);
	EXPECT_STREQ(ns_Parameters_::GFR_No_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(ns_Parameters_::GFR_No_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(ns_Parameters_::GFR_Partial_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(ns_Parameters_::GFR_Partial_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(ns_Parameters_::GFR_Partial_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(ns_Parameters_::GFR_Full_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(ns_Parameters_::GFR_Full_Naming.getFunctionName<1>(), "boolFunction");
	EXPECT_STREQ(ns_Parameters_::GFR_Full_Naming.getFunctionName<2>(), "charFunction");


	EXPECT_STREQ(ns_tuple_::GFR_No_Naming.getFunctionName<0>(), nullptr);
	EXPECT_STREQ(ns_tuple_::GFR_No_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(ns_tuple_::GFR_No_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(ns_tuple_::GFR_Partial_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(ns_tuple_::GFR_Partial_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(ns_tuple_::GFR_Partial_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(ns_tuple_::GFR_Full_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(ns_tuple_::GFR_Full_Naming.getFunctionName<1>(), "boolFunction");
	EXPECT_STREQ(ns_tuple_::GFR_Full_Naming.getFunctionName<2>(), "charFunction");
}