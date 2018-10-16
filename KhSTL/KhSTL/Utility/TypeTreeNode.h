#ifndef KH_STL_TYPE_TREE_NODE_H_
#define KH_STL_TYPE_TREE_NODE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"

namespace KhSTL {

enum class RBTreeColorType
{
	RED,
	BLACK
};

template<class _Ty>
class tRBTreeNode
{
public:
	using ColorType = RBTreeColorType;

	using LinkType = tRBTreeNode<_Ty>*;

public:
	tRBTreeNode() = default;

	explicit tRBTreeNode(const _Ty& svalue)
		: value(svalue)
	{}
	~tRBTreeNode() = default;
	/**
	* @brief : Find most left node
	*/
	tRBTreeNode* Minimum(tRBTreeNode* x)
	{
		while (x->left != 0)
		{
			x = x->left;
		}
		return x;
	}
	/**
	* @brief : Find most right node
	*/
	tRBTreeNode* Maximum(tRBTreeNode* x)
	{
		while (x->right != 0)
		{
			x = x->right;
		}
		return x;
	}
	///Node color
	ColorType color;
	///Node parent
	tRBTreeNode* parent;
	///Node left child
	tRBTreeNode* left;
	///Node right child
	tRBTreeNode* right;
	///Node value
	_Ty value; 
};

}

#endif // !KH_STL_TYPE_TREE_NODE_H_
