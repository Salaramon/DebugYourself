#include "pch.h"

#include <DebugYourself.h>

using DebugYourself = dy::DebugYourself<true>;

namespace ns__ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR()
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		auto getVoidVariable() { return &voidVariable; }
	};
};

namespace ns_ObjectType_tuple_ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR(this, std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		auto getVoidVariable() { return &voidVariable; }
	};
};

namespace ns_ObjectType_char_tuple_ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		auto getVoidVariable() { return &voidVariable; }
	};
};

namespace ns_ObjectType_tuple_tuple_ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR_No_Naming(this, std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple()),

			OVR_Partial_Naming(this, std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple("voidVariable")),

			OVR_Full_Naming(this, std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_No_Naming;

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Partial_Naming;

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Full_Naming;

		auto getVoidVariable() { return &voidVariable; }
	};
};

namespace ns_ObjectType_char_tuple_tuple_ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR_No_Naming(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple()),

			OVR_Partial_Naming(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple("voidVariable")),

			OVR_Full_Naming(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_No_Naming;

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Partial_Naming;

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Full_Naming;

		auto getVoidVariable() { return &voidVariable; }
	};
};
TEST(ObjectVariableRegister, __) {
	ns__::TestClass newClass;

	EXPECT_EQ(newClass.OVR.associatedObject, nullptr);

	EXPECT_EQ(std::get<0>(newClass.OVR.associatedVariables), nullptr);
	EXPECT_EQ(std::get<1>(newClass.OVR.associatedVariables), nullptr);
	EXPECT_EQ(std::get<2>(newClass.OVR.associatedVariables), nullptr);

	EXPECT_STREQ(std::get<0>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR.objectName, nullptr);
	EXPECT_GT(newClass.OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR.instanceID, 1);
}

TEST(ObjectVariableRegister, _ObjectType_tuple_) {
	ns_ObjectType_tuple_::TestClass newClass;

	EXPECT_EQ(newClass.OVR.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR.objectName, nullptr);
	EXPECT_GT(newClass.OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR.instanceID, 1);
}

TEST(ObjectVariableRegister, _ObjectType_char_tuple_) {
	ns_ObjectType_char_tuple_::TestClass newClass;

	EXPECT_EQ(newClass.OVR.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR.objectName, "TestObject");
	EXPECT_GT(newClass.OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR.instanceID, 1);
}

TEST(ObjectVariableRegister, _ObjectType_tuple_tuple_) {
	ns_ObjectType_tuple_tuple_::TestClass newClass;

	EXPECT_EQ(newClass.OVR_No_Naming.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR_No_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_No_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_No_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_No_Naming.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.OVR_No_Naming.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR_No_Naming.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR_No_Naming.objectName, nullptr);
	EXPECT_GT(newClass.OVR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_No_Naming.instanceID, 1);


	EXPECT_EQ(newClass.OVR_Partial_Naming.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR_Partial_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_Partial_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_Partial_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_Partial_Naming.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR_Partial_Naming.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR_Partial_Naming.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR_Partial_Naming.objectName, nullptr);
	EXPECT_GT(newClass.OVR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_Partial_Naming.instanceID, 2);


	EXPECT_EQ(newClass.OVR_Full_Naming.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR_Full_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_Full_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_Full_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_Full_Naming.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR_Full_Naming.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(newClass.OVR_Full_Naming.associatedVariableNames), "charVariable");

	EXPECT_STREQ(newClass.OVR_Full_Naming.objectName, nullptr);
	EXPECT_GT(newClass.OVR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_Full_Naming.instanceID, 3);
}

