#include <memory>
#include <iostream>

std::unique_ptr<int> ufunc()
{
	std::unique_ptr<int> ptr = std::make_unique<int>(100);
	return ptr;
}

void unique_ptr_func()
{
	//유니크 포인터
	//다른 포인터 타입에 할당되거나 변경이 불가
	std::unique_ptr<int> uptr(new int(10));
	std::unique_ptr<int> uptr2 = std::make_unique<int>(20);
	std::cout << *uptr << std::endl;
	std::cout << *uptr2 << std::endl;

	//유니크 포인터를 가져올 때 .get()
	int* raw_ptr = uptr.get();
	std::cout << "get() : "<< *raw_ptr << std::endl;

	//유니크 포인터는 다른 유니크 포인터에 할당 불가
	//std::unique_ptr<int> uptr_cp{ uptr };
	//std::unique_ptr<int> cp_uptr = uptr;

	//이동생성자 사용 가능(move)
	std::unique_ptr<int> uptr_cp{ move(uptr) };
	std::cout << "move: "<< *uptr_cp << std::endl;
	
	//함수 포인터 반환
	//메모리 소유권 전달(move)
	auto re_ptr = ufunc();
	std::cout << "func return: "<< *re_ptr << std::endl;

	//스마트포인터 사용자 임의 제거 .reset()
	uptr.reset();
	std::cout << "reset : "<< * uptr << std::endl;
}

void sfunc(std::shared_ptr<int> ptr)
{
	std::shared_ptr<int> ptr_cp = ptr;
	std::cout << *ptr_cp << std::endl;

	std::shared_ptr<int> ptr_cp2 = ptr_cp;
	std::cout << __func__ << "::Ref Count: " << ptr.use_count() << std::endl;
}

int main(void)
{
	std::shared_ptr<int> sptr = std::make_shared<int>(10);
	std::cout << sptr << std::endl;
	std::cout << *sptr << std::endl;
	
	std::shared_ptr<int> sptr_cp = sptr;
	std::cout << sptr << std::endl;
	std::cout << *sptr << std::endl;

	std::shared_ptr<int> sptr_cp2 = sptr_cp;
	std::cout << "Ref count: " << sptr.use_count() << std::endl;

	sfunc(sptr);
	std::cout << "Func call after Ref count: " << sptr.use_count() << std::endl;
	
	return 0;
}