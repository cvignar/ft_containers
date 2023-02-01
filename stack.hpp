/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:52:59 by cvignar           #+#    #+#             */
/*   Updated: 2022/12/26 19:52:59 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef stack_hpp
# define stack_hpp

#include "vector.hpp"

namespace ft {

template<
	class T,
	class Container = ft::vector<T>
> class stack {
public:
	/* Member types */
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;
	/* Member functions */
	explicit stack( const Container& cont = Container() ) : c(cont) {}
	~stack() {}
	stack& operator=( const stack& other ) {
		c = other.c;
		return (*this);
	}
	/* Element access */
	reference top() {
		return (c.back());
	}
	const_reference top() const {
		return (c.back());
	}
	/* Capacity */
	bool empty() const {
		return (c.empty());
	}
	size_type size() const {
		return (c.size());
	}
	/* Modifiers */
	void push( const value_type& value ) {
		c.push_back(value);
	}
	void pop() {
		c.pop_back();
	}

	/* Non-member functions */

	friend bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c == rhs.c);
	}
	friend bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c != rhs.c);
	}
	friend bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c < rhs.c);
	}
	friend bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c <= rhs.c);
	}
	friend bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c > rhs.c);
	}
	friend bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return (lhs.c >= rhs.c);
	}

protected:
	/* Member objects */
	Container	c;
};

}

#endif /* stack_h */
