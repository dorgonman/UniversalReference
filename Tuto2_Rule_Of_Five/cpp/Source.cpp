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
        //Always use member list initialization, because it always faster than initiallize in the function body
        //ref:
        //http://advanced-c-plus.blogspot.tw/2010/02/advantage-of-constructor-initialization.html
        //http://sevensavants.blogspot.tw/2010/02/c_06.html
       /* There are two steps that takes place when Member Objects of a class are initialized inside the body of a constructor.
        1. Member Objects are allocated a memry / constructed and are given default values by the time when the control enters body of the constructor.
        2. Later on the actual initialization happens inside the body of the constructor i.e.user written initilization code that gets called.*/
        : m_pHeapStorageResource(new Resource())
        , m_i(0){
    }

    /** Copy constructor */
    Widget(const Widget& other){
        memberwiseDeepCopy(other);

    }

    /** Destructor */
    ~Widget(){
        SAFE_DELETE(m_pHeapStorageResource);//safe release resource
    }
    /** Copy assignment operator */
    Widget& operator= (const Widget& other)
    {
        memberwiseDeepCopy(other);
        return *this;
    }






    /** Move constructor */
    Widget(Widget&& other){
        //memberwiseMove(other);//oops! will call memberwiseMove(Widget& other), not our intent here
        //member list initialization
        memberwiseMove(std::forward<Widget>(other));
    }

    /** Move assignment operator */
    Widget& operator= (Widget&& other)
    {
        Widget* test = &other;
        //memberwiseMove(other);//oops! will call memberwiseMove(Widget& other), other is lvalue because it has a name
        memberwiseMove(std::forward<Widget>(other));//forward rvalue to memberwiseMove
        return *this;
    }

private:
    void memberwiseDeepCopy(const Widget& other){
    
        SAFE_DELETE(m_pHeapStorageResource);//safe release resource
        //pointer will call assignment operator of int(memory address), means copying an int
        //But it may get some trouble because "other" object may delete m_pHeapStorageResource later
        m_pHeapStorageResource = other.m_pHeapStorageResource;
        //we want deep copy here, so call Resource::deepCopy
        m_pHeapStorageResource = other.m_pHeapStorageResource->deepCopy();

        //will call "Default Copy assignment operator" of class Resource
        m_stackStorageResource = other.m_stackStorageResource;
        m_i = other.m_i; //copying an int
    }


    void memberwiseMove(Widget&& other){
        SAFE_DELETE(m_pHeapStorageResource);//safe release resource
        m_pHeapStorageResource = other.m_pHeapStorageResource; //move
        other.m_pHeapStorageResource = nullptr;
    
        //Did not benefit from move semantics,
        //because we didn't implement Move assignment operator for class Resource, so it will call it's own default Copy assignment operator(memberwiseCopy)
        m_stackStorageResource = other.m_stackStorageResource;  
        m_i = other.m_i;                                        //did not benefit from move semantics, because it as same as copying an int
    }

    //will call this function if you didn't use forward
    void memberwiseMove(Widget& other){
        SAFE_DELETE(m_pHeapStorageResource);//safe release resource
        m_pHeapStorageResource = other.m_pHeapStorageResource; //move
        other.m_pHeapStorageResource = nullptr;
        m_stackStorageResource = other.m_stackStorageResource;
        m_i = other.m_i;
    }
public:
    Resource* m_pHeapStorageResource;
    Resource m_stackStorageResource;
    int m_i;
};



int main(){

    Widget obj1;

    Widget obj2(obj1);// call Copy constructor
    Widget obj3;
    obj3 = obj1; // call Copy assignment operator

    Widget obj4;
    obj4 = Widget(); //call Move assignment operator

    // call Move constructor, should not call obj1 again, because we mark obj1 move to obj5 here
    Widget obj5 = std::move(obj1);

    //call Move assignment operator, should not call obj2 again, because we mark obj2 move to obj5 here
    obj5 = std::move(obj2);
    return 0;
}