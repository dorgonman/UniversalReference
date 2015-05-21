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
    myCopyFunc1(origin); // call by value
    cout << origin.m_pHeapStorageResource->m_data.c_str() << endl;
    cout << origin.m_stackStorageResource.m_data.c_str() << endl;
    myCopyFunc2(origin); // call by reference
    myCopyFunc2(Widget());// call by reference, generate a temp object

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