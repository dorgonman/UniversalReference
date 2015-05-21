
#include <iostream>
using namespace std;
class Widget{

public:
    /** Default constructor */
    Widget(){
        m_pMyResource = new std::string("HelloWorld");
        cout << "Widget ctor" << endl;
     };


    /** Copy constructor */
    Widget(Widget& other) :
        m_pMyResource(other.m_pMyResource){
        cout << "Widget copy ctor" << endl;
    };
    /** Destructor */
    ~Widget(){
        delete m_pMyResource;
        m_pMyResource = nullptr;
        cout << "Widget dtor" << endl;
    };
    /** Copy assignment operator */
    Widget& operator= (Widget& other)
    {
        Widget tmp(other); // re-use copy-constructor
        return *this;
    }
public:
    std::string* m_pMyResource;
};
static Widget g_myBackupWidget;
void myCopyFunc1(Widget param){
    *(param.m_pMyResource) = "HelloWorld1";
    g_myBackupWidget.m_pMyResource = param.m_pMyResource;
}
void myCopyFunc2(Widget& param){
    g_myBackupWidget.m_pMyResource = param.m_pMyResource;
}
void myCopyFunc3(Widget* param){
    g_myBackupWidget.m_pMyResource = param->m_pMyResource;
}


int main(){
    Widget a;
    myCopyFunc1(a);  // call by value，會產生個新的param object，並使用member-wise copy將a的member copy給param
    myCopyFunc2(a);  // call by reference
    myCopyFunc2(Widget());// call by reference，產生一個臨時物件
    myCopyFunc3(&a);// call by pointer
    system("pause");
    return 0;
}



//#include <iostream>
//using namespace std;
//class Widget{
//
//public:
///** Default constructor */
//Widget(){
//    data = "HelloWorld";
//    cout << "Widget ctor" << endl;
//};
//
//
///** Copy constructor */
//Widget(Widget& other) :
//data(other.data){
//    cout << "Widget copy ctor" << endl;
//};
///** Destructor */
//~Widget(){
//    delete data;
//    data = nullptr;
//    cout << "Widget dtor" << endl;
//};
///** Copy assignment operator */
//Widget& operator= (Widget& other)
//{
//    Widget tmp(other); // re-use copy-constructor
//    return *this;
//}
//char* data;
//};
//static Widget g_myBackupWidget;
//void myCopyFunc1(Widget param){
//    param.data = "HelloWorld1";
//    size_t size = strlen(param.data) + 1;
//    g_myBackupWidget.data = new char[size];
//    memcpy(g_myBackupWidget.data, param.data, size);
//}
//void myCopyFunc2(Widget& param){
//    size_t size = strlen(param.data) + 1;
//    g_myBackupWidget.data = new char[size];
//    memcpy(g_myBackupWidget.data, param.data, size);
//}
//void myCopyFunc3(Widget* param){
//    size_t size = strlen(param->data) + 1;
//    g_myBackupWidget.data = new char[size];
//    memcpy(g_myBackupWidget.data, param->data, size);
//}
//
//
//int main(){
//    Widget a;
//    myCopyFunc1(a);  // call by value，會產生個新的param object，並使用member-wise copy將a的member copy給param
//    myCopyFunc2(a);  // call by reference
//    myCopyFunc2(Widget());// call by reference，產生一個臨時物件
//    myCopyFunc3(&a);// call by pointer
//    system("pause");
//    return 0;
//}

