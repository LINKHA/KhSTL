#ifndef KH_STL_TYPE_RED_BLACK_TREE_H_
#define KH_STL_TYPE_RED_BLACK_TREE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"

namespace KhSTL{

template <typename _Kty
	, typename _Ty
	, typename _keyOfValue
	, typename _Sort = tLess<_Ty>
	, typename _Alloc = tAllocator<_Kty>>
	class tTree
{
	using LinkType = tRBTreeNodeTree*;
	using KeyType = _Kty; // ��
	using ValueType = _Ty	; //ֵ

	using rb_tree_node_allocator = simple_alloc<tRBTreeNodeTree, Alloc>; // �ڵ�ռ�������
public:
	using iterator = tRBTreeIterator<_Ty, _Ty&, _Ty*> ; // ���������ĵ�����
	using const_iterator = const tRBTreeIterator<_Ty, _Ty&, _Ty*> ; // ����������const������

#pragma endregion

#pragma region ���ĳ�ʼ�����ڵ�Ĺ��졢����������

protected:
	/* ���ÿռ�����������һ���ڵ� */
	LinkType getNode() { return rb_tree_node_allocator::allocate(); }

	/* ���ÿռ��������ͻ�һ���ڵ� */
	void putNode(LinkType p) { rb_tree_node_allocator::deallocate(p); }

	/* ���벢��ʼ���ڵ� */
	LinkType createNode(const value_type& x)
	{
		// x�ǽڵ��ֵ
		LinkType tmp = get_node(); // ����һ���ڵ�
		construct(&tmp->value_field, x); // ����ȫ�ֹ��캯����ʼ���ڵ�
		return tmp;
	}

	/* ��¡�ڵ� */
	LinkType cloneNode(LinkType x)
	{
		LinkType tmp = create_node(x->value_field); // ���벢��ʼ���ڵ�
		tmp->color = x->color;
		tmp->left = 0;
		tmp->right = 0;
		return tmp;
	}

	/* �ͻ��ڵ� */
	void destroyNode(LinkType p)
	{
		destroy(&p->value_field); // ����ȫ�������������ٽڵ�ֵ
		put_node(p); // �ͻ��ڴ�
	}

private:
	/* ��ʼ������� */
	void init()
	{
		header = get_node(); // ��ʼ��header�ڵ㣬header�ڵ���Ϊ���ź�������ڱ���header��parentָ��ָ����ڵ㣬header��������__rb_tree_node*
		color(header) = __rb_tree_red; // ����header�ڵ�Ϊ��ɫ
		root() = 0; // root()��ú�����ĸ��ڵ㣬header��parentָ��ָ����ڵ㣬��ʼ��������ĸ��ڵ�ָ��Ϊnull
		leftmost() = header; // ����header�ڵ��������ָ���Լ�
		rightmost() = header; // ����header�ڵ��������ָ���Լ�
	}

public:
	/* ���캯�� */
	tTree(const compare& cmp = compare()) 
		: node_count(0)
		, key_compare(cmp) 
	{ 
		init(); 
	}

	/* �������� */
	~tTree()
	{
		putNode(header);
	}

#pragma endregion

#pragma region protected����������

protected:
	/* ��ø��ڵ㣨header���ڱ�����parentִ�и��ڵ㣩 */
	LinkType& root()const { return (LinkType&)header->parent; }

	/* �������������ߵĽڵ� */
	LinkType& leftmost()const { return (LinkType&)header->left; }

	/* ������������ұߵĽڵ� */
	LinkType& rightmost()const { return (LinkType&)header->right; }

	/* ���ؽڵ�����ӽڵ� */
	static LinkType& left(LinkType x) { return (LinkType&)(x->left); }

	/* ���ؽڵ�����ӽڵ� */
	static LinkType& right(LinkType x) { return (LinkType&)(x->right); }

	/* ���ؽڵ�ĸ��ڵ� */
	static LinkType& parent(LinkType x) { return (LinkType&)(x->parent); }

	/* ���ؽڵ��value */
	static reference value(LinkType x) { return (x->value_field); }

