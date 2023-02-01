/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidir_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:59:13 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/04 19:59:13 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_H
#define MAP_ITERATOR_H
#include "iterator.hpp"
#include "utils.hpp"

namespace ft {

template<typename node_type, typename value_type, bool isConst = false>

class bidir_iterator : public ft::iterator<ft::bidirectional_iterator_tag, value_type> {

public:
	typedef	node_type*	node_pointer;
	typedef node_type&	node_reference;
	typedef bidir_iterator<node_type, typename ft::remove_const<value_type>::type>							non_const_iterator;

	typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::value_type val_type;
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

protected:
	node_pointer													ptr;
	node_pointer													max_keeper;

public:

	node_pointer	get_ptr(void) const { return (ptr); }
	node_pointer	get_max(void) const { return (max_keeper); }
	node_pointer	findMaxNode(node_pointer node) const {
		while (node && node->parent)
			node = node->parent;
		while (node && node->right)
			node = node->right;
		return (node);
	}

	bidir_iterator() : ptr(NULL), max_keeper(NULL) {}

	bidir_iterator(node_pointer node, node_pointer max = NULL) : ptr(node), max_keeper(max) {
		if (max_keeper == NULL)
			max_keeper = findMaxNode(ptr);
	}

	bidir_iterator(const non_const_iterator& other) : ptr(other.get_ptr()), max_keeper(other.get_max()) {}
	virtual	~bidir_iterator() {}
	bidir_iterator	operator=(const non_const_iterator& other) {
		ptr = other.get_ptr();
		max_keeper = other.get_max();
		return (*this);
	}

	operator	bidir_iterator<const node_type, const value_type> () const {
		return (bidir_iterator<const node_type, const value_type>(ptr, max_keeper));
	}

	reference	operator*() const {
		if (ptr == u_nullptr)
			return (*(max_keeper->value));
		return (*(ptr->value));
	}
	pointer		operator->() const {
		if (ptr == u_nullptr)
			return (max_keeper->value);
		return (ptr->value);
		
	}

	bidir_iterator&	operator++(void) {
		if (ptr != NULL) {
			max_keeper = findMaxNode(ptr);
			if (ptr->right != NULL) {
				ptr = ptr->right;
				while(ptr->left != NULL)
					ptr = ptr->left;
				return (*this);
			}
			while (ptr->parent != NULL) {
				if (ptr == ptr->parent->left) {
					ptr = ptr->parent;
					return (*this);
				}
				ptr = ptr->parent;
			}
			ptr = u_nullptr;
		}
		return (*this);
	}
	bidir_iterator	operator++(int) {
		bidir_iterator	tmp = *this;
		++(*this);
		return (tmp);
	}
	bidir_iterator&	operator--(void) {
		if (ptr == u_nullptr) {
			ptr = max_keeper;
			return (*this);
		}
		if (ptr != NULL) {
			max_keeper = findMaxNode(ptr);
			if (ptr->left != NULL) {
				ptr = ptr->left;
				while (ptr->right != NULL)
					ptr = ptr->right;
				return (*this);
			}
			while (ptr->parent != NULL) {
				if (ptr == ptr->parent->right) {
					ptr = ptr->parent;
					return (*this);
				}
				ptr = ptr->parent;
			}
			ptr = u_nullptr;
		}
		return (*this);
	}

	bidir_iterator	operator--(int) {
		bidir_iterator	tmp = *this;
		--(*this);
		return (tmp);
	}

	friend bool	operator==(const bidir_iterator& lhs, const bidir_iterator& rhs) { return (lhs.get_ptr() == rhs.get_ptr()); }
	friend bool	operator!=(const bidir_iterator& lhs, const bidir_iterator& rhs) { return (lhs.get_ptr() != rhs.get_ptr()); }
};


}

#endif /* bidir_iterator_h */
