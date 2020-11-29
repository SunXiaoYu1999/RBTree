#pragma once
#include <memory>
#include <vector>
#include <string>
#include <share.h>
namespace sy {

	enum class Rb_Color {
		SYBLACK = 0,
		SYRED
	};

	template<class T1>
	struct RbNode {
		Rb_Color		color;	// 节点颜色
		T1				key;	// 节点信息
		RbNode<T1>* parent;// 父亲节点
		RbNode<T1>* left;	// 左孩子
		RbNode<T1>* right;	// 右孩子

		RbNode() { parent = NULL; left = NULL; right = NULL; color = Rb_Color::SYRED; key; }

		template<class T>
		RbNode(T elem) { parent = NULL; left = NULL; right = NULL; color = Rb_Color::SYRED; key = elem; }
	};


	class lab_3;
	template<class T>
	class RBTree
	{
		friend class lab_3;

	public:
		RBTree();
		~RBTree();
		bool	   Find(T elem);
		void	   Insert(RbNode<T>* elem);
		void	   Insert(T elem);
		RbNode<T>* Delete(T data);			// 若成功删除则返回已删除节点指针，否则返回nil
		RbNode<T>* null() { return nil; }	// 用于测试是否到达空
	private:
		RbNode<T>* nil;		// 哨兵
		RbNode<T>* root;	// 根节点

		void init();
		void left_rotate(RbNode<T>* node);		// 左旋
		void right_rotate(RbNode<T>* node);		// 右旋
		void rb_insert(RbNode<T>* elem);		// 插入
		void rb_insert_fixup(RbNode<T>* elem);	// 插入调整

		void rb_transplant(RbNode<T>* a, RbNode<T>* b);	// 交换两棵子树
		void rb_delete(RbNode<T>* elem);
		void rb_delete_fixup(RbNode<T>* fix);
		RbNode<T>* tree_minimum(RbNode<T>* root);		//查找并返回root树的最小节点 
		RbNode<T>* rb_find(T data);						// 若没找到则返回nil

	};

	template<class T>
	inline RBTree<T>::RBTree()
	{
		init();
	}

	template<class T>
	RBTree<T>::~RBTree()
	{
		delete nil;
	}

	template<class T>
	inline bool RBTree<T>::Find(T elem)
	{
		RbNode<T>* tmp = root;
		while (tmp != nil) {
			if (tmp->key == elem)
				return true;
			else if (tmp->key < elem) {
				tmp = tmp->right;
			}
			else {
				tmp = tmp->left;
			}
		}
		return false;
	}

	template<class T>
	void RBTree<T>::Insert(RbNode<T>* elem)
	{
		rb_insert(elem);
	}

	template<class T>
	void RBTree<T>::Insert(T elem)
	{
		RbNode<T>* ptr = new RbNode<T>(elem);
		Insert(ptr);
	}

	template<class T>
	inline RbNode<T>* RBTree<T>::Delete(T data)
	{
		RbNode<T>* tmp = rb_find(data);
		if (tmp != nil) {
			rb_delete(tmp);
		}
		return tmp;
	}

	template<class T>
	void RBTree<T>::init()
	{
		nil = new RbNode<T>;
		nil->color = Rb_Color::SYBLACK;
		root = nil;
		root->parent = nil;
		root->left = nil;
		root->right = nil;
	}

	template<class T>
	void RBTree<T>::left_rotate(RbNode<T>* node)
	{
		if (node->right != nil) {
			RbNode<T>* tmp = node->right;
			node->right = tmp->left;
			if (tmp->left != nil)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (node->parent == nil)
				root = tmp;
			else if (node->parent->left == node)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			node->parent = tmp;
			tmp->left = node;
		}
	}

	template<class T>
	void RBTree<T>::right_rotate(RbNode<T>* node)
	{
		if (node->left != nil) {
			RbNode<T>* tmp = node->left;
			node->left = tmp->right;
			if (tmp->right != nil)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (node->parent == nil)
				root = tmp;
			else if (node->parent->left == node)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			node->parent = tmp;
			tmp->right = node;
		}
	}

	template<class T>
	void RBTree<T>::rb_insert(RbNode<T>* elem)
	{
		RbNode<T>* cur = root, * tmp = nil;
		while (cur != nil) {
			tmp = cur;
			if (cur->key < elem->key)
				cur = cur->right;
			else
				cur = cur->left;
		}
		elem->parent = tmp;
		if (tmp == nil)
			root = elem;
		else if (tmp->key > elem->key)
			tmp->left = elem;
		else
			tmp->right = elem;
		elem->color = Rb_Color::SYRED;
		elem->left = nil;
		elem->right = nil;
		rb_insert_fixup(elem);
	}

