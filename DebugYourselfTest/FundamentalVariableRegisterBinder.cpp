#include "pch.h"

#include <DebugYourself.h>

namespace ns__registers_ {

	void* voidVariable11;
	bool boolVariable11;
	char charVariable11;

	void* voidVariable12;
	bool boolVariable12;
	char charVariable12;

	void* voidVariable13;
	bool boolVariable13;
	char charVariable13;

	void* voidVariable21;
	bool boolVariable21;
	char charVariable21;

	void* voidVariable22;
	bool boolVariable22;
	char charVariable22;

	void* voidVariable23;
	bool boolVariable23;
	char charVariable23;

	void* voidVariable31;
	bool boolVariable31;
	char charVariable31;

	void* voidVariable32;
	bool boolVariable32;
	char charVariable32;

	void* voidVariable33;
	bool boolVariable33;
	char charVariable33;

	DebugYourself::FundamentalVariableRegister<
		decltype(voidVariable11),
		decltype(boolVariable11),
		decltype(charVariable11)> FVR11(std::tuple(
			&voidVariable11,
			&boolVariable11,
			&charVariable11),
			std::tuple(
				"voidVariable11",
				"boolVariable11",
				"charVariable11"));

	DebugYourself::FundamentalVariableRegister<
		decltype(voidVariable12),
		decltype(boolVariable12),
		decltype(charVariable12)> FVR12(std::tuple(
			&voidVariable12,
			&boolVariable12,
			&charVariable12),
			std::tuple(
				"voidVariable12",
				"boolVariable12",
				"charVariable12"));

	DebugYourself::FundamentalVariableRegister<
		decltype(voidVariable13),
		decltype(boolVariable13),
		decltype(charVariable13)> FVR13(std::tuple(
			&voidVariable13,
			&boolVariable13,
			&charVariable13),
			std::tuple(
				"voidVariable13",
				"boolVariable13",
				"charVariable13"));

	DebugYourself::FundamentalVariableRegister<
		decltype(boolVariable21),
		decltype(voidVariable21),
		decltype(charVariable21)> FVR21(std::tuple(
			&boolVariable21,
			&voidVariable21,
			&charVariable21),
			std::tuple(
				"boolVariable21",
				"voidVariable21",
				"charVariable21"));

	DebugYourself::FundamentalVariableRegister<
		decltype(boolVariable22),
		decltype(voidVariable22),
		decltype(charVariable22)> FVR22(std::tuple(
			&boolVariable22,
			&voidVariable22,
			&charVariable22),
			std::tuple(
				"boolVariable22",
				"voidVariable22",
				"charVariable22"));

	DebugYourself::FundamentalVariableRegister<
		decltype(boolVariable23),
		decltype(voidVariable23),
		decltype(charVariable23)> FVR23(std::tuple(
			&boolVariable23,
			&voidVariable23,
			&charVariable23),
			std::tuple(
				"boolVariable23",
				"voidVariable23",
				"charVariable23"));

	DebugYourself::FundamentalVariableRegister<
		decltype(charVariable31),
		decltype(boolVariable31),
		decltype(voidVariable31)> FVR31(std::tuple(
			&charVariable31,
			&boolVariable31,
			&voidVariable31),
			std::tuple(
				"charVariable31",
				"boolVariable31",
				"voidVariable31"));

	DebugYourself::FundamentalVariableRegister<
		decltype(charVariable32),
		decltype(boolVariable32),
		decltype(voidVariable32)> FVR32(std::tuple(
			&charVariable32,
			&boolVariable32,
			&voidVariable32),
			std::tuple(
				"charVariable32",
				"boolVariable32",
				"voidVariable32"));

	DebugYourself::FundamentalVariableRegister<
		decltype(charVariable33),
		decltype(boolVariable33),
		decltype(voidVariable33)> FVR33(std::tuple(
			&charVariable33,
			&boolVariable33,
			&voidVariable33),
			std::tuple(
				"charVariable33",
				"boolVariable33",
				"voidVariable33"));


	DebugYourself::ObjectVariableRegisterBinder<
		decltype(FVR11),
		decltype(FVR21),
		decltype(FVR31)> FVRB__;

	DebugYourself::ObjectVariableRegisterBinder FVRB_Register_(
		FVR11,
		FVR21,
		FVR31);

}

TEST(FundamentalVariableBinder, __) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns__registers_::FVRB__.binder)>, 3);
}

TEST(FundamentalVariableBinder, _registers_) {
	EXPECT_EQ(std::tuple_size_v<decltype(ns__registers_::FVRB_Register_.binder)>, 3);
}

