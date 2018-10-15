#ifndef KH_STL_TYPE_TREE_ITERATOR_H_
#define KH_STL_TYPE_TREE_ITERATOR_H_

#include "TypeTreeNode.h"
#include <iterator>

namespace KhSTL {

template<typename _Ty>
struct tRBTreeBaseIterator
{
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef ptrdiff_t							difference_type;

	tRBTreeNode<_Ty>* node;

	/**
	* @brief : This function is called when subclasses of the iterator implement operator 
	*/
	void increment()
	{
		if (node->right != 0)
		{
			node = node->right;
			while (node->left != 0)
			{
				node = node->left;
			}
		}
		else
		{
			tRBTreeNode<_Ty>* y = node->parent;
			while (node == y->right)
			{
				node = y;
				y = y->parent;
			}
			if (node->right != y)
			{
				node = y;
			}
		}
	}
	/**
	* @brief : This function is called when subclasses of the iterator implement operator --
	*/
	void decrement()
	{
		if (node->color == __rb_tree_red && node->parent->parent == node)
		{
			node = node->right;
		}
		else if (node->left != 0)
		{
			tRBTreeNode<_Ty>* y = node->left;
			while (y->right != 0)
			{
				y = y->right;
			}
			node = y;
		}
		else
		{
			tRBTreeNode<_Ty>* y = node->parent;
			while (node == y->left)
			{
				node = y;
				y = y->parent;
			}
			node = y; 
		}
	}
};

template<class _Ty, class ref, class ptr>
struct tRBTreeIterator :public tRBTreeBaseIterator<_Ty>
{

	using Base = tRBTreeBaseIterator<_Ty>;
	typedef _Ty											value_type;
	typedef ref												reference;
	typedef ptr												pointer;
	typedef tRBTreeIterator<_Ty, _Ty&, _Ty*>		iterator;
	using This = tRBTreeIterator<_Ty, ref, ptr>;
	typedef tRBTreeNode<_Ty>*							link_type;
	typedef size_t											size_type;

	tRBTreeIterator() {}
	tRBTreeIterator(link_type x) { Base::node = x; }
	tRBTreeIterator(const iterator& it) { Base::node = it.node; }
	/**
	* @brief : Dereference, return node value
	*/
	reference operator *()const { return link_type(Base::node)->value; }
	/**
	* @brief : Dereference, return node value
	*/
	pointer operator ->()const { return *(operator *()); }
	/**
	* @brief : Returns the color of the node the iterator points to
	*/
	rbTreeColorType color() { return Base::node->color == __rb_tree_red ? 0 : 1; }
	/**
	* @brief : Iterator stepIterator step
	*/
	This& operator ++() { Base::increment(); return *this; }
	/**
	* @brief : Iterator step
	*/
	This& operator ++(int)
	{
		This tmp = *this;
		Base::increment();
		return tmp;
	}
	/**
	* @brief : Iterator step
	*/
	This& operator --()const { Base::decrement(); return *this; }
	/**
	* @brief : Iterator step
	*/
	This& operator --(int)
	{
		This tmp = *this;
		Base::decrement();
		return tmp;
	}
	/**
	* @brief : Comparison of two iterators
	*/
	bool operator ==(const This& x)const { return x.node == Base::node; }

	/**
	* @brief : Comparison of two iterators
	*/
	bool operator !=(const This& x)const { return x.node != Base::node; }
};



}

#endif //!KH_STL_TYPE_TREE_ITERATOR_H_