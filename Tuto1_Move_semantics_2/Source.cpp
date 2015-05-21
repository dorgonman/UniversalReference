#include <iostream>
class Resource{

public:
    Resource* deepCopy(){
        Resource* pResource = new Resource();
        pResource->m_data = m_data;
        return pResource;
    }
public:
    std::string m_data;
};
class Widget{
public:
    /** Default constructor */
    Widget(){
        m_pHeapStorageResource = new Resource();
        m_pHeapStorageResource->m_data = "data are allocated on heap Storage";
    }
    /** Copy constructor */
    Widget(const Widget& other){
        memberwiseCopy(other);
        m_pHeapStorageResource->m_data = "data are allocated on heap Storage";
    }
    /** Destructor */
    ~Widget(){
        if (m_pHeapStorageResource){
            delete m_pHeapStorageResource;
            m_pHeapStorageResource = nullptr;
        }
    }
    /** Copy assignment operator */
    Widget& operator= (const Widget& other)
    {
        memberwiseCopy(other);
        return *this;
    }

    //simulate default compiler generated copy behavior
    void memberwiseCopy(const Widget& other){
        m_pHeapStorageResource = other.m_pHeapStorageResource;
        m_stackStorageResource = other.m_stackStorageResource;
        m_i = other.m_i;
    }
public:
    Resource* m_pHeapStorageResource;
    Resource m_stackStorageResource;
    int m_i;
};
static Widget g_myBackupWidget;
void myCopyFunc2(Widget& param){
    g_myBackupWidget.m_pHeapStorageResource = param.m_pHeapStorageResource->deepCopy();
    g_myBackupWidget.m_stackStorageResource = param.m_stackStorageResource;
    g_myBackupWidget.m_i = param.m_i;
    if (param.m_pHeapStorageResource){
        param.m_pHeapStorageResource->m_data = "myCopyFunc2 param heap Storage: change data here will change origin widget";
    }
    param.m_stackStorageResource.m_data = "myCopyFunc2 param stack storage: change data here will change origin widget";
}

void myCopyFunc2(Widget&& param){
    g_myBackupWidget.m_pHeapStorageResource = param.m_pHeapStorageResource; //move
    param.m_pHeapStorageResource = nullptr;
    g_myBackupWidget.m_stackStorageResource = param.m_stackStorageResource;//no move, will copy
    g_myBackupWidget.m_i = param.m_i; //copy
    g_myBackupWidget.m_pHeapStorageResource->m_data = "myCopyFunc2 rvalue param heap Storage: move param.m_pHeapStorageResource to g_myBackupWidget ";

}

int main(){
    using namespace std;
    Widget origin;

    myCopyFunc2(origin); // ©I¥svoid myCopyFunc2(Widget& param){
    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    myCopyFunc2(Widget());//©I¥svoid myCopyFunc2(Widget&& param){
    cout << g_myBackupWidget.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << g_myBackupWidget.m_stackStorageResource.m_data.c_str() << endl;

    system("pause");
    return 0;
}