#include "pch.h"

#include <DebugYourself.h>

using DebugYourself = dy::DebugYourself<true>;

namespace ns__ {
    void* voidVariable;
    bool boolVariable;
    char charVariable;

    DebugYourself::FundamentalVariableRegister<
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> FVR;
};

namespace ns_variables_ {
    void* voidVariable;
    bool boolVariable;
    char charVariable;

    DebugYourself::FundamentalVariableRegister<
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> FVR(std::tuple(
            &voidVariable,
            &boolVariable,
            &charVariable));
};

namespace ns_variables_names_{
    void* voidVariable;
    bool boolVariable;
    char charVariable;

    DebugYourself::FundamentalVariableRegister<
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> FVR_No_Naming(std::tuple(
            &voidVariable,
            &boolVariable,
            &charVariable),
            std::tuple());

    DebugYourself::FundamentalVariableRegister<
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> FVR_Partial_Naming(std::tuple(
            &voidVariable,
            &boolVariable,
            &charVariable),
            std::tuple("voidVariable"));

    DebugYourself::FundamentalVariableRegister<
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> FVR_Full_Naming(std::tuple(
            &voidVariable,
            &boolVariable,
            &charVariable),
            std::tuple(
                "voidVariable",
                "boolVariable",
                "charVariable"));
};


TEST(FundamentalVariableRegister, __) {
    EXPECT_EQ(std::get<0>(ns__::FVR.associatedVariables), nullptr);
    EXPECT_EQ(std::get<1>(ns__::FVR.associatedVariables), nullptr);
    EXPECT_EQ(std::get<2>(ns__::FVR.associatedVariables), nullptr);

    EXPECT_STREQ(std::get<0>(ns__::FVR.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<1>(ns__::FVR.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<2>(ns__::FVR.associatedVariableNames), nullptr);

    EXPECT_GT(ns__::FVR.timeStamp + std::numeric_limits<long double>::min(), 0);
    EXPECT_EQ(ns__::FVR.instanceID, 1);
};

TEST(FundamentalVariableRegister, _variables_) {
    EXPECT_EQ(std::get<0>(ns_variables_::FVR.associatedVariables), &ns_variables_::voidVariable);
    EXPECT_EQ(std::get<1>(ns_variables_::FVR.associatedVariables), &ns_variables_::boolVariable);
    EXPECT_EQ(std::get<2>(ns_variables_::FVR.associatedVariables), &ns_variables_::charVariable);

    EXPECT_STREQ(std::get<0>(ns_variables_::FVR.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<1>(ns_variables_::FVR.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<2>(ns_variables_::FVR.associatedVariableNames), nullptr);

    EXPECT_GT(ns__::FVR.timeStamp + std::numeric_limits<long double>::min(), 0);
    EXPECT_EQ(ns__::FVR.instanceID, 1);
};

TEST(FundamentalVariableRegister, _variables_names_) {
    EXPECT_EQ(std::get<0>(ns_variables_names_::FVR_No_Naming.associatedVariables), &ns_variables_names_::voidVariable);
    EXPECT_EQ(std::get<1>(ns_variables_names_::FVR_No_Naming.associatedVariables), &ns_variables_names_::boolVariable);
    EXPECT_EQ(std::get<2>(ns_variables_names_::FVR_No_Naming.associatedVariables), &ns_variables_names_::charVariable);

    EXPECT_STREQ(std::get<0>(ns_variables_names_::FVR_No_Naming.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<1>(ns_variables_names_::FVR_No_Naming.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<2>(ns_variables_names_::FVR_No_Naming.associatedVariableNames), nullptr);

    EXPECT_GT(ns_variables_names_::FVR_No_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
    EXPECT_EQ(ns_variables_names_::FVR_No_Naming.instanceID, 1);


    EXPECT_EQ(std::get<0>(ns_variables_names_::FVR_Partial_Naming.associatedVariables), &ns_variables_names_::voidVariable);
    EXPECT_EQ(std::get<1>(ns_variables_names_::FVR_Partial_Naming.associatedVariables), &ns_variables_names_::boolVariable);
    EXPECT_EQ(std::get<2>(ns_variables_names_::FVR_Partial_Naming.associatedVariables), &ns_variables_names_::charVariable);

    EXPECT_STREQ(std::get<0>(ns_variables_names_::FVR_Partial_Naming.associatedVariableNames), "voidVariable");
    EXPECT_STREQ(std::get<1>(ns_variables_names_::FVR_Partial_Naming.associatedVariableNames), nullptr);
    EXPECT_STREQ(std::get<2>(ns_variables_names_::FVR_Partial_Naming.associatedVariableNames), nullptr);

    EXPECT_GT(ns_variables_names_::FVR_Partial_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
    EXPECT_EQ(ns_variables_names_::FVR_Partial_Naming.instanceID, 1);


    EXPECT_EQ(std::get<0>(ns_variables_names_::FVR_Full_Naming.associatedVariables), &ns_variables_names_::voidVariable);
    EXPECT_EQ(std::get<1>(ns_variables_names_::FVR_Full_Naming.associatedVariables), &ns_variables_names_::boolVariable);
    EXPECT_EQ(std::get<2>(ns_variables_names_::FVR_Full_Naming.associatedVariables), &ns_variables_names_::charVariable);

    EXPECT_STREQ(std::get<0>(ns_variables_names_::FVR_Full_Naming.associatedVariableNames), "voidVariable");
    EXPECT_STREQ(std::get<1>(ns_variables_names_::FVR_Full_Naming.associatedVariableNames), "boolVariable");
    EXPECT_STREQ(std::get<2>(ns_variables_names_::FVR_Full_Naming.associatedVariableNames), "charVariable");

    EXPECT_GT(ns_variables_names_::FVR_Full_Naming.timeStamp + std::numeric_limits<long double>::min(), 0);
    EXPECT_EQ(ns_variables_names_::FVR_Full_Naming.instanceID, 1);
};


namespace ns_function1_3 {
    void* voidVariable;
    bool boolVariable;
    char charVariable;

    DebugYourself::FundamentalVariableRegister<
        decltype(voidVariable),
        decltype(boolVariable),
        decltype(charVariable)> FVR(std::tuple(
            &voidVariable,
            &boolVariable,
            &charVariable),
            std::tuple(
                "voidVariable",
                "boolVariable",
                "charVariable"));
}


TEST(FundamentalVariableRegister, getVariablePointer) {
    EXPECT_EQ(ns_function1_3::FVR.getVariablePointer<0>(), &ns_function1_3::voidVariable);
    EXPECT_EQ(ns_function1_3::FVR.getVariablePointer<1>(), &ns_function1_3::boolVariable);
    EXPECT_EQ(ns_function1_3::FVR.getVariablePointer<2>(), &ns_function1_3::charVariable);
}

TEST(FundamentalVariableRegister, getVariableName) {
    EXPECT_STREQ(ns_function1_3::FVR.getVariableName<0>(), "voidVariable");
    EXPECT_STREQ(ns_function1_3::FVR.getVariableName<1>(), "boolVariable");
    EXPECT_STREQ(ns_function1_3::FVR.getVariableName<2>(), "charVariable");
}

TEST(FundamentalVariableRegister, getNumberOfVariables) {
    EXPECT_EQ(ns_function1_3::FVR.getNumberOfVariables(), 3);
}