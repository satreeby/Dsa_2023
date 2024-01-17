#include <iostream>
using namespace std;

class Complex
{
private:
    double re;
    double im;
public:
    Complex();
    Complex(double);
    Complex(double, double);
    Complex operator+(Complex &);
    Complex operator-(Complex &);
    Complex operator*(Complex &);
    Complex operator /(Complex &);
    friend ostream &operator<<( ostream &, const Complex &);
    friend double getre(const Complex &);
    friend double getim(const Complex &);
    void changere(double);
    void changeim(double);
};

Complex::Complex(){ re=0.0; im=0.0; }
Complex::Complex(double real){ re=real; im=0.0; }
Complex::Complex(double real, double imabinary){ re=real; im=imabinary; }
Complex Complex::operator+(Complex &c2){
    Complex c3(re+c2.re,im+c2.im);
    return c3;
}
Complex Complex::operator-(Complex &c2){
    Complex c3(re-c2.re,im-c2.im);
    return c3;
}
Complex Complex::operator*(Complex &c2){
    Complex c3(re*c2.re-im*c2.im,re*c2.im+im*c2.re);
    return c3;
}
Complex Complex::operator/(Complex &c2){
    Complex c3((re*c2.re+im*c2.im)/(c2.re*c2.re+c2.im*c2.im),(re*c2.im-im*c2.re)/(c2.re*c2.re+c2.im*c2.im));
    return c3;
}
ostream &operator<<( ostream &output, const Complex &C ){ 
    if (C.im<0)
        output << C.re << C.im << 'i' ;
    else
        output << C.re << '+' << C.im << 'i' ;
    return output;            
}
double getre(const Complex &C){
    return C.re;
}
double getim(const Complex &C){
    return C.im;
}
void Complex ::changere(double real){
    re=real;
}
void Complex ::changeim(double imaginary){
    im=imaginary;
}
int main(){
    Complex c1(3,4);
    Complex c2(5);
    Complex c3;
    cout << "The real part of c1 is: " << getre(c1) << endl;
    cout << "The imabinary part of c1 is: " << getim(c2) << endl;
    c3=c1+c2;
    cout << c3 << endl;
    c3=c1*c2;
    cout << c3 << endl;
    c3=c1-c2;
    cout << c3 << endl;
    c3=c1/c2;
    cout << c3 << endl;
    c3.changere(2);
    c3.changeim(-5.5);
    cout << c3 << endl;
}