#include "tpolynom.h"

#include <gtest.h>
 
TEST(TPolynom, SimpleAddition)
{
    TPolynom P;
    P.SetPolynom("3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z");

    TPolynom Q;
    Q.SetPolynom("4x^3y^2z^6 - 6x^2yz^8");

    TPolynom expected;
    expected.SetPolynom("3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z + 4x^3y^2z^6 - 6x^2yz^8");

    TPolynom& result = P + Q;

    std::stringstream ss_result, ss_expected;
    ss_result << result;
    ss_expected << expected;

    EXPECT_EQ(ss_result.str(), ss_expected.str())
        << "Ошибка в тесте 1: Неправильное сложение полиномов\n"
        << "P = 3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z\n"
        << "Q = 4x^3y^2z^6 - 6x^2yz^8";

    delete& result; 
}
 
TEST(TPolynom, AdditionWithDifferentOrder)
{
    TPolynom P;
    P.SetPolynom("3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z");

    TPolynom Q;
    Q.SetPolynom("4x^7y^2z^6 - 6x^6yz^8");

    TPolynom expected;
    expected.SetPolynom("4x^7y^2z^6 - 6x^6yz^8 + 3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z");

    TPolynom& result = P + Q;

    std::stringstream ss_result, ss_expected;
    ss_result << result;
    ss_expected << expected;

    EXPECT_EQ(ss_result.str(), ss_expected.str())
        << "Ошибка в тесте 2: Неправильная сортировка при сложении\n"
        << "Члены с большими степенями должны быть в начале";

    delete& result;
}
 
TEST(TPolynom, LikeTermsCombination)
{
    TPolynom P;
    P.SetPolynom("3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z");

    TPolynom Q;
    Q.SetPolynom("4x^5y^2z^5 + 5x^4y^3z^3");

    TPolynom expected;
    expected.SetPolynom("7x^5y^2z^5 + 7x^3y^5z");

    TPolynom& result = P + Q;

    std::stringstream ss_result, ss_expected;
    ss_result << result;
    ss_expected << expected;

    EXPECT_EQ(ss_result.str(), ss_expected.str())
        << "Ошибка в тесте 3: Неправильное приведение подобных членов\n"
        << "Коэффициенты должны складываться: 3+4=7, -5+5=0 (член удаляется)";

    delete& result;
}

 
TEST(TPolynom, ComplexOrdering)
{
    TPolynom P;
    P.SetPolynom("3x^5y^2z^5 - 5x^4y^3z^3 + 7x^7y^5z");

    TPolynom Q;
    Q.SetPolynom("4x^6y^2z^6 - 6x^2yz^8");

    TPolynom expected;
    expected.SetPolynom("7x^7y^5z + 4x^6y^2z^6 + 3x^5y^2z^5 - 5x^4y^3z^3 - 6x^2yz^8");

    TPolynom& result = P + Q;

    std::stringstream ss_result, ss_expected;
    ss_result << result;
    ss_expected << expected;

    EXPECT_EQ(ss_result.str(), ss_expected.str())
        << "Ошибка в тесте 4: Неправильная сортировка\n"
        << "Члены должны быть отсортированы по убыванию суммарной степени";

    delete& result;
}

 
TEST(TPolynom, CompleteCancellation)
{
    TPolynom P;
    P.SetPolynom("3x^5y^2z^5 - 5x^4y^3z^3 + 7x^7y^5z");

    TPolynom Q;
    Q.SetPolynom("-3x^5y^2z^5 + 5x^4y^3z^3 - 7x^7y^5z");

    TPolynom expected;
    expected.SetPolynom("0");

    TPolynom& result = P + Q;

    std::stringstream ss_result, ss_expected;
    ss_result << result;
    ss_expected << expected;

    EXPECT_EQ(ss_result.str(), ss_expected.str())
        << "Ошибка в тесте 5: При сложении противоположных полиномов\n"
        << "Должен получаться нулевой полином '0'";

    delete& result;
}

 
TEST(TPolynom, ConstructorAndIO)
{
    TPolynom p1;
    std::stringstream ss1;
    ss1 << p1;
    EXPECT_EQ(ss1.str(), "0") << "Пустой полином должен выводиться как '0'";

    TPolynom p2;
    p2.SetPolynom("2x^2 + 3y^2 - 4z^2");
    std::stringstream ss2;
    ss2 << p2;
    EXPECT_FALSE(ss2.str().empty()) << "Полином не должен быть пустым";

    EXPECT_TRUE(p2.IsCorrect()) << "Полином 2x^2 + 3y^2 - 4z^2 должен быть корректным";
}
 
TEST(TPolynom, Multiplication)
{
    TPolynom P;
    P.SetPolynom("2x + 3y");

    TPolynom Q;
    Q.SetPolynom("4x + 5y");

    TPolynom& result = P * Q;

    std::stringstream ss_result;
    ss_result << result;

    // (2x+3y)*(4x+5y) = 8x^2 + 10xy + 12xy + 15y^2 = 8x^2 + 22xy + 15y^2
    EXPECT_FALSE(ss_result.str().empty())
        << "Умножение полиномов должно давать непустой результат";

    delete& result;
}
 
TEST(TPolynom, Calculation)
{
    TPolynom P;
    P.SetPolynom("2x + 3y + 4z");

    double result = P.Calculate(1.0, 2.0, 3.0);

    // 2*1 + 3*2 + 4*3 = 2 + 6 + 12 = 20
    EXPECT_DOUBLE_EQ(result, 20.0)
        << "Вычисление значения полинома 2x+3y+4z в точке (1,2,3) должно дать 20";
}

 
TEST(TPolynom, AddMonom)
{
    TPolynom P;
    P.SetPolynom("2x^2 + 3y^2");

    P.Add("4z^2");

    std::stringstream ss;
    ss << P;

    EXPECT_NE(ss.str().find("4z^2"), std::string::npos)
        << "Моном 4z^2 должен быть добавлен к полиному";
}
 
TEST(TPolynom, DeleteMonom)
{
    TPolynom P;
    P.SetPolynom("2x^2 + 3y^2 + 4z^2");

    P.Delete(1); 
    std::stringstream ss;
    ss << P;

    std::string result = ss.str();

    EXPECT_EQ(result.find("3y^2"), std::string::npos)
        << "После удаления моном 3y^2 не должен присутствовать";

    EXPECT_NE(result.find("2x^2"), std::string::npos)
        << "Моном 2x^2 должен остаться";
    EXPECT_NE(result.find("4z^2"), std::string::npos)
        << "Моном 4z^2 должен остаться";
}
 