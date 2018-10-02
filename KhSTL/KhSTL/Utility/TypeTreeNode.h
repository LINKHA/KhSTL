#ifndef KH_STL_TYPE_TREE_NODE_H_
#define KH_STL_TYPE_TREE_NODE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"

namespace KhSTL {

//using TreeColorType = bool;
//const TreeColorType rbTreeRed = false; 
//const TreeColorType rbTreeBlack = true; 

enum class RBTreeColor
{
	RED,
	BLACK
};


struct tRBTreeNodeTreeBase 
{
	using ColorType = RBTreeColor; // 节点颜色
	using BasePtr = tRBTreeNodeTreeBase*; // 节点指针

	RBTreeColor color; // 节点颜色
	BasePtr parent; // 父节点指针
	BasePtr left; // 左子节点指针
	BasePtr right; // 右子节点指针

	/*
		给定某个节点位置，找到最左边的节点
		如果给定根节点的位置，可以找到整颗红黑树最左边的节点（也就是找到了最小值节点）
		返回节点位置
	*/
	BasePtr minimum(BasePtr x)
	{
		while (x->left != 0)
		{
			x = x->left; // 一直向左走，就能找到最小节点
		}
		return x;
	}

	/*
		给定某个节点位置，找到最右边的节点
		如果给定根节点的位置，可以找到整颗红黑树最右边的节点（也就是找到了最大值节点）
		返回节点位置
	*/
	BasePtr maximum(BasePtr x)
	{
		while (x->right != 0)
		{
			x = x->right; // 一直向左右走，就能找到最大节点
		}
		return x;
	}
};

/* 正规节点 */
template<typename _Ty>
struct tRBTreeNodeTree : public tRBTreeNodeTreeBase 
{
	using LinkType = tRBTreeNodeTree<_Ty>*;
	_Ty value; // 节点值域
};

}

#endif // !KH_STL_TYPE_TREE_NODE_H_
