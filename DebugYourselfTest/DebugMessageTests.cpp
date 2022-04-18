#include "pch.h"

#include <DebugYourselfUtility.h>
#include <DebugYourself.h>

template<size_t n>
class TestClass {
private:
    void voidFunction() {}
public:
    bool boolFunction() { return true; }
    char charFunction() { return ' '; }

    inline static auto classRegister =
        DebugYourself::ClassFunctionRegister<
        &TestClass<n>::voidFunction,
        &TestClass<n>::boolFunction,
        &TestClass<n>::charFunction>(
            "voidFunction",
            "boolFunction",
            "charFunction");

private:
    void* voidVariable;
public:
    bool boolVariable;
    char charVariable;

    DebugYourself::ObjectVariableRegister<
        TestClass<n>,
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

TEST(DebugMessageTests, ClassMessaging) {

    

    DebugYourself::ClassFunctionRegisterBinder ClassBinder(
        TestClass<0>::classRegister,
        TestClass<1>::classRegister,
        TestClass<2>::classRegister
    );
    ClassBinder.use(ClassBinder);


    TestClass<1> testClass11;
    TestClass<1> testClass12;
    TestClass<1> testClass13;

    TestClass<2> testClass21;
    TestClass<2> testClass22;
    TestClass<2> testClass23;

    TestClass<3> testClass31;
    TestClass<3> testClass32;
    TestClass<3> testClass33;


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

    using DY = DebugYourself::Dependencies<decltype(ClassBinder), decltype(ObjectRegisterBinder), void, void>;

    DY::debug<&TestClass<2>::boolFunction>(&testClass22, &(testClass22.boolVariable), 50, "This is the message");
}