TEST(FundamentalVariableBinder, add) {
	ns__registers_::FVRB__.add(
		ns__registers_::FVR11,
		ns__registers_::FVR12,
		ns__registers_::FVR13,
	
		ns__registers_::FVR21,
		ns__registers_::FVR22,
		ns__registers_::FVR23,
	
		ns__registers_::FVR31,
		ns__registers_::FVR32,
		ns__registers_::FVR33);


	EXPECT_EQ(std::get<0>(ns__registers_::FVRB__.binder).at(0)->associatedVariables, ns__registers_::FVR11.associatedVariables);
	EXPECT_EQ(std::get<0>(ns__registers_::FVRB__.binder).at(1)->associatedVariables, ns__registers_::FVR12.associatedVariables);
	EXPECT_EQ(std::get<0>(ns__registers_::FVRB__.binder).at(2)->associatedVariables, ns__registers_::FVR13.associatedVariables);

	EXPECT_EQ(std::get<1>(ns__registers_::FVRB__.binder).at(0)->associatedVariables, ns__registers_::FVR21.associatedVariables);
	EXPECT_EQ(std::get<1>(ns__registers_::FVRB__.binder).at(1)->associatedVariables, ns__registers_::FVR22.associatedVariables);
	EXPECT_EQ(std::get<1>(ns__registers_::FVRB__.binder).at(2)->associatedVariables, ns__registers_::FVR23.associatedVariables);

	EXPECT_EQ(std::get<2>(ns__registers_::FVRB__.binder).at(0)->associatedVariables, ns__registers_::FVR31.associatedVariables);
	EXPECT_EQ(std::get<2>(ns__registers_::FVRB__.binder).at(1)->associatedVariables, ns__registers_::FVR32.associatedVariables);
	EXPECT_EQ(std::get<2>(ns__registers_::FVRB__.binder).at(2)->associatedVariables, ns__registers_::FVR33.associatedVariables);


	ns__registers_::FVRB_Register_.add(
		ns__registers_::FVR11,
		ns__registers_::FVR12,
		ns__registers_::FVR13,

		ns__registers_::FVR21,
		ns__registers_::FVR22,
		ns__registers_::FVR23,

		ns__registers_::FVR31,
		ns__registers_::FVR32,
		ns__registers_::FVR33);


	EXPECT_EQ(std::get<0>(ns__registers_::FVRB_Register_.binder).at(0)->associatedVariables, ns__registers_::FVR11.associatedVariables);
	EXPECT_EQ(std::get<0>(ns__registers_::FVRB_Register_.binder).at(1)->associatedVariables, ns__registers_::FVR12.associatedVariables);
	EXPECT_EQ(std::get<0>(ns__registers_::FVRB_Register_.binder).at(2)->associatedVariables, ns__registers_::FVR13.associatedVariables);

	EXPECT_EQ(std::get<1>(ns__registers_::FVRB_Register_.binder).at(0)->associatedVariables, ns__registers_::FVR21.associatedVariables);
	EXPECT_EQ(std::get<1>(ns__registers_::FVRB_Register_.binder).at(1)->associatedVariables, ns__registers_::FVR22.associatedVariables);
	EXPECT_EQ(std::get<1>(ns__registers_::FVRB_Register_.binder).at(2)->associatedVariables, ns__registers_::FVR23.associatedVariables);

	EXPECT_EQ(std::get<2>(ns__registers_::FVRB_Register_.binder).at(0)->associatedVariables, ns__registers_::FVR31.associatedVariables);
	EXPECT_EQ(std::get<2>(ns__registers_::FVRB_Register_.binder).at(1)->associatedVariables, ns__registers_::FVR32.associatedVariables);
	EXPECT_EQ(std::get<2>(ns__registers_::FVRB_Register_.binder).at(2)->associatedVariables, ns__registers_::FVR33.associatedVariables);

}

TEST(FundamentalVariableBinder, getVariableName) {

	ns__registers_::FVRB__.add(
		ns__registers_::FVR11,
		ns__registers_::FVR12,
		ns__registers_::FVR13,

		ns__registers_::FVR21,
		ns__registers_::FVR22,
		ns__registers_::FVR23,

		ns__registers_::FVR31,
		ns__registers_::FVR32,
		ns__registers_::FVR33);


	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable11), "voidVariable11");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable11), "boolVariable11");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable11), "charVariable11");

	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable12), "voidVariable12");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable12), "boolVariable12");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable12), "charVariable12");

	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable13), "voidVariable13");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable13), "boolVariable13");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable13), "charVariable13");


	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable21), "voidVariable21");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable21), "boolVariable21");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable21), "charVariable21");

	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable22), "voidVariable22");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable22), "boolVariable22");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable22), "charVariable22");

	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable23), "voidVariable23");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable23), "boolVariable23");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable23), "charVariable23");


	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable31), "voidVariable31");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable31), "boolVariable31");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable31), "charVariable31");

	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable32), "voidVariable32");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable32), "boolVariable32");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable32), "charVariable32");

	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::voidVariable33), "voidVariable33");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::boolVariable33), "boolVariable33");
	EXPECT_STREQ(ns__registers_::FVRB__.getVariableName(&ns__registers_::charVariable33), "charVariable33");


	ns__registers_::FVRB_Register_.add(
		ns__registers_::FVR11,
		ns__registers_::FVR12,
		ns__registers_::FVR13,

		ns__registers_::FVR21,
		ns__registers_::FVR22,
		ns__registers_::FVR23,

		ns__registers_::FVR31,
		ns__registers_::FVR32,
		ns__registers_::FVR33);


	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable11), "voidVariable11");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable11), "boolVariable11");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable11), "charVariable11");

	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable12), "voidVariable12");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable12), "boolVariable12");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable12), "charVariable12");

	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable13), "voidVariable13");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable13), "boolVariable13");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable13), "charVariable13");


	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable21), "voidVariable21");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable21), "boolVariable21");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable21), "charVariable21");

	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable22), "voidVariable22");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable22), "boolVariable22");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable22), "charVariable22");

	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable23), "voidVariable23");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable23), "boolVariable23");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable23), "charVariable23");


	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable31), "voidVariable31");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable31), "boolVariable31");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable31), "charVariable31");

	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable32), "voidVariable32");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable32), "boolVariable32");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable32), "charVariable32");

	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::voidVariable33), "voidVariable33");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::boolVariable33), "boolVariable33");
	EXPECT_STREQ(ns__registers_::FVRB_Register_.getVariableName(&ns__registers_::charVariable33), "charVariable33");

}