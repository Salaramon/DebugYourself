
#include "pch.h"

#include <DebugYourselfUtility.h>

#include "TestingVariables.h"

#include <DebugYourself.h>

TEST(FundamentalVariableRegisterTests, NoNaming) {
    DebugYourself::FundamentalVariableRegister variableRegister(V(
        &voidVariable, 
        &boolVariable, 
        &charVariable));

    EXPECT_EQ(&voidVariable, variableRegister.getVariablePointer<0>());
    EXPECT_EQ(&boolVariable, variableRegister.getVariablePointer<1>());
    EXPECT_EQ(&charVariable, variableRegister.getVariablePointer<2>());

    EXPECT_STREQ(nullptr, variableRegister.getVariableName<0>());
    EXPECT_STREQ(nullptr, variableRegister.getVariableName<1>());
    EXPECT_STREQ(nullptr, variableRegister.getVariableName<2>());
}

TEST(FundamentalVariableRegisterTests, PartialNaming) {
    DebugYourself::FundamentalVariableRegister variableRegister(V(
        &voidVariable,
        &boolVariable,
        &charVariable), N("voidVariable"));

    EXPECT_EQ(&voidVariable, variableRegister.getVariablePointer<0>());
    EXPECT_EQ(&boolVariable, variableRegister.getVariablePointer<1>());
    EXPECT_EQ(&charVariable, variableRegister.getVariablePointer<2>());

    EXPECT_STREQ("voidVariable", variableRegister.getVariableName<0>());
    EXPECT_STREQ(nullptr, variableRegister.getVariableName<1>());
    EXPECT_STREQ(nullptr, variableRegister.getVariableName<2>());
}

TEST(FundamentalVariableRegisterTests, FullNaming) {
    DebugYourself::FundamentalVariableRegister variableRegister(V(
        &voidVariable,
        &boolVariable,
        &charVariable), N(
            "voidVariable",
            "boolVariable",
            "charVariable"));

    EXPECT_EQ(&voidVariable, variableRegister.getVariablePointer<0>());
    EXPECT_EQ(&boolVariable, variableRegister.getVariablePointer<1>());
    EXPECT_EQ(&charVariable, variableRegister.getVariablePointer<2>());

    EXPECT_STREQ("voidVariable", variableRegister.getVariableName<0>());
    EXPECT_STREQ("boolVariable", variableRegister.getVariableName<1>());
    EXPECT_STREQ("charVariable", variableRegister.getVariableName<2>());
}