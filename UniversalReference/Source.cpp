
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
    myCopyFunc1(a);  // call by value�A�|���ͭӷs��param object�A�èϥ�member-wise copy�Na��member copy��param
    myCopyFunc2(a);  // call by reference
    myCopyFunc2(Widget());// call by reference�A���ͤ@���{�ɪ���
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
//    myCopyFunc1(a);  // call by value�A�|���ͭӷs��param object�A�èϥ�member-wise copy�Na��member copy��param
//    myCopyFunc2(a);  // call by reference
//    myCopyFunc2(Widget());// call by reference�A���ͤ@���{�ɪ���
//    myCopyFunc3(&a);// call by pointer
//    system("pause");
//    return 0;
//}

