
#include "pch.h"

#include <DebugYourselfUtility.h>
#include <DebugYourself.h>

template<const char*... names>
class TestClass {
private:
    void* voidVariable;
public:
    bool boolVariable;
    char charVariable;

    DebugYourself::ObjectVariableRegister<
        TestClass,
        decltype(voidVariable), 
        decltype(boolVariable), 
        decltype(charVariable)> objectRegister =
            DebugYourself::ObjectVariableRegister(
                this, "TestClass", V(
                &voidVariable, 
                &boolVariable,
                &charVariable), 
                N(names...));

    bool test() {
        bool result;
        result |= (&voidVariable == objectRegister.getVariablePointer<0>());
        result |= (&boolVariable == objectRegister.getVariablePointer<1>());
        result |= (&charVariable == objectRegister.getVariablePointer<2>());

        return result;
    }
};

TEST(ObjectRegisterTests, FunctionsPointers) {
    TestClass<> testClass;
    EXPECT_TRUE(testClass.test());
}

TEST(ObjectRegisterTests, ClassName) {
    TestClass<> testClass;
    EXPECT_STREQ("TestClass", testClass.objectRegister.getObjectName());
}
TEST(ObjectRegisterTests, NoNaming) {
    TestClass<> testClass;

    EXPECT_STREQ(nullptr, testClass.objectRegister.getVariableName<0>());
    EXPECT_STREQ(nullptr, testClass.objectRegister.getVariableName<1>());
    EXPECT_STREQ(nullptr, testClass.objectRegister.getVariableName<2>());
}

TEST(ObjectRegisterTests, PartialNaming) {
    static const char voidVariable[] = "voidVariable";

    TestClass<voidVariable> testClass;

    EXPECT_STREQ("voidVariable", testClass.objectRegister.getVariableName<0>());
    EXPECT_STREQ(nullptr, testClass.objectRegister.getVariableName<1>());
    EXPECT_STREQ(nullptr, testClass.objectRegister.getVariableName<2>());
}
TEST(ObjectRegisterTests, FullNaming) {
    static const char voidVariable[] = "voidVariable";
    static const char boolVariable[] = "boolVariable";
    static const char charVariable[] = "charVariable";

    TestClass<voidVariable, boolVariable, charVariable> testClass;

    EXPECT_STREQ("voidVariable", testClass.objectRegister.getVariableName<0>());
    EXPECT_STREQ("boolVariable", testClass.objectRegister.getVariableName<1>());
    EXPECT_STREQ("charVariable", testClass.objectRegister.getVariableName<2>());
}

//Testing for each constructor should be done.