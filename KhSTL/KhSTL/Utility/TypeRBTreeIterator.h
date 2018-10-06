#ifndef KH_STL_TYPE_TREE_ITERATOR_H_
#define KH_STL_TYPE_TREE_ITERATOR_H_

#include "TypeTreeNode.h"
#include <iterator>

namespace KhSTL {

	/* ��������� */
	template<typename _Ty>
	struct tRBTreeBaseIterator
	{
		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef ptrdiff_t							difference_type;

		tRBTreeNode<_Ty>* node; // ��Ա������ָ����ڵ��ָ�룬������ϵ�������ͽڵ��Ŧ��

		/* ������������ʵ��operator++ʱ���ñ����� */
		void increment()
		{
			if (node->right != 0) // ��������ӽڵ�
			{
				node = node->right; // ��������
				while (node->left != 0) // Ȼ��һֱ���������ߵ���
				{
					node = node->left;
				}
			}
			else // û�����ӽڵ�
			{
				tRBTreeNode<_Ty>* y = node->parent; // �ҳ����ڵ�
				while (node == y->right) // ������нڵ㱾���Ǹ����ӽڵ�
				{
					node = y; // ��һֱ���ݣ�ֱ������Ϊ���ӽڵ㡱Ϊֹ
					y = y->parent;
				}
				if (node->right != y) // ����ʱ�����ӽڵ㲻���ڴ�ʱ�ĸ��ڵ㣬��ʱ�ĸ��ڵ㼴Ϊ���
				{					  // �����ʱ��nodeΪ���
					node = y;
				}
			}
		}

		/* ������������ʵ��operator--ʱ���ñ����� */
		void decrement()
		{
			if (node->color == __rb_tree_red && node->parent->parent == node)
			{
				// ����Ǻ�ڵ㣬���游�ڵ�����Լ�����ô�ҽڵ㼴Ϊ���
				// �����������nodeΪheaderʱ��ע�⣬header�����ӽڵ㣨��mostright����ָ����������max�ڵ�
				node = node->right;
			}
			else if (node->left != 0) // ��������ӽڵ㣬��y
			{
				tRBTreeNode<_Ty>* y = node->left; // ��yָ�����ӽڵ�
				while (y->right != 0) // ��y�����ӽڵ�ʱ
				{
					y = y->right; // һֱ�����ӽڵ��ߵ���
				}
				node = y; // ���Ϊ��
			}
			else // ���Ǹ��ڵ㣬Ҳû�����ӽڵ�
			{
				tRBTreeNode<_Ty>* y = node->parent; // �ҳ����ڵ�
				while (node == y->left) // �����нڵ�Ϊ���ӽڵ�
				{
					node = y; // һֱ���������ߣ�ֱ�����нڵ�
					y = y->parent; // ��Ϊ���ӽڵ�
				}
				node = y; // ��ʱ���ڵ㼴Ϊ��
			}
		}
	};

	/* ��������� */
	template<class _Ty, class ref, class ptr>
	struct tRBTreeIterator :public tRBTreeBaseIterator<_Ty>
	{
#pragma region typedef
		/*
			ע�⣬���������û�г�Ա������ֻ�̳��˻����������node����
			�����������node�����Ǻ�����ڵ�����������ӵ�Ŧ��
		*/
		using Base = tRBTreeBaseIterator<_Ty>;
		typedef _Ty											value_type;
		typedef ref												reference;
		typedef ptr												pointer;
		typedef tRBTreeIterator<_Ty, _Ty&, _Ty*>		iterator;
		typedef tRBTreeIterator<_Ty, ref, ptr>				self;
		typedef tRBTreeNode<_Ty>*							link_type;
		typedef size_t											size_type;

#pragma endregion

#pragma region ���캯��

		tRBTreeIterator() {} // default���캯��
		tRBTreeIterator(link_type x) { Base::node = x; } // ��ͨ���캯��
		tRBTreeIterator(const iterator& it) { Base::node = it.node; } // copy���캯��

#pragma endregion

#pragma region �������Ļ�������

/* ������ã����ؽڵ�ֵ */
		reference operator*()const { return link_type(Base::node)->value; }

		/* ������ã����ؽڵ�ֵ */
		pointer operator->()const { return *(operator*()); }

		/* ���ص�����ָ��Ľڵ����ɫ */
		rbTreeColorType color() { return Base::node->color == __rb_tree_red ? 0 : 1; }

		/* ���������� */
		self& operator++() { Base::increment(); return *this; }

		/* ���������� */
		self& operator++(int)
		{
			self tmp = *this;
			Base::increment();
			return tmp;
		}

		/* ���������� */
		self& operator--()const { Base::decrement(); return *this; }

		/* ���������� */
		self& operator--(int)
		{
			self tmp = *this;
			Base::decrement();
			return tmp;
		}

		/* �Ƚ����������Ƿ�ָ��ͬһ���ڵ� */
		bool operator==(const self& x)const { return x.node == Base::node; }

		/* �Ƚ����������Ƿ�ָ��ͬһ���ڵ� */
		bool operator!=(const self& x)const { return x.node != Base::node; }

#pragma endregion
	};



}

#endif //!KH_STL_TYPE_TREE_ITERATOR_H_