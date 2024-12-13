#include <iostream>

class CParent
{
public:
    CParent():mPublic(1),mPrivate(10),mProtected(100)
    {
        std::cout << "부모 생성자" << std::endl;
    }
    ~CParent()
    {
        std::cout << "부모 소멸자" << std::endl;
    }
public:
    int mPublic;
private:
    int mPrivate;
protected:
    int mProtected;
};

class CChild: public CParent
{
public:
    CChild()
    {
        std::cout << "자식 생성자" << std::endl;
    }
    ~CChild()
    {
        std::cout << "자식 소멸자" << std::endl;
    }
public:
    int mChildPublic;
};

class CChild1: public CParent
{
public:
    CChild1()
    {
        std::cout << "자식1 생성자" << std::endl;
    }
    ~CChild1()
    {
        std::cout << "자식1 소멸자" << std::endl;
    }
};
class CGrandChild : public CChild
{
public:
    CGrandChild()
    {
        std::cout << "손자 생성자" << std::endl;
    }
    ~CGrandChild()
    {
        std::cout << "손자 생성자" << std::endl;
    }
public:
    int mGrandChildPublic;
};

int main()
{
    //CParent parent;
    //CChild child;
    CGrandChild gc;
    
    return 0;
}
