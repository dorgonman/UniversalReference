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


#include "iostream"
#include "memory"

class Resource{
public:
    Resource(){};

    ~Resource(){};


private:
    void memberwiseCopy(const Resource& other){
        m_data = other.m_data;
    }

public:
    std::string m_data;
};

class SpecialResource : public Resource {
public:

};

class Resource2 : public Resource {
public:

};
class URWidget{
public:
    URWidget(){};

    //template<typename T>
    template<
        typename T,
        typename = std::enable_if_t<
        !std::is_convertible<std::shared_ptr<SpecialResource>, std::decay_t<T>>::value
        &&
        !std::is_integral<std::remove_reference_t<T>>::value
        >
    >
    void setResource(T&& newResoure) // universal reference
    {

        static_assert(std::is_convertible<T, decltype(m_resourcePtr) >::value,
            "T can't assign to m_resourcePtr");

        m_resourcePtr = std::forward<T>(newResoure);
    }


    void setResource(const std::shared_ptr<Resource>& newResourePtr)
    {
        m_resourcePtr = newResourePtr;
    }

    //oops!? why case 2 call this function if we implement this!?
    //But it seems work just like lvalue version...
    //TODO: check smart pointer implementation.
    /*void setResource(std::shared_ptr<Resource>&& newResourePtr)
    {
        m_resourcePtr = std::move(newResourePtr);
    }*/
private:
    std::shared_ptr<Resource> m_resourcePtr;

};

int main(){
    
    //case 1
    URWidget widget;
    auto newRes1 = std::make_shared<Resource>();
    widget.setResource(newRes1); // call void setResource(const std::shared_ptr<Resource>& newResourePtr)

    //case 2
    URWidget widget2;
    auto newRes2 = std::make_shared<SpecialResource>(); // call void setResource(const std::shared_ptr<Resource>& newResourePtr)
    widget2.setResource(newRes2);
 
    //case 3
    URWidget widget3;
    auto newRes3 = std::make_shared<Resource2>();
    widget3.setResource(newRes3);//call UR Version
    return 0;
}




#include "Timer.h"





/*int main(){

    {
        Timer t;
        for (int i = 0; i < 10000000; i++){
            char s[] = "small_string";
            char t[10];

            memcpy(&t, &s, 10);
        }

        std::cout << "test, memcpy: " << t.elapsed() << " second" << std::endl;
    }


    {
        Timer t;
        for (int i = 0; i < 10000000; i++){
            char s[] = "small_string";
            char t[10];
            memmove(&t, &s, 10);
            //std::clog << t << std::endl;
        }

        std::cout << "test, memmove: " << t.elapsed() << " second" << std::endl;
    }


    {
        Timer t;
        for (int i = 0; i < 10000000; i++){

            std::string test = "small_string";
            std::string test2_1 = test;   // line 1
            // std::clog << test2_1.c_str() << std::endl;
        }

        std::cout << "test, str copy: " << t.elapsed() << " second" << std::endl;
    }


    {
        Timer t;
        for (int i = 0; i < 10000000; i++){

            std::string test = "small_string";
            std::string test2_2 = std::move(test); // line 2

            // std::clog << test2_2.c_str() << std::endl;
        }
        std::cout << "test, str move: " << t.elapsed() << " second" << std::endl;
    }
}*/