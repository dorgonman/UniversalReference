#include <iostream>
class Resource{
public:
    std::string m_data;
};
class Widget{
public:
    Widget() 
        : m_pHeapStorageResource(nullptr){
    }
public:
    Resource* m_pHeapStorageResource;
    Resource m_stackStorageResource;
    int m_i;
};
static Widget g_myBackupWidget;
void myCopyFunc1(Widget param){
    g_myBackupWidget.m_pHeapStorageResource = param.m_pHeapStorageResource;
    g_myBackupWidget.m_stackStorageResource = param.m_stackStorageResource;
    g_myBackupWidget.m_i = param.m_i;

    if (param.m_pHeapStorageResource){
        param.m_pHeapStorageResource->m_data = "myCopyFunc1 param heap Storage: change data here will change origin widget";
    }
    param.m_stackStorageResource.m_data = "myCopyFunc1 param stack storage: change data here will not change origin widget";
}
void myCopyFunc2(Widget& param){
    g_myBackupWidget.m_pHeapStorageResource = param.m_pHeapStorageResource;
    g_myBackupWidget.m_stackStorageResource = param.m_stackStorageResource;
    g_myBackupWidget.m_i = param.m_i;
    if (param.m_pHeapStorageResource){
        param.m_pHeapStorageResource->m_data = "myCopyFunc2 param heap Storage: change data here will change origin widget";
    }
    param.m_stackStorageResource.m_data = "myCopyFunc2 param stack storage: change data here will change origin widget";
}
void myCopyFunc3(Widget* param){
    g_myBackupWidget.m_pHeapStorageResource = param->m_pHeapStorageResource;
    g_myBackupWidget.m_stackStorageResource = param->m_stackStorageResource;
    g_myBackupWidget.m_i = param->m_i;

    if (param->m_pHeapStorageResource){
        param->m_pHeapStorageResource->m_data = "myCopyFunc3 param heap Storage: change data here will change origin widget";
    }
    param->m_stackStorageResource.m_data = "myCopyFunc3 param stack storage: change data here will change origin widget";
}

int main(){
    using namespace std;
    Widget origin;
    origin.m_pHeapStorageResource = new Resource();
    origin.m_pHeapStorageResource->m_data = "data are allocated on heap Storage";
    origin.m_stackStorageResource.m_data = "data are allocated on stack storage";

    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    myCopyFunc1(origin); // call by value，會產生個新的param object，並使用member-wise copy將a的member copy給param
    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    myCopyFunc2(origin); // call by reference
    myCopyFunc2(Widget());// call by reference，產生一個臨時物件

    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    myCopyFunc3(&origin);// call by pointer

    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    delete origin.m_pHeapStorageResource;
    origin.m_pHeapStorageResource = nullptr;
    system("pause");
    return 0;
}