#include "pch.h"

#include <DebugYourself.h>

namespace ns_Parameters_ {
	class TestClass {
	private:
		void voidFunction(bool, char) {}
	public:
		bool boolFunction(void*, char) { return true; }
		char charFunction(void*, bool) { return ' '; }

		inline static auto CFR_No_Naming = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>();

		inline static auto CFR_Partial_Naming = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>("voidFunction");

		inline static auto CFR_Full_Naming = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(
				"voidFunction",
				"boolFunction",
				"charFunction");

		static auto getVoidFunction() { return &voidFunction; }
	};
}

namespace ns_tuple_ {
	class TestClass {
	private:
		void voidFunction(bool, char) {}
	public:
		bool boolFunction(void*, char) { return true; }
		char charFunction(void*, bool) { return ' '; }

		inline static auto CFR_No_Naming = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(std::tuple());

		inline static auto CFR_Partial_Naming = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(std::tuple("voidFunction"));

		inline static auto CFR_Full_Naming = DebugYourself::ClassFunctionRegister<
			&voidFunction,
			&boolFunction,
			&charFunction>(std::tuple(
				"voidFunction",
				"boolFunction",
				"charFunction"));

		static constexpr auto getVoidFunction() { return &voidFunction; }
	};
}

TEST(ClassFunctionRegister, _Parameters_) {
	ns_Parameters_::TestClass newClass;
	EXPECT_EQ(std::get<0>(newClass.CFR_No_Naming.associatedFunctions), ns_Parameters_::TestClass::getVoidFunction());
	EXPECT_EQ(std::get<1>(newClass.CFR_No_Naming.associatedFunctions), &ns_Parameters_::TestClass::boolFunction);
	EXPECT_EQ(std::get<2>(newClass.CFR_No_Naming.associatedFunctions), &ns_Parameters_::TestClass::charFunction);

	EXPECT_STREQ(std::get<0>(newClass.CFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.CFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.CFR_No_Naming.associatedFunctionNames), nullptr);

	EXPECT_STREQ(ns_Parameters_::TestClass::CFR_No_Naming.className.c_str(), "ns_Parameters_::TestClass");
	EXPECT_GT(newClass.CFR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(newClass.CFR_Partial_Naming.associatedFunctions), ns_Parameters_::TestClass::getVoidFunction());
	EXPECT_EQ(std::get<1>(newClass.CFR_Partial_Naming.associatedFunctions), &ns_Parameters_::TestClass::boolFunction);
	EXPECT_EQ(std::get<2>(newClass.CFR_Partial_Naming.associatedFunctions), &ns_Parameters_::TestClass::charFunction);

	EXPECT_STREQ(std::get<0>(newClass.CFR_Partial_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(newClass.CFR_Partial_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.CFR_Partial_Naming.associatedFunctionNames), nullptr);

	EXPECT_STREQ(ns_Parameters_::TestClass::CFR_Partial_Naming.className.c_str(), "ns_Parameters_::TestClass");
	EXPECT_GT(newClass.CFR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(newClass.CFR_Full_Naming.associatedFunctions), ns_Parameters_::TestClass::getVoidFunction());
	EXPECT_EQ(std::get<1>(newClass.CFR_Full_Naming.associatedFunctions), &ns_Parameters_::TestClass::boolFunction);
	EXPECT_EQ(std::get<2>(newClass.CFR_Full_Naming.associatedFunctions), &ns_Parameters_::TestClass::charFunction);

	EXPECT_STREQ(std::get<0>(newClass.CFR_Full_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(newClass.CFR_Full_Naming.associatedFunctionNames), "boolFunction");
	EXPECT_STREQ(std::get<2>(newClass.CFR_Full_Naming.associatedFunctionNames), "charFunction");

	EXPECT_STREQ(ns_Parameters_::TestClass::CFR_Full_Naming.className.c_str(), "ns_Parameters_::TestClass");
	EXPECT_GT(newClass.CFR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
}
TEST(ClassFunctionRegister, _tuple_) {
	ns_tuple_::TestClass newClass;


	EXPECT_EQ(std::get<0>(newClass.CFR_No_Naming.associatedFunctions), ns_tuple_::TestClass::getVoidFunction());
	EXPECT_EQ(std::get<1>(newClass.CFR_No_Naming.associatedFunctions), &ns_tuple_::TestClass::boolFunction);
	EXPECT_EQ(std::get<2>(newClass.CFR_No_Naming.associatedFunctions), &ns_tuple_::TestClass::charFunction);

	EXPECT_STREQ(std::get<0>(newClass.CFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.CFR_No_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.CFR_No_Naming.associatedFunctionNames), nullptr);

	EXPECT_STREQ(ns_tuple_::TestClass::CFR_No_Naming.className.c_str(), "ns_tuple_::TestClass");
	EXPECT_GT(newClass.CFR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(newClass.CFR_Partial_Naming.associatedFunctions), ns_tuple_::TestClass::getVoidFunction());
	EXPECT_EQ(std::get<1>(newClass.CFR_Partial_Naming.associatedFunctions), &ns_tuple_::TestClass::boolFunction);
	EXPECT_EQ(std::get<2>(newClass.CFR_Partial_Naming.associatedFunctions), &ns_tuple_::TestClass::charFunction);

	EXPECT_STREQ(std::get<0>(newClass.CFR_Partial_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(newClass.CFR_Partial_Naming.associatedFunctionNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.CFR_Partial_Naming.associatedFunctionNames), nullptr);

	EXPECT_STREQ(ns_tuple_::TestClass::CFR_Partial_Naming.className.c_str(), "ns_tuple_::TestClass");
	EXPECT_GT(newClass.CFR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);


	EXPECT_EQ(std::get<0>(newClass.CFR_Full_Naming.associatedFunctions), ns_tuple_::TestClass::getVoidFunction());
	EXPECT_EQ(std::get<1>(newClass.CFR_Full_Naming.associatedFunctions), &ns_tuple_::TestClass::boolFunction);
	EXPECT_EQ(std::get<2>(newClass.CFR_Full_Naming.associatedFunctions), &ns_tuple_::TestClass::charFunction);

	EXPECT_STREQ(std::get<0>(newClass.CFR_Full_Naming.associatedFunctionNames), "voidFunction");
	EXPECT_STREQ(std::get<1>(newClass.CFR_Full_Naming.associatedFunctionNames), "boolFunction");
	EXPECT_STREQ(std::get<2>(newClass.CFR_Full_Naming.associatedFunctionNames), "charFunction");
	
	EXPECT_STREQ(ns_tuple_::TestClass::CFR_Full_Naming.className.c_str(), "ns_tuple_::TestClass");
	EXPECT_GT(newClass.CFR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
}

TEST(ClassFunctionRegister, getFunctionPointer) {
	ns_Parameters_::TestClass _Parameters_Constructed;

	EXPECT_EQ(_Parameters_Constructed.CFR_No_Naming.getFunctionPointer<0>(), ns_Parameters_::TestClass::getVoidFunction());
	EXPECT_EQ(_Parameters_Constructed.CFR_No_Naming.getFunctionPointer<1>(), &ns_Parameters_::TestClass::boolFunction);
	EXPECT_EQ(_Parameters_Constructed.CFR_No_Naming.getFunctionPointer<2>(), &ns_Parameters_::TestClass::charFunction);

	EXPECT_EQ(_Parameters_Constructed.CFR_Partial_Naming.getFunctionPointer<0>(), ns_Parameters_::TestClass::getVoidFunction());
	EXPECT_EQ(_Parameters_Constructed.CFR_Partial_Naming.getFunctionPointer<1>(), &ns_Parameters_::TestClass::boolFunction);
	EXPECT_EQ(_Parameters_Constructed.CFR_Partial_Naming.getFunctionPointer<2>(), &ns_Parameters_::TestClass::charFunction);

	EXPECT_EQ(_Parameters_Constructed.CFR_Full_Naming.getFunctionPointer<0>(), ns_Parameters_::TestClass::getVoidFunction());
	EXPECT_EQ(_Parameters_Constructed.CFR_Full_Naming.getFunctionPointer<1>(), &ns_Parameters_::TestClass::boolFunction);
	EXPECT_EQ(_Parameters_Constructed.CFR_Full_Naming.getFunctionPointer<2>(), &ns_Parameters_::TestClass::charFunction);

	
	ns_tuple_::TestClass _tuple_Constructed;

	EXPECT_EQ(_tuple_Constructed.CFR_No_Naming.getFunctionPointer<0>(), ns_tuple_::TestClass::getVoidFunction());
	EXPECT_EQ(_tuple_Constructed.CFR_No_Naming.getFunctionPointer<1>(), &ns_tuple_::TestClass::boolFunction);
	EXPECT_EQ(_tuple_Constructed.CFR_No_Naming.getFunctionPointer<2>(), &ns_tuple_::TestClass::charFunction);

	EXPECT_EQ(_tuple_Constructed.CFR_Partial_Naming.getFunctionPointer<0>(), ns_tuple_::TestClass::getVoidFunction());
	EXPECT_EQ(_tuple_Constructed.CFR_Partial_Naming.getFunctionPointer<1>(), &ns_tuple_::TestClass::boolFunction);
	EXPECT_EQ(_tuple_Constructed.CFR_Partial_Naming.getFunctionPointer<2>(), &ns_tuple_::TestClass::charFunction);

	EXPECT_EQ(_tuple_Constructed.CFR_Full_Naming.getFunctionPointer<0>(), ns_tuple_::TestClass::getVoidFunction());
	EXPECT_EQ(_tuple_Constructed.CFR_Full_Naming.getFunctionPointer<1>(), &ns_tuple_::TestClass::boolFunction);
	EXPECT_EQ(_tuple_Constructed.CFR_Full_Naming.getFunctionPointer<2>(), &ns_tuple_::TestClass::charFunction);
}

TEST(ClassFunctionRegister, getFunctionName) {
	ns_Parameters_::TestClass _Parameters_Constructed;

	EXPECT_STREQ(_Parameters_Constructed.CFR_No_Naming.getFunctionName<0>(), nullptr);
	EXPECT_STREQ(_Parameters_Constructed.CFR_No_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(_Parameters_Constructed.CFR_No_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(_Parameters_Constructed.CFR_Partial_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(_Parameters_Constructed.CFR_Partial_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(_Parameters_Constructed.CFR_Partial_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(_Parameters_Constructed.CFR_Full_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(_Parameters_Constructed.CFR_Full_Naming.getFunctionName<1>(), "boolFunction");
	EXPECT_STREQ(_Parameters_Constructed.CFR_Full_Naming.getFunctionName<2>(), "charFunction");


	ns_tuple_::TestClass _tuple_Constructed;

	EXPECT_STREQ(_tuple_Constructed.CFR_No_Naming.getFunctionName<0>(), nullptr);
	EXPECT_STREQ(_tuple_Constructed.CFR_No_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(_tuple_Constructed.CFR_No_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(_tuple_Constructed.CFR_Partial_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(_tuple_Constructed.CFR_Partial_Naming.getFunctionName<1>(), nullptr);
	EXPECT_STREQ(_tuple_Constructed.CFR_Partial_Naming.getFunctionName<2>(), nullptr);

	EXPECT_STREQ(_tuple_Constructed.CFR_Full_Naming.getFunctionName<0>(), "voidFunction");
	EXPECT_STREQ(_tuple_Constructed.CFR_Full_Naming.getFunctionName<1>(), "boolFunction");
	EXPECT_STREQ(_tuple_Constructed.CFR_Full_Naming.getFunctionName<2>(), "charFunction");
}

TEST(ClassFunctionRegister, getClassName) {
	ns_Parameters_::TestClass _Parameters_Constructed;
	EXPECT_STREQ(_Parameters_Constructed.CFR_No_Naming.getClassName(), "ns_Parameters_::TestClass");
	EXPECT_STREQ(_Parameters_Constructed.CFR_Partial_Naming.getClassName(), "ns_Parameters_::TestClass");
	EXPECT_STREQ(_Parameters_Constructed.CFR_Full_Naming.getClassName(), "ns_Parameters_::TestClass");

	ns_tuple_::TestClass _tuple_Constructed;
	EXPECT_STREQ(_tuple_Constructed.CFR_No_Naming.getClassName(), "ns_tuple_::TestClass");
	EXPECT_STREQ(_tuple_Constructed.CFR_Partial_Naming.getClassName(), "ns_tuple_::TestClass");
	EXPECT_STREQ(_tuple_Constructed.CFR_Full_Naming.getClassName(), "ns_tuple_::TestClass");
}