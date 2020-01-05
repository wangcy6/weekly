// Effective C++ item 24: Declare Non-member Functions When Type Conversions Should Apply to All Parameters
//若所有参数皆需类型转换，请为此采用non-member函数
//https://harttle.land/2015/08/22/effective-cpp-24.html
#include <iostream>

using namespace std;

class Rational
{
public:
    Rational(int numerator = 0,
             int denominator = 1);
    int numerator() const;
    int denominator() const;
    // const Rational operator*(const Rational& rhs) const
    // {

    // }

    const Rational operator*(const Rational &lhs,
                             const Rational &rhs)
    {
        return Rational(lhs.numerator() * rhs.numerator(),
                        lhs.denominator() * rhs.denominator());
    }

private:
    int m_numerator;
    int m_denominator;
};


int main() 
{   
    Rational oneHalf(1, 2);

    Rational result = oneHalf * oneHalf;   // OK
    result = oneHalf * 2;                  // OK
    result = 2 * oneHalf;                  // Error
    return 0;
}