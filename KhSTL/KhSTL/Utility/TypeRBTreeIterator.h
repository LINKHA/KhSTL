#ifndef KH_STL_TYPE_TREE_ITERATOR_H_
#define KH_STL_TYPE_TREE_ITERATOR_H_

#include "TypeTreeNode.h"

namespace KhSTL {

/* ��������� */
struct tRBTreeBaseIterator
{
	using BasePtr = tRBTreeNodeTreeBase::BasePtr; // ����ڵ�ָ��
	using iterator_category = bidirectional_iterator_tag;
//	typedef ptrdiff_t							difference_type;

	BasePtr	node; // ��Ա������ָ����ڵ��ָ�룬������ϵ�������ͽڵ��Ŧ��

	/* ������������ʵ��operator++ʱ���ñ����� */
	void increment()
	{
		if (node->right != 0) // ��������ӽڵ�
		{
			node = node->right; // ��������
			while (node->left != 0) // Ȼ��һֱ���������ߵ���
			{
				node = node->left;
			}
		}
		else // û�����ӽڵ�
		{
			BasePtr y = node->parent; // �ҳ����ڵ�
			while (node == y->right) // ������нڵ㱾���Ǹ����ӽڵ�
			{
				node = y; // ��һֱ���ݣ�ֱ������Ϊ���ӽڵ㡱Ϊֹ
				y = y->parent;
			}
			if (node->right != y) // ����ʱ�����ӽڵ㲻���ڴ�ʱ�ĸ��ڵ㣬��ʱ�ĸ��ڵ㼴Ϊ���
			{					  // �����ʱ��nodeΪ���
				node = y;
			}
		}
	}

	/* ������������ʵ��operator--ʱ���ñ����� */
	void decrement()
	{
		if (node->color == RBTreeColor::RED && node->parent->parent == node)
		{
			// ����Ǻ�ڵ㣬���游�ڵ�����Լ�����ô�ҽڵ㼴Ϊ���
			// �����������nodeΪheaderʱ��ע�⣬header�����ӽڵ㣨��mostright����ָ����������max�ڵ�
			node = node->right;
		}
		else if (node->left != 0) // ��������ӽڵ㣬��y
		{
			BasePtr y = node->left; // ��yָ�����ӽڵ�
			while (y->right != 0) // ��y�����ӽڵ�ʱ
			{
				y = y->right; // һֱ�����ӽڵ��ߵ���
			}
			node = y; // ���Ϊ��
		}
		else // ���Ǹ��ڵ㣬Ҳû�����ӽڵ�
		{
			BasePtr y = node->parent; // �ҳ����ڵ�
			while (node == y->left) // �����нڵ�Ϊ���ӽڵ�
			{
				node = y; // һֱ���������ߣ�ֱ�����нڵ�
				y = y->parent; // ��Ϊ���ӽڵ�
			}
			node = y; // ��ʱ���ڵ㼴Ϊ��
		}
	}
};

/* ��������� */
template<class value, class ref, class ptr>
struct tRBTreeIterator :public tRBTreeBaseIterator
{
#pragma region typedef
	/*
		ע�⣬���������û�г�Ա������ֻ�̳��˻����������node����
		�����������node�����Ǻ�����ڵ�����������ӵ�Ŧ��
	*/
	typedef value											value_type;
	typedef ref												reference;
	typedef ptr												pointer;
	typedef tRBTreeIterator<value, value&, value*>		iterator;
	typedef tRBTreeIterator<value, ref, ptr>				self;
	typedef tRBTreeNodeTree<value>*							link_type;
	typedef size_t											size_type;

#pragma endregion

#pragma region ���캯��

	tRBTreeIterator() {} // default���캯��
	tRBTreeIterator(link_type x) { node = x; } // ��ͨ���캯��
	tRBTreeIterator(const iterator& it) { node = it.node; } // copy���캯��

#pragma endregion

#pragma region �������Ļ�������

/* ������ã����ؽڵ�ֵ */
	reference operator*()const { return link_type(node)->value_field; }

	/* ������ã����ؽڵ�ֵ */
	pointer operator->()const { return *(operator*()); }

	/* ���ص�����ָ��Ľڵ����ɫ */
	RBTreeColor color() { return node->color; }

	/* ���������� */
	self& operator++() { increment(); return *this; }

	/* ���������� */
	self& operator++(int)
	{
		self tmp = *this;
		increment();
		return tmp;
	}

	/* ���������� */
	self& operator--()const { decrement(); return *this; }

	/* ���������� */
	self& operator--(int)
	{
		self tmp = *this;
		decrement();
		return tmp;
	}

	/* �Ƚ����������Ƿ�ָ��ͬһ���ڵ� */
	bool operator==(const self& x)const { return x.node == node; }

	/* �Ƚ����������Ƿ�ָ��ͬһ���ڵ� */
	bool operator!=(const self& x)const { return x.node != node; }

#pragma endregion
};




}

#endif //!KH_STL_TYPE_TREE_ITERATOR_H_