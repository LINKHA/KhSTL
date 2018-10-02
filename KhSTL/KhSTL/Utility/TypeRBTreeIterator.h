#ifndef KH_STL_TYPE_TREE_ITERATOR_H_
#define KH_STL_TYPE_TREE_ITERATOR_H_

#include "TypeTreeNode.h"

namespace KhSTL {

/* 基层迭代器 */
struct tRBTreeBaseIterator
{
	using BasePtr = tRBTreeNodeTreeBase::BasePtr; // 父类节点指针
	using iterator_category = bidirectional_iterator_tag;
//	typedef ptrdiff_t							difference_type;

	BasePtr	node; // 成员变量：指向父类节点的指针，这是联系迭代器和节点的纽带

	/* 迭代器的子类实现operator++时调用本函数 */
	void increment()
	{
		if (node->right != 0) // 如果有右子节点
		{
			node = node->right; // 就向右走
			while (node->left != 0) // 然后一直往左子树走到底
			{
				node = node->left;
			}
		}
		else // 没有右子节点
		{
			BasePtr y = node->parent; // 找出父节点
			while (node == y->right) // 如果现行节点本身是个右子节点
			{
				node = y; // 就一直上溯，直到“不为右子节点”为止
				y = y->parent;
			}
			if (node->right != y) // 若此时的右子节点不等于此时的父节点，此时的父节点即为解答
			{					  // 否则此时的node为解答
				node = y;
			}
		}
	}

	/* 迭代器的子类实现operator--时调用本函数 */
	void decrement()
	{
		if (node->color == RBTreeColor::RED && node->parent->parent == node)
		{
			// 如果是红节点，且祖父节点等于自己，那么右节点即为解答
			// 该情况发生于node为header时，注意，header的右子节点（即mostright），指向整棵树的max节点
			node = node->right;
		}
		else if (node->left != 0) // 如果有左子节点，当y
		{
			BasePtr y = node->left; // 令y指向左子节点
			while (y->right != 0) // 当y有右子节点时
			{
				y = y->right; // 一直往右子节点走到底
			}
			node = y; // 最后即为答案
		}
		else // 即非根节点，也没有左子节点
		{
			BasePtr y = node->parent; // 找出父节点
			while (node == y->left) // 当现行节点为左子节点
			{
				node = y; // 一直交替往上走，直到现行节点
				y = y->parent; // 不为左子节点
			}
			node = y; // 此时父节点即为答案
		}
	}
};

/* 正规迭代器 */
template<class value, class ref, class ptr>
struct tRBTreeIterator :public tRBTreeBaseIterator
{
#pragma region typedef
	/*
		注意，正规迭代器没有成员变量，只继承了基层迭代器的node变量
		基层迭代器的node变量是红黑树节点与迭代器连接的纽带
	*/
	typedef value											value_type;
	typedef ref												reference;
	typedef ptr												pointer;
	typedef tRBTreeIterator<value, value&, value*>		iterator;
	typedef tRBTreeIterator<value, ref, ptr>				self;
	typedef tRBTreeNodeTree<value>*							link_type;
	typedef size_t											size_type;

#pragma endregion

#pragma region 构造函数

	tRBTreeIterator() {} // default构造函数
	tRBTreeIterator(link_type x) { node = x; } // 普通构造函数
	tRBTreeIterator(const iterator& it) { node = it.node; } // copy构造函数

#pragma endregion

#pragma region 迭代器的基本操作

/* 解除引用，返回节点值 */
	reference operator*()const { return link_type(node)->value_field; }

	/* 解除引用，返回节点值 */
	pointer operator->()const { return *(operator*()); }

	/* 返回迭代器指向的节点的颜色 */
	RBTreeColor color() { return node->color; }

	/* 迭代器步进 */
	self& operator++() { increment(); return *this; }

	/* 迭代器步进 */
	self& operator++(int)
	{
		self tmp = *this;
		increment();
		return tmp;
	}

	/* 迭代器步退 */
	self& operator--()const { decrement(); return *this; }

	/* 迭代器步退 */
	self& operator--(int)
	{
		self tmp = *this;
		decrement();
		return tmp;
	}

	/* 比较两迭代器是否指向同一个节点 */
	bool operator==(const self& x)const { return x.node == node; }

	/* 比较两迭代器是否指向同一个节点 */
	bool operator!=(const self& x)const { return x.node != node; }

#pragma endregion
};




}

#endif //!KH_STL_TYPE_TREE_ITERATOR_H_