/****************************************************************************
MIT License
Copyright (c) 2015 horizon-studio

http://horizon-studio.net/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/



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

    myCopyFunc2(origin); // call void myCopyFunc2(Widget& param)
    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    myCopyFunc2(Widget());// call void myCopyFunc2(Widget&& param)
    cout << g_myBackupWidget.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << g_myBackupWidget.m_stackStorageResource.m_data.c_str() << endl;

    system("pause");
    return 0;
}