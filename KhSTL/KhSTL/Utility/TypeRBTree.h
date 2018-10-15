#ifndef KH_STL_TYPE_RED_BLACK_TREE_H_
#define KH_STL_TYPE_RED_BLACK_TREE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"
#include "../Utility/TypeTreeNode.h"
#include "../Utility/TypeRBTreeIterator.h"
#include "../Utility/TypePair.h"
#include "TypeRBTreeAlloc.h"

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>

namespace KhSTL{

template<typename _Kty
	, typename _Comp
	, typename _Alloc = tAllocator<tRBTreeNode<_Kty>>>
	class RBTree : public tRBTreeAlloc<tRBTreeNode<_Kty>, _Kty, _Comp, _Alloc>
{

protected:
	using ValueType = _Kty;

	using color_type = rbTreeColorType; 

	using Base = tRBTreeAlloc<tRBTreeNode<_Kty>, _Kty, _Comp, _Alloc>;

	using Alloc = tRBTreeAlloc<tRBTreeNode<_Kty>, _Kty, _Comp, _Alloc>;

protected:

	/// Red black tree count
	unsigned _count; 
	tRBTreeNode<ValueType>* _header;
	_Comp _comp;

public:
	typedef tRBTreeIterator<ValueType, ValueType&, ValueType*> Iterator; 
	typedef const tRBTreeIterator<ValueType, ValueType&, ValueType*> const_iterator; 

private:
	/**
	* @brief : Init red and black tree
	*/
	void init()
	{
		_header = Alloc::getNode();
		GetColor(_header) = __rb_tree_red;
		root() = 0;
		leftmost() = _header;
		rightmost() = _header;
	}

public:
	/**
	* @brief : Constructed
	*/
	RBTree() 
		: _count(0)
		, _comp(_Comp())
	{ 
		init(); 
	}
	/**
	* @brief : Destructing
	*/
	~RBTree()
	{
		Alloc::putNode(_header);
	}

protected:
	/**
	* @brief : Get the root node
	*/
	tRBTreeNode<ValueType>*& root()const 
	{ 
		return (tRBTreeNode<ValueType>*&)_header->parent; 
	}
	/**
	* @brief : Get the leftmost node
	*/
	tRBTreeNode<ValueType>*& leftmost()const 
	{ 
		return (tRBTreeNode<ValueType>*&)_header->left; 
	}
	/**
	* @brief : Get the rightmost node
	*/
	tRBTreeNode<ValueType>*& rightmost()const 
	{ 
		return (tRBTreeNode<ValueType>*&)_header->right; 
	}
	/**
	* @brief : Returns the left child node of the node
	*/
	static tRBTreeNode<ValueType>*& left(tRBTreeNode<ValueType>* x) 
	{ 
		return (tRBTreeNode<ValueType>*&)(x->left); 
	}
	/**
	* @brief : Returns the right child node of the node
	*/
	static tRBTreeNode<ValueType>*& right(tRBTreeNode<ValueType>* x) 
	{ 
		return (tRBTreeNode<ValueType>*&)(x->right);
	}
	/**
	* @brief : Returns the parent node of the node
	*/
	static tRBTreeNode<ValueType>*& parent(tRBTreeNode<ValueType>* x) 
	{ 
		return (tRBTreeNode<ValueType>*&)(x->parent); 
	}
	/**
	* @brief : Returns the value of the node
	*/
	static ValueType& GetValue(tRBTreeNode<ValueType>* x) 
	{ 
		return x->value; 
	}
	/**
	* @brief : Returns the color of the node
	*/
	static color_type& GetColor(tRBTreeNode<ValueType>* x)
	{ 
		return (color_type&)(x->color); 
	}

