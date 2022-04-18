#include "pch.h"

#include <DebugYourselfUtility.h>
#include <DebugYourself.h>

template<size_t n>
class TestClassCFR {
private:
    void voidFunction() {}
public:
    bool boolFunction() { return true; }
    char charFunction() { return ' '; }

    inline static auto classRegister =
        DebugYourself::ClassFunctionRegister<
        &TestClassCFR<n>::voidFunction,
        &TestClassCFR<n>::boolFunction,
        &TestClassCFR<n>::charFunction>(
            "voidFunction",
            "boolFunction",
            "charFunction");
};

TEST(BinderTests, ClassBinder) {
    DebugYourself::ClassFunctionRegisterBinder ClassBinder(
        TestClassCFR<0>::classRegister,
        TestClassCFR<1>::classRegister,
        TestClassCFR<2>::classRegister
    );

    ClassBinder.use(ClassBinder);
    EXPECT_STREQ("boolFunction", ClassBinder.getFunctionName<&TestClassCFR<1>::boolFunction>());

}


template<size_t n>
class TestClassOVR {
private:
    void* voidVariable;
public:
    bool boolVariable;
    char charVariable;

    DebugYourself::ObjectVariableRegister<
        TestClassOVR<n>,
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> objectRegister =
        DebugYourself::ObjectVariableRegister(
            this, "TestClass", V(
                &voidVariable,
                &boolVariable,
                &charVariable), N(
                    "voidVariable",
                    "boolVariable",
                    "charVariable"));
};
TEST(BinderTests, ObjectBinder) {

    
    TestClassOVR<1> testClass11;
    TestClassOVR<1> testClass12;
    TestClassOVR<1> testClass13;

    TestClassOVR<2> testClass21;
    TestClassOVR<2> testClass22;
    TestClassOVR<2> testClass23;

    TestClassOVR<3> testClass31;
    TestClassOVR<3> testClass32;
    TestClassOVR<3> testClass33;

    DebugYourself::ObjectVariableRegisterBinder ObjectRegisterBinder(
        testClass11.objectRegister,
        testClass21.objectRegister,
        testClass31.objectRegister);

    ObjectRegisterBinder.add(
        testClass11.objectRegister,
        testClass12.objectRegister,
        testClass13.objectRegister,
        testClass21.objectRegister,
        testClass22.objectRegister,
        testClass23.objectRegister,
        testClass31.objectRegister,
        testClass32.objectRegister,
        testClass33.objectRegister);


    EXPECT_STREQ("charVariable", ObjectRegisterBinder.getVariableName(&testClass22.charVariable));
    EXPECT_STREQ("TestClass", ObjectRegisterBinder.getObjectName(&testClass22));
    
}

namespace fts {

    void voidFunction() {}
    bool boolFunction() { return true; }
    char charFunction() { return ' '; }

    using RegisterType1 = DebugYourself::GlobalFunctionRegister<
        &voidFunction,
        &boolFunction>;

    using RegisterType2 = DebugYourself::GlobalFunctionRegister<
        &charFunction>;

    auto reg1 =
        RegisterType1("voidFunction", "boolFunction");

    auto reg2 =
        RegisterType2("charFunction");
};
TEST(BinderTests, FunctionBinder) {

    DebugYourself::GlobalFunctionRegisterBinder binder(
        fts::reg1,
        fts::reg2
    );

    binder.use(binder);
    EXPECT_STREQ("boolFunction", binder.getFunctionName<&fts::boolFunction>());
}

namespace vts {
    void* voidVariable;
    bool boolVariable;
    char charVariable;
    
    auto reg1 = DebugYourself::FundamentalVariableRegister(V(
        &voidVariable,
        &boolVariable), N(
            "voidVariable",
            "boolVariable"));
    
    DebugYourself::FundamentalVariableRegister reg2(V(
        &charVariable), N(
            "charVariable"));
          

};

TEST(BinderTests, VariableBinder) {
    auto binder = DebugYourself::FundamentalVariableRegisterBinder(vts::reg1, vts::reg2);

    binder.add(vts::reg1, vts::reg2);
    EXPECT_STREQ("boolVariable", binder.getVariableName<decltype(vts::boolVariable)>(&vts::boolVariable));

}