/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:04:52 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/08 13:04:52 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "utils.hpp"
#include "iterator.hpp"
#include "RBTree.hpp"
#include "bidir_iterator.hpp"
#include "pair.hpp"

namespace	ft {
template<
class Key,
class Compare = std::less<Key>,
class Allocator = std::allocator<Key>
> class set {
public:

	/* Member types */

	typedef				Key							key_type;
	typedef				Key							value_type;
	typedef				std::size_t					size_type;
	typedef				std::ptrdiff_t				difference_type;
	typedef				Compare						key_compare;
	typedef				Compare						value_compare;
	typedef				Allocator					allocator_type;
	typedef				value_type&					reference;
	typedef				const value_type&			const_reference;
	typedef	typename	Allocator::pointer			pointer;
	typedef typename	Allocator::const_pointer	const_pointer;

protected:
	/* value_compare class */

	class value_comp {
	protected:
		value_compare	comp;
	public:
		value_comp() {}
		value_comp(key_compare c) : comp(c) {}
		~value_comp() {}

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool	operator()(pointer x, pointer y) const {
			return (comp(*x, *y));
		}
		bool	operator()(value_type x, value_type y) const {
			return (comp(x, y));
		}
		bool	operator()(value_type x, pointer y) const {
			return (comp(x, *y));
		}
		bool	operator()(pointer x, value_type y) const {
			return (comp(*x, y));
		}
	};

	/* My member types */
	
	typedef 			ft::RBNode<pointer>									node_type;
	typedef typename 	allocator_type::template rebind<node_type>::other 	node_allocator;
	typedef				ft::RBTree<pointer, value_comp, node_allocator>		tree_type;
	typedef				node_type*											node_pointer;
	typedef				node_type&											node_reference;

	/* Memper objects */

	tree_type		tree;
	allocator_type	allocator;
	key_compare		compare;
	value_compare	v_compare;

public:

	/* iterator types */

	typedef	ft::bidir_iterator<node_type, const value_type, true>	const_iterator;
	typedef	ft::bidir_iterator<node_type, const value_type, true>	iterator;
	typedef	ft::reverse_iterator<iterator>							reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;

protected:

	/* pair<iterator, bool>,
	 pair<iterator, iterator>
	 and pair<const_iterator,const_iterator> */


public:
	/* Member functions */

	/* Constructors */

	set() : tree(), allocator(), compare() {}
	explicit set( const Compare& comp, const Allocator& alloc = Allocator() ) : tree(), allocator(alloc), compare(comp) {}
	template< class InputIt >
	set( InputIt first, InputIt last,
		 const Compare& comp = Compare(),
		const Allocator& alloc = Allocator(),
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type* = 0 ) :
	allocator(alloc), compare(comp) {
		InputIt	it = first;
		for (; it != last; ++it)
			insert(value_type(*it));
	}
	set( const set& other ) :
	allocator(other.allocator), compare(other.compare)
	{ insert(other.begin(), other.end()); }
	~set() { clear(); }

	/* copy-assignment operator */

	set& operator=( const set& other ) {
		if ( other.size() >= max_size() / 2 )
			throw std::bad_array_new_length();
		tree_type	clone_tree;
		try {
			node_pointer node = other.tree.findMin();
			while (node != NULL) {
				cloneNode(*node->value, clone_tree);
				node = other.tree.findNextNode(node);
			}
			clear(tree);
			tree.set_root(clone_tree.get_root());
			clone_tree.set_root(NULL);
			tree.set_size(clone_tree.get_size());
			clone_tree.set_size(0);

			return (*this);
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
			clear(clone_tree);
		}
		return (*this);
	}

	/* get_allocator */

	allocator_type get_allocator() const { return (this->allocator); }

	/* iterators */

	iterator				begin() { return iterator(tree.findMin(), tree.findMax()); }
	const_iterator			begin() const { return const_iterator(tree.findMin(), tree.findMax()); }
	iterator				end() { return iterator(u_nullptr, tree.findMax()); }
	const_iterator			end() const { return const_iterator(u_nullptr, tree.findMax()); }
	reverse_iterator		rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator		rend() { return reverse_iterator(begin()); }
	const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

	/* Capacity */

	bool		empty() const { return (begin() == end()); }
	size_type	size() const { return (tree.get_size()); }
	size_type	max_size() const { return ((allocator.max_size() * sizeof(value_type)) / (sizeof(value_type) + sizeof(node_type))); }

	/* Modifiers */

	void						clear() { clear(tree); }
	ft::pair<iterator, bool>	insert( const value_type& value ) {
		node_pointer	node = findKey(value);
		bool			is_inserted = (node == NULL ? true : false);
		if ( is_inserted ) {
			try {
				node = insertNode(value);
			} catch (std::exception &e) {
				node = tree.findMax();
			}
		}
		return (ft::pair<iterator, bool>(iterator(node, tree.findMax()), is_inserted));
	}
	iterator					insert( iterator pos, const value_type& value ) {
		if (pos != end() && (!compare(value, *pos) && !compare(*pos, value)))
			return (pos);
		return ( insert(value).first );
	}
	template< class InputIt >
	void						insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type* = 0 ) {
		InputIt	it = first;
		for (; it != last; ++it) {
			insert(value_type(*it));
		}
	}
	void						erase( iterator pos ) {
		if (pos != end()) {
			node_pointer node = findKey(*pos);
			++pos;
			if (node != NULL) {
				allocator.destroy(node->value);
				allocator.deallocate(node->value, 1);
				node->value = NULL;
				tree.deleteNode(node);
			}
		}
	}
	void						erase( iterator first, iterator last ) {
		while (first != last)
			erase(*first++);
	}
	size_type					erase( const Key& key ) {
		size_type	s = size();
		node_pointer node = findKey(key);
		if (node != NULL) {
			allocator.destroy(node->value);
			allocator.deallocate(node->value, 1);
			node->value = NULL;
			tree.deleteNode(node);
		}
		return (s - size());
	}
	void						swap( set& other ) {
		node_pointer	root_tmp;
		size_type		size_tmp;
		root_tmp = tree.get_root();
		size_tmp = tree.get_size();
		tree.set_root(other.tree.get_root());
		other.tree.set_root(root_tmp);
		tree.set_size(other.tree.get_size());
		other.tree.set_size(size_tmp);
	}

