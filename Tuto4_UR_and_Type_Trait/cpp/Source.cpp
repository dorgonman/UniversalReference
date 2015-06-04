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


#include <stdlib.h>
#include <iostream>
#include <memory>


#define SAFE_DELETE(a) do { delete (a); (a) = NULL; } while (0)
class Resource{
public:
    Resource(){};

    template<typename T>
    Resource(T&& data)
        : m_data(std::forward<T>(data)){

    };

    Resource* deepCopy(){
        Resource* pResource = new Resource();
        pResource->m_data = m_data;
        return pResource;
    }


public:
    std::string m_data;
};



class SpecialResource /*: public Resource*/ {
public:
};

class URWidget{
public:
    URWidget(){};

    template<typename T>
    void setResource(T&& newResoure) // universal reference
    {

        static_assert(std::is_convertible<T, decltype(m_resourcePtr) >::value,
            "T can't assign to m_resourcePtr");
        setResource2(std::forward<T>(newResoure));
       // m_resourcePtr = std::forward<T>(newResoure);
    }

    template<typename T>
    void setName(T&& newName) // universal reference
    {
        m_name = std::forward<T>(newName);
    }

    static URWidget makeWidget() // Moving version of makeWidget
    {
        URWidget w;
        //do somthing
        return std::move(w); // move w into return value
    } // (don't do this!)
private:
    template<typename T>
    void setResource2(T&& newResoure){ // universal reference
        setResource3(std::forward<T>(newResoure));
    }


    template<typename T>
    void setResource3(T&& newResoure){ // universal reference

        setResource4(std::forward<T>(newResoure));
    }
    template<typename T>
    void setResource4(T&& newResoure){ // universal reference
        m_resourcePtr = std::forward<T>(newResoure);
    }
private:
    std::string m_name;
    std::shared_ptr<Resource> m_resourcePtr;

};


int main(){

    URWidget widget;
    auto newRes = std::make_shared<Resource>("test");
    widget.setResource(newRes); //ok


    //widget.setResource("test"); //oops! should compile error
   // auto newRes2 = std::make_shared<SpecialResource>();

    //widget.setResource(newRes2);
    return 0;
}


