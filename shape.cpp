#include <iostream>
#include "shape.h"
using namespace std;

int main(){
    ShapeVector<double> v(6);

    /*检测三角形*/
    cout << "检测三角形:" << endl;
    Point<double> p1(3.0, 0.0);
    Point<double> p2(3.0, 4.0);
    Point<double> p3(0.0, 0.0);
    Triangle<double> t(p1, p2, p3);

    cout << "hi";

    v.put((&t));
    v.printinfo();
    cout << endl;
    
    /*检测长方形*/
    cout << "检测三角形:" << endl;
    Point<double> p4(0.0, 4.0);
    Rectangle<double> r(p1, p2, p4, p3);
    v.put((&r));
    v.printinfo();
    cout << endl;
    
    /*检测正方形*/
    cout << "检测正方形:" << endl;
    Point<double> p5(3.0, 3.0);
    Point<double> p6(0.0, 3.0);
    Square<double> a(p1, p5, p6, p3);
    v.put((&a));
    v.printinfo();
    cout << endl;
    
    /*检测任意四边形*/
    cout << "检测任意四边形:" << endl;
    Point<double> p7(0.0, -4.0);
    Quadrangle<double> q(p1, p2, p3, p7);
    v.put((&q));
    v.printinfo();
    cout << endl;
    
    /*检测任意凸多边形*/
    cout << "检测任意凸多边形:" << endl;
    Point<double> p8(0.0, 4.0);
    Point<double> p9(-3.0, 0.0);
    Point<double> p10(-3.0, -4.0);
    Point<double> p11(3.0, -4.0);
    Point<double> P[5];
    P[0]=p1;
    P[1]=p8;
    P[2]=p9;
    P[3]=p10;
    P[4]=p11;
    Polygon<double> p(5, P);
    v.put((&p));
    v.printinfo();
    cout << endl;
    
    /*检测圆*/
    cout << "检测圆:" << endl;
    Circle<double> c(p3, 1.0);
    v.put((&c));
    v.printinfo();
    cout << endl;
    
    /*检测拿走*/
    cout << "检测拿走:" << endl;
    v.take();
    v.printinfo();
    cout << endl;
    
    /*检测访问*/
    cout << "检测访问:" << endl;
    cout << "the 4th shape's infomations are:" << endl;
    v.visit(3)->printinfo();
    cout << endl;
    
    /*检测容器大小与现有数量*/
    cout << "检测容器大小与现有数量:" << endl;
    cout << "the maxsize of this shapevector is " << v.getSize() << endl;
    cout << "the quantities of shapes in this shapevector is " << v.gettop()+1 << endl;
    
    /*检测深拷贝*/
    /*初始化深拷贝*/
    /*先检测单个形状的拷贝*/
    cout << "先检测单个形状的拷贝:" << endl;
    Triangle<double> t1=t;
    t1.printinfo();
    t1.print_addr_ps();
    t.print_addr_ps();
    cout << endl;
    /*检测容器的拷贝*/
    cout << "检测容器的拷贝:" << endl;
    ShapeVector<double> v1=v;
    v1.printinfo();
    v1.visit(0)->printinfo();
    v1.print_addr_v();
    v.print_addr_v();
    cout << endl;
    
    
    /*但是一级指针是相同的，肿么办呢？*/
}