/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:17:12 by cvignar           #+#    #+#             */
/*   Updated: 2022/12/14 18:17:12 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"
#include "RBTree.hpp"
#include "utils.hpp"
#include "bidir_iterator.hpp"

namespace	ft {

template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator< ft::pair<const Key, T> >
> class	map {
public:
	/* Member types */

	typedef				ft::map<Key, T, Compare, Allocator>	self;
	typedef				Key									key_type;
	typedef 			T									mapped_type;
	typedef typename	ft::pair<const Key, T>				value_type;
	typedef	typename	Allocator::size_type				size_type;
	typedef				std::ptrdiff_t						difference_type;
	typedef				Compare								key_compare;
	typedef				Allocator							allocator_type;
	typedef				value_type&							reference;
	typedef				const value_type&					const_reference;
	typedef	typename 	Allocator::pointer					pointer;
	typedef	typename	Allocator::const_pointer			const_pointer;

	
	/* Member class */

	class value_compare {

	protected:
		key_compare	comp;
	public:
		value_compare() {}
		value_compare(key_compare c) : comp(c) {}
		~value_compare() {}

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;
		bool	operator()(pointer x, pointer y) const {
			return (comp(x->first, y->first));
		}
		bool	operator()(value_type x, value_type y) const {
			return (comp(x.first, y.first));
		}
		bool	operator()(value_type x, pointer y) const {
			return (comp(x.first, y->first));
		}
		bool	operator()(pointer x, value_type y) const {
			return (comp(x->first, y.first));
		}
	};

protected:

	/* My member types */

	typedef 			ft::RBNode<pointer>									node_type;
	typedef typename	allocator_type::template rebind<node_type>::other	node_allocator;
	typedef				ft::RBTree<pointer, value_compare, node_allocator>	tree_type;
	typedef 			node_type*											node_pointer;
	typedef				node_type&											node_reference;

	/* Member objects */

	tree_type				tree;
	allocator_type			allocator;
	value_compare			compare;
	key_compare				k_comp;

public:

	/* iterator member types */

	typedef typename	ft::bidir_iterator<node_type, value_type, false> 		iterator;
	typedef typename	ft::bidir_iterator<node_type, const value_type, true>	const_iterator;
	typedef 			ft::reverse_iterator<iterator> 							reverse_iterator;
	typedef 			ft::reverse_iterator<const_iterator>					const_reverse_iterator;

protected:

	/* pair<iterator, bool>,
	 pair<iterator, iterator>
	 and pair<const_iterator,const_iterator> */

	
