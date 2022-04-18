
#include "pch.h"

#include <DebugYourselfUtility.h>
#include <DebugYourself.h>

template<const char*... names>
class TestClass {
private:
    void voidFunction() {}
public:
    bool boolFunction() { return true; }
    char charFunction() { return ' '; }

    inline static auto ClassRegister =
        DebugYourself::ClassFunctionRegister<
        &TestClass::voidFunction,
        &TestClass::boolFunction,
        &TestClass::charFunction>(names...);

    static bool test() {
        bool result;
        result |= (& TestClass::voidFunction == TestClass::ClassRegister.getFunctionPointer<0>());
        result |= (&TestClass::boolFunction == TestClass::ClassRegister.getFunctionPointer<1>());
        result |= (&TestClass::charFunction == TestClass::ClassRegister.getFunctionPointer<2>());

        return result;
    }
};

TEST(ClassRegisterTests, FunctionsPointers) {
    EXPECT_TRUE(TestClass<>::test());
}

TEST(ClassRegisterTests, ClassName) {
    EXPECT_STREQ("TestClass<>", TestClass<>::ClassRegister.getClassName());
}
TEST(ClassRegisterTests, NoNaming) {
    EXPECT_STREQ(nullptr, TestClass<>::ClassRegister.getFunctionName<0>());
    EXPECT_STREQ(nullptr, TestClass<>::ClassRegister.getFunctionName<1>());
    EXPECT_STREQ(nullptr, TestClass<>::ClassRegister.getFunctionName<2>());

}
TEST(ClassRegisterTests, PartialNaming) {
    static const char voidFunction[] = "voidFunction";
    EXPECT_STREQ("voidFunction", TestClass<voidFunction>::ClassRegister.getFunctionName<0>());
    EXPECT_STREQ(nullptr, TestClass<voidFunction>::ClassRegister.getFunctionName<1>());
    EXPECT_STREQ(nullptr, TestClass<voidFunction>::ClassRegister.getFunctionName<2>());
}
TEST(ClassRegisterTests, FullNaming) {
    static const char voidFunction[] = "voidFunction";
    static const char boolFunction[] = "boolFunction";
    static const char charFunction[] = "charFunction";
    
    const char* t1 = TestClass<voidFunction, boolFunction, charFunction>::ClassRegister.getFunctionName<0>();
    const char* t2 = TestClass<voidFunction, boolFunction, charFunction>::ClassRegister.getFunctionName<1>();
    const char* t3 = TestClass<voidFunction, boolFunction, charFunction>::ClassRegister.getFunctionName<2>();

    EXPECT_STREQ("voidFunction", t1);
    EXPECT_STREQ("boolFunction", t2);
    EXPECT_STREQ("charFunction", t3);
}