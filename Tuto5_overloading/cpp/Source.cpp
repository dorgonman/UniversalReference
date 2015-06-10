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

    template<
        typename T,
        typename = std::enable_if_t<
        !std::is_convertible<std::shared_ptr<SpecialResource>, std::decay_t<T>>::value
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


    void setResourceByValue(std::shared_ptr<Resource> newResourePtr){
        m_resourcePtr = std::move(newResourePtr);
    }

public:
    template< typename T >
    void setResourceTagDispatch(T&& newResoure) // universal reference
    {

        static_assert(std::is_convertible<T, decltype(m_resourcePtr) >::value,
            "T can't assign to m_resourcePtr");
        setResourceTagDispatchImp(std::forward<T>(newResoure),
                                  std::is_base_of<std::shared_ptr<SpecialResource>, 
                                  typename std::decay<T>::type >());
        
    }
private:
    template< typename T >
    void setResourceTagDispatchImp(T&& newResoure, std::true_type){
        std::cout << "do something for SpecialResource type" << std::endl;
        m_resourcePtr = std::forward<T>(newResoure);

    }
    template< typename T >
    void setResourceTagDispatchImp(T&& newResoure, std::false_type){
        std::cout << "do something for other Resource type" << std::endl;
        m_resourcePtr = std::forward<T>(newResoure);
    }



private:
    std::shared_ptr< Resource > m_resourcePtr;

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


    //case 4
    URWidget widget4;
    auto newRes4 = std::make_shared<Resource2>();
    widget4.setResourceByValue(newRes4); //copy to newResourePtr
    widget4.setResourceByValue(std::move(newRes4)); //move to newResourePtr



    //case 5: tag dispatch
    URWidget widget5;
    auto newRes5_1 = std::make_shared<Resource>();
    widget5.setResourceTagDispatch(newRes5_1); //copy to newResourePtr
    const auto&& newRes5_2 = std::make_shared<SpecialResource>();
    widget5.setResourceTagDispatch(newRes5_2); //move to newResourePtr



    return 0;
}