	template<class T>
	void RBTree<T>::rb_insert_fixup(RbNode<T>* elem)
	{
		while (elem->parent->color == Rb_Color::SYRED) {
			if (elem->parent == elem->parent->parent->left) {
				RbNode<T>* tmp = elem->parent->parent->right;
				if (tmp->color == Rb_Color::SYRED) {
					elem->parent->color = Rb_Color::SYBLACK;
					elem = elem->parent->parent;
					elem->color = Rb_Color::SYRED;
					tmp->color = Rb_Color::SYBLACK;
				}
				else {
					if (elem == elem->parent->right) {
						elem = elem->parent;
						left_rotate(elem);
					}
					elem->parent->color = Rb_Color::SYBLACK;
					elem->parent->parent->color = Rb_Color::SYRED;
					right_rotate(elem->parent->parent);
				}

			}
			else {
				RbNode<T>* tmp = elem->parent->parent->left;
				if (tmp->color == Rb_Color::SYRED) {
					elem->parent->color = Rb_Color::SYBLACK;
					elem = elem->parent->parent;
					elem->color = Rb_Color::SYRED;
					tmp->color = Rb_Color::SYBLACK;
				}
				else {
					if (elem == elem->parent->left) {
						elem = elem->parent;
						right_rotate(elem);
					}
					elem->parent->color = Rb_Color::SYBLACK;
					elem->parent->parent->color = Rb_Color::SYRED;
					left_rotate(elem->parent->parent);
				}
			}
		}
		root->color = Rb_Color::SYBLACK;
	}

	template<class T>
	inline void RBTree<T>::rb_transplant(RbNode<T>* a, RbNode<T>* b)
	{
		if (nullptr != a && nullptr != b) {
			if (a->parent == nil) {
				root = b;
			}
			else if (a == a->parent->left) {
				a->parent->left = b;
			}
			else {
				a->parent->right = b;
			}
			b->parent = a->parent;
		}
	}

	template<class T>
	inline void RBTree<T>::rb_delete(RbNode<T>* elem)
	{
		RbNode<T>* tmp = elem;
		RbNode<T>* fix = nullptr;
		Rb_Color tmp_original_color = tmp->color;
		if (elem->left == nil) {
			fix = elem->right;
			rb_transplant(elem, elem->right);
		}
		else if (elem->right == nil) {
			fix = elem->left;
			rb_transplant(elem, elem->left);
		}
		else {
			tmp = tree_minimum(elem->right);		// 找到elem 的后继
			tmp_original_color = tmp->color;
			fix = tmp->right;
			if (tmp->parent == elem) {
				fix->parent = tmp;
			}
			else {
				rb_transplant(tmp, tmp->right);
				tmp->right = elem->right;
				tmp->right->parent = tmp;
			}
			rb_transplant(elem, tmp);
			tmp->left = elem->left;
			tmp->left->parent = tmp;
			tmp->color = elem->color;
		}
		if (tmp_original_color == Rb_Color::SYBLACK)
			rb_delete_fixup(fix);
	}

	template<class T>
	inline void RBTree<T>::rb_delete_fixup(RbNode<T>* fix)
	{
		while (fix->color == Rb_Color::SYBLACK && fix != root) {
			if (fix == fix->parent->left) {
				RbNode<T>* tmp = fix->parent->right;
				if (tmp->color == Rb_Color::SYRED) {
					fix->parent->color = Rb_Color::SYRED;
					tmp->color = Rb_Color::SYBLACK;
					left_rotate(fix->parent);
				}
				else {
					if (tmp->left->color == Rb_Color::SYBLACK && tmp->right->color == Rb_Color::SYBLACK) {
						tmp->color = Rb_Color::SYRED;
						fix = fix->parent;
					}
					else {
						if (tmp->right->color == Rb_Color::SYBLACK) {
							tmp->left->color = Rb_Color::SYBLACK;
							tmp->color = Rb_Color::SYRED;
							right_rotate(tmp);
							tmp = fix->parent->right;
						}
						tmp->color = fix->parent->color;
						fix->parent->color = Rb_Color::SYBLACK;
						tmp->right->color = Rb_Color::SYBLACK;
						left_rotate(fix->parent);
						fix = root;				// 退出循环标志
					}
				}
			}
			else {
				RbNode<T>* tmp = fix->parent->left;
				if (tmp->color == Rb_Color::SYRED) {
					fix->parent->color = Rb_Color::SYRED;
					tmp->color = Rb_Color::SYBLACK;
					right_rotate(fix->parent);
				}
				else {
					if (tmp->right->color == Rb_Color::SYBLACK && tmp->left->color == Rb_Color::SYBLACK) {
						tmp->color = Rb_Color::SYRED;
						fix = fix->parent;
					}
					else {
						if (tmp->left->color == Rb_Color::SYBLACK) {
							tmp->right->color = Rb_Color::SYBLACK;
							tmp->color = Rb_Color::SYRED;
							left_rotate(tmp);
							tmp = fix->parent->left;
						}
						tmp->color = fix->parent->color;
						fix->parent->color = Rb_Color::SYBLACK;
						tmp->left->color = Rb_Color::SYBLACK;
						right_rotate(fix->parent);
						fix = root;				// 退出循环标志
					}
				}
			}
		}
		fix->color = Rb_Color::SYBLACK;
	}

	template<class T>
	inline RbNode<T>* RBTree<T>::tree_minimum(RbNode<T>* root)
	{
		if (root) {
			RbNode<T>* res = root;
			RbNode<T>* resPar = root;
			while (res != nil) {
				resPar = res;
				res = res->left;
			}
			return resPar;
		}
		else {
			return nullptr;
		}
	}

	template<class T>
	inline RbNode<T>* RBTree<T>::rb_find(T data)
	{
		RbNode<T>* ans = root;
		while (ans != nil) {
			if (ans->key < data) {
				ans = ans->right;
			}
			else if (ans->key > data) {
				ans = ans->left;
			}
			else {
				break;
			}
		}
		return ans;
	}
}
