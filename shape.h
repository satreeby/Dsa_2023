#include <iostream>
#include <math.h>
#define PI 3.14159265358979
using namespace std;

void error(){
    cout << "error!" << endl;
    exit(1);
}

template<class T>
struct Point
{
    T x, y;
    Point(){};
    Point(T in_x, T in_y){
        x=in_x;
        y=in_y;
    }
    void operator=(const Point<T> p){
        x=p.x;
        y=p.y;
    }
};

template<class T>
class Shape
{
private:
    Point <T>* ps;
    int number;
public:
    Shape(){};
    Shape(int n){
        number=n;
        ps=new Point<T>[n];
    };
    virtual ~Shape(){
        delete [] ps;
        number=0;
    };
    void setpoint(Point<T> p, int n){
        if (n<number)
            ps[n]=p;
        else
            error();
    }
    Point<T> getpoint(int n){
        if (n<number)      
            return ps[n];
        else
            error(); 
    }
    int getnumber(){
        return number;
    }
    virtual T Calarea()=0;
    virtual T Calcircumference()=0;
    void printinfo(){
        cout << "the points consist of this shape are: ";
        for (int i = 0; i < getnumber(); i++)
            cout << '(' << getpoint(i).x << ',' << getpoint(i).y << ')' << ' ';
        cout << endl ;
        cout << "its area is: " << Calarea() << endl;
        cout << "its circumference is: " << Calcircumference() << endl;
    };
    void print_addr_ps(){
        cout << ps << endl;
    }
};

template<class T>
class Triangle: public Shape<T>
{
private:
    T a, b, c, p;
public:
    Triangle(Point<T> p1, Point<T> p2, Point<T> p3):Shape<T>(3){
        this->setpoint(p1,0);
        this->setpoint(p2,1);
        this->setpoint(p3,2);
        a=sqrt( pow( (this->getpoint(0).x-this->getpoint(1).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(1).y) , 2 ) );
        b=sqrt( pow( (this->getpoint(0).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(2).y) , 2 ) );
        c=sqrt( pow( (this->getpoint(1).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(1).y-this->getpoint(2).y) , 2 ) );
        p=(a+b+c)/2.0;
    };
    Triangle(const Triangle<T>& t):Shape<T>(3){
        this->setpoint((const_cast<Triangle<T>&>(t)).getpoint(0),0);
        this->setpoint((const_cast<Triangle<T>&>(t)).getpoint(1),1);
        this->setpoint((const_cast<Triangle<T>&>(t)).getpoint(2),2);
        a=sqrt( pow( (this->getpoint(0).x-this->getpoint(1).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(1).y) , 2 ) );
        b=sqrt( pow( (this->getpoint(0).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(2).y) , 2 ) );
        c=sqrt( pow( (this->getpoint(1).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(1).y-this->getpoint(2).y) , 2 ) );
        p=(a+b+c)/2.0;
    }
    ~Triangle(){};
    virtual T Calarea(){
        T S;
        S=sqrt(p*(p-a)*(p-b)*(p-c));
        return S;
    }
    virtual T Calcircumference(){
        T C;
        C=2*p;
        return C;
    }
};

template<class T>
class Rectangle: public Shape<T>
{
private:
    T a, b;
public:
    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4):Shape<T>(4){
        this->setpoint(p1,0);
        this->setpoint(p2,1);
        this->setpoint(p3,2);
        this->setpoint(p4,3);
        a=sqrt( pow( (this->getpoint(0).x-this->getpoint(1).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(1).y) , 2 ) );
        b=sqrt( pow( (this->getpoint(1).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(1).y-this->getpoint(2).y) , 2 ) );
    };
    Rectangle(const Rectangle<T>& r):Shape<T>(4){
        this->setpoint((const_cast<Triangle<T>&>(r)).getpoint(0),0);
        this->setpoint((const_cast<Triangle<T>&>(r)).getpoint(1),1);
        this->setpoint((const_cast<Triangle<T>&>(r)).getpoint(2),2);
        this->setpoint((const_cast<Triangle<T>&>(r)).getpoint(3),3);
        a=sqrt( pow( (this->getpoint(0).x-this->getpoint(1).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(1).y) , 2 ) );
        b=sqrt( pow( (this->getpoint(1).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(1).y-this->getpoint(2).y) , 2 ) );
    };
    ~Rectangle(){};
    virtual T Calarea(){
        T S;
        S=a*b;
        return S;
    }
    virtual T Calcircumference(){
        T C;
        C=2*(a+b);
        return C;
    }
};

