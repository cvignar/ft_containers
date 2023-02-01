/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:13:40 by cvignar           #+#    #+#             */
/*   Updated: 2022/12/10 18:13:40 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {

struct	input_iterator_tag {};
struct	output_iterator_tag {};
struct	forward_iterator_tag : public input_iterator_tag {};
struct	bidirectional_iterator_tag : public forward_iterator_tag {};
struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

template< class Iter >
struct	iterator_traits {
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template< class T >
struct	iterator_traits<T*> {
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template< typename T>
struct iterator_traits<const T*> {
	typedef std::ptrdiff_t					difference_type;
	typedef const T							value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

static class	nullptr_t {
public:
	template<class T>
	operator	T*() const {return (0);}
	template<class C, class T>
	operator	T	C::*() const {return (0);}
	template<class T>
	T			operator->() const {return (0);}
private:
	void	operator&() const;
} u_nullptr = {};

/* enable_if implementation */

template<bool B, typename T = void>
struct	enable_if {};

template<typename T>
struct enable_if<true, T> {
	typedef T	type;
};

/* remove_const implementation */

template <typename T>
struct	remove_const {

	typedef T	type;
};

template <typename T>
struct	remove_const<const T> {

	typedef T	type;
};

/* remove_reference implementation */

template <typename T>
struct	remove_reference {

	typedef T	type;
};

template <typename T>
struct	remove_reference<T&> {

	typedef T	type;
};

/* integral_constant implementation */

template <class T, T v>
struct	integral_constant
{
	typedef T						value_type;
	typedef integral_constant<T, v>	type;
	static const T					value = v;
	operator T() {return v;}
};

/* is_integral implementation */
typedef ft::integral_constant<bool, true>	true_type;
typedef ft::integral_constant<bool, false>	false_type;

template <class T> struct	is_integral : ft::integral_constant<bool, false> {};

template <> struct	is_integral<bool> : ft::integral_constant<bool, true> {};
template <> struct	is_integral<char> : ft::integral_constant<char, true> {};
template <> struct	is_integral<signed char> : ft::integral_constant<signed char, true> {};
template <> struct	is_integral<unsigned char> : ft::integral_constant<unsigned char, true> {};
template <> struct	is_integral<short> : ft::integral_constant<short, true> {};
template <> struct	is_integral<unsigned short> : ft::integral_constant<unsigned short, true> {};
template <> struct	is_integral<int> : ft::integral_constant<int, true> {};
template <> struct	is_integral<unsigned int> : ft::integral_constant<unsigned int, true> {};
template <> struct	is_integral<long> : ft::integral_constant<long, true> {};
template <> struct	is_integral<unsigned long> : ft::integral_constant<unsigned long, true> {};
template <> struct	is_integral<long long> : ft::integral_constant<long long, true> {};
template <> struct	is_integral<unsigned long long> : ft::integral_constant<unsigned long long, true> {};
template <> struct	is_integral<wchar_t> : ft::integral_constant<wchar_t, true> {};
template <> struct	is_integral<char16_t> : ft::integral_constant<char16_t, true> {};

/* is_const implementation */

template<class T> struct is_const          : ft::false_type {};
template<class T> struct is_const<const T> : ft::true_type {};

/* conditional implementation */

template<bool B, class T, class F>
struct	conditional {
	typedef T	type;
};

template<class T, class F>
struct	conditional<false, T, F> {
	typedef F	type;
};

/* equal first implementation */

template<	class InputIt1, class InputIt2 >
bool	equal( InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	
	for (; first1 != last1; ++first1, ++first2) {
		
		if (!(*first1 == *first2))
			return (false);
	}
	return (true);
}

/* equal second implementation with comparing function */

template <	class InputIt1,
			class InputIt2,
			class BinaryPredicate >
bool	equal(	InputIt1 first1,
			  InputIt1 last1,
			  InputIt2 first2,
			  BinaryPredicate p) {
	
	for (; first1 != last1; ++first1, ++first2) {
		
		if (!p(*first1, *first2))
			return (false);
	}
	return (true);
}

/* lexicographical_compare first implementation */

template<	class InputIt1, class InputIt2 >
bool	lexicographical_compare(	InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2) {

	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {

		if (*first1 < *first2)
			return (true);
		if (*first2 < *first1)
			return (false);
	}
	return ((first1 == last1) && (first2 != last2));
}

/* lexicographical_compare second implementation
 * with comparing function */

template<	class InputIt1, class InputIt2, class Compare >
bool	lexicographical_compare(	InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2, Compare comp) {

	for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {

		if (comp(*first1, *first2))
			return (true);
		if (comp(*first2, *first1))
			return (false);
	}
	return ((first1 == last1) && (first2 != last2));
}
}

#endif