	/* ���ؽڵ����ɫ */
	static color_type& color(LinkType x) { return (color_type)(x->color); }

	/* ���ؽڵ��value */
	static const key& key(base_ptr x) { return keyOfValue()(value(LinkType(x))); }

	/* ������Сֵ�ڵ� */
	static LinkType minimum(LinkType x)
	{
		return (LinkType)__rb_tree_node_base::minimum(x); // ���û���ڵ����С�ڵ㺯��
	}

	/* �������ֵ�ڵ� */
	static LinkType maximum(LinkType x)
	{
		return (LinkType)__rb_tree_node_base::maximum(x); // ���û���ڵ�����ڵ㺯��
	}

#pragma endregion

#pragma region �ṩ���û��Ĺ��ߺ���

public:
	/* ��ø��ڵ��ֵ��header���ڱ�����parentִ�и��ڵ㣩; return (LinkType&)header->parent->; */
	value_type root_value() { return value((LinkType)header->parent); }

	/* ���رȽϴ�С�ĺ��� */
	compare key_comp()const { return key_compare; }

	/* ����һ����������ָ����������ߵĽڵ� */
	iterator begin() { return leftmost(); }

	/* ����һ����������ָ���������ұߵĽڵ� */
	iterator end() { return header; }

	/* �жϺ�����Ƿ�Ϊ�� */
	bool empty()const { return node_count == 0; }

	/* ���غ������С���ڵ���Ŀ�� */
	size_type size() const { return node_count; }

	/* ��������ڵ��� */
	size_type max_size()const { return size_type(-1); }

#pragma endregion

#pragma region ���������

public:
	/*
		������ֵ���ڵ��ֵ�����ظ�������ظ��������Ч
		����ֵ��pair��pair�ĵ�һ��Ԫ����rb_tree��������ָ���½ڵ�
		�ڶ���Ԫ�ر�ʾ����ɹ����
	*/
	std::pair<iterator, bool> insert_unique(const value_type& v)
	{
		LinkType y = header; // LinkType��������__rb_tree_node*��header���ڱ�����y�õ�header
		LinkType x = root(); // x�õ�������ĸ��ڵ㣬������ĸ��ڵ㱻��ʼ��Ϊnull����˲����һ��ֵʱ��x����null
		bool comp = true; // �Ƚϴ�С�Ĳ���ֵ
		while (x != 0) // x�ڵ㲻Ϊnull��˵�������ҵ������½ڵ��λ�ã�����ִ��whileѭ���ڵ���䣬��ͣ���±���
		{
			y = x; // y������x�ڵ�ĸ��ڵ�
			// ����������ֵС�ڽڵ�x��ֵ��compΪtrue������compΪfalse��key_compare�ǱȽϴ�С�ĺ�������ģ��ָ����
			comp = key_compare(keyOfValue()(v), key(x));
			// ���compΪtrue��˵��������ֵС�ڽڵ�x��ֵ�����������ߣ���xΪx��������
			// ���compΪfalse��˵��������ֵ���ڽڵ�x��ֵ�����������ߣ���xΪx��������
			x = comp ? left(x) : right(x);
		}
		iterator j = iterator(y); // ��jָ������ĸ��ڵ�
		if (comp) // ��������ֵ�ȸ��ڵ��ֵС����ζ������Ҫ���뵽���ڵ����ߣ�������if
		{
			// begin()����leftmost()����������������Ľڵ㣬�������ڵ�Ϊ�������������ڵ�ͽ���if
			if (begin() == j)
			{
				return std::pair<iterator, bool>(__insert(x, y, v), true); // x�ǲ���㡢yΪ�����ĸ��ڵ㣬vΪ�����ֵ
			}
			else
			{
				j--;
			}
		}
		// ��ֵ������нڵ�ֵ�ظ������Բ���
		if (key_compare(key(j.node), keyOfValue()(v)))
		{
			return std::pair<iterator, bool>(__insert(x, y, v), true);
		}
		return std::pair<iterator, bool>(j, false); // ����������˵����ֵһ�������м�ֵ�ظ������ܲ���
	}

