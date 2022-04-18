#pragma once

#include <DebugYourselfUtility.h>
#include <DebugYourself.h>

class TestClass1
{
public:

    void voidFunction() {

    }

    bool boolFunction() {
        return true;
    }
    
private:

    char charFunction() {
        return ' ';
    }

    int intVariable = 1;
    bool boolVariable = true;
    char charVariable = 'a';

public:
    inline static auto TestClass1_ClassRegister = DebugYourself::ClassFunctionRegister<
        &TestClass1::voidFunction,
        &TestClass1::boolFunction,
        &TestClass1::charFunction>();
};

class TestClass2
{
public:
    void voidFunction() {

    }

    bool boolFunction() {
        return true;
    }

    char charFunction() {
        return ' ';
    }

    int intVariable = 1;
    bool boolVariable = true;
    char charVariable = 'a';
};

class TestClass3
{
public:
    void voidFunction() {

    }

    bool boolFunction() {
        return true;
    }

    char charFunction() {
        return ' ';
    }

    int intVariable = 1;
    bool boolVariable = true;
    char charVariable = 'a';
};

