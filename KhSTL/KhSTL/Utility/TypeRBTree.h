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

template<typename _Traits
	,typename _Comp
	,typename _Alloc>
	class RBTree : public tRBTreeAlloc<_Traits, _Comp, _Alloc>
{
protected:
	using KeyType = typename _Traits::KeyType;

	using ValueType = typename _Traits::ValueType;

	using Compare = _Comp;

	using ColorType = RBTreeColorType; 

	using Base = tRBTreeAlloc<_Traits, _Comp, _Alloc>;

	using Alloc = tRBTreeAlloc<_Traits, _Comp, _Alloc>;

	using Iterator = tRBTreeIterator<_Traits>;

	using ConstIterator = const tRBTreeIterator<_Traits>;

	using NodeType = typename Alloc::NodeType;
public:
	/**
	* @brief : Constructed
	*/
	RBTree() 
		: _count(0)
		, _comp(Compare())
	{ 
		_header = Alloc::getNode();
		getColor(_header) = RBTreeColorType::RED;
		root() = 0;
		leftmost() = _header;
		rightmost() = _header;
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
	NodeType*& root()const 
	{ 
		return (NodeType*&)_header->parent; 
	}
	/**
	* @brief : Get the leftmost node
	*/
	NodeType*& leftmost()const 
	{ 
		return (NodeType*&)_header->left; 
	}
	/**
	* @brief : Get the rightmost node
	*/
	NodeType*& rightmost()const 
	{ 
		return (NodeType*&)_header->right; 
	}
	/**
	* @brief : Returns the left child node of the node
	*/
	NodeType*& left(NodeType* node)
	{ 
		return (NodeType*&)(node->left);
	}
	/**
	* @brief : Returns the right child node of the node
	*/
	NodeType*& right(NodeType* node)
	{ 
		return (NodeType*&)(node->right);
	}
	/**
	* @brief : Returns the parent node of the node
	*/
	NodeType*& parent(NodeType* node)
	{ 
		return (NodeType*&)(node->parent);
	}
	KeyType& getKey(NodeType* node)
	{
		return node->key;
	}
	/**
	* @brief : Returns the value of the node
	*/
	ValueType& getValue(NodeType* node)
	{
		return node->value;
	}

	/**
	* @brief : Returns the color of the node
	*/
	ColorType& getColor(NodeType* node)
	{ 
		return (ColorType&)(node->color);
	}

	/**
	* @brief : Return minimum node
	*/
	NodeType* minimum(NodeType* node)
	{
		return (NodeType*)NodeType::Minimum(node);
	}
	/**
	* @brief : Return maximum node
	*/
	NodeType* maximum(NodeType* node)
	{
		return (NodeType*)NodeType::Maximum(node);
	}

public:
	/**
	* @brief : Get the value of the root node
	*/
	ValueType RootValue()
	{ 
		return getValue((NodeType*)_header->parent); 
	}
	/**
	* @brief : Return a function that compares the size
	*/
	Compare KeyComp()const
	{
		return _comp;
	}
	/**
	* @brief : Return leftmost iterator
	*/
	inline Iterator Begin() { return leftmost(); }
	/**
	* @brief : Return leftmost const iterator
	*/
	inline ConstIterator Begin() const { return leftmost(); }
	/**
	* @brief : Return head iterator
	*/
	inline Iterator End() { return _header; }
	/**
	* @brief : Return head const iterator
	*/
	inline ConstIterator End() const { return _header; }
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
	/**
	* @brief : Insert new value, node key value cannot be repeated, 
	*			insert invalid if repeated
	*/
	tPair<Iterator, bool> InsertUnique(const KeyType& key,const ValueType& value)
	{
		NodeType* y = _header; 
		NodeType* x = root(); 
		bool comp = true; 

		while (x != 0) 
		{
			y = x; 
			comp = _comp(key, getKey(x));
			x = comp ? left(x) : right(x);
		}
		Iterator j = Iterator(y);
		if (comp)
		{
			if (Begin() == j)
			{
				return tPair<Iterator, bool>(insertNode(x, y, key ,value), true);
			}
			else
			{
				j--;
			}
		}
		if (_comp(getKey(j.node), key))
		{
			return tPair<Iterator, bool>(insertNode(x, y, key, value), true);
		}
		return tPair<Iterator, bool>(j, false);
	}
	/**
	* @brief : Insert a new value, the node's key value allows repetition
	*/
	Iterator InsertEqual(const KeyType& key, const ValueType& value)
	{
		NodeType* y = _header;
		NodeType* x = root();
		while (x != 0)
		{
			y = x;
			x = _comp(key, getKey(x)) ? left(x) : right(x);
		}
		return insertNode(x, y, key, value);
	}
	/**
	* @brief : Look for a node in a red-black tree with a key value of key
	*/
	Iterator Find(const KeyType& key)
	{
		NodeType* y = _header; 
		NodeType* x = root(); 
		while (x != 0)
		{
			if (!_comp(getKey(x), key))
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
		return (j == End() || _comp(key, getKey(j.node))) ? End() : j;
	}

private:
	/**
	* @brief : Insert node
	* @param : insertWith : To insert node 
	*		 : insertTarget : Insert the parent node of the node
	*/
	Iterator insertNode(NodeType* insertWith, NodeType* insertTarget, const KeyType& key , const ValueType& value)
	{
		NodeType* tmpWith = (NodeType*)insertWith; 
		NodeType* tmpTarget = (NodeType*)insertTarget; 
		NodeType* tmp;

		if (tmpTarget == _header || tmpWith != 0 || _comp(key, getKey(tmpTarget)))
		{
			tmp = Alloc::getNode(key,value);
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
			tmp = Alloc::getNode(key,value);
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
	void RBTreeRebalance(NodeType* value, NodeType*& root)
	{
		value->color = RBTreeColorType::RED;
		while (value != root && value->parent->color == RBTreeColorType::RED)
		{
			if (value->parent == value->parent->parent->left)
			{
				NodeType* y = value->parent->parent->right;
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
				NodeType* y = value->parent->parent->left;
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
	void RBTreeRotateLeft(NodeType* x, NodeType*& root)
	{
		NodeType* y = x->right;
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
	void RBTreeRotateRight(NodeType* value, NodeType*& root)
	{
		NodeType* y = value->left;
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

protected:
	/// Red black tree count
	unsigned _count;
	NodeType* _header;
	Compare _comp;

};

}

#endif // !KH_STL_TYPE_RED_BLACK_TREE_H_