	/*
		������ֵ���ڵ�ļ�ֵ�����ظ�
		���غ�����ĵ��������õ�����ָ���½ڵ�
	*/
	iterator insert_equal(const value_type& v)
	{
		LinkType y = header;
		LinkType x = root(); // xָ����ڵ�
		while (x != 0) // �Ӹ��ڵ㿪ʼ����Ѱ�Һ��ʵĲ����
		{
			y = x;
			// �������ң���С����
			x = key_compare(keyOfValue()(v), key(x)) ? left(x) : right(x);
		}
		return __insert(x, y, v); // xΪ������㣬yΪ�����ĸ��ڵ㣬vΪ�����ֵ
	}

	/* Ѱ�Һ�������Ƿ��м�ֵΪk�Ľڵ� */
	iterator find(const value_type& k)
	{
		LinkType y = header; // ��y�����ڱ��ڵ㣨�ڱ��ڵ㲻������һ���֣�������parentָ����ڵ㣩
		LinkType x = root(); // �õ����ڵ�

		while (x != 0)
		{
			// key_compare�ǱȽϴ�С�ĺ���
			if (!key_compare(key(x), k)) // xֵ����k
			{
				y = x;
				x = left(x); // ������ֵ��������
			}
			else // xֵ����k
			{
				x = right(x); // ����Сֵ������
			}
		}
		iterator j = iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end() : j;
	}
private:
	/*
		�������
		x_��������ڵ�
		y_������ڵ�ĸ��ڵ�
		v�������ֵ
	*/
	iterator __insert(base_ptr x_, base_ptr y_, const value_type& v)
	{
		// base_ptrʵΪ__rb_tree_node_base*��LinkTypeʵΪ__rb_tree_node*
		// ���ǰ�__rb_tree_node_base*����ǿתΪ__rb_tree_node*
		// __rb_tree_node�ṹ���__rb_tree_node_base�ṹ�����value_field��value_field���ڱ���ֵ
		LinkType x = (LinkType)x_; // xָ������
		LinkType y = (LinkType)y_; // yָ������ĸ��ڵ�
		LinkType z;

		// 1.y == header�������ĸ��ڵ�Ϊheader��ע��header���ڱ���header����������һ���֣�����header��parentָ����ڵ㣩��y == header˵�������Ϊ���ڵ�
		// 2.x == 0��˵���������Ҷ�ӽڵ��·���Ҷ�ӽڵ������������������Ϊnull����Ҳ������Ҷ�ӽڵ��¹��µĽڵ㣻x != 0˵��������������ڲ�ĳ���ڵ���
		// 3.key_compare(keyOfValue()(v), key(y))��������ڵ��ֵҪ�ȸ��ڵ��ֵС����ζ������Ҫ���뵽���ڵ���������ϣ�
		if (y == header || x != 0 || key_compare(keyOfValue()(v), key(y)))
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
		++node_count; // ���ӽڵ���
		return iterator(z);
	}

	/*
		����ƽ���������ı���ɫ����ת���Σ�
		x�������ڵ�
		rootΪ���ڵ�
	*/
	inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		x->color = __rb_tree_red; // �²���Ľڵ��Ǻ�ɫ��
		// ��������ڵ㣨x����Ϊ���ڵ㣬�������ڵ�ĸ��ڵ�Ϊ��ɫ�����鷳�ʹ��ˣ�Ҫ����whileһ������
		while (x != root && x->parent->color == __rb_tree_red)
		{
			if (x->parent == x->parent->parent->left) // ������ڵ����游�ڵ�����ӽڵ�
			{
				__rb_tree_node_base* y = x->parent->parent->right; // ��yΪ�����ڵ�
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
				__rb_tree_node_base* y = x->parent->parent->left; // ��yΪ�����ڵ�
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
	inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		__rb_tree_node_base* y = x->right; // yΪ��ת������ӽڵ�
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
	inline void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		__rb_tree_node_base* y = x->left; // ��yΪ��ת������ӽڵ�
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

#pragma endregion

private:
	unsigned _count; 
	LinkType _header;
	_Arr _keyCompare;
};

}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_H_