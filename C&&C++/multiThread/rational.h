#include <iostream>

class rational
{
protected:
    long Numerator;
    long Denominator;
    general_exception Exception;

public:
    rational(long Num = 0, long Den = 1);
    rational(const rational &X);
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
};





