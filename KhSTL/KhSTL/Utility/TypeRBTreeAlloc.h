#ifndef KH_STL_TYPE_RED_BLACK_TREE_ALLOCATOR_H_
#define KH_STL_TYPE_RED_BLACK_TREE_ALLOCATOR_H_

namespace KhSTL {


template<class T>
inline T* _allocate(ptrdiff_t size, T*)
{
	std::set_new_handler(0);
	T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tmp == 0)
	{
		std::cerr << "out of memory" << std::endl;
		exit(1);
	}
	return tmp;
}

// �ڴ��ͷ�
template<class T>
inline void _deallocate(T* buffer)
{
	::operator delete(buffer);
}

// Ԫ�ع���
template<class T1, class  T2>
inline void _construct(T1* p, const T2& value)
{
	new(p)T1(value);
}

// Ԫ������
template<class T>
inline void _destroy(T* ptr)
{
	ptr->~T();
}


template<class T>
class mapTempAllocator
{
public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef const T*	const_pointer;
	typedef T&			reference;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	template<class U>
	struct rebind
	{
		typedef mapTempAllocator<U> other;
	};

	static pointer allocate(size_type n, const void* hint = 0)
	{
		return _allocate((difference_type)n, (pointer)0);
	}

	static void deallocate(pointer p, size_type n)
	{
		_deallocate(p);
	}

	static void deallocate(void* p)
	{
		_deallocate(p);
	}

	void construct(pointer p, const T& value)
	{
		_construct(p, value);
	}

	void destroy(pointer p)
	{
		_destroy(p);
	}

	pointer address(reference x)
	{
		return (pointer)&x;
	}

	const_pointer const_address(const_reference x)
	{
		return (const_pointer)&x;
	}

	size_type max_size() const
	{
		return size_type(UINT_MAX / sizeof(T));
	}
};

template<class T, class Alloc = mapTempAllocator<T>>
class simple_alloc
{
public:
	static T* allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}

	static T* allocate(void)
	{
		return (T*)Alloc::allocate(sizeof(T));
	}

	static void deallocate(T* p, size_t n)
	{
		if (0 != n)Alloc::deallocate(p, n * sizeof(T));
	}

	static void deallocate(void* p)
	{
		Alloc::deallocate(p);
	}
};





template<typename _Ty
	, typename _Kty
	, typename _Comp
	, typename _Alloc>
	class tRBTreeAlloc 
{
public:
	using ValueType = _Kty;
protected:
	/* ���ÿռ�����������һ���ڵ� */
	_Ty* getNode() { return simple_alloc<_Ty, _Alloc>::allocate(); }

	/* ���ÿռ��������ͻ�һ���ڵ� */
	void putNode(_Ty* p) { simple_alloc<_Ty, _Alloc>::deallocate(p); }

	/* ���벢��ʼ���ڵ� */
	_Ty* createNode(const ValueType& x)
	{
		// x�ǽڵ��ֵ
		_Ty* tmp = getNode(); // ����һ���ڵ�
		construct(&tmp->value, x); // ����ȫ�ֹ��캯����ʼ���ڵ�
		return tmp;
	}

	/* ��¡�ڵ� */
	_Ty* cloneNode(_Ty* x)
	{
		_Ty* tmp = createNode(x->value); // ���벢��ʼ���ڵ�
		tmp->color = x->color;
		tmp->left = 0;
		tmp->right = 0;
		return tmp;
	}

	/* �ͻ��ڵ� */

	void destroyNode(_Ty* p)
	{
		destroy(&p->value); // ����ȫ�������������ٽڵ�ֵ
		putNode(p); // �ͻ��ڴ�
	}
};


}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_ALLOCATOR_H_
