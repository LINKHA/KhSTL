#include <iostream>
#include "../Core/Vector.h"
#include "../Core/List.h"
#include "../Core/String.h"
#include "../Core/HashMap.h"
#include "../Core/StringHash.h"
#include "../Core/AutoPtr.h"

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
	list.Push(1);
	ForEach(list);
	list.PushFront(0);
	ForEach(list);
	list.Pop();
	ForEach(list);
	Print("List_end-----------------------------------------");
}
void StringTest()
{
	Print("String_begin-----------------------------------------");
	String str;
	

	Print("String_end-----------------------------------------");
}

void HashMapTest()
{
	Print("HashMap_begin-----------------------------------------");
	HashMap<int, int> hashMap;
	hashMap.Insert(MakePair(1, 3));
	hashMap.Insert(MakePair(2, 3));
	hashMap.Insert(MakePair(3, 3));
	hashMap.Erase(1);
	Print("HashMap_end-----------------------------------------");
}

void StringHashTest()
{
	Print("StringHash_begin-----------------------------------------");
	StringHash stringHash("Hash");
	StringHash stringHash2("Hash");
	Print("StringHash_end-----------------------------------------");
}
int main()
{
	//VectorTest();
	//ListTest();
	//StringTest();
	HashMapTest();
	StringHashTest();


	system("pause");
	return 0;
}