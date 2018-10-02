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
	using ColorType = RBTreeColor; // �ڵ���ɫ
	using BasePtr = tRBTreeNodeTreeBase*; // �ڵ�ָ��

	RBTreeColor color; // �ڵ���ɫ
	BasePtr parent; // ���ڵ�ָ��
	BasePtr left; // ���ӽڵ�ָ��
	BasePtr right; // ���ӽڵ�ָ��

	/*
		����ĳ���ڵ�λ�ã��ҵ�����ߵĽڵ�
		����������ڵ��λ�ã������ҵ����ź��������ߵĽڵ㣨Ҳ�����ҵ�����Сֵ�ڵ㣩
		���ؽڵ�λ��
	*/
	BasePtr minimum(BasePtr x)
	{
		while (x->left != 0)
		{
			x = x->left; // һֱ�����ߣ������ҵ���С�ڵ�
		}
		return x;
	}

	/*
		����ĳ���ڵ�λ�ã��ҵ����ұߵĽڵ�
		����������ڵ��λ�ã������ҵ����ź�������ұߵĽڵ㣨Ҳ�����ҵ������ֵ�ڵ㣩
		���ؽڵ�λ��
	*/
	BasePtr maximum(BasePtr x)
	{
		while (x->right != 0)
		{
			x = x->right; // һֱ�������ߣ������ҵ����ڵ�
		}
		return x;
	}
};

/* ����ڵ� */
template<typename _Ty>
struct tRBTreeNodeTree : public tRBTreeNodeTreeBase 
{
	using LinkType = tRBTreeNodeTree<_Ty>*;
	_Ty value; // �ڵ�ֵ��
};

}

#endif // !KH_STL_TYPE_TREE_NODE_H_
