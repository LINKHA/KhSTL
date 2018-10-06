#ifndef KH_STL_TYPE_TREE_NODE_H_
#define KH_STL_TYPE_TREE_NODE_H_

#include "../Allocator/TypeAllocator.h"
#include "../Utility/TypeDef.h"

namespace KhSTL {
typedef bool rbTreeColorType; // �ò������Ͷ�����������ɫ
const rbTreeColorType __rb_tree_red = false; // ��ɫΪ0
const rbTreeColorType __rb_tree_black = true; // ��ɫΪ1

/* ����ڵ� */
//struct tRBTreeNodeBase {
//	typedef rbTreeColorType	ColorType; // �ڵ���ɫ
//
//};

/* ����ڵ� */
template<class _Ty>
struct tRBTreeNode{
	/* ����̳��˸���ĳ�Ա��color��parent��left��right��value_field������ʾ�ڵ��ֵ�� */
	typedef rbTreeColorType	ColorType; // �ڵ���ɫ
	ColorType color; // �ڵ���ɫ
	tRBTreeNode* parent; // ���ڵ�ָ��
	tRBTreeNode* left; // ���ӽڵ�ָ��
	tRBTreeNode* right; // ���ӽڵ�ָ��

	/*
		����ĳ���ڵ�λ�ã��ҵ�����ߵĽڵ�
		����������ڵ��λ�ã������ҵ����ź��������ߵĽڵ㣨Ҳ�����ҵ�����Сֵ�ڵ㣩
		���ؽڵ�λ��
	*/
	static tRBTreeNode* minimum(tRBTreeNode* x)
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
	static tRBTreeNode* maximum(tRBTreeNode* x)
	{
		while (x->right != 0)
		{
			x = x->right; // һֱ�������ߣ������ҵ����ڵ�
		}
		return x;
	}

	typedef tRBTreeNode<_Ty>* LinkType;

	_Ty value; // �ڵ�ֵ��
};

}

#endif // !KH_STL_TYPE_TREE_NODE_H_