template<class T>
class Square: public Shape<T>
{
private:
    Rectangle<T> r;
public:
    Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4):Shape<T>(4),r(p1,p2,p3,p4){
        this->setpoint(p1,0);
        this->setpoint(p2,1);
        this->setpoint(p3,2);
        this->setpoint(p4,3);
    };
    Square(const Square& a):Shape<T>(4),r((const_cast<Square &> (a)).getpoint(0),(const_cast<Square &> (a)).getpoint(1),(const_cast<Square &> (a)).getpoint(2),(const_cast<Square &> (a)).getpoint(4)){
        this->setpoint((const_cast<Triangle<T>&>(a)).getpoint(0),0);
        this->setpoint((const_cast<Triangle<T>&>(a)).getpoint(1),1);
        this->setpoint((const_cast<Triangle<T>&>(a)).getpoint(2),2);
        this->setpoint((const_cast<Triangle<T>&>(a)).getpoint(3),3);
    };
    virtual ~Square(){};
    virtual T Calarea(){
        return r.Calarea();
    }
    virtual T Calcircumference(){
        return r.Calcircumference();
    }
};

template<class T>
class Circle: public Shape<T>
{
private:
    T r;
public:
    Circle(Point<T> p1, T in_r):Shape<T>(1){
        this->setpoint(p1,0);
        r=in_r;
    };
    Circle(const Circle& c):Shape<T>(1){
        this->setpoint((const_cast<Triangle<T>&>(c)).getpoint(0),0);
        r=c.r;
    };
    virtual ~Circle(){};
    virtual T Calarea(){
        T S;
        S=PI*pow(r,2);
        return S;
    }
    virtual T Calcircumference(){
        T C;
        C=2*PI*r;
        return C;
    }
};

template<class T>
class Quadrangle: public Shape<T>
{
private:
    T a, b, c, d;
    T e;
    T l1, l2;
public:
    Quadrangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4):Shape<T>(4){
        this->setpoint(p1,0);
        this->setpoint(p2,1);
        this->setpoint(p3,2);
        this->setpoint(p4,3);
        a=sqrt( pow( (this->getpoint(0).x-this->getpoint(1).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(1).y) , 2 ) );
        b=sqrt( pow( (this->getpoint(1).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(1).y-this->getpoint(2).y) , 2 ) );
        c=sqrt( pow( (this->getpoint(2).x-this->getpoint(3).x) , 2 ) + pow( (this->getpoint(2).y-this->getpoint(3).y) , 2 ) );
        d=sqrt( pow( (this->getpoint(3).x-this->getpoint(0).x) , 2 ) + pow( (this->getpoint(3).y-this->getpoint(0).y) , 2 ) );
        e=sqrt( pow( (this->getpoint(0).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(2).y) , 2 ) );
        l1=(a+b+e)/2;
        l2=(c+d+e)/2;
    };
    Quadrangle(const Quadrangle<T>& q):Shape<T>(4){
        this->setpoint((const_cast<Triangle<T>&>(q)).getpoint(0),0);
        this->setpoint((const_cast<Triangle<T>&>(q)).getpoint(1),1);
        this->setpoint((const_cast<Triangle<T>&>(q)).getpoint(2),2);
        this->setpoint((const_cast<Triangle<T>&>(q)).getpoint(3),3);
        a=sqrt( pow( (this->getpoint(0).x-this->getpoint(1).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(1).y) , 2 ) );
        b=sqrt( pow( (this->getpoint(1).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(1).y-this->getpoint(2).y) , 2 ) );
        c=sqrt( pow( (this->getpoint(2).x-this->getpoint(3).x) , 2 ) + pow( (this->getpoint(2).y-this->getpoint(3).y) , 2 ) );
        d=sqrt( pow( (this->getpoint(3).x-this->getpoint(0).x) , 2 ) + pow( (this->getpoint(3).y-this->getpoint(0).y) , 2 ) );
        e=sqrt( pow( (this->getpoint(0).x-this->getpoint(2).x) , 2 ) + pow( (this->getpoint(0).y-this->getpoint(2).y) , 2 ) );
        l1=(a+b+e)/2;
        l2=(c+d+e)/2;
    };
    virtual ~Quadrangle(){
        a=b=c=d=e=l1=l2=0;
    };
    virtual T Calarea(){
        T S;
        S=sqrt(l1*(l1-a)*(l1-b)*(l1-e))+sqrt(l2*(l2-c)*(l2-d)*(l2-e));
        return S;
    }
    virtual T Calcircumference(){
        T C;
        C=a+b+c+d;
        return C;
    }
};

