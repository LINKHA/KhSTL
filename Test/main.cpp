#include <iostream>
#include "../Core/Vector.h"
#include "../Core/List.h"

using namespace KhSTL;

#define Print(_x) std::cout<< _x <<std::endl
#define ForEach(_x)\
for (auto it = _x.Begin(); it != _x.End(); it++)\
{\
	std::cout<< *it<<"\t";\
} std::cout << std::endl

void VectorTest()
{
	Print("Vector_begin-----------------------------------------");
	Vector<int> vec;
	vec.Push(1);
	ForEach(vec);
	vec.Push(2);
	ForEach(vec);
	vec.Push(3);
	ForEach(vec);
	vec.Insert(0, 4);
	ForEach(vec);
	vec.Erase(0);
	ForEach(vec);
	vec.Pop();
	ForEach(vec);
	Print("Vector_end-----------------------------------------");
}
void ListTest()
{
	Print("List_begin-----------------------------------------");
	List<int> list;
	
	Print("List_end-----------------------------------------");
}

int main()
{
	//VectorTest();
	ListTest();



	system("pause");
	return 0;
}