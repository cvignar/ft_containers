/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:10:59 by cvignar           #+#    #+#             */
/*   Updated: 2022/12/14 20:10:59 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "utils.hpp"

namespace	ft {

template<
	class	Category,
	class	T,
	bool	isConst = false,
	class	Distance = std::ptrdiff_t,
	class	Pointer = T*,
	class	Reference = T&
> struct	iterator {

	typedef Category										iterator_category;
	typedef T												value_type;
	typedef Distance										difference_type;
	typedef Pointer											pointer;
	typedef Reference										reference;

};

template< class Iter>
class reverse_iterator {
protected:

    Iter    current;

public:

	typedef	Iter													iterator_type;
	typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iter>::value_type			value_type;
	typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iter>::pointer				pointer;
	typedef typename ft::iterator_traits<Iter>::reference			reference;

    reverse_iterator() {}

	explicit reverse_iterator( iterator_type x ) : current(x) {}

	template< class U >
	reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {}

	template< class U >
	reverse_iterator& operator=( const reverse_iterator<U>& other ) {
		if (*this != other)
			current = other.base();
		return (*this);
	}

	Iter				base() const { return (current); }

	reference	operator*(void) const {
		Iter tmp(base());
		return (*(--tmp));
	}

	pointer operator->(void) const {
		Iter tmp(base());
		return (&(*--tmp));
	}

	reference	operator[]( difference_type n ) const {
		return(base()[-n-1]);
	}

	reverse_iterator&	operator++(void) { --current; return *this; }

	reverse_iterator	operator++(int)	{
		reverse_iterator	tmp = *this;
		++(*this);
		return (tmp);
	}

	reverse_iterator&	operator--(void) {
		++current; return (*this);
	}

	reverse_iterator	operator--(int) {
		reverse_iterator	tmp = (*this);
		--(*this);
		return (tmp);
	}

	reverse_iterator operator+( difference_type n ) const {
		return (reverse_iterator(base() - n));
	}

	reverse_iterator& operator+=( difference_type n ) {
		current -= n;
		return (*this);
	}
	reverse_iterator& operator-=( difference_type n ) {
		current += n;
		return (*this);
	}
};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2>
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
			   const ft::reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2>
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() >= rhs.base());
}

template< class Iterator1, class Iterator2>
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
			   const ft::reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2>
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() <= rhs.base());
}

template< class Iter>
typename ft::enable_if<!ft::is_integral<Iter>::value, reverse_iterator<Iter> >::type
	operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
		return (reverse_iterator<Iter>(it.base() - n));
	}

template< class Iter>
typename ft::enable_if<!ft::is_integral<Iter>::value, reverse_iterator<Iter> >::type
operator-(const reverse_iterator<Iter>& it, typename reverse_iterator<Iter>::difference_type n ) {
	return (reverse_iterator<Iter>(it.base() + n));
}

template< class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type
	operator-( const reverse_iterator<Iterator1>& lhs,
			  const reverse_iterator<Iterator2>& rhs ) {
		return (rhs.base() - lhs.base());
	}

namespace detail {
 
template<class It>
typename std::iterator_traits<It>::difference_type
	do_distance(It first, It last, std::input_iterator_tag)
{
	typename std::iterator_traits<It>::difference_type result = 0;
	while (first != last) {
		++first;
		++result;
	}
	return result;
}

template<class It>
typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, ft::forward_iterator_tag)
{
	typename ft::iterator_traits<It>::difference_type result = 0;
	while (first != last) {
		++first;
		++result;
	}
	return result;
}

 
template<class It>
typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, ft::random_access_iterator_tag)
{
	return last - first;
}

template<class It>
typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, std::random_access_iterator_tag)
{
	return last - first;
}
}

template<class It>
typename ft::iterator_traits<It>::difference_type
	distance(It first, It last)
{
	return detail::do_distance(first, last,
							   typename ft::iterator_traits<It>::iterator_category());
}

}

#endif /* iterator_hpp */
