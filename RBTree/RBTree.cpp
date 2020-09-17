//#include "RBTree.h"
//
//template<class T>
//inline RBTree<T>::RBTree()
//{
//	init();
//}
//
//template<class T>
//RBTree<T>::~RBTree()
//{
//	delete nil;
//}
//
//template<class T>
//void RBTree<T>::Insert(RbNode<T>* elem)
//{
//	rb_insert(elem);
//}
//
//template<class T>
//void RBTree<T>::init()
//{
//	nil = new RBTree<T>;
//	nil->color = Rb_Color::BLACK;
//	root = nil;
//	root->parent = nil;
//}
//
//template<class T>
//void RBTree<T>::left_rotate(RbNode<T>* node)
//{
//	if (node->right != nil) {
//		RbNode<T>* tmp = node->right;
//		node->right = tmp->left;
//		if (tmp->left != nil)
//			tmp->left->parent = node;
//		tmp->parent = node->parent;
//		if (node->parent == nil)
//			root = tmp;
//		else if (node->parent->left == node)
//			node->parent->left = tmp;
//		else
//			node->parent->right = tmp;
//		node->parent = tmp;
//		tmp->left = node;
//	}
//}
//
//template<class T>
//void RBTree<T>::right_rotate(RbNode<T>* node)
//{
//	if (node->left != nil) {
//		RbNode<T>* tmp = node->left;
//		node->left = tmp->right;
//		if (tmp->right != nil)
//			tmp->right->parent = node;
//		tmp->parent = node->parent;
//		if (node->parent == nil)
//			root = tmp;
//		else if (node->parent->left == node)
//			node->parent->left = tmp;
//		else
//			node->parent->right = tmp;
//		node->parent = tmp;
//		tmp->left = node;
//	}
//}
//
//template<class T>
//void RBTree<T>::rb_insert(RbNode<T>	*elem)
//{
//	RbNode<T>* cur = root, * tmp = nil;
//	while (cur != nil) {
//		tmp = cur;
//		if (cur->key < elem->key)
//			cur = cur->right;
//		else
//			cur = cur->left;
//	}
//	elem->parent = tmp;
//	if (tmp == nil)
//		root = elem;
//	else if (tmp->key > elem->key)
//		tmp->left = elem;
//	else
//		tmp->right = elem;
//	elem->color = Rb_Color::RED;
//	elem->left = nil;
//	elem->right = nil;
//	rb_insert_fixup(elem);
//}
//
//template<class T>
//void RBTree<T>::rb_insert_fixup(RbNode<T>* elem)
//{
//	while (elem->parent->color == Rb_Color::RED) {
//		if (elem->parent == elem->parent->parent->left) {
//			RbNode<T> tmp = elem->parent->parent->right;
//			if (tmp->color == Rb_Color::RED) {
//				elem->parent->color = Rb_Color::BLACK;
//				elem = elem->parent->parent;
//				elem->color = Rb_Color::RED;
//				tmp->color = Rb_Color::BLACK;
//			}
//			else if (elem == elem->parent->right) {
//				elem = elem->parent;
//				left_rotate(elem);
//			}
//			elem->parent->color = Rb_Color::BLACK;
//			elem->parent->parent->color = Rb_Color::RED;
//			right_rotate(elem->parent->parent);
//		}else {
//			RbNode<T> tmp = elem->parent->parent->left;
//			if (tmp->color == Rb_Color::RED) {
//				elem->parent->color = Rb_Color::BLACK;
//				elem = elem->parent->parent;
//				elem->color = Rb_Color::RED;
//				tmp->color = Rb_Color::BLACK;
//			}
//			else if (elem == elem->parent->left) {
//				elem = elem->parent;
//				right_rotate(elem);
//			}
//			elem->parent->color = Rb_Color::BLACK;
//			elem->parent->parent->color = Rb_Color::RED;
//			left_rotate(elem->parent->parent);
//		}
//	}
//}
