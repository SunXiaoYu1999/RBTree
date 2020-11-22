#pragma once
#include <memory>
#include <vector>
#include <string>
enum Rb_Color {
	BLACK,
	RED
};

template<class T1>
struct RbNode{
	Rb_Color		color;	// �ڵ���ɫ
	T1				key;	// �ڵ���Ϣ
	RbNode<T1>		*parent;// ���׽ڵ�
	RbNode<T1>		*left;	// ����
	RbNode<T1>		*right;	// �Һ���

	RbNode() { parent = NULL; left = NULL; right = NULL; color = Rb_Color::RED; key; }
}; 

template<class T>
class RBTree
{
public:
	RBTree();
	~RBTree();
	void		Insert(RbNode<T> *elem);
	RbNode<T>*	Delete(T data);			// ���ɹ�ɾ���򷵻���ɾ���ڵ�ָ�룬���򷵻�nil
	RbNode<T>*	null() { return nil; }	// ���ڲ����Ƿ񵽴��
private:
	RbNode<T> *nil;		// �ڱ�
	RbNode<T> *root;	// ���ڵ�

	void init();
	void left_rotate(RbNode<T>* node);		// ����
	void right_rotate(RbNode<T>* node);		// ����
	void rb_insert(RbNode<T>* elem);		// ����
	void rb_insert_fixup(RbNode<T>* elem);	// �������

	void rb_transplant(RbNode<T>* a, RbNode<T>* b);	// ������������
	void rb_delete(RbNode<T>* elem);
	void rb_delete_fixup(RbNode<T>* fix);
	RbNode<T>* tree_minimum(RbNode<T>* root);		//���Ҳ�����root������С�ڵ� 
	RbNode<T>* rb_find(T data);						// ��û�ҵ��򷵻�nil

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
void RBTree<T>::Insert(RbNode<T>* elem)
{
	rb_insert(elem);
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
	nil->color = Rb_Color::BLACK;
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
	elem->color = Rb_Color::RED;
	elem->left = nil;
	elem->right = nil;
	rb_insert_fixup(elem);
}

template<class T>
void RBTree<T>::rb_insert_fixup(RbNode<T>* elem)
{
	while (elem->parent->color == Rb_Color::RED) {
		if (elem->parent == elem->parent->parent->left) {
			RbNode<T> *tmp = elem->parent->parent->right;
			if (tmp->color == Rb_Color::RED) {
				elem->parent->color = Rb_Color::BLACK;
				elem = elem->parent->parent;
				elem->color = Rb_Color::RED;
				tmp->color = Rb_Color::BLACK;
			}
			else{
				if (elem == elem->parent->right) {
					elem = elem->parent;
					left_rotate(elem);
				}
				elem->parent->color = Rb_Color::BLACK;
				elem->parent->parent->color = Rb_Color::RED;
				right_rotate(elem->parent->parent);
			}
			
		}
		else {
			RbNode<T> *tmp = elem->parent->parent->left;
			if (tmp->color == Rb_Color::RED) {
				elem->parent->color = Rb_Color::BLACK;
				elem = elem->parent->parent;
				elem->color = Rb_Color::RED;
				tmp->color = Rb_Color::BLACK;
			}
			else{
				if (elem == elem->parent->left) {
					elem = elem->parent;
					right_rotate(elem);
				}
				elem->parent->color = Rb_Color::BLACK;
				elem->parent->parent->color = Rb_Color::RED;
				left_rotate(elem->parent->parent);
			}	
		}
	}
	root->color = Rb_Color::BLACK;
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
		tmp = tree_minimum(elem->right);		// �ҵ�elem �ĺ��
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
		if (tmp_original_color == Rb_Color::BLACK)
			rb_delete_fixup(fix);
	}
}

template<class T>
inline void RBTree<T>::rb_delete_fixup(RbNode<T>* fix)
{
	while (fix->color == Rb_Color::BLACK && fix != root) {
		if (fix = fix->parent->left) {
			RbNode<T>* tmp = fix->parent->right;
			if (tmp->color == Rb_Color::RED) {
				fix->parent->color = Rb_Color::RED;
				tmp->color = Rb_Color::BLACK;
				left_rotate(fix->parent);
			}
			else {
				if (tmp->left->color == Rb_Color::BLACK && tmp->right->color == Rb_Color::BLACK) {
					tmp->color = Rb_Color::RED;
					fix = fix->parent;
				}else {
					if (tmp->right->color == Rb_Color::BLACK) {
						tmp->left->color = Rb_Color::BLACK;
						tmp->color = Rb_Color::RED;
						right_rotate(tmp);
						tmp = fix->parent->right;
					}
					tmp->color = fix->parent->color;
					fix->parent->color = Rb_Color::BLACK;
					tmp->right->color = Rb_Color::BLACK;
					left_rotate(fix->parent);
					fix = root;				// �˳�ѭ����־
				}
			}
		}
		else {
			RbNode<T>* tmp = fix->parent->left;
			if (tmp->color == Rb_Color::RED) {
				fix->parent->color = Rb_Color::RED;
				tmp->color = Rb_Color::BLACK;
				right_rotate(fix->parent);
			}
			else {
				if (tmp->right->color == Rb_Color::BLACK && tmp->left->color == Rb_Color::BLACK) {
					tmp->color = Rb_Color::RED;
					fix = fix->parent;
				}
				else {
					if (tmp->left->color == Rb_Color::BLACK) {
						tmp->right->color = Rb_Color::BLACK;
						tmp->color = Rb_Color::RED;
						left_rotate(tmp);
						tmp = fix->parent->left;
					}
					tmp->color = fix->parent->color;
					fix->parent->color = Rb_Color::BLACK;
					tmp->left->color = Rb_Color::BLACK;
					right_rotate(fix->parent);
					fix = root;				// �˳�ѭ����־
				}
			}
		}
	 }
	fix->color = Rb_Color::BLACK;
}

template<class T>
inline RbNode<T>* RBTree<T>::tree_minimum(RbNode<T>* root)
{
	if (root) {
		RbNode<T>* res		= root;
		RbNode<T>* resPar	= root;
		while (res != nil) {
			resPar	= res;
			res		= res->left;
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
