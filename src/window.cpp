
#include "wintypes.h"
#include "window.h"
#include<stdio.h>
using namespace WinWidgets;
#include <windows.h>
#include <vector>
#include "menu.h"
#include "trayicon.h"


class A{
public:
    virtual void call(int o) = 0;
    template<class T> void callfunc(void(*c)(T, int) ){ c(T(99), 0); }
};
template<class T> class B : public A{
    void (*e)(T,int);
    T data;
public:
    B(void (*ee)(T,int), T d):e(ee),data(d){
    }
    void call( int o ){
        e(data, o);
    }

};
template<class T> B<T>* create(void (*ee)(T,int), T d){
        return new B<T>(ee,d);
    }
template<class T> B<T&>* create(void (*ee)(T&,int), T& d){
        return new B<T&>(ee,d);
    }




std::vector<A*> as;

void func1(int a, int b){
    printf("%d\t%d\n", a, b);
}
void func2(double a, int b){
    printf("%f\t%d\n", a, b);
}
void func3(ClampValue<int, 0, 100> a, int b){
    printf("%d\t%d\n", a.Get(), b);
}
void func4(int &a, int b){
    a += 10;
    printf("%d\t%d\n", a, b);
}


int main(){
    int t = 10;
    as.push_back( new B<int>(func1, 10) );
    as.push_back( new B<double>(func2, 50) );
    as.push_back( new B<ClampValue<int, 0, 100> >(func3, ClampValue<int, 0, 100>(888)) );
    as.push_back( new B<double>(func2, 50) );
    as.push_back( new B<int&>(func4, t) );
    as.push_back( new B<int&>(func4, t) );
    as.push_back( new B<int&>(func4, t) );
    as.push_back( create(func4, t) );
    as.push_back( create(func4, t) );
    as.push_back( create(func4, t) );
    as.push_back( create(func4, t) );
    as.push_back( create(func4, t) );




    for( int i = 0; i < as.size(); ++i ){
        as[i]->call(i);
    }
    as[0]->callfunc(func2);
    printf("t=%d\n", t);
}