	/**
	* @brief : Return minimum node
	*/
	static tRBTreeNode<ValueType>* minimum(tRBTreeNode<ValueType>* x)
	{
		return (tRBTreeNode<ValueType>*)tRBTreeNode<ValueType>::minimum(x);
	}
	/**
	* @brief : Return maximum node
	*/
	static tRBTreeNode<ValueType>* maximum(tRBTreeNode<ValueType>* x)
	{
		return (tRBTreeNode<ValueType>*)tRBTreeNode<ValueType>::maximum(x); 
	}

public:
	/**
	* @brief : Get the value of the root node
	*/
	ValueType RootValue() { return GetValue((tRBTreeNode<ValueType>*)_header->parent); }
	/**
	* @brief : Return a function that compares the size
	*/
	_Comp KeyComp()const { return _comp; }
	/**
	* @brief : Return leftmost iterator
	*/
	Iterator Begin() { return leftmost(); }
	/**
	* @brief : Return head iterator
	*/
	Iterator End() { return _header; }
	/**
	* @brief : To determine if the red-black tree is empty
	*/
	bool empty()const { return _count == 0; }
	/**
	* @brief : Retrurn tree count
	*/
	unsigned GetSize() const { return _count; }


public:
	/**
	* @brief : Insert new value, node key value cannot be repeated, 
	*			insert invalid if repeated
	*/
	tPair<Iterator, bool> InsertUnique(const ValueType& v)
	{
		tRBTreeNode<ValueType>* y = _header; 
		tRBTreeNode<ValueType>* x = root(); 
		bool comp = true; 

		while (x != 0) 
		{
			y = x; 
			comp = _comp(v, GetValue(x));
			x = comp ? left(x) : right(x);
		}
		Iterator j = Iterator(y);
		if (comp)
		{
			if (Begin() == j)
			{
				return tPair<Iterator, bool>(insertNode(x, y, v), true);
			}
			else
			{
				j--;
			}
		}
		if (_comp(GetValue(j.node), v))
		{
			return tPair<Iterator, bool>(insertNode(x, y, v), true);
		}
		return tPair<Iterator, bool>(j, false);
	}
	/**
	* @brief : Insert a new value, the node's key value allows repetition
	*/
	Iterator InsertEqual(const ValueType& v)
	{
		tRBTreeNode<ValueType>* y = _header;
		tRBTreeNode<ValueType>* x = root();
		while (x != 0)
		{
			y = x;
			x = _comp(v, GetValue(x)) ? left(x) : right(x);
		}
		return insertNode(x, y, v);
	}
	/**
	* @brief : Look for a node in a red-black tree with a key value of key
	*/
	Iterator Find(const ValueType& key)
	{
		tRBTreeNode<ValueType>* y = _header; 
		tRBTreeNode<ValueType>* x = root(); 
		while (x != 0)
		{
			if (!_comp(GetValue(x), key))
			{
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		Iterator j = Iterator(y);
		return (j == End() || _comp(key, GetValue(j.node))) ? End() : j;
	}
private:
	/**
	* @brief : Insert node
	* @param : insertWith : To insert node 
	*		 : insertTarget : Insert the parent node of the node
	*/
	Iterator insertNode(tRBTreeNode<ValueType>* insertWith, tRBTreeNode<ValueType>* insertTarget, const ValueType& v)
	{
		tRBTreeNode<ValueType>* x = (tRBTreeNode<ValueType>*)insertWith; 
		tRBTreeNode<ValueType>* y = (tRBTreeNode<ValueType>*)insertTarget; 
		tRBTreeNode<ValueType>* z;

		if (y == _header || x != 0 || _comp(v, GetValue(y)))
		{
			z = Alloc::getNode(v); 
			left(y) = z; 
			if (y == _header) 
			{
				root() = z;
				rightmost() = z;
			}
			else if (y == leftmost())
			{
				leftmost() = z;
			}
		}
		else
		{
			z = Alloc::getNode(v);
			right(y) = z;
			if (y == rightmost())
			{
				rightmost() = z;
			}
		}
		parent(z) = y;
		left(z) = 0;
		right(z) = 0;

		__rb_tree_rebalance(z, _header->parent);
		++_count;
		return Iterator(z);
	}
	/**
	* @brief : Rebalance the red-black tree
	*/
	inline void __rb_tree_rebalance(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
	{
		x->color = __rb_tree_red;
		while (x != root && x->parent->color == __rb_tree_red)
		{
			if (x->parent == x->parent->parent->left)
			{
				tRBTreeNode<ValueType>* y = x->parent->parent->right;
				if (y && y->color == __rb_tree_red)
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						__rb_tree_rotate_left(x, root);
					}
					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__rb_tree_rotate_right(x->parent->parent, root);
				}
			}
			else 
			{
				tRBTreeNode<ValueType>* y = x->parent->parent->left;
				if (y && y->color == __rb_tree_red)
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else
				{
					
					if (x == x->parent->left)
					{
						x = x->parent;
						__rb_tree_rotate_right(x, root);
					}
					x->parent->color = __rb_tree_black; 
					x->parent->parent->color = __rb_tree_red; 
					__rb_tree_rotate_left(x->parent->parent, root); 
				}
			}
		}
		root->color = __rb_tree_black;
	}
	/**
	* @brief : Light handed rotation 
	*/
	inline void __rb_tree_rotate_left(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
	{
		tRBTreeNode<ValueType>* y = x->right;
		x->right = y->left;
		if (y->left != 0)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;

		if (x == root)
		{
			root = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	/**
	* @brief : Right handed rotation 
	*/
	inline void __rb_tree_rotate_right(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
	{
		tRBTreeNode<ValueType>* y = x->left;
		x->left = y->right;
		if (y->right != 0)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x == root)
		{
			root = y;
		}
		else if (x == x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
};

}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_H_
