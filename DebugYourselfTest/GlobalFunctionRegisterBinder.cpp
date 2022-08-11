#include "pch.h"

#include <DebugYourself.h>

using DebugYourself = dy::DebugYourself<true>;

namespace ns_Registers_ {
	void voidFunction1(bool, char) {}
	bool boolFunction1(void*, char) { return true; }
	char charFunction1(void*, bool) { return ' '; }

	void voidFunction2(bool, char) {}
	bool boolFunction2(void*, char) { return true; }
	char charFunction2(void*, bool) { return ' '; }

	void voidFunction3(bool, char) {}
	bool boolFunction3(void*, char) { return true; }
	char charFunction3(void*, bool) { return ' '; }

	void voidFunction4(bool, char) {}
	bool boolFunction4(void*, char) { return true; }
	char charFunction4(void*, bool) { return ' '; }


	DebugYourself::FunctionRegister<
		&voidFunction1,
		&boolFunction1,
		&charFunction1> GFR1(
			"voidFunction1",
			"boolFunction1",
			"charFunction1");

	DebugYourself::FunctionRegister<
		&voidFunction2,
		&boolFunction2,
		&charFunction2> GFR2(
			"voidFunction2",
			"boolFunction2",
			"charFunction2");

	DebugYourself::FunctionRegister<
		&voidFunction3,
		&boolFunction3,
		&charFunction3> GFR3(
			"voidFunction3",
			"boolFunction3",
			"charFunction3");

	DebugYourself::FunctionRegister<
		&voidFunction4,
		&boolFunction4,
		&charFunction4> GFR4(
			"voidFunction4",
			"boolFunction4",
			"charFunction4");


	DebugYourself::FunctionBinder FB(
		GFR1,
		GFR2,
		GFR3);

	DebugYourself::FunctionBinder FB_RegisterCollection_(
		FB,
		GFR4);
};

TEST(FunctionBinder, _Registers_) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns_Registers_::FB.internalBinder)>, 3);
}

TEST(FunctionBinder, _RegisterCollection_) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns_Registers_::FB_RegisterCollection_)::RegisterCollection>, 4);
}

TEST(FunctionBinder, use) {
	ns_Registers_::FB.use(ns_Registers_::FB);
	EXPECT_EQ(std::tuple_size_v<decltype(ns_Registers_::FB.binder)>, 3);

	EXPECT_EQ(std::get<0>(ns_Registers_::FB.binder).associatedFunctions, std::get<0>(ns_Registers_::FB.internalBinder).associatedFunctions);
	EXPECT_EQ(std::get<1>(ns_Registers_::FB.binder).associatedFunctions, std::get<1>(ns_Registers_::FB.internalBinder).associatedFunctions);
	EXPECT_EQ(std::get<2>(ns_Registers_::FB.binder).associatedFunctions, std::get<2>(ns_Registers_::FB.internalBinder).associatedFunctions);
}

TEST(FunctionBinder, getFunctionName) {

	ns_Registers_::FB.use(ns_Registers_::FB);

	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::voidFunction1>(), "voidFunction1");
	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::boolFunction1>(), "boolFunction1");
	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::charFunction1>(), "charFunction1");

	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::voidFunction2>(), "voidFunction2");
	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::boolFunction2>(), "boolFunction2");
	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::charFunction2>(), "charFunction2");

	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::voidFunction3>(), "voidFunction3");
	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::boolFunction3>(), "boolFunction3");
	EXPECT_STREQ(ns_Registers_::FB.getFunctionName<&ns_Registers_::charFunction3>(), "charFunction3");
}