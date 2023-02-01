/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:53:52 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/05 01:53:52 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace	ft {

template<typename T, bool isConst = false>
class	random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {

protected:
	typename ft::remove_const<T>::type*	ptr;

public:
	typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;

	typedef	ft::random_access_iterator<typename ft::remove_const<value_type>::type>	non_const_iterator;

	random_access_iterator() : ptr(NULL) {}
	random_access_iterator(pointer other_ptr) {
		ptr = const_cast<typename ft::remove_const<T>::type*>(other_ptr);
	}
	random_access_iterator(const non_const_iterator& other) : ptr(other.get_ptr()) {}
	~random_access_iterator() {}
	random_access_iterator	operator=(const non_const_iterator& other) {
		ptr = other.get_ptr();
		return (*this);
	}

	reference	operator*() const { return (*ptr); }
	pointer		operator->() const { return (&(*ptr)); }
	random_access_iterator&		operator++(void) {
		ptr++;
		return (*this);
	}
	random_access_iterator			operator++(int) {
		random_access_iterator	tmp = *this;
		++(*this);
		return (tmp);
	}
	random_access_iterator&		operator--(void) {
		ptr--;
		return (*this);
	}
	random_access_iterator		operator--(int) {
		random_access_iterator<T, isConst>	tmp = *this;
		--(*this);
		return (tmp);
	}

	random_access_iterator	operator+(const difference_type& n) {
		random_access_iterator	tmp(ptr);
		return (tmp += n);
	}

	random_access_iterator	operator-(const difference_type& n) {
		random_access_iterator	tmp(ptr);
		return (tmp -= n);
	}

	random_access_iterator&		operator+=(difference_type n) {
		difference_type	m = n;
		if (m >= 0) {
			while (m--)
				++(*this);
		}
		else {
			while (m++)
				--(*this);
		}
		return (*this);
	}
	random_access_iterator&		operator-=(difference_type n) {
		return (*this += -n);
	}

	reference				operator[](difference_type n) {
		return (*(ptr + n));
	}
	pointer						get_ptr() const{
		return(ptr);
	}

	friend bool		operator==(const random_access_iterator& lhs, const random_access_iterator& rhs) { return (lhs.get_ptr() == rhs.get_ptr()); }
	friend bool		operator!=(const random_access_iterator& lhs, const random_access_iterator& rhs) { return (lhs.get_ptr() != rhs.get_ptr()); }

	friend bool		operator<(const random_access_iterator& lhs, const random_access_iterator& rhs) { return (rhs.get_ptr() - lhs.get_ptr() > 0); }
	friend bool		operator>(const random_access_iterator& lhs, const random_access_iterator& rhs) { return (rhs < lhs); }
	friend bool		operator<=(const random_access_iterator& lhs, const random_access_iterator& rhs) { return (!(lhs > rhs)); }
	friend bool		operator>=(const random_access_iterator& lhs, const random_access_iterator& rhs) { return (!(lhs < rhs)); }

};

template<typename T, bool isConst>
random_access_iterator<T, isConst>	operator+(const typename random_access_iterator<T, isConst>::difference_type& n, const random_access_iterator<T, isConst>& it){
	random_access_iterator<T, isConst>	tmp(it.get_ptr());
	return (tmp += n);
}

template<typename T, bool isConst>
typename random_access_iterator<T, isConst>::difference_type			operator-(const random_access_iterator<T, isConst>& lhs, const random_access_iterator<T, isConst>& rhs) {
	typename random_access_iterator<T, isConst>::difference_type	n = lhs.get_ptr() - rhs.get_ptr();
	return (n);
}

template<typename T>
typename random_access_iterator<const T, true>::difference_type	operator-(const random_access_iterator<const T, true>& lhs, const random_access_iterator<typename ft::remove_const<T>::type>& rhs) {
	typename random_access_iterator<T, true>::difference_type	n = lhs.get_ptr() - rhs.get_ptr();
	return (n);
}

template<typename T>
typename random_access_iterator<typename ft::remove_const<T>::type>::difference_type	operator-(const random_access_iterator<typename ft::remove_const<T>::type>& lhs, const random_access_iterator<const T, true>& rhs) {
	typename random_access_iterator<T, true>::difference_type	n = lhs.get_ptr() - rhs.get_ptr();
	return (n);
}

}

#endif /* random_access_iterator_h */
