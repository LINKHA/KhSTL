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

	using color_type = RBTreeColorType; 

	using Base = tRBTreeAlloc<tRBTreeNode<_Kty>, _Kty, _Comp, _Alloc>;

	using Alloc = tRBTreeAlloc<tRBTreeNode<_Kty>, _Kty, _Comp, _Alloc>;

protected:

	/// Red black tree count
	unsigned _count; 
	tRBTreeNode<ValueType>* _header;
	_Comp _comp;

public:
	typedef tRBTreeIterator<ValueType, ValueType&, ValueType*> Iterator;
	typedef const tRBTreeIterator<ValueType, ValueType&, ValueType*> ConstIterator;

private:
	/**
	* @brief : Init red and black tree
	*/
	void init()
	{
		_header = Alloc::getNode();
		GetColor(_header) = RBTreeColorType::RED;
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
		return (tRBTreeNode<ValueType>*)tRBTreeNode<ValueType>::Minimum(x);
	}
	/**
	* @brief : Return maximum node
	*/
	static tRBTreeNode<ValueType>* maximum(tRBTreeNode<ValueType>* x)
	{
		return (tRBTreeNode<ValueType>*)tRBTreeNode<ValueType>::Maximum(x); 
	}

public:
	/**
	* @brief : Get the value of the root node
	*/
	ValueType RootValue() 
	{ 
		return GetValue((tRBTreeNode<ValueType>*)_header->parent); 
	}
	/**
	* @brief : Return a function that compares the size
	*/
	_Comp KeyComp()const 
	{
		return _comp;
	}
	/**
	* @brief : Return leftmost iterator
	*/
	Iterator Begin() 
	{ 
		return leftmost(); 
	}
	/**
	* @brief : Return head iterator
	*/
	Iterator End() { return _header; }
	/**
	* @brief : To determine if the red-black tree is Empty
	*/
	bool Empty()const 
	{ 
		return _count == 0; 
	}
	/**
	* @brief : Retrurn tree count
	*/
	unsigned GetSize() const 
	{ 
		return _count; 
	}


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
		tRBTreeNode<ValueType>* tmpWith = (tRBTreeNode<ValueType>*)insertWith; 
		tRBTreeNode<ValueType>* tmpTarget = (tRBTreeNode<ValueType>*)insertTarget; 
		tRBTreeNode<ValueType>* tmp;

		if (tmpTarget == _header || tmpWith != 0 || _comp(v, GetValue(tmpTarget)))
		{
			tmp = Alloc::getNode(v); 
			left(tmpTarget) = tmp; 
			if (tmpTarget == _header) 
			{
				root() = tmp;
				rightmost() = tmp;
			}
			else if (tmpTarget == leftmost())
			{
				leftmost() = tmp;
			}
		}
		else
		{
			tmp = Alloc::getNode(v);
			right(tmpTarget) = tmp;
			if (tmpTarget == rightmost())
			{
				rightmost() = tmp;
			}
		}
		parent(tmp) = tmpTarget;
		left(tmp) = 0;
		right(tmp) = 0;

		RBTreeRebalance(tmp, _header->parent);
		++_count;
		return Iterator(tmp);
	}
	/**
	* @brief : Rebalance the red-black tree
	*/
	void RBTreeRebalance(tRBTreeNode<ValueType>* value, tRBTreeNode<ValueType>*& root)
	{
		value->color = RBTreeColorType::RED;
		while (value != root && value->parent->color == RBTreeColorType::RED)
		{
			if (value->parent == value->parent->parent->left)
			{
				tRBTreeNode<ValueType>* y = value->parent->parent->right;
				if (y && y->color == RBTreeColorType::RED)
				{
					value->parent->color = RBTreeColorType::BLACK;
					y->color = RBTreeColorType::BLACK;
					value->parent->parent->color = RBTreeColorType::RED;
					value = value->parent->parent;
				}
				else
				{
					if (value == value->parent->right)
					{
						value = value->parent;
						RBTreeRotateLeft(value, root);
					}
					value->parent->color = RBTreeColorType::BLACK;
					value->parent->parent->color = RBTreeColorType::RED;
					RBTreeRotateRight(value->parent->parent, root);
				}
			}
			else 
			{
				tRBTreeNode<ValueType>* y = value->parent->parent->left;
				if (y && y->color == RBTreeColorType::RED)
				{
					value->parent->color = RBTreeColorType::BLACK;
					y->color = RBTreeColorType::BLACK;
					value->parent->parent->color = RBTreeColorType::RED;
					value = value->parent->parent;
				}
				else
				{
					
					if (value == value->parent->left)
					{
						value = value->parent;
						RBTreeRotateRight(value, root);
					}
					value->parent->color = RBTreeColorType::BLACK;
					value->parent->parent->color = RBTreeColorType::RED;
					RBTreeRotateLeft(value->parent->parent, root); 
				}
			}
		}
		root->color = RBTreeColorType::BLACK;
	}
	/**
	* @brief : Light handed rotation 
	*/
	void RBTreeRotateLeft(tRBTreeNode<ValueType>* x, tRBTreeNode<ValueType>*& root)
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
	void RBTreeRotateRight(tRBTreeNode<ValueType>* value, tRBTreeNode<ValueType>*& root)
	{
		tRBTreeNode<ValueType>* y = value->left;
		value->left = y->right;
		if (y->right != 0)
		{
			y->right->parent = value;
		}
		y->parent = value->parent;
		if (value == root)
		{
			root = y;
		}
		else if (value == value->parent->right)
		{
			value->parent->right = y;
		}
		else
		{
			value->parent->left = y;
		}
		y->right = value;
		value->parent = y;
	}
};

}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_H_
