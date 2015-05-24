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


#include "vld.h"
#include <stdlib.h>
#include <crtdbg.h>
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



class Widget {
public:
    Widget(){};
 

 
 
    void setName(const std::string& newName) 
    {
        m_name = newName;
    } // const lvalue
    void setName(std::string&& newName)
    {
        m_name = std::move(newName);
    } // rvalue
 
    void setResource(std::shared_ptr<Resource>&  resourcePtr){
        m_resourcePtr = resourcePtr;
    }
    void setResource(std::shared_ptr<Resource>&&  resourcePtr){
        m_resourcePtr = std::move(resourcePtr);
    }
 
    
private:
    std::string m_name;
    std::shared_ptr<Resource> m_resourcePtr;
};


class URWidget{
public:
    URWidget(){};


    /*template<typename T>
    URWidget(T&& ohter){

    };*/



    template<typename T>
    void setResource(T&& newResoure) // universal reference
    {
        //name = std::move(newName);  //bad
        m_resourcePtr = std::forward<T>(newResoure);
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
    std::string m_name;
    std::shared_ptr<Resource> m_resourcePtr;

};



template<typename T>
class TWidget{
public:
    TWidget(){};


    void setResource(T&& newResoure) // universal reference
    {
        //name = std::move(newName);  //bad
        m_resourcePtr = std::forward<T>(newResoure);
    }


    void setName(T&& newName) // universal reference
    {
        m_name = std::forward<T>(newName);
    }

private:
    std::string m_name;
    std::shared_ptr<Resource> m_resourcePtr;

};

int main(){

    {
        Widget widget;

        widget.setName("rvalue reference");
        std::string name = "lvalue reference";
        widget.setName(name);


        widget.setResource(std::make_shared<Resource>());


        auto resourcePtr = std::make_shared<Resource>();
        widget.setResource(resourcePtr);

        auto& resourcePtr1 = std::make_shared<Resource>();
        //widget.setResource(&resourcePtr1);

        auto&& resourcePtr2 = std::make_shared<Resource>();
        //widget.setResource(&resourcePtr2);//
    }


    {
        URWidget widget;

        widget.setName("rvalue reference");
        std::string name = "lvalue reference";
        widget.setName(name);


        widget.setResource(std::make_shared<Resource>());

        auto resourcePtr = std::make_shared<Resource>();
        widget.setResource(resourcePtr);
    }



    {
        TWidget<std::shared_ptr<Resource>> widget;
        widget.setResource(std::make_shared<Resource>());//will call rvalue reference version
        auto resourcePtr = std::make_shared<Resource>();
        //widget.setResource(resourcePtr); //compile error, rvalue reference version can't bind lvalue
    }
    {
        TWidget<std::shared_ptr<Resource>&> widget;
        widget.setResource(std::make_shared<Resource>());//will call lvalue reference version
        auto resourcePtr = std::make_shared<Resource>();
        widget.setResource(resourcePtr); //will call lvalue reference version
    }

    {
         TWidget<std::shared_ptr<Resource>&&> widget;
         widget.setResource(std::make_shared<Resource>());
         auto resourcePtr = std::make_shared<Resource>();
        // widget.setResource(resourcePtr); //compile error, rvalue reference version can't bind lvalue
    }


    //perfect forwarding demo
    {
        URWidget widget;
        widget.setResource<std::shared_ptr<Resource> >(std::make_shared<Resource>());//call rvalue version

        auto resourcePtr = std::make_shared<Resource>();
        widget.setResource<std::shared_ptr<Resource>& >(resourcePtr); //call lvalue version
        widget.setResource<std::shared_ptr<Resource>&& >(std::move(resourcePtr));//call rvalue version
    
    }



    return 0;
}


