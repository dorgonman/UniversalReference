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

//http://stackoverflow.com/questions/3734247/what-are-all-the-member-functions-created-by-compiler-for-a-class-does-that-hap

#include <iostream>
class Resource{
//compiler generated functions:
    //default constructor
    //copy constructor
    //destructor

   // Resource(Resource const& kSource) = delete;
   // Resource& operator=(Resource&& rhs) = delete;
    //generate move constructor 
    //generate  move assignment operator
public:
    Resource* deepCopy(){
        Resource* pResource = new Resource();
        pResource->m_data = m_data;
        return pResource;
    }
public:
    std::string m_data;
};


class UnCopableResource : Resource{
public:
    UnCopableResource(UnCopableResource const& kSource) = delete;
    UnCopableResource& operator=(UnCopableResource& rhs) = delete;
public:
    std::string m_dataUnMovable;
};


class UnMovableResource: Resource{
public:
     UnMovableResource(Resource const&& kSource) = delete;
     UnMovableResource& operator=(Resource&& rhs) = delete;
public:
    std::string m_dataUnMovable;
};


class Widget{
public:
    /** Default constructor */
    Widget(){
        m_pHeapStorageResource = new Resource();
    }

    /** Copy constructor */
    Widget(const Widget& other){
        memberwiseDeepCopy(other);

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
        memberwiseDeepCopy(other);
        return *this;
    }






    /** Move constructor */
    Widget(Widget&& other){
        //memberwiseMove(other);//oops! will call memberwiseMove(Widget& other), not our intent here
        memberwiseMove(std::forward<Widget>(other));
    }

    /** Move assignment operator */
    Widget& operator= (Widget&& other)
    {
        //memberwiseMove(other);//oops! will call memberwiseMove(Widget& other), not our intent here
        memberwiseMove(std::forward<Widget>(other));
        return *this;
    }

private:
    void memberwiseDeepCopy(const Widget& other){
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
        m_pHeapStorageResource = other.m_pHeapStorageResource; //move
        other.m_pHeapStorageResource = nullptr;
        //Did not benefit from move semantics,
        //because it will call std::string's  Copy assignment operator that will deep copy whole string 
        m_stackStorageResource = other.m_stackStorageResource;  
        m_i = other.m_i;                                        //did not benefit from move semantics, because it as same as copying an int
    }

    //will call this function if you didn't use forward
    void memberwiseMove(Widget& other){
        m_pHeapStorageResource = other.m_pHeapStorageResource; //move
        other.m_pHeapStorageResource = nullptr;
    }
public:
    Resource* m_pHeapStorageResource;
    Resource m_stackStorageResource;
    int m_i;
};



int main(){
    using namespace std;
    Widget origin;
    Widget or2;
    origin = or2;


    system("pause");
    return 0;
}