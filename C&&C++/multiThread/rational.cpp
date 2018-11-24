#include "multiThread/rational.h"

rational::rational(long Num, long Den)
{
    Numerator = Num;
    if (Den == 0)
    {
        Exception.message("Zero is not a valid Denominator!");
        throw Exception;
    }
    Denominator = Den;
}

rational::rational(const rational &X)
{
    Numerator = X.Numerator;
    Denominator = X.Denominator;
}

    virtual void assign(long X, long Y);
    rational operator*(const rational &X);
    rational operator+(const rational &X);
    rational operator/(const rational &X);
    rational operator-(const rational &X);
    rational &operator=(const rational &X);
    int operator==(const rational &X);
    long numerator(void) const;
    long denominator(void) const;
    friend ostream &operator<<(ostream &out, rational X);
    void reduce(void);
)




