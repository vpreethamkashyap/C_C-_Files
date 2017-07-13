// Example program
#include <iostream>
#include <string>

using namespace std;

float processTempData();

template <typename T1, typename T2>
class BMS{
    
    private:
    
    T1 cellcurrent;
    T1 cellvoltage;
    
    T2 ADCValue;
    T2 RSOC;
    T2 NoOfCells;
    
    public:
    
    T1 Temparature;
    virtual T1 GetTemparature() = 0;
    virtual T1 Getcellcurrent() = 0;
    virtual T1 Getcellvoltage() = 0;   
};

template <typename T1, typename T2>
class classic:public BMS<T1, T2>
{
    
    public:
    
    virtual T1 GetTemparature();
    virtual T1 Getcellcurrent();
    virtual T1 Getcellvoltage();
    
    T1 Temparature = GetTemparature();
        
};

template <typename T1, typename T2>
T1 classic<T1,T2>::GetTemparature(){

T1 TemparatureDate = processTempData();
return TemparatureDate;

}

template <typename T1, typename T2>
T1 classic<T1,T2>::Getcellcurrent(){

T1 currentDate = -17.34;
return currentDate;

}

template <typename T1, typename T2>
T1 classic<T1,T2>::Getcellvoltage(){

T1  voltageData = 52.65;
return voltageData;

}

float processTempData()
{
    float TemparatureData = 40.32;
 
    return TemparatureData;    
}


int main()
{
    BMS<float,int> *bms;
    classic<float,int> bms_1;
    
    bms = &bms_1;
    
    //float value = bms->GetTemparature();
    
    cout << bms->GetTemparature() << endl;
    cout << bms->Getcellcurrent() << endl;
    cout << bms->Getcellvoltage() << endl;
    cout << bms_1.Temparature << endl;

}