	/* Lookup */

	size_type									count( const Key& key ) const { return (!(findKey(key) == NULL)); }
	iterator									find( const Key& key ) {
		node_pointer node = findKey(key);
		if (node != NULL)
			return (iterator(node, tree.findMax()));
		return (end());
	}
	const_iterator								find( const Key& key ) const {
		node_pointer node = findKey(key);
		if (node != NULL)
			return (const_iterator(node, tree.findMax()));
		return (end());
	}
	ft::pair<iterator, iterator>								equal_range( const Key& key ) {
		return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
	}
	ft::pair<const_iterator, const_iterator>	equal_range( const Key& key ) const {
		return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
	}
	iterator									lower_bound( const Key& key ) {
		node_pointer	node = findKey(key);
		if (node != NULL)
			return (iterator(node, tree.findMax()));
		iterator	it = begin();
		iterator	e = end();
		while (it != e && compare(*it, key))
			it++;
		return (it);
	}
	const_iterator								lower_bound( const Key& key ) const {
		node_pointer	node = findKey(key);
		if (node != NULL)
			return (const_iterator(node, tree.findMax()));
		const_iterator	it = begin();
		const_iterator	e = end();
		while (it != e && compare(*it, key))
			it++;
		return (it);
	}
	iterator									upper_bound( const Key& key ) {
		iterator	it = begin();
		iterator	e = end();
		while (it != e && !compare(key, *it))
			it++;
		return (it);
	}
	const_iterator								upper_bound( const Key& key ) const {
		const_iterator	it(begin());
		const_iterator	e(end());
		while (it != e && !compare(key, *it))
			it++;
		return (const_iterator(it));
	}

	/* Observers */

	key_compare key_comp() const { return (compare); }
	value_compare value_comp() const { return (v_compare); }

protected:

	/* My member functions */

	node_pointer	insertNode( const key_type& key) {
		if ( size() >= max_size() )
			throw std::bad_array_new_length();
		pointer p = allocator.allocate(1);
		try {
			allocator.construct(p, key);
		}
		catch (...) {
			allocator.deallocate(p, 1);
			throw;
		}
		return ( tree.insertNode(p) );
	}
	node_pointer	findKey(  value_type value ) const { return tree.findNode( &value ); }
	void			cloneNode( const value_type& value, tree_type& clone_tree ) {
		pointer p = allocator.allocate(1);
		try {
			allocator.construct(p, value);
		} catch (...) {
			allocator.deallocate(p, 1);
			throw;
		}
		clone_tree.insertNode(p);
	}
	void						clear(tree_type& tree_to_clear) {
		while (tree_to_clear.get_size()) {
			node_pointer	node = tree_to_clear.findMin();
			allocator.destroy(node->value);
			allocator.deallocate(node->value, 1);
			node->value = NULL;
			tree_to_clear.deleteNode(node);
		}
	}
};

/* Set non-member functions */
template< class Key, class Compare, class Alloc >
bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs ) {
	if (lhs.size() == rhs.size()) {
		return(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	return (false);
}

template< class Key, class Compare, class Alloc >
bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
				 const ft::set<Key,Compare,Alloc>& rhs ) { return (!(lhs == rhs)); }
template< class Key, class Compare, class Alloc >
bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs )
{ return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
template< class Key, class Compare, class Alloc >
bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
				 const ft::set<Key,Compare,Alloc>& rhs )
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
template< class Key, class Compare, class Alloc >
bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
				const ft::set<Key,Compare,Alloc>& rhs ) { return (!(lhs <= rhs)); }
template< class Key, class Compare, class Alloc >
bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
				 const ft::set<Key,Compare,Alloc>& rhs ) { return (!(lhs < rhs)); }
template< class Key, class Compare, class Alloc >
void swap( ft::set<Key,Compare,Alloc>& lhs,
		   ft::set<Key,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif /* SET_HPP */
