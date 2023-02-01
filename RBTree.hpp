/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:51:57 by cvignar           #+#    #+#             */
/*   Updated: 2022/12/12 16:51:57 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# define RED	false
# define BLACK	true
# define LEFT	false
# define RIGHT	true

namespace	ft {

template<typename T>
struct	RBNode {

	typedef T		value_type;
	typedef	RBNode*	node_pointer;

	value_type			value;
	bool				color;
	node_pointer		parent;
	node_pointer		left;
	node_pointer		right;

	RBNode() : value(), color(RED), parent(NULL), left(NULL), right(NULL) {}
	RBNode(const value_type& value, bool color = RED, RBNode* parent = NULL, RBNode* left = NULL, RBNode* right = NULL) :
	value(value), color(color), parent(parent), left(left), right(right) {}
	RBNode(const RBNode& node) :
	value(node.value), color(node.color), parent(node.parent), left(node.left), right(node.right) {}
	RBNode&	operator=(const RBNode& node) {
		value(node.value);
		color = node.color;
		parent = node.parent;
		left = node.left;
		right = node.right;
		return (*this);
	}
};

template<
	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator< RBNode<T> >
> class RBTree {
public:

	typedef ft::RBTree<T, Compare, Allocator>				self;
	typedef self*											self_pointer;
	typedef T												value_type;
	typedef value_type*										value_pointer;
	typedef value_type&										value_reference;
	typedef Compare											compare_type;
	typedef RBNode<value_type>								node_type;
	typedef typename Allocator::pointer						node_pointer;
	typedef node_type&										node_reference;
	typedef Allocator										allocator_type;
	typedef typename Allocator::size_type					size_type;

private:
	node_pointer	root;
	compare_type	compare;
	size_type		size;
	allocator_type	allocator;

public:

	RBTree() : root(NULL), size(0) {
	}
	~RBTree() {
		while (size)
			deleteNode(findMin());
	}
	node_pointer	get_root(void) const { return (root); }
	void			set_root(node_pointer r) {this->root = r; }
	size_type		get_size(void) const { return (size); }
	void			set_size(size_type s) { this->size = s; }
	size_type		max_size(void) const { return (allocator.max_size()); }
	node_pointer	insertNode(const value_type& value) {
		if ( size >= max_size() )
			throw std::bad_array_new_length();
		if ( root != NULL ) {
			bool child = RIGHT;
			node_pointer node = root, parent = NULL;
			while (node != NULL) {
				if ( !compare(value, node->value) && !compare(node->value, value) )
					return (NULL);
				parent = node;
				child = (compare(value, node->value) ? LEFT : RIGHT);
				node = (child == LEFT ? node->left : node->right);
			}
			node = allocator.allocate(1);
			allocator.construct(node, node_type(value, RED, parent));
			child == LEFT ? parent->left = node : parent->right = node;
			size++;
			insertCase1(node);
			return (node);
		} else {
			root = allocator.allocate(1);
			allocator.construct(root, node_type(value, BLACK));
			size++;
			return (root);
		}
	}
	node_pointer	findNode(const value_type& value) const {
		node_pointer	node = root;
		while (node != NULL) {
			if ( !compare(value, node->value) && !compare(node->value, value) )
				break ;
			else if ( compare(value, node->value) )
				node = node->left;
			else
				node = node->right;
		}
		return (node);
	}
	void	swap(node_pointer to_delete, node_pointer candidate) {
		node_pointer	to_delete_parent = to_delete->parent;
		node_pointer	to_delete_left_child = to_delete->left;
		node_pointer	to_delete_right_child = to_delete->right;
		node_pointer	candidate_parent = candidate->parent;
		node_pointer	candidate_left_child = candidate->left;
		node_pointer	candidate_right_child = candidate->right;
		bool			tmp_color = to_delete->color;

		to_delete->color = candidate->color;
		candidate->color = tmp_color;
		if (to_delete_parent == NULL)
			root = candidate;
		else if (to_delete == to_delete_parent->left)
			to_delete_parent->left = candidate;
		else if (to_delete == to_delete_parent->right)
			to_delete_parent->right = candidate;
		if (candidate == candidate_parent->left)
			candidate_parent->left = to_delete;
		else if (candidate == candidate_parent->right)
			candidate_parent->right = to_delete;
		if (to_delete_left_child)
			to_delete_left_child->parent = candidate;
		if (to_delete_right_child)
			to_delete_right_child->parent = candidate;
		if (candidate_left_child)
			candidate_left_child->parent = to_delete;
		if (candidate_right_child)
			candidate_right_child->parent = to_delete;
		to_delete->left = candidate_left_child;
		to_delete->right = candidate_right_child;
		candidate->left = to_delete_left_child;
		candidate->right = to_delete_right_child;
		candidate->parent = to_delete_parent;
		to_delete->parent = candidate_parent;
		if (to_delete == to_delete->parent)
			to_delete->parent = candidate;
		if (candidate->left == candidate)
			candidate->left = to_delete;
		else if (candidate->right == candidate)
			candidate->right = to_delete;
	}
	void	deleteNode(const value_type& value) {
		node_pointer	node = findNode(value), tmp = NULL;
		if (node != NULL) {
			if (node->left != NULL) {
				tmp = findMaxNode(node->left);
				swap(node, tmp);
				deleteOneChild(node);
			}
			else if (node->right != NULL) {
				tmp = findMinNode(node->right);
				swap(node, tmp);
				deleteOneChild(node);
			}
			else
				deleteOneChild(node);
		}
	}
	void	deleteNode(node_pointer node) {
		node_pointer	tmp = NULL;
		if (node != NULL) {
			if (node->left != NULL) {
				tmp = findMaxNode(node->left);
				swap(node, tmp);
				deleteOneChild(node);
			}
			else if (node->right != NULL) {
				tmp = findMinNode(node->right);
				swap(node, tmp);
				deleteOneChild(node);
			}
			else
				deleteOneChild(node);
		}
	}
	node_pointer	findMaxNode(node_pointer node) const {
		while (node != NULL && node->right != NULL)
			node = node->right;
		return (node);
	}
	node_pointer	findMinNode(node_pointer node) const {
		while (node != NULL && node->left != NULL)
			node = node->left;
		return (node);
	}
	node_pointer	findMin(void) const { return (findMinNode(root)); }
	node_pointer	findMax(void) const { return (findMaxNode(root)); }
	node_pointer	findNextNode(node_pointer node) const {
		if (node != NULL) {
			if (node->right != NULL)
				return (findMinNode(node->right));
			while (node->parent != NULL) {
				if (node == node->parent->left)
					return (node->parent);
				node = node->parent;
			}
		}
		return (NULL);
	}
	node_pointer	findPrevNode(node_pointer node) const {
		if (node != NULL) {
			if (node->left != NULL)
				return (findMinNode(node->left));
			while (node->parent != NULL) {
				if (node == node->parent->right)
					return (node->parent);
				node = node->parent;
			}
		}
		return (NULL);
	}

private:

	void	replaceNode(node_pointer node, node_pointer child) {
		child->parent = node->parent;
		if (node == node->parent->left)
			node->parent->left = child;
		else
			node->parent->right = child;
	}
	void	deleteOneChild(node_pointer node) {
		if (node->left == NULL && node->right == NULL) {
			if (node->parent == NULL)
				root = NULL;
			else {
				if (node == node->parent->left) {
					node->parent->left = NULL;
				}
				else {
					node->parent->right = NULL;
				}
				deleteCase1(node->parent);
			}
		}
		else {
			node_pointer	child = (node->right == NULL ? node->left : node->right);
			replaceNode(node, child);
			if (node->color == BLACK) {
				if (child->color == RED)
					child->color = BLACK;
				else
					deleteCase1(child);
			}
		}
		allocator.destroy(node);
		allocator.deallocate(node, 1);
		size--;
	}
	node_pointer	grandparent(node_pointer node) {
		if (node != NULL && node->parent != NULL)
			return (node->parent->parent);
		return (NULL);
	}
	node_pointer	uncle(node_pointer node) {
		node_pointer	grandpa = grandparent(node);
		if (grandpa == NULL)
			return (NULL);
		if (node->parent == grandpa->left)
			return (grandpa->right);
		else
			return (grandpa->left);
	}
	node_pointer	sibling(node_pointer node) {
		if (node != NULL && node->parent != NULL) {
			if (node == node->parent->left)
				return (node->parent->right);
			else
				return (node->parent->left);
		}
		return (NULL);
	}
	void			rotateLeft(node_pointer node) {
		node_pointer	pivot = node->right;
		pivot->parent = node->parent;
		if (node->parent != NULL) {
			if (node->parent->left == node)
				node->parent->left = pivot;
			else
				node->parent->right = pivot;
		} else
			root = pivot;
		node->right = pivot->left;
		if (pivot->left != NULL)
			pivot->left->parent = node;
		node->parent = pivot;
		pivot->left = node;
	}
	void			rotateRight(node_pointer node) {
		node_pointer	pivot = node->left;
		pivot->parent = node->parent;
		if (node->parent != NULL) {
			if (node->parent->left == node)
				node->parent->left = pivot;
			else
				node->parent->right = pivot;
		} else
			root = pivot;
		node->left = pivot->right;
		if (pivot->right != NULL)
			pivot->right->parent = node;
		node->parent = pivot;
		pivot->right = node;
	}
	void			insertCase1(node_pointer node) {
		if (node->parent == NULL)
			node->color = BLACK;
		else
			insertCase2(node);
	}
	void			insertCase2(node_pointer node) {
		if (node->parent->color == BLACK)
			return;
		else
			insertCase3(node);
	}
	void			insertCase3(node_pointer node) {
		node_pointer	uncl = uncle(node);
		node_pointer	grandpa = grandparent(node);
		if ((uncl != NULL) && (uncl->color == RED)) {
			node->parent->color = BLACK;
			uncl->color = BLACK;
			grandpa->color = RED;
			insertCase1(grandpa);
		} else {
			insertCase4(node);
		}
	}
	void			insertCase4(node_pointer node) {
		node_pointer	grandpa = grandparent(node);

		if ((node == node->parent->right) && (node->parent == grandpa->left)) {
			rotateLeft(node->parent);
			node = node->left;
		} else if ((node == node->parent->left) && (node->parent == grandpa->right)) {
			rotateRight(node->parent);
			node = node->right;
		}
		insertCase5(node);
	}
	void			insertCase5(node_pointer node) {
		node_pointer	grandpa = grandparent(node);
		node->parent->color = BLACK;
		grandpa->color = RED;
		if ((node == node->parent->left) && (node->parent == grandpa->left)) {
			rotateRight(grandpa);
		} else {
			rotateLeft(grandpa);
		}
	}
	void			deleteCase1(node_pointer node) {
		if (node->parent != NULL)
			deleteCase2(node);
	}
	void			deleteCase2(node_pointer node) {
		node_pointer	siblng = sibling(node);
		if (siblng != NULL && siblng->color == RED) {
			node->parent->color = RED;
			siblng->color = BLACK;
			if (node == node->parent->left)
				rotateLeft(node->parent);
			else
				rotateRight(node->parent);
		}
		deleteCase3(node);
	}
	void			deleteCase3(node_pointer node) {
		node_pointer	siblng = sibling(node);
		if ( siblng != NULL &&
			(node->parent->color == BLACK) &&
			(siblng->color == BLACK) &&
			(siblng->left == NULL || siblng->left->color == BLACK) &&
			(siblng->right == NULL || siblng->right->color == BLACK)
			)
		{
			siblng->color = RED;
			deleteCase1(node->parent);
		} else
			deleteCase4(node);
	}
	void			deleteCase4(node_pointer node) {
		node_pointer	siblng = sibling(node);
		if ( siblng != NULL &&
			(node->parent->color == RED) &&
			(siblng->color == BLACK) &&
			(siblng->left == NULL || siblng->left->color == BLACK) &&
			(siblng->right == NULL || siblng->right->color == BLACK)
			)
		{
			siblng->color = RED;
			node->parent->color = BLACK;
		} else
			deleteCase5(node);
	}
	void			deleteCase5(node_pointer node) {
		node_pointer	siblng = sibling(node);
		if (siblng != NULL && siblng->color == BLACK) {
			if (
				(node == node->parent->left) &&
				(siblng->right == NULL || siblng->right->color == BLACK) &&
				(siblng->left != NULL && siblng->left->color == RED)
			   )
			{
				siblng->color = RED;
				siblng->left->color = BLACK;
				rotateRight(siblng);
			} else if (
					(node == node->parent->right) &&
					(siblng->left == NULL || siblng->left->color == BLACK) &&
					(siblng->right != NULL && siblng->right->color == RED)
				)
			{
				siblng->color = RED;
				siblng->right->color = BLACK;
				rotateLeft(siblng);
			}
		}
		deleteCase6(node);
	}
	void			deleteCase6(node_pointer node) {
		node_pointer	siblng = sibling(node);
		if (siblng != NULL)
		{
			siblng->color = node->parent->color;
			node->parent->color = BLACK;
			
			if (node == node->parent->left) {
				if (siblng->right != NULL)
					siblng->right->color = BLACK;
				rotateLeft(node->parent);
			} else {
				if (siblng->left != NULL)
					siblng->left->color = BLACK;
				rotateRight(node->parent);
			}
		}
	}
};
}

#endif /* RBTree_h */