public:
	
	/* Member functions */

	/* Constructors */

	map() : tree(), allocator(), compare() {}
	explicit map( const Compare& comp, const Allocator& alloc = Allocator()) : allocator(alloc), compare(comp) {}
	template< class InputIt >
	map( InputIt first, InputIt last,
		 const Compare& comp = Compare(),
		const Allocator& alloc = Allocator(),
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type* = 0) : allocator(alloc), compare(comp) {
		InputIt	it = first;
		for (; it != last; ++it) {
			insert(value_type(it->first, it->second));
		}
	}
	map( const map& other ) : allocator(other.allocator), compare(other.compare) {
		insert(other.begin(), other.end());
	}

	/* Destructor */

	~map() { clear(); }

	/* copy-assignment operator */

	map&	operator=( const map& other ) {
		if ( other.size() >= max_size() / 2 )
			throw std::bad_array_new_length();
		tree_type	clone_tree;
		try {
			node_pointer node = other.tree.findMin();
			while (node != NULL) {
				clonePairAndNode(*node->value, clone_tree);
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

	allocator_type		get_allocator() const {return (this->allocator);}

	/* Element access */

	mapped_type&		at(const key_type& key) {
		node_pointer	node = findKey(key);
		if (node == NULL)
			throw std::out_of_range("ft::map::at: key not found");
		return (node->value->second);
	}
	const mapped_type&	at(const key_type& key) const {
		node_pointer	node = findKey(key);
		if (node == NULL)
			throw std::out_of_range("ft::map::at: key not found");
		return (node->value->second);
	}
	mapped_type&		operator[]( const Key& key ) {
		node_pointer node = findKey(key);
		if (node == NULL) {
			try {
				node = insertPairAndNode(key, mapped_type());
				return (node->value->second);
			}
			catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				return ( tree.findMax()->value->second );
			}
		}
		return (node->value->second);
	}

	/* iterators */

	iterator				begin(void) { return iterator(tree.findMin(), tree.findMax()); }
	const_iterator			begin(void) const { return const_iterator(tree.findMin(), tree.findMax()); }
	iterator				end(void) { return iterator(u_nullptr, tree.findMax()); }
	const_iterator			end(void) const { return const_iterator(u_nullptr, tree.findMax()); }
	reverse_iterator		rbegin(void) { return reverse_iterator(end()); }
	const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(end()); }
	reverse_iterator		rend(void) { return reverse_iterator(begin()); }
	const_reverse_iterator	rend(void) const { return const_reverse_iterator(begin()); }

	/* Capacity */

	bool		empty(void) const {return (begin() == end()); }
	size_type	size(void) const {return (tree.get_size()); }
	size_type	max_size(void) const {
				return ((allocator.max_size() * sizeof(value_type)) / (sizeof(value_type) + sizeof(node_type))); }

	/* Modifiers */

	void						clear(void) { clear(tree);}
	iterator					insert( iterator pos, const value_type& value ) {
		if (pos != end() && (!compare(value, *pos) && !compare(*pos, value)))
			return (pos);
		return ( insert(value).first );
	}
	ft::pair<iterator, bool>	insert( const value_type& value ) {
		node_pointer	node = findKey(value.first);
		bool			is_inserted = (node == NULL ? true : false);
		if ( is_inserted ) {
			try {
				node = insertPairAndNode(value.first, value.second);
			} catch (std::exception &e) {
				node = tree.findMax();
			}
		}
		return (ft::pair<iterator, bool>(iterator(node, tree.findMax()), is_inserted));
	}
	template< class InputIt >
	void						insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type* = 0 ) {
		InputIt	it = first;
		for (; it != last; ++it) {
			insert(value_type(it->first, it->second));
		}
	}
	void						erase( iterator pos ) {
		if (pos != end()) {
			erase(pos++->first);
		}
	}
	void						erase( iterator first, iterator last ) {
		while (first != last && first != end())
			erase(first++->first);
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
	void						swap( map& other ) {
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
	iterator									find( const key_type& key ) {
		node_pointer node = findKey(key);
		if (node != NULL)
			return (iterator(node, tree.findMax()));
		return (end());
	}
	const_iterator								find( const key_type& key ) const {
		node_pointer node = findKey(key);
		if (node != NULL)
			return (const_iterator(node, tree.findMax()));
		return (end());
	}
	ft::pair<iterator, iterator>				equal_range( const key_type& key ) {
		return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
	}
	ft::pair<const_iterator, const_iterator>	equal_range( const key_type& key ) const { return (ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key))); }
	iterator									lower_bound( const key_type& key ) {
		node_pointer	node = findKey(key);
		if (node != NULL)
			return (iterator(node, tree.findMax()));
		iterator	it = begin();
		iterator	e = end();
		value_type	value(key, mapped_type());
		while (it != e && compare(*it, value))
			it++;
		return (it);
	}
	const_iterator 								lower_bound( const key_type& key ) const {
		node_pointer	node = findKey(key);
		if (node != NULL)
			return (const_iterator(node, tree.findMax()));
		const_iterator	it(begin());
		const_iterator	e(end());
		value_type	value(key, mapped_type());
		while (it != e && compare(*it, value))
			it++;
		return (it);
	}
	iterator 									upper_bound( const Key& key ) {
		iterator	it = begin();
		iterator	e = end();
		value_type	value(key, mapped_type());
		while (it != e && !compare(value, *it))
			it++;
		return (it);
	}
	const_iterator 								upper_bound( const Key& key ) const {
		const_iterator	it(begin());
		const_iterator	e(end());
		value_type	value(key, mapped_type());
		while (it != e && !compare(value, *it))
			it++;
		return (const_iterator(it));
	}

	/* Observers */

	key_compare		key_comp(void) const { return (k_comp); }
	value_compare	value_comp() const { return (value_compare()); }

private:

	/* My member functions */

	node_pointer	insertPairAndNode( const key_type& key, const mapped_type& t ) {
		if ( size() >= max_size() )
			throw std::bad_array_new_length();
		pointer p = allocator.allocate(1);
		try {
			allocator.construct(p, value_type(key, t));
		}
		catch (...) {
			allocator.deallocate(p, 1);
			throw;
		}
		return ( tree.insertNode(p) );
	}
	node_pointer	findKey( const key_type& key ) const {
		value_type value( key, mapped_type() );
		return tree.findNode( &value );
	}
	void			clonePairAndNode( const value_type& value, tree_type& clone_tree ) {
		pointer p = allocator.allocate(1);
		try {
			allocator.construct(p, value_type(value));
		} catch (...) {
			allocator.deallocate(p, 1);
			throw;
		}
		clone_tree.insertNode(p);
	}
	void			clear(tree_type& tree_to_clear) {
		while (tree_to_clear.get_size()) {
			node_pointer	node = tree_to_clear.findMin();
			allocator.destroy(node->value);
			allocator.deallocate(node->value, 1);
			node->value = NULL;
			tree_to_clear.deleteNode(node);
		}
	}
};

/* Map non-member functions */

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) {
	if (lhs.size() == rhs.size()) {
		return(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	return (false);
}
template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) { return (!(lhs == rhs)); }
template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
			   const ft::map<Key,T,Compare,Alloc>& rhs )
{ return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs )
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
			   const ft::map<Key,T,Compare,Alloc>& rhs ) { return (!(lhs <= rhs)); }
template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs ) { return (!(lhs < rhs)); }
template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs,
		  ft::map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif /* map_h */
