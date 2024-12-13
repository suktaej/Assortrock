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
    void Output()
    {
        std::cout << "Parent Output" << std::endl;
    }
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
    void Output()
    {
        std::cout << "Child Output" << std::endl;
    }
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
     void Output() 
    {
        std::cout << "Child-Second Output" << std::endl;
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
    void Output()
    {
        std::cout << "GrandChild Output" << std::endl;
    }

};

int main()
{
    //CParent* ptr_Parent;
    CParent P1;
    std::cout << "--------------------" << std::endl;
    CChild C1;
    std::cout << "--------------------" << std::endl;
    CChild1 C2;
    std::cout << "--------------------" << std::endl;
    CGrandChild G1;
    std::cout << "+++이하 부모 포인터+++" << std::endl;
    //ptr_Parent = &P1;
    //ptr_Parent->Output();
    CParent *ptr_Parent = &P1;
    ptr_Parent->Output();
    std::cout << "====================" << std::endl;
    ptr_Parent = &C1;
    ptr_Parent->Output();
    std::cout << "====================" << std::endl;
    ptr_Parent = &C2;
    ptr_Parent->Output();
    std::cout << "====================" << std::endl;
    ptr_Parent = &G1;
    ptr_Parent->Output();
    std::cout << "+++이하 자식 포인터+++" << std::endl;
    CChild *ptr_Child = &C1;
    ptr_Child->Output();
    std::cout << "=========C1=========" << std::endl;
    //ptr_Child = &C2;
    //ptr_Child->Output();
    std::cout << "+++C2는 sibling으로 대입불가+++" << std::endl;
    ptr_Child = &G1;
    ptr_Child->Output();
    std::cout << "=========G1=========" << std::endl;
/*
    CParent* Child = new CChild;
    CParent* Child1 = new CChild1;
    
    CParent* Array[10] = {};
    Array[0] = Child;
    Array[1] = Child1;
    // 다형성의 존재 이유
    // 여러 자식을 하나로 묶어서 관리 가능
    Array[0]->Output();
    Array[1]->Output();
    // 재정의(Overiding)된 Child의 Output이 아니라 Parent의 Output출력
    
    // new CChild를 해 주어서 CChild타입의 메모리 크기만큼 힙에 공간을 할당
    // 그 주소를 반환
    // CChild포인터타입으로 CParent포인터 타입으로 대입
    // 업케스팅 : 자식타입을 부모타입으로 형변환(안전)
    // 다운캐스팅 : 부모타입을 자식타입으로 형변환(위험요소있음)
*/
    return 0;
}
