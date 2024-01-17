#include <iostream>
#include <math.h>
using namespace std;

/*建立抽象函数系统*/
class Func
{
public:
    Func(){};
    ~Func(){};
    virtual double f(double)=0;
};
class P2x: public Func
{
private:
    double a, b, c;
public:
    P2x(double a, double b, double c): a(a), b(b), c(c){};
    ~P2x(){};
    virtual double f(double x){
        return a*x*x+b*x+c;
    }
};

/*建立高斯表*/
struct Gauss
{
    double x;
    double w;
};
Gauss* getgauss(int n){
    Gauss* g=new Gauss[n+1];
    switch (n)
    {
    case 0:
        g[0].x=0;
        g[0].w=2;
        break;
    case 1:
        g[0].x=1.0/sqrt(3);
        g[1].x=-g[0].x;
        g[0].w=g[1].w=1;
        break;
    case 2:
        g[0].x=0;
        g[1].x=sqrt(3.0/5.0);
        g[2].x=-g[1].x;
        g[0].w=8.0/9.0;
        g[1].w=g[2].w=5.0/9.0;
        break;
    case 3:
        g[0].x=sqrt(3.0/7.0-2.0/7.0*sqrt(6.0/5.0));
        g[1].x=-g[0].x;
        g[2].x=sqrt(3.0/7.0+2.0/7.0*sqrt(6.0/5.0));
        g[3].x=-g[2].x;
        g[0].w=g[1].w=(18+sqrt(30)/36);
        g[2].w=g[3].w=(18-sqrt(30)/36);
        break;
    case 4:
        g[0].x=0;
        g[1].x=1/3.0*sqrt(5-2*sqrt(10.0/7.0));
        g[2].x=-g[1].x;
        g[3].x=1/3.0*sqrt(5+2*sqrt(10.0/7.0));
        g[4].x=-g[3].x;
        g[0].w=128.0/225.0;
        g[1].w=g[2].w=(322+13*sqrt(70))/900;
        g[3].w=g[4].w=(322-13*sqrt(70))/900;
        break;
    default:
        cout << "sorry! I can't handle it!" << endl;
        break;
    }
    return g;
}

/*高斯积分*/
double GaussIntegral(double low, double up, Func* f, int n){
    Gauss* g=getgauss(n);
    double sum=0.0;
    for (int i = 0; i < n+1; i++)
        sum += g[i].w * f->f(((up-low)/2*g[i].x+(up+low)/2));
    return sum;
}

class GaussIntegral
{
private:
    /* data */
public:
    GaussIntegral(/* args */);
    ~GaussIntegral();
};

GaussIntegral::GaussIntegral(/* args */)
{
}

GaussIntegral::~GaussIntegral()
{
}

/*测试*/
int main(){
    P2x f(1, 2, 1);
    cout << GaussIntegral(0, 2, dynamic_cast<Func *>(&f), 1) << endl;
}