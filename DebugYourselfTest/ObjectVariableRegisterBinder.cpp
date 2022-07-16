#include "pch.h"

#include <DebugYourself.h>

using DebugYourself = dy::DebugYourself<true>;

namespace ns__registers_ {
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

		DebugYourself::ObjectVariableRegister<
			TestClass3,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;
	};


	DebugYourself::ObjectVariableRegisterBinder<
		decltype(TestClass1::OVR),
		decltype(TestClass2::OVR),
		decltype(TestClass3::OVR)> OVRB__;


	TestClass1 _TC1;
	TestClass2 _TC2;
	TestClass3 _TC3;

	DebugYourself::ObjectVariableRegisterBinder OVRB_Register_(
		_TC1.OVR,
		_TC2.OVR,
		_TC3.OVR);
	
}

TEST(ObjectVariableRegisterBinder, __) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns__registers_::OVRB__.binder)>, 3);
}

TEST(ObjectVariableRegisterBinder, _registers_) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns__registers_::OVRB_Register_.binder)>, 3);
}

TEST(ObjectVariableRegisterBinder, add) {
	ns__registers_::TestClass1 newObject11;
	ns__registers_::TestClass1 newObject12;
	ns__registers_::TestClass1 newObject13;

	ns__registers_::TestClass2 newObject21;
	ns__registers_::TestClass2 newObject22;
	ns__registers_::TestClass2 newObject23;

	ns__registers_::TestClass3 newObject31;
	ns__registers_::TestClass3 newObject32;
	ns__registers_::TestClass3 newObject33;

	
	ns__registers_::OVRB__.add(
		newObject11.OVR,
		newObject12.OVR,
		newObject13.OVR,

		newObject21.OVR,
		newObject22.OVR,
		newObject23.OVR,

		newObject31.OVR,
		newObject32.OVR,
		newObject33.OVR);
	

	EXPECT_EQ(std::get<0>(ns__registers_::OVRB__.binder).at(0)->associatedObject, &newObject11);
	EXPECT_EQ(std::get<0>(ns__registers_::OVRB__.binder).at(1)->associatedObject, &newObject12);
	EXPECT_EQ(std::get<0>(ns__registers_::OVRB__.binder).at(2)->associatedObject, &newObject13);

	EXPECT_EQ(std::get<1>(ns__registers_::OVRB__.binder).at(0)->associatedObject, &newObject21);
	EXPECT_EQ(std::get<1>(ns__registers_::OVRB__.binder).at(1)->associatedObject, &newObject22);
	EXPECT_EQ(std::get<1>(ns__registers_::OVRB__.binder).at(2)->associatedObject, &newObject23);

	EXPECT_EQ(std::get<2>(ns__registers_::OVRB__.binder).at(0)->associatedObject, &newObject31);
	EXPECT_EQ(std::get<2>(ns__registers_::OVRB__.binder).at(1)->associatedObject, &newObject32);
	EXPECT_EQ(std::get<2>(ns__registers_::OVRB__.binder).at(2)->associatedObject, &newObject33);


	ns__registers_::OVRB_Register_.add(
		newObject11.OVR,
		newObject12.OVR,
		newObject13.OVR,

		newObject21.OVR,
		newObject22.OVR,
		newObject23.OVR,

		newObject31.OVR,
		newObject32.OVR,
		newObject33.OVR);


	EXPECT_EQ(std::get<0>(ns__registers_::OVRB_Register_.binder).at(0)->associatedObject, &newObject11);
	EXPECT_EQ(std::get<0>(ns__registers_::OVRB_Register_.binder).at(1)->associatedObject, &newObject12);
	EXPECT_EQ(std::get<0>(ns__registers_::OVRB_Register_.binder).at(2)->associatedObject, &newObject13);

	EXPECT_EQ(std::get<1>(ns__registers_::OVRB_Register_.binder).at(0)->associatedObject, &newObject21);
	EXPECT_EQ(std::get<1>(ns__registers_::OVRB_Register_.binder).at(1)->associatedObject, &newObject22);
	EXPECT_EQ(std::get<1>(ns__registers_::OVRB_Register_.binder).at(2)->associatedObject, &newObject23);

	EXPECT_EQ(std::get<2>(ns__registers_::OVRB_Register_.binder).at(0)->associatedObject, &newObject31);
	EXPECT_EQ(std::get<2>(ns__registers_::OVRB_Register_.binder).at(1)->associatedObject, &newObject32);
	EXPECT_EQ(std::get<2>(ns__registers_::OVRB_Register_.binder).at(2)->associatedObject, &newObject33);
	
}

