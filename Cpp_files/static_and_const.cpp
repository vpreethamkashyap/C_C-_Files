#include <iostream>

using namespace std;

class TestAll{
    
    private:
    
    static const char a;
    static int c;
    const int b;
    const char* objname;
    
    // Non static memeber variable can not be initalized before C++11 compilers.
    int* ptr;
    
    public:
    
    // 'b' being a const value it should only be initialized during construtor creation. 
    TestAll(int value, const char* obj, int C):b(value), objname(obj){
        
        // So the variable ptr is initialized inside constructor
        ptr = new int();
        c = C;
    }
    
    void modifystatic(const int &val){
        
        c = val;
    }
    
    void print(void){
        
        cout << "value of a in obj " << objname <<" is " << a << endl;
        cout << "value of b in obj " << objname <<" is " << b << endl;
        cout << "value of b in obj " << objname <<" is " << c << endl;
        cout << "address ptr holds " << ptr << endl;
    }
    
    ~TestAll(){
        
        delete(ptr);
    }
};

// Being a static variable it should be assigned a value only at definition. 
const char TestAll::a = 'T';
int TestAll::c = 100;

int main()
{
    TestAll test(25, "test", 100);
    test.print();
    
    TestAll test_1(45, "test_1", 200);
    //test_1.b = 55; error because the const is already initialized with value 45 for this obj and can not be cahnged. 
    
    test_1.modifystatic(300);
    test_1.print();
}

