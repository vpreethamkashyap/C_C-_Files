#include <iostream>
#include <string>

namespace std{

namespace new_name{
    
    class A
    {
        public:
        A();
        ~A();
        void f();
    };
    
    A::A(){
        ::std::cout << "I am Inside" << ::std::endl;
    }
    A::~A(){
        ::std::cout << "I am outside !!!! " << ::std::endl;
    }
    void A::f(){
        ::std::cout << "I am walking out" << ::std::endl;
    }
 };

};

class B 
{
    public:
    B(int a): x(a)
    {};
    ~B();
    int const v = f();
    int g() const{
        return (99);
    }
    int h(int , int);
    
    private:
    int const x;
    int f() const{
        return 65;
        }
};

B::~B(){

};

int B::h(int a, int b)
{
    a = this->x;
    b = this->f();
    return a+b;
}

using namespace std;
        
int main (void){
    
    int w,e;
    ::new_name::A a;
    B b(3);
    std::cout<< "value =" << b.h(w, e) << std::endl;
    a.f();
    
    }