TEST(ObjectVariableRegisterBinder, getVariableName) {
	ns__registers_::TestClass1 newObject11;
	ns__registers_::TestClass1 newObject12;
	ns__registers_::TestClass1 newObject13;

	ns__registers_::TestClass2 newObject21;
	ns__registers_::TestClass2 newObject22;
	ns__registers_::TestClass2 newObject23;

	ns__registers_::TestClass3 newObject31;
	ns__registers_::TestClass3 newObject32;
	ns__registers_::TestClass3 newObject33;


	ns__registers_::OVRB__.add(
		newObject11.OVR,
		newObject12.OVR,
		newObject13.OVR,

		newObject21.OVR,
		newObject22.OVR,
		newObject23.OVR,

		newObject31.OVR,
		newObject32.OVR,
		newObject33.OVR);


	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject11.voidVariable), "voidVariable1");
	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject12.boolVariable), "boolVariable1");
	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject13.charVariable), "charVariable1");

	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject21.voidVariable), "voidVariable2");
	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject22.boolVariable), "boolVariable2");
	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject23.charVariable), "charVariable2");

	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject31.voidVariable), "voidVariable3");
	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject32.boolVariable), "boolVariable3");
	EXPECT_STREQ(ns__registers_::OVRB__.getVariableName(&newObject33.charVariable), "charVariable3");

	ns__registers_::OVRB_Register_.add(
		newObject11.OVR,
		newObject12.OVR,
		newObject13.OVR,

		newObject21.OVR,
		newObject22.OVR,
		newObject23.OVR,

		newObject31.OVR,
		newObject32.OVR,
		newObject33.OVR);


	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject11.voidVariable), "voidVariable1");
	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject12.boolVariable), "boolVariable1");
	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject13.charVariable), "charVariable1");

	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject21.voidVariable), "voidVariable2");
	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject22.boolVariable), "boolVariable2");
	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject23.charVariable), "charVariable2");

	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject31.voidVariable), "voidVariable3");
	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject32.boolVariable), "boolVariable3");
	EXPECT_STREQ(ns__registers_::OVRB_Register_.getVariableName(&newObject33.charVariable), "charVariable3");

}

TEST(ObjectVariableRegisterBinder, getObjectName) {
	ns__registers_::TestClass1 newObject11;
	ns__registers_::TestClass1 newObject12;
	ns__registers_::TestClass1 newObject13;

	ns__registers_::TestClass2 newObject21;
	ns__registers_::TestClass2 newObject22;
	ns__registers_::TestClass2 newObject23;

	ns__registers_::TestClass3 newObject31;
	ns__registers_::TestClass3 newObject32;
	ns__registers_::TestClass3 newObject33;

	
	ns__registers_::OVRB__.add(
		newObject11.OVR,
		newObject12.OVR,
		newObject13.OVR,

		newObject21.OVR,
		newObject22.OVR,
		newObject23.OVR,

		newObject31.OVR,
		newObject32.OVR,
		newObject33.OVR);

	ns__registers_::OVRB_Register_.add(
		newObject11.OVR,
		newObject12.OVR,
		newObject13.OVR,

		newObject21.OVR,
		newObject22.OVR,
		newObject23.OVR,

		newObject31.OVR,
		newObject32.OVR,
		newObject33.OVR);


	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject11), "TestObject1");
	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject12), "TestObject1");
	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject13), "TestObject1");

	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject21), "TestObject2");
	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject22), "TestObject2");
	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject23), "TestObject2");

	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject31), "TestObject3");
	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject32), "TestObject3");
	EXPECT_STREQ(ns__registers_::OVRB__.getObjectName(&newObject33), "TestObject3");
	
}