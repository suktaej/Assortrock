#include <iostream>
#include <vector>

class CContainer
{
public:
    CContainer() { std::cout << "constructor" << std::endl; }
    CContainer(const CContainer&& Con) { mNum = Con.mNum; std::cout << "Copy" << std::endl; }
    ~CContainer() { std::cout << "destroy" << std::endl; }
    int mNum = 10;
};

int main()
{
    std::vector<int> vecInt;
    //int type을 저장하는 vector
    std::vector<CContainer> vecCon;

    std::vector<int>::iterator iter;
    //iterator 선언
    
    //vecInt.reserve(20);
    //vecInt.resize(20);
    std::cout << "처음 Capacity:" << vecInt.capacity() << std::endl;
    for (int i = 0;i < 10;i++)
    {
        vecInt.push_back(i * 10);
        std::cout << "size:" << vecInt.size();
		std::cout << ", Capacity:" << vecInt.capacity() << std::endl;
    }

    std::vector<int>::iterator iterEnd = vecInt.end();
    //for (iter = vecInt.begin();iter != vecInt.end();iter++) 
    //vecInt.end()호출이 반복횟수 만큼 발생
    for (iter = vecInt.begin();iter != iterEnd;iter++) 
    {
        std::cout << *iter << std::endl;
    }

    vecInt.push_back(1);
    vecInt.push_back(2);
    vecInt.push_back(3);
    vecInt.push_back(4);
    vecInt.push_back(5);

    //vecInt.resize(2);
    //vecInt.resize(20);

    //vecInt.reserve(2);
    //size에는 영향이 없음
    //capacity만 증가

    return 0;
}
