
#include "pch.h"

#include "TestingFunctions.h"

#include <DebugYourself.h>

TEST(GlobalFunctionRegisterTests, NoNaming) {
    DebugYourself::GlobalFunctionRegister<
        &voidFunction, 
        &boolFunction, 
        &charFunction> functionRegister;

    EXPECT_EQ(&voidFunction, functionRegister.getFunctionPointer<0>());
    EXPECT_EQ(&boolFunction, functionRegister.getFunctionPointer<1>());
    EXPECT_EQ(&charFunction, functionRegister.getFunctionPointer<2>());

    EXPECT_STREQ(nullptr, functionRegister.getFunctionName<0>());
    EXPECT_STREQ(nullptr, functionRegister.getFunctionName<1>());
    EXPECT_STREQ(nullptr, functionRegister.getFunctionName<2>());
}

TEST(GlobalFunctionRegisterTests, PartialNaming) {
    DebugYourself::GlobalFunctionRegister<
        &voidFunction, 
        &boolFunction, 
        &charFunction> functionRegister("voidFunction");

    EXPECT_EQ(&voidFunction, functionRegister.getFunctionPointer<0>());
    EXPECT_EQ(&boolFunction, functionRegister.getFunctionPointer<1>());
    EXPECT_EQ(&charFunction, functionRegister.getFunctionPointer<2>());

    EXPECT_STREQ("voidFunction", functionRegister.getFunctionName<0>());
    EXPECT_STREQ(nullptr, functionRegister.getFunctionName<1>());
    EXPECT_STREQ(nullptr, functionRegister.getFunctionName<2>());
}

TEST(GlobalFunctionRegisterTests, FullNaming) {
    DebugYourself::GlobalFunctionRegister<
        &voidFunction, 
        &boolFunction, 
        &charFunction> functionRegister(
            "voidFunction", 
            "boolFunction", 
            "charFunction");

    EXPECT_EQ(&voidFunction, functionRegister.getFunctionPointer<0>());
    EXPECT_EQ(&boolFunction, functionRegister.getFunctionPointer<1>());
    EXPECT_EQ(&charFunction, functionRegister.getFunctionPointer<2>());

    EXPECT_STREQ("voidFunction", functionRegister.getFunctionName<0>());
    EXPECT_STREQ("boolFunction", functionRegister.getFunctionName<1>());
    EXPECT_STREQ("charFunction", functionRegister.getFunctionName<2>());
}