template<class T>
class Polygon: public Shape<T>
{
private:
    T* d;
    T* e;
    T *l;
public:
    Polygon(int n, Point<T>* P):Shape<T>(n){
        for (int i = 0; i < n; i++)
            this->setpoint(P[i], i);
        d=new double[n];
        e=new double[n-2];
        l=new double[n-2];
        for (int i = 0; i < n; i++)
        {
            d[i]=sqrt( pow( (this->getpoint(i).x-this->getpoint((i+1)%n).x) , 2 ) + pow( (this->getpoint(i).y-this->getpoint((i+1)%n).y) , 2 ) );
            if (i>0 && i<n-1)
            {               
                e[i-1]=sqrt( pow( (this->getpoint(i+1).x-this->getpoint(0).x) , 2 ) + pow( (this->getpoint(i+1).y-this->getpoint(0).y) , 2 ) );
                if (i==1)
                    l[i-1]=(d[i-1]+d[i]+e[i-1])/2;
                else
                    l[i-1]=(e[i-2]+d[i]+e[i-1])/2;
            }
        }
    };
    Polygon(const Polygon<T>& p):Shape<T>((const_cast <Polygon<T>&> (p)).getnumber()){
        int n=p.number;
        Point<T> P[n];
        for (int i = 0; i < n; i++)
            this->setpoint((const_cast <Polygon<T>&> (p)).getpoint(i), i);
        d=new double[n];
        e=new double[n-2];
        l=new double[n-2];
        for (int i = 0; i < n-1; i++)
        {
            d[i]=sqrt( pow( (this->getpoint(i).x-this->getpoint((i+1)%n).x) , 2 ) + pow( (this->getpoint(i).y-this->getpoint((i+1)%n).y) , 2 ) );
            if (i>0 && i<n-1)
            {               
                e[i-1]=sqrt( pow( (this->getpoint(i+1).x-this->getpoint(0).x) , 2 ) + pow( (this->getpoint(i+1).y-this->getpoint(0).y) , 2 ) );
                if (i==1)
                    l[i-1]=(d[i-1]+d[i]+e[i-1])/2;
                else
                    l[i-1]=(e[i-2]+d[i]+e[i-1])/2;
            }
        }
    };
    ~Polygon(){
        delete [] d;
        delete [] e;
        delete [] l;
    };
    virtual T Calarea(){
        T S=0;
        for (int i = 0; i < this->getnumber()-2; i++)
        {
            if (i==0)
                S+=sqrt(l[i]*(l[i]-d[i])*(l[i]-d[i+1])*(l[i]-e[i]));
            else
                S+=sqrt(l[i]*(l[i]-e[i-1])*(l[i]-d[i+1])*(l[i]-e[i]));
        }
        return S;
    }
    virtual T Calcircumference(){
        T C=0;
        for (int i = 0; i < this->getnumber(); i++)
            C+=d[i];
        return C;
    }
};

template<class T>
class ShapeVector
{
private:
    Shape<T> **v;
    int size;
    int top;
    T S;
    T C;
public:
    ShapeVector(int n){
        size=n;
        v=new Shape<T>*[size];
        top=-1;
        S=C=0;
    }
    ShapeVector(const ShapeVector<T>& v1){
        v=new Shape<T>*[size];
        size=const_cast<ShapeVector<T>&>(v1).getSize();
        top=const_cast<ShapeVector<T>&>(v1).gettop();
        for (int i = 0; i <= top; i++)
            v[i]=const_cast<ShapeVector<T>&>(v1).visit(i);
        S=const_cast<ShapeVector<T>&>(v1).getarea();
        C=const_cast<ShapeVector<T>&>(v1).getcircumference();
        return;
    }
    ~ShapeVector(){
        delete [] v;
        v=NULL;
    }
    int getSize(){
        return size;
    };
    int gettop(){
        return top;
    };
    T getarea(){
        return S;
    }
    T getcircumference(){
        return C;
    }
    Shape<T>* visit(){
        visit(top);
    };
    Shape<T>* visit(int n){
        if (n<0 || n>top)
            error();
        Shape<T>* s=v[n];
        return s;
    };
    void put(Shape<T>* s){
        if (top<size-1)
        {
            v[++top]=s;
            S= S + s->Calarea();
            C= C + s->Calcircumference();
            return;
        }
        error();
    }
    template <class S> void put(S* a){
        Shape<T>* s = dynamic_cast <Shape<T>*> (a);
        put(s);
    }
    Shape<T>* take(){
        if (top<0)
            error();
        S= S - v[top]->Calarea();
        C= C - v[top]->Calcircumference();
        return v[top--];
    }
    void printinfo(){
        cout << "the total area is: " << S << endl;
        cout << "the total circumference is: " << C << endl;
    }
    void print_addr_v(){
        cout << v << endl;
    }
};