TEST(ObjectVariableRegister, _ObjectType_char_tuple_tuple_) {
	ns_ObjectType_char_tuple_tuple_::TestClass newClass;

	EXPECT_EQ(newClass.OVR_No_Naming.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR_No_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_No_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_No_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_No_Naming.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.OVR_No_Naming.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR_No_Naming.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR_No_Naming.objectName, "TestObject");
	EXPECT_GT(newClass.OVR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_No_Naming.instanceID, 1);


	EXPECT_EQ(newClass.OVR_Partial_Naming.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR_Partial_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_Partial_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_Partial_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_Partial_Naming.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR_Partial_Naming.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR_Partial_Naming.associatedVariableNames), nullptr);

	EXPECT_STREQ(newClass.OVR_Partial_Naming.objectName, "TestObject");
	EXPECT_GT(newClass.OVR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_Partial_Naming.instanceID, 2);


	EXPECT_EQ(newClass.OVR_Full_Naming.associatedObject, &newClass);

	EXPECT_EQ(std::get<0>(newClass.OVR_Full_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_Full_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_Full_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_Full_Naming.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR_Full_Naming.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(newClass.OVR_Full_Naming.associatedVariableNames), "charVariable");

	EXPECT_STREQ(newClass.OVR_Full_Naming.objectName, "TestObject");
	EXPECT_GT(newClass.OVR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_Full_Naming.instanceID, 3);
}








namespace ns_ObjectVariableRegister_l_ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :

			OVR_Full_Naming(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Full_Naming;

		auto getVoidVariable() { return &voidVariable; }
	};
};


namespace ns_assignment_ObjectVariableRegister_l {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR(),

			OVR_Full_Naming(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Full_Naming;

		auto getVoidVariable() { return &voidVariable; }
	};
}

namespace ns_ObjectVariableRegister_r_ {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :

			OVR(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		auto getVoidVariable() { return &voidVariable; }
	};
};


namespace ns_assignment_ObjectVariableRegister_r {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR(),

			OVR_Full_Naming(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR_Full_Naming;

		auto getVoidVariable() { return &voidVariable; }
	};
};


TEST(ObjectVariableRegister, _ObjectVariableRegister_l) {

	ns_ObjectVariableRegister_l_::TestClass newClass;

	DebugYourself::ObjectVariableRegister<
		ns_ObjectVariableRegister_l_::TestClass,
		void*,
		bool,
		char> OVR(newClass.OVR_Full_Naming);

	EXPECT_EQ(std::get<0>(OVR.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(OVR.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(OVR.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(OVR.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(OVR.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(OVR.associatedVariableNames), "charVariable");

	EXPECT_STREQ(OVR.objectName, "TestObject");
	EXPECT_GT(OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(OVR.instanceID, 2);



	EXPECT_EQ(std::get<0>(newClass.OVR_Full_Naming.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR_Full_Naming.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR_Full_Naming.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR_Full_Naming.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR_Full_Naming.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(newClass.OVR_Full_Naming.associatedVariableNames), "charVariable");

	EXPECT_STREQ(newClass.OVR_Full_Naming.objectName, "TestObject");
	EXPECT_GT(newClass.OVR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR_Full_Naming.instanceID, 1);

}

TEST(ObjectVariableRegister, assignment_ObjectVariableRegister_l) {
	ns_assignment_ObjectVariableRegister_l::TestClass newClass;

	newClass.OVR = newClass.OVR_Full_Naming;

	EXPECT_EQ(std::get<0>(newClass.OVR.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(newClass.OVR.associatedVariableNames), "charVariable");

	EXPECT_STREQ(newClass.OVR.objectName, "TestObject");
	EXPECT_GT(newClass.OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR.instanceID, 3);
}

TEST(ObjectVariableRegister, _ObjectVariableRegister_r) {
	ns_ObjectVariableRegister_r_::TestClass newClass;

	DebugYourself::ObjectVariableRegister<
		ns_ObjectVariableRegister_r_::TestClass,
		void*,
		bool,
		char> OVR(std::move(newClass.OVR));

	EXPECT_EQ(std::get<0>(OVR.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(OVR.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(OVR.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(OVR.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(OVR.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(OVR.associatedVariableNames), "charVariable");

	EXPECT_STREQ(OVR.objectName, "TestObject");
	EXPECT_GT(OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(OVR.instanceID, 1);



	EXPECT_EQ(std::get<0>(newClass.OVR.associatedVariables), nullptr);
	EXPECT_EQ(std::get<1>(newClass.OVR.associatedVariables), nullptr);
	EXPECT_EQ(std::get<2>(newClass.OVR.associatedVariables), nullptr);

	EXPECT_STREQ(std::get<0>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<1>(newClass.OVR.associatedVariableNames), nullptr);
	EXPECT_STREQ(std::get<2>(newClass.OVR.associatedVariableNames), nullptr);

	EXPECT_EQ(newClass.OVR.objectName, nullptr);
	EXPECT_GT(newClass.OVR.timeStamp + std::numeric_limits<long double>::min(), std::chrono::duration_values<long double>::zero());
	EXPECT_EQ(newClass.OVR.instanceID, 0);
}

TEST(ObjectVariableRegister, assignment_ObjectVariableRegister_r) {
	ns_assignment_ObjectVariableRegister_r::TestClass newClass;

	newClass.OVR = std::move(newClass.OVR_Full_Naming);

	EXPECT_EQ(std::get<0>(newClass.OVR.associatedVariables), newClass.getVoidVariable());
	EXPECT_EQ(std::get<1>(newClass.OVR.associatedVariables), &newClass.boolVariable);
	EXPECT_EQ(std::get<2>(newClass.OVR.associatedVariables), &newClass.charVariable);

	EXPECT_STREQ(std::get<0>(newClass.OVR.associatedVariableNames), "voidVariable");
	EXPECT_STREQ(std::get<1>(newClass.OVR.associatedVariableNames), "boolVariable");
	EXPECT_STREQ(std::get<2>(newClass.OVR.associatedVariableNames), "charVariable");

	EXPECT_STREQ(newClass.OVR.objectName, "TestObject");
	EXPECT_GT(newClass.OVR.timeStamp + std::numeric_limits<long double>::min(), 0);
	EXPECT_EQ(newClass.OVR.instanceID, 2);
}








namespace ns_function1_5 {
	class TestClass {
	private:
		void* voidVariable;
	public:
		bool boolVariable;
		char charVariable;

		TestClass() :
			OVR(this, "TestObject", std::tuple(
				&voidVariable,
				&boolVariable,
				&charVariable),
				std::tuple(
					"voidVariable",
					"boolVariable",
					"charVariable"))
		{}

		DebugYourself::ObjectVariableRegister<
			TestClass,
			decltype(voidVariable),
			decltype(boolVariable),
			decltype(charVariable)> OVR;

		auto getVoidVariable() { return &voidVariable; }
	};
};

TEST(ObjectVariableRegister, getVariablePointer) {
	ns_function1_5::TestClass newClass;

	EXPECT_EQ(newClass.OVR.getVariablePointer<0>(), newClass.getVoidVariable());
	EXPECT_EQ(newClass.OVR.getVariablePointer<1>(), &newClass.boolVariable);
	EXPECT_EQ(newClass.OVR.getVariablePointer<2>(), &newClass.charVariable);
}

TEST(ObjectVariableRegister, getVariableName) {
	ns_function1_5::TestClass newClass;

	EXPECT_STREQ(newClass.OVR.getVariableName<0>(), "voidVariable");
	EXPECT_STREQ(newClass.OVR.getVariableName<1>(), "boolVariable");
	EXPECT_STREQ(newClass.OVR.getVariableName<2>(), "charVariable");
}

TEST(ObjectVariableRegister, getObject) {
	ns_function1_5::TestClass newClass;

	EXPECT_EQ(newClass.OVR.getObject(), &newClass);
}

TEST(ObjectVariableRegister, getObjectName) {
	ns_function1_5::TestClass newClass;

	EXPECT_STREQ(newClass.OVR.getObjectName(), "TestObject");
}

TEST(ObjectVariableRegister, getNumberOfVariables) {
	ns_function1_5::TestClass newClass;

	EXPECT_EQ(newClass.OVR.getNumberOfVariables(), 3);
}