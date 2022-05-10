#include "pch.h"

#include <DebugYourself.h>

namespace ns_TestClasses {
	class TestClass1 {
	public:
		TestClass1() :
			OVR(this, "TestObject1", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable1",
					"boolVariable1",
					"charVariable1"))
		{}

		void* voidVariable;
		bool boolVariable;
		char charVariable;

		DebugYourself::ObjectVariableRegister<
			TestClass1,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

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
		TestClass2() :
			OVR(this, "TestObject2", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable2",
					"boolVariable2",
					"charVariable2"))
		{}

		void* voidVariable;
		bool boolVariable;
		char charVariable;

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

		DebugYourself::ObjectVariableRegister<
			TestClass2,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;
	};

	class TestClass3 {
	public:
		TestClass3() :
			OVR(this, "TestObject3", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable3",
					"boolVariable3",
					"charVariable3"))
		{}

		void* voidVariable;
		bool boolVariable;
		char charVariable;

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

		DebugYourself::ObjectVariableRegister<
			TestClass3,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;
	};


	TestClass1 _TC1;
	TestClass2 _TC2;
	TestClass3 _TC3;

	DebugYourself::ObjectVariableRegisterBinder OVRB_Register_(
		_TC1.OVR,
		_TC2.OVR,
		_TC3.OVR);

	DebugYourself::ClassFunctionRegisterBinder CFRB_Register_(
		TestClass1::CFR,
		TestClass2::CFR,
		TestClass3::CFR);

}

TEST(Dependencies, CreateDatabase) {

	using DY = DebugYourself::Dependencies<decltype(ns_TestClasses::CFRB_Register_), decltype(ns_TestClasses::OVRB_Register_), void, void>;

	ns_TestClasses::CFRB_Register_.use(ns_TestClasses::CFRB_Register_);
	ns_TestClasses::OVRB_Register_.add(
		ns_TestClasses::_TC1.OVR,
		ns_TestClasses::_TC2.OVR,
		ns_TestClasses::_TC3.OVR
	);

	DY::debug<&ns_TestClasses::TestClass2::charFunction>(&ns_TestClasses::_TC2, &ns_TestClasses::_TC2.boolVariable, 5, { "testTag", "otherTag", }, "test message");
	DY::debug<&ns_TestClasses::TestClass2::charFunction>(&ns_TestClasses::_TC2, &ns_TestClasses::_TC2.boolVariable, 5, { "testTag2", "otherTag", }, "sdfh");
	DY::debug<&ns_TestClasses::TestClass2::charFunction>(&ns_TestClasses::_TC2, &ns_TestClasses::_TC2.boolVariable, 5, { "testTag", "otherTag2", }, "asdgfhf");

	DebugYourself::end();
}