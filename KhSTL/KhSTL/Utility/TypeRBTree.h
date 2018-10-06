#ifndef KH_STL_TYPE_RED_BLACK_TREE_H_
#define KH_STL_TYPE_RED_BLACK_TREE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"
#include "../Utility/TypeTreeNode.h"
#include "../Utility/TypeRBTreeIterator.h"
#include "../Allocator/TypeConstruct.h"
#include "../Utility/TypePair.h"

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace KhSTL{

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





template<typename _Kty
	, typename _Comp
	, typename _Alloc = mapTempAllocator<_Kty>>
class RBTree {

protected:
	using ValueType = _Kty;

	using color_type			= rbTreeColorType; // �ڵ���ɫ

public:
	//using key_type				= _Kty; // ��
	//using value_type			= _Ty; //ֵ
	using pointer				= ValueType*; // ֵָ��
	using const_pointer			= const ValueType*; // constֵָ��
	using reference				= ValueType&;  // ֵ����
	using const_reference		= const ValueType&; // constֵ����

	using size_type				= size_t;
	using difference_type		= ptrdiff_t;

protected:

	/// Red black tree count
	unsigned _count; 
	tRBTreeNode<ValueType>* header; // �ڱ��ڵ㣬��parentָ��ָ����ڵ�
	_Comp key_compare; // �Ƚ�ֵ��С�ĺ���

public:
	typedef tRBTreeIterator<ValueType, ValueType&, ValueType*> Iterator; // ���������ĵ�����
	typedef const tRBTreeIterator<ValueType, ValueType&, ValueType*> const_iterator; // ����������const������

protected:
	/* ���ÿռ�����������һ���ڵ� */
	tRBTreeNode<ValueType>* get_node() { return simple_alloc<tRBTreeNode<ValueType>, _Alloc>::allocate(); }

	/* ���ÿռ��������ͻ�һ���ڵ� */
	void put_node(tRBTreeNode<ValueType>* p) { simple_alloc<tRBTreeNode<ValueType>, _Alloc>::deallocate(p); }

	/* ���벢��ʼ���ڵ� */
	tRBTreeNode<ValueType>* create_node(const ValueType& x)
	{
		// x�ǽڵ��ֵ
		tRBTreeNode<ValueType>* tmp = get_node(); // ����һ���ڵ�
		construct(&tmp->value, x); // ����ȫ�ֹ��캯����ʼ���ڵ�
		return tmp;
	}

	/* ��¡�ڵ� */
	tRBTreeNode<ValueType>* clone_node(tRBTreeNode<ValueType>* x)
	{
		tRBTreeNode<ValueType>* tmp = create_node(x->value); // ���벢��ʼ���ڵ�
		tmp->color = x->color;
		tmp->left = 0;
		tmp->right = 0;
		return tmp;
	}

	/* �ͻ��ڵ� */
	void destroy_node(tRBTreeNode<ValueType>* p)
	{
		destroy(&p->value); // ����ȫ�������������ٽڵ�ֵ
		put_node(p); // �ͻ��ڴ�
	}
private:
	/* ��ʼ������� */
	void init()
	{
		header = get_node(); // ��ʼ��header�ڵ㣬header�ڵ���Ϊ���ź�������ڱ���header��parentָ��ָ����ڵ㣬header��������__rb_tree_node*
		GetColor(header) = __rb_tree_red; // ����header�ڵ�Ϊ��ɫ
		root() = 0; // root()��ú�����ĸ��ڵ㣬header��parentָ��ָ����ڵ㣬��ʼ��������ĸ��ڵ�ָ��Ϊnull
		leftmost() = header; // ����header�ڵ��������ָ���Լ�
		rightmost() = header; // ����header�ڵ��������ָ���Լ�
	}
	
public:
	/* ���캯�� */
	RBTree() 
		: _count(0)
		, key_compare(_Comp())
	{ 
		init(); 
	}

	/* �������� */
	~RBTree()
	{
		put_node(header);
	}

protected:
	/* ��ø��ڵ㣨header���ڱ�����parentִ�и��ڵ㣩 */
	tRBTreeNode<ValueType>*& root()const 
	{ 
		return (tRBTreeNode<ValueType>*&)header->parent; 
	}

	/* �������������ߵĽڵ� */
	tRBTreeNode<ValueType>*& leftmost()const 
	{ 
		return (tRBTreeNode<ValueType>*&)header->left; 
	}

	/* ������������ұߵĽڵ� */
	tRBTreeNode<ValueType>*& rightmost()const 
	{ 
		return (tRBTreeNode<ValueType>*&)header->right; 
	}

	/* ���ؽڵ�����ӽڵ� */
	static tRBTreeNode<ValueType>*& left(tRBTreeNode<ValueType>* x) 
	{ 
		return (tRBTreeNode<ValueType>*&)(x->left); 
	}

	/* ���ؽڵ�����ӽڵ� */
	static tRBTreeNode<ValueType>*& right(tRBTreeNode<ValueType>* x) 
	{ 
		return (tRBTreeNode<ValueType>*&)(x->right);
	}

	/* ���ؽڵ�ĸ��ڵ� */
	static tRBTreeNode<ValueType>*& parent(tRBTreeNode<ValueType>* x) 
	{ 
		return (tRBTreeNode<ValueType>*&)(x->parent); 
	}

	/* ���ؽڵ��value */
	static ValueType& GetValue(tRBTreeNode<ValueType>* x) 
	{ 
		return x->value; 
	}

	/* ���ؽڵ����ɫ */
	static color_type& GetColor(tRBTreeNode<ValueType>* x)
	{ 
		return (color_type&)(x->color); 
	}


	/* ������Сֵ�ڵ� */
	static tRBTreeNode<ValueType>* minimum(tRBTreeNode<ValueType>* x)
	{
		return (tRBTreeNode<ValueType>*)tRBTreeNode::minimum(x); // ���û���ڵ����С�ڵ㺯��
	}

	/* �������ֵ�ڵ� */
	static tRBTreeNode<ValueType>* maximum(tRBTreeNode<ValueType>* x)
	{
		return (tRBTreeNode<ValueType>*)tRBTreeNode::maximum(x); // ���û���ڵ�����ڵ㺯��
	}

public:
	/* ��ø��ڵ��ֵ��header���ڱ�����parentִ�и��ڵ㣩; return (tRBTreeNode<_Ty>*&)header->parent->; */
	ValueType root_value() { return GetValue((tRBTreeNode<ValueType>*)header->parent); }

	/* ���رȽϴ�С�ĺ��� */
	_Comp key_comp()const { return key_compare; }

	/* ����һ����������ָ����������ߵĽڵ� */
	Iterator Begin() { return leftmost(); }

	/* ����һ����������ָ���������ұߵĽڵ� */
	Iterator End() { return header; }

	/* �жϺ�����Ƿ�Ϊ�� */
	bool empty()const { return _count == 0; }

	/* ���غ������С���ڵ���Ŀ�� */
	unsigned GetSize() const { return _count; }


public:
	/*
		������ֵ���ڵ��ֵ�����ظ�������ظ��������Ч
		����ֵ��pair��pair�ĵ�һ��Ԫ����rb_tree��������ָ���½ڵ�
		�ڶ���Ԫ�ر�ʾ����ɹ����
	*/
	tPair<Iterator, bool> insert_unique(const ValueType& v)
	{
		tRBTreeNode<ValueType>* y = header; // tRBTreeNode<_Ty>*��������tRBTreeNode*��header���ڱ�����y�õ�header
		tRBTreeNode<ValueType>* x = root(); // x�õ�������ĸ��ڵ㣬������ĸ��ڵ㱻��ʼ��Ϊnull����˲����һ��ֵʱ��x����null
		bool comp = true; // �Ƚϴ�С�Ĳ���ֵ

		while (x != 0) // x�ڵ㲻Ϊnull��˵�������ҵ������½ڵ��λ�ã�����ִ��whileѭ���ڵ���䣬��ͣ���±���
		{
			y = x; // y������x�ڵ�ĸ��ڵ�
			// ����������ֵС�ڽڵ�x��ֵ��compΪtrue������compΪfalse��key_compare�ǱȽϴ�С�ĺ�������ģ��ָ����

			//comp = key_compare(keyOfValue()(v), GetKey(x));
			
			comp = key_compare(v, GetValue(x));

			// ���compΪtrue��˵��������ֵС�ڽڵ�x��ֵ�����������ߣ���xΪx��������
			// ���compΪfalse��˵��������ֵ���ڽڵ�x��ֵ�����������ߣ���xΪx��������
			x = comp ? left(x) : right(x);
		}
		Iterator j = Iterator(y); // ��jָ������ĸ��ڵ�
		if (comp) // ��������ֵ�ȸ��ڵ��ֵС����ζ������Ҫ���뵽���ڵ����ߣ�������if
		{
			// begin()����leftmost()����������������Ľڵ㣬�������ڵ�Ϊ�������������ڵ�ͽ���if
			if (Begin() == j)
			{
				return tPair<Iterator, bool>(insertNode(x, y, v), true); // x�ǲ���㡢yΪ�����ĸ��ڵ㣬vΪ�����ֵ
			}
			else
			{
				j--;
			}
		}
		// ��ֵ������нڵ�ֵ�ظ������Բ���
		if (key_compare(GetValue(j.node), v))
		{
			return tPair<Iterator, bool>(insertNode(x, y, v), true);
		}
		return tPair<Iterator, bool>(j, false); // ����������˵����ֵһ�������м�ֵ�ظ������ܲ���
	}

	/*
		������ֵ���ڵ�ļ�ֵ�����ظ�
		���غ�����ĵ��������õ�����ָ���½ڵ�
	*/

	Iterator insert_equal(const ValueType& v)
	{
		tRBTreeNode<ValueType>* y = header;
		tRBTreeNode<ValueType>* x = root(); // xָ����ڵ�
		while (x != 0) // �Ӹ��ڵ㿪ʼ����Ѱ�Һ��ʵĲ����
		{
			y = x;
			// �������ң���С����
			x = key_compare(v, GetValue(x)) ? left(x) : right(x);
		}
		return insertNode(x, y, v); // xΪ������㣬yΪ�����ĸ��ڵ㣬vΪ�����ֵ
	}

	/* Ѱ�Һ�������Ƿ��м�ֵΪk�Ľڵ� */
	Iterator find(const ValueType& k)
	{
		tRBTreeNode<ValueType>* y = header; // ��y�����ڱ��ڵ㣨�ڱ��ڵ㲻������һ���֣�������parentָ����ڵ㣩
		tRBTreeNode<ValueType>* x = root(); // �õ����ڵ�

		while (x != 0)
		{
			// key_compare�ǱȽϴ�С�ĺ���
			if (!key_compare(GetValue(x), k)) // xֵ����k
			{
				y = x;
				x = left(x); // ������ֵ��������
			}
			else // xֵ����k
			{
				x = right(x); // ����Сֵ������
			}
		}
		Iterator j = Iterator(y);
		return (j == End() || key_compare(k, GetValue(j.node))) ? End() : j;
	}
private:
	/*
		�������
		x_��������ڵ�
		y_������ڵ�ĸ��ڵ�
		v�������ֵ
	*/
	Iterator insertNode(tRBTreeNode<ValueType>* x_, tRBTreeNode<ValueType>* y_, const ValueType& v)
	{
		// tRBTreeNodeBase*ʵΪtRBTreeNode_base*��tRBTreeNode<_Ty>*ʵΪtRBTreeNode*
		// ���ǰ�tRBTreeNode_base*����ǿתΪtRBTreeNode*
		// tRBTreeNode�ṹ���tRBTreeNode_base�ṹ�����value_field��value_field���ڱ���ֵ
		tRBTreeNode<ValueType>* x = (tRBTreeNode<ValueType>*)x_; // xָ������
		tRBTreeNode<ValueType>* y = (tRBTreeNode<ValueType>*)y_; // yָ������ĸ��ڵ�
		tRBTreeNode<ValueType>* z;

		// 1.y == header�������ĸ��ڵ�Ϊheader��ע��header���ڱ���header����������һ���֣�����header��parentָ����ڵ㣩��y == header˵�������Ϊ���ڵ�
		// 2.x == 0��˵���������Ҷ�ӽڵ��·���Ҷ�ӽڵ������������������Ϊnull����Ҳ������Ҷ�ӽڵ��¹��µĽڵ㣻x != 0˵��������������ڲ�ĳ���ڵ���
		// 3.key_compare(keyOfValue()(v), key(y))��������ڵ��ֵҪ�ȸ��ڵ��ֵС����ζ������Ҫ���뵽���ڵ���������ϣ�
		if (y == header || x != 0 || key_compare(v, GetValue(y)))
		{
			z = create_node(v); // �����½ڵ㣬���½ڵ��ֵ��value_field��Ϊv
			left(y) = z; // ��ڵ��������Ϊz�����ǳɹ��İ��½ڵ���뵽������
			if (y == header) // y == header�������ĸ��ڵ�Ϊheader��˵�����ڵ㻹û�б���ʼ��������if����Ҫ��ʼ�����ڵ�
			{
				root() = z; // z���˸��ڵ�
				rightmost() = z; // ��zΪ���������ұߵĽڵ�
			}
			else if (y == leftmost()) // ������ڵ�������������ߵĽڵ�
			{
				leftmost() = z; // ���ǰ��½ڵ���Ϊ����������ߵĽڵ�
			}
		}
		else
		{
			z = create_node(v); // �����½ڵ�
			right(y) = z; // ����ڵ㵽���ڵ���ұ�
			if (y == rightmost()) // ������ڵ������������ұߵĽڵ�
			{
				rightmost() = z; // ���ǰ��½ڵ���Ϊ���������ұߵĽڵ�
			}
		}
		parent(z) = y; // ���½ڵ�ĸ��ڵ�Ϊy
		left(z) = 0; // �½ڵ��������Ϊnull
		right(z) = 0; // �½ڵ��������Ϊnull

		__rb_tree_rebalance(z, header->parent); // header���ڱ���һ�������Ͳ��ı䣬header->parentִ�����ĸ��ڵ�
		++_count; // ���ӽڵ���
		return Iterator(z);
	}

	/*
		����ƽ���������ı���ɫ����ת���Σ�
		x�������ڵ�
		rootΪ���ڵ�
	*/
	inline void __rb_tree_rebalance(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
	{
		x->color = __rb_tree_red; // �²���Ľڵ��Ǻ�ɫ��
		// ��������ڵ㣨x����Ϊ���ڵ㣬�������ڵ�ĸ��ڵ�Ϊ��ɫ�����鷳�ʹ��ˣ�Ҫ����whileһ������
		while (x != root && x->parent->color == __rb_tree_red)
		{
			if (x->parent == x->parent->parent->left) // ������ڵ����游�ڵ�����ӽڵ�
			{
				tRBTreeNode<ValueType>* y = x->parent->parent->right; // ��yΪ�����ڵ�
				if (y && y->color == __rb_tree_red) // ��������ڵ������Ϊ��
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else // ��������ڵ㲻���ڣ����߲����ڵ�Ϊ��
				{
					if (x == x->parent->right) // ��������ڵ�Ϊ���ڵ�����ӽڵ㣨Ϊ���ڵ�����ӽڵ㣬��˵������ڵ�ķ�ʽ���ڲ壩
					{
						x = x->parent; // ���ڵ�Ϊ��ת֧��
						// ����һ�´�while��ʼ�������жϷ�֧�����ǿ��Եó�������ת��������
						// 1.�����ڵ㲻�Ǹ��ڵ�
						// 2.�����ڵ�ĸ��ڵ��Ǻ�ɫ
						// 3.���ڵ����游�ڵ�����ӽڵ�
						// 4.�����ڵ㲻���ڣ����߲����ڵ�Ϊ��
						// 5.�����ڵ�Ϊ���ڵ�����ӽڵ�
						__rb_tree_rotate_left(x, root); // ������ת
					}
					x->parent->color = __rb_tree_black; // �޸���ɫ
					x->parent->parent->color = __rb_tree_red; // �޸���ɫ
					__rb_tree_rotate_right(x->parent->parent, root); // �������˽�������
				}
			}
			else // ������ڵ����游�ڵ�����ӽڵ�
			{
				tRBTreeNode<ValueType>* y = x->parent->parent->left; // ��yΪ�����ڵ�
				if (y && y->color == __rb_tree_red) // ��������ڵ������Ϊ��
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else // ��������ڵ㲻���ڣ����߲����ڵ�Ϊ��
				{
					// ��������ڵ�Ϊ���ڵ�����ӽڵ㣨Ϊ���ڵ�����ӽڵ㣬��˵������ڵ�ķ�ʽ���ڲ壩
					if (x == x->parent->left)
					{
						x = x->parent; // ���ڵ�Ϊ��ת֧��
						// ����һ�´�while��ʼ�������жϷ�֧�����ǿ��Եó�������ת��������
						// 1.�����ڵ㲻�Ǹ��ڵ�
						// 2.�����ڵ�ĸ��ڵ��Ǻ�ɫ
						// 3.���ڵ����游�ڵ�����ӽڵ�
						// 4.�����ڵ㲻���ڣ����߲����ڵ�Ϊ��
						// 5.�����ڵ�Ϊ���ڵ�����ӽڵ�
						__rb_tree_rotate_right(x, root); // ������ת
					}
					x->parent->color = __rb_tree_black; // �޸���ɫ
					x->parent->parent->color = __rb_tree_red; // �޸���ɫ
					__rb_tree_rotate_left(x->parent->parent, root); // �������˽�������
				}
			}
		}
		root->color = __rb_tree_black; // ���ĸ��ڵ���Զ�Ǻ�
	}

	/*
		����ת
		�½ڵ��Ϊ��ڵ㣬�������ڵ�ĸ��ڵ�ҲΪ��ɫ����Υ���˺�������򣬴�ʱ��������ת
		x������ת��֧��
		root��������ĸ�
	*/
	inline void __rb_tree_rotate_left(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
	{
		tRBTreeNode<ValueType>* y = x->right; // yΪ��ת������ӽڵ�
		x->right = y->left; // ��ת��Ϊ������ת������ӽڵ�Ϊ�ӣ���ɸ��ӶԻ�
		if (y->left != 0)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;

		if (x == root)
		{
			root = y; // ��yΪ���ڵ�
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y; // ����ת��ĸ��ڵ�����ӽڵ�Ϊy
		}
		else
		{
			x->parent->right = y; // ����ת��ĸ��ڵ�����ӽڵ�Ϊy
		}
		y->left = x; // ���ӽڵ��������Ϊx
		x->parent = y; // ���ӽڵ�Ϊ��ת��ĸ��ڵ�
	}

	/*
		����ת
		�½ڵ��Ϊ��ڵ㣬�������ڵ�ĸ��ڵ�ҲΪ��ɫ����Υ���˺�������򣬴�ʱ��������ת
		x������ת��֧��
		root��������ĸ�
	*/
	inline void __rb_tree_rotate_right(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
	{
		tRBTreeNode<ValueType>* y = x->left; // ��yΪ��ת������ӽڵ�
		x->left = y->right; // ��y�����ӽڵ�Ϊ��ת������ӽڵ�
		if (y->right != 0)
		{
			y->right->parent = x; // �趨���ڵ�
		}
		y->parent = x->parent;

		// ��y��ȫ����x�ĵ�λ�����뽫���丸�ڵ�Ĺ�ϵ��ȫ���չ�����
		if (x == root)
		{
			root = y; // xΪ���ڵ�
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y; // xΪ�丸�ڵ�����ӽڵ�
		}
		else
		{
			x->parent->left = y; // xΪ�丸�ڵ�����ӽڵ�
		}
		y->right = x;
		x->parent = y;
	}
};

}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_H_
