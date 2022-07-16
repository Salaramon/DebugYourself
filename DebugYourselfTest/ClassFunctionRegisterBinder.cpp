#include "pch.h"

#include <DebugYourself.h>

using DebugYourself = dy::DebugYourself<true>;

namespace ns__Registers_ {
	class TestClass1 {
	public:
		void voidFunction(bool, char) {}
		bool boolFunction(void*, char) { return true; }
		char charFunction(void*, bool) { return ' '; }

		inline static auto CFR = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(
				"voidFunction1",
				"boolFunction1",
				"charFunction1");
	};

	class TestClass2 {
	public:
		void voidFunction(bool, char) {}
		bool boolFunction(void*, char) { return true; }
		char charFunction(void*, bool) { return ' '; }

		inline static auto CFR = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(
				"voidFunction2",
				"boolFunction2",
				"charFunction2");
	};

	class TestClass3 {
	public:
		void voidFunction(bool, char) {}
		bool boolFunction(void*, char) { return true; }
		char charFunction(void*, bool) { return ' '; }

		inline static auto CFR = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(
				"voidFunction3",
				"boolFunction3",
				"charFunction3");
	};


	DebugYourself::ClassFunctionRegisterBinder<
		decltype(TestClass1::CFR),
		decltype(TestClass2::CFR),
		decltype(TestClass3::CFR)> CFRB__;

	DebugYourself::ClassFunctionRegisterBinder CFRB_Registers_(
		TestClass1::CFR,
		TestClass2::CFR,
		TestClass3::CFR);
}

TEST(ClassFunctionRegisterBinder, __) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns__Registers_::CFRB__.internalBinder)>, 3);
}

TEST(ClassFunctionRegisterBinder, _Registers_) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns__Registers_::CFRB_Registers_.internalBinder)>, 3);
}

TEST(ClassFunctionRegisterBinder, use) {
	ns__Registers_::CFRB__.use(ns__Registers_::CFRB__);
	EXPECT_EQ(std::tuple_size_v<decltype(ns__Registers_::CFRB__.binder)>, 3);

	EXPECT_EQ(std::get<1>(ns__Registers_::CFRB__.binder).associatedFunctions, std::get<1>(ns__Registers_::CFRB__.internalBinder).associatedFunctions);
	EXPECT_EQ(std::get<2>(ns__Registers_::CFRB__.binder).associatedFunctions, std::get<2>(ns__Registers_::CFRB__.internalBinder).associatedFunctions);
	EXPECT_EQ(std::get<0>(ns__Registers_::CFRB__.binder).associatedFunctions, std::get<0>(ns__Registers_::CFRB__.internalBinder).associatedFunctions);


	ns__Registers_::CFRB_Registers_.use(ns__Registers_::CFRB_Registers_);
	EXPECT_EQ(std::tuple_size_v<decltype(ns__Registers_::CFRB_Registers_.binder)>, 3);

	EXPECT_EQ(std::get<0>(ns__Registers_::CFRB_Registers_.binder).associatedFunctions, std::get<0>(ns__Registers_::CFRB_Registers_.internalBinder).associatedFunctions);
	EXPECT_EQ(std::get<1>(ns__Registers_::CFRB_Registers_.binder).associatedFunctions, std::get<1>(ns__Registers_::CFRB_Registers_.internalBinder).associatedFunctions);
	EXPECT_EQ(std::get<2>(ns__Registers_::CFRB_Registers_.binder).associatedFunctions, std::get<2>(ns__Registers_::CFRB_Registers_.internalBinder).associatedFunctions);

}

TEST(ClassFunctionRegisterBinder, getFunctionName) {
	ns__Registers_::CFRB__.use(ns__Registers_::CFRB__);

	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass1::voidFunction>(), nullptr);
	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass1::boolFunction>(), nullptr);
	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass1::charFunction>(), nullptr);

	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass2::voidFunction>(), nullptr);
	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass2::boolFunction>(), nullptr);
	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass2::charFunction>(), nullptr);

	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass3::voidFunction>(), nullptr);
	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass3::boolFunction>(), nullptr);
	EXPECT_STREQ(ns__Registers_::CFRB__.getFunctionName<&ns__Registers_::TestClass3::charFunction>(), nullptr);


	ns__Registers_::CFRB_Registers_.use(ns__Registers_::CFRB_Registers_);

	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass1::voidFunction>(), "voidFunction1");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass1::boolFunction>(), "boolFunction1");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass1::charFunction>(), "charFunction1");

	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass2::voidFunction>(), "voidFunction2");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass2::boolFunction>(), "boolFunction2");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass2::charFunction>(), "charFunction2");

	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass3::voidFunction>(), "voidFunction3");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass3::boolFunction>(), "boolFunction3");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getFunctionName<&ns__Registers_::TestClass3::charFunction>(), "charFunction3");
}

TEST(ClassFunctionRegisterBinder, getClassName) {
	EXPECT_STREQ(ns__Registers_::CFRB__.getClassName<&ns__Registers_::TestClass1::voidFunction>(), "ns__Registers_::TestClass1");
	EXPECT_STREQ(ns__Registers_::CFRB__.getClassName<&ns__Registers_::TestClass2::boolFunction>(), "ns__Registers_::TestClass2");
	EXPECT_STREQ(ns__Registers_::CFRB__.getClassName<&ns__Registers_::TestClass3::charFunction>(), "ns__Registers_::TestClass3");

	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getClassName<&ns__Registers_::TestClass1::voidFunction>(), "ns__Registers_::TestClass1");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getClassName<&ns__Registers_::TestClass2::boolFunction>(), "ns__Registers_::TestClass2");
	EXPECT_STREQ(ns__Registers_::CFRB_Registers_.getClassName<&ns__Registers_::TestClass3::charFunction>(), "ns__Registers_::TestClass3");
}