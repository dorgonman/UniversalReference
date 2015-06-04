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


//#include "vld.h"
#include <stdlib.h>
#include <iostream>
#include <memory>


#define SAFE_DELETE(a) do { delete (a); (a) = NULL; } while (0)
//http://stackoverflow.com/questions/3734247/what-are-all-the-member-functions-created-by-compiler-for-a-class-does-that-hap
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


class UnCopableResource : public Resource{
public:
    UnCopableResource(UnCopableResource const& kSource) = delete;
    UnCopableResource& operator=(UnCopableResource& rhs) = delete;
public:
    std::string m_dataUnCopable;
};


class UnMovableResource : public Resource{
public:
    UnMovableResource(Resource const&& kSource) = delete;
    UnMovableResource& operator=(Resource&& rhs) = delete;
public:
    std::string m_dataUnMovable;
};


class Widget{
public:
    /** Default constructor */
    Widget()
        : m_resourcePtr(new Resource())
        , m_i(0){

    }
 


public:
    std::shared_ptr<Resource> m_resourcePtr;
    Resource m_stackStorageResource;
    int m_i;
};



int main(){

    Widget obj1;
    obj1.m_resourcePtr.get()->m_data = "this is obj1";
    Widget obj2(obj1);// call Copy constructor
    obj2.m_resourcePtr.get()->m_data = "this is obj2";
    Widget obj3;
    obj3 = obj1; // call Copy assignment operator

    Widget obj4;
    obj4 = Widget(); //call Move assignment operator


    Widget obj5 = std::move(obj1);

    obj5 = std::move(obj2);


    return 0;
}