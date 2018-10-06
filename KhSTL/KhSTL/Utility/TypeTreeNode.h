#ifndef KH_STL_TYPE_TREE_NODE_H_
#define KH_STL_TYPE_TREE_NODE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"

namespace KhSTL {
typedef bool rbTreeColorType; // 用布尔类型定义红黑树的颜色
const rbTreeColorType __rb_tree_red = false; // 红色为0
const rbTreeColorType __rb_tree_black = true; // 黑色为1

/* 基层节点 */
//struct tRBTreeNodeBase {
//	typedef rbTreeColorType	ColorType; // 节点颜色
//
//};

/* 正规节点 */
template<class _Ty>
struct tRBTreeNode{
	/* 子类继承了父类的成员：color、parent、left、right，value_field用来表示节点的值域 */
	typedef rbTreeColorType	ColorType; // 节点颜色
	ColorType color; // 节点颜色
	tRBTreeNode* parent; // 父节点指针
	tRBTreeNode* left; // 左子节点指针
	tRBTreeNode* right; // 右子节点指针

	/*
		给定某个节点位置，找到最左边的节点
		如果给定根节点的位置，可以找到整颗红黑树最左边的节点（也就是找到了最小值节点）
		返回节点位置
	*/
	static tRBTreeNode* minimum(tRBTreeNode* x)
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
	static tRBTreeNode* maximum(tRBTreeNode* x)
	{
		while (x->right != 0)
		{
			x = x->right; // 一直向左右走，就能找到最大节点
		}
		return x;
	}

	typedef tRBTreeNode<_Ty>* LinkType;

	_Ty value; // 节点值域
};

}

#endif // !KH_STL_TYPE_TREE_NODE_H_
