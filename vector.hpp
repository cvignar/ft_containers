/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:52:52 by cvignar           #+#    #+#             */
/*   Updated: 2022/12/26 19:52:52 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef vector_hpp
#define vector_hpp

#include "iterator.hpp"
#include "utils.hpp"
#include "random_access_iterator.hpp"

namespace ft {

template<
	class T,
	class Allocator = std::allocator<T>
> class vector {
public:
	/* Member types */
	typedef 			T												value_type;
	typedef 			Allocator										allocator_type;
	typedef 			std::size_t										size_type;
	typedef 			std::ptrdiff_t									difference_type;
	typedef 			value_type&										reference;
	typedef 			const value_type&								const_reference;
	typedef typename	Allocator::pointer								pointer;
	typedef	typename	Allocator::const_pointer						const_pointer;

	typedef 			random_access_iterator<value_type, false>		iterator;
	typedef 			random_access_iterator<const value_type, true>	const_iterator;
	typedef 			ft::reverse_iterator<iterator> 					reverse_iterator;
	typedef 			ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

	/* Member functions */

	/* Constructors */

	explicit vector(const Allocator& alloc = allocator_type()) : _capacity(0), _size(0), allocator(alloc) {}
	explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _capacity(0), _size(0), allocator(alloc) {
		if (count > 0)
			insert(begin(), count, value);
	}
	template< class InputIt >
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		   typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type* = 0) : _capacity(0), _size(0), allocator(alloc) { insert(begin(), first, last); }
	vector(const vector& other) :_capacity(0), _size(0), allocator(other.allocator) { *this = other; }

	/* Destructor */

	~vector() {
		for (size_type i = 0; i < _size; ++i)
			allocator.destroy(arr + i);
		if (_capacity > 0)
			allocator.deallocate(arr, _capacity);
		_size = 0;
		_capacity = 0;
	}

	/* copy-assingment operator */

	vector& operator=( const vector& other ) {
		size_type	i = 0;
		if (_capacity < other._size) {
			T*	newarr = NULL;
			if (other._capacity != 0)
				newarr = allocator.allocate(other._size);
			try {
				for (; i < other._size; ++i)
					allocator.construct(newarr + i, other.arr[i]);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					allocator.destroy(newarr + j);
				allocator.deallocate(newarr, other._size);
				throw ;
			}
			delete_arr(arr, _capacity, _size);
			arr = newarr; newarr = NULL;
			_size = other._size; _capacity = other._size;
		}
		else {
			T*	copy = copy_arr(_capacity);
			clear();
			try {
				for (; i < other._size; ++i)
					allocator.construct(arr + i, other.arr[i]);
			}
			catch (...) {
				for (size_type j = 0; j < i; ++j)
					allocator.destroy(arr + j);
				allocator.deallocate(arr, _capacity);
				arr = copy; copy = NULL;
				throw ;
			}
			delete_arr(copy, _capacity, _size);
			_size = other._size;
		}
		return (*this);
	}

	/* Assign */

	void assign( size_type count, const T& value ) {
		clear();
		insert(NULL, count, value);
	}
	template< class InputIt >
	void assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) {
		clear();
		insert(NULL, first, last);
	}

	/* get_allocator */

	allocator_type get_allocator() const { return (allocator); }

	/* Element access */

	reference			at( size_type pos ) {
		if (!(pos < _size))
			throw std::out_of_range("std::vector::at: key not found");
		return (arr[pos]);
	}
	const_reference 	at( size_type pos ) const {
		if (!(pos < _size))
			throw std::out_of_range("std::vector::at: key not found");
		return (arr[pos]);
	}
	reference			operator[](size_type pos) const { return (arr[pos]); }
	reference			front() { return (*arr); }
	const_reference		front() const { return (*arr); }
	reference			back() { return (*(--end())); }
	const_reference		back() const { return (*(--end())); }
	value_type*			data() { return (arr); }
	const value_type*	data() const { return (arr); }


	/* Iterators */

	iterator				begin() { return (iterator(arr)); }
	const_iterator			begin() const { return (const_iterator(arr)); }
	iterator				end() { return (iterator(arr + _size)); }
	const_iterator			end() const { return (const_iterator(arr + _size)); }
	reverse_iterator		rbegin() { return(reverse_iterator(end())); }
	const_reverse_iterator	rbegin() const { return(const_reverse_iterator(end())); }
	reverse_iterator		rend() { return (reverse_iterator(begin())); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }


	/* Capacity */

	bool		empty(void) const { return (begin() == end()); }
	size_type	size(void) const { return (_size); }
	size_type	max_size(void) const { return (allocator.max_size()); }
	void		reserve( size_type new_cap ) {
		if (new_cap <= _capacity && _capacity != 0)
			return ;
		T*	newarr = allocator.allocate(new_cap);
		size_type	i = 0;
		try {
			for ( ; i < _size; ++i)
				allocator.construct(newarr + i, arr[i]);
		}
		catch (...) {
			for (size_type j = 0; j < i; ++j)
				allocator.destroy(newarr + j);
			allocator.deallocate(newarr, new_cap);
			throw;
		}
		for (i = 0; i < _size; ++i)
			allocator.destroy(arr + i);
		if (_capacity > 0)
			allocator.deallocate(arr, _capacity);
		arr = newarr;
		_capacity = new_cap;
	}
	size_type	capacity(void) const { return (_capacity); }

	/* Modifiers */

	void		clear(void) {
		size_type	i = 0;
		for(; i != _size; ++i)
			allocator.destroy(arr + i);
		_size = 0;
	}
	iterator	insert( iterator pos, const T& value ) { return (insert(pos, 1, value)); }
	iterator	insert( iterator pos, size_type count, const T& value ) {
		if (count == 0)
			return (pos);
		size_type	new_size = _size + count;
		size_type	position = (_capacity == 0 || pos == NULL ? 0 : check_pos(pos));
		size_type	new_cap = (_capacity * 2 < new_size || pos == NULL ? new_size : _capacity * 2);
		size_type	range_end = position + count;
		if (_capacity < new_size)
		{
			T*	newarr = allocator.allocate(new_cap);
			size_type	i = 0;
			try {
				for (; i < position; ++i)
					allocator.construct(newarr + i, arr[i]);
				for (; i < range_end; ++i)
					allocator.construct(newarr + i, value);
				for (; i < new_size; ++i)
					allocator.construct(newarr + i, arr[i - count]);
			}
			catch (...) {
				for (size_type j = 0; j < i; ++j)
					allocator.destroy(newarr + j);
				allocator.deallocate(newarr, new_cap);
				throw;
			}
			for (i = 0; i < _size; ++i)
				allocator.destroy(arr + i);
			if (_capacity != 0)
				allocator.deallocate(arr, _capacity);
			arr = newarr;
			_size = new_size;
			_capacity = new_cap;
		}
		else {
			size_type	i = new_size;
			T*	copy = copy_arr(_capacity);
			try {
				for (; i > range_end; --i) {
					allocator.construct(arr + i - 1, *(arr + (i - count - 1)));
					allocator.destroy(arr + (i - count - 1));
				}
				for (; i > position; --i) {
					allocator.construct(arr + i - 1, value);
				}
			}
			catch (...) {
				for (size_type j = 0; j < i - 1; ++j)
					allocator.destroy(arr + j);
				if (_capacity > 0)
					allocator.deallocate(arr, _capacity);
				arr = copy;
			}
			for (i = 0; i < _size; ++i)
				allocator.destroy(copy + i);
			allocator.deallocate(copy, _capacity);
			_size = new_size;
		}
		return (iterator(arr + position));
	}
	template< class InputIt >
	iterator	insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) {
		difference_type	rng = range_size(first, last);
		size_type	position = (_capacity == 0 || pos == NULL ? 0 : check_pos(pos));
		size_type	range = (size_type)rng;
		size_type	new_cap = (_capacity * 2 < _size + range || pos == NULL ? _size + range : _capacity * 2);
		size_type	new_size = _size + range;
		size_type	range_end = position + range;
		if (_capacity < new_size)
		{
			T*	newarr = allocator.allocate(new_cap);
			size_type	i = 0;
			try {
				for (; i < position; ++i)
					allocator.construct(newarr + i, arr[i]);
				for (; i < range_end; ++i, ++first)
					allocator.construct(newarr + i, *first);
				for (; i < new_size; ++i)
					allocator.construct(newarr + i, arr[i - range]);
			}
			catch (...) {
				for (size_type j = 0; j < i; ++j)
					allocator.destroy(newarr + j);
				allocator.deallocate(newarr, new_cap);
				throw;
			}
			for (i = 0; i < _size; ++i)
				allocator.destroy(arr + i);
			if (_capacity > 0)
				allocator.deallocate(arr, _capacity);
			arr = newarr;
			_size = new_size;
			_capacity = new_cap;
		}
		else {
			size_type	i = new_size;
			T*	copy = copy_arr(_capacity);
			try {
				for (; i > range_end; --i) {
					allocator.construct(arr + i - 1, *(arr + (i - range - 1)));
					allocator.destroy(arr + (i - range - 1));
				}
				--last;
				for (; i > position; --i, --last) {
					allocator.construct(arr + i - 1, *last);
				}
			}
			catch (...) {
				for (size_type j = 0; j < i - 1; ++j)
					allocator.destroy(arr + j);
				if (_capacity)
					allocator.deallocate(arr, _capacity);
				arr = copy;
				throw;
			}
			for (i = 0; i < _size; ++i)
				allocator.destroy(copy + i);
			allocator.deallocate(copy, _capacity);
			_size = new_size;
		}
		return (iterator(arr + position));
	}
	iterator	erase( iterator pos ) {
		size_type	position = check_pos(pos);
		return (common_erase(position, 1));
	}
	iterator	erase( iterator first, iterator last ) {
		size_type	position_first = check_pos(first);
		size_type	position_last = check_pos(last);
		return (common_erase(position_first, position_last - position_first));
	}
	void		push_back( const T& value ) {
		if (_capacity > 0) {
			if (_size == _capacity)
				reserve(_capacity * 2);
				allocator.construct(arr + _size, value);
				++_size;
		}
		else {
			arr = allocator.allocate(1);
			++_capacity;
			try {
				allocator.construct(arr, value);
				++_size;
			} catch (...) {
				allocator.deallocate(arr, 1);
				--_capacity;
				throw;
			}
		}

	}
	void		pop_back(void) {
		if (_size > 0) {
			allocator.destroy(arr + (_size - 1));
			_size--;
		}
	}
	void		resize( size_type count, T value = T() ) {
		
		if (_size == count)
			return ;
		if (_size > count) {
			for (size_type i = count; i < _size; ++i)
				allocator.destroy(arr + i);
			_size = count;
		} else {
			if (_capacity < count) {
				size_type i = 0;
				size_type	new_cap = (_capacity * 2 >= count ? _capacity * 2 : count);
				T*	newarr = allocator.allocate(new_cap);
				try {
					for (; i < _size; ++i)
						allocator.construct(newarr + i, arr[i]);
					for (; i < count; ++i)
						allocator.construct(newarr + i, value);
				} catch (...) {
					for (size_type j = 0; j < i; ++j)
						allocator.destroy(newarr + j);
					allocator.deallocate(newarr, new_cap);
					throw;
				}
				for (i = 0; i < _size; ++i)
					allocator.destroy(arr + i);
				if (_capacity > 0)
					allocator.deallocate(arr, _capacity);
				arr = newarr;
				_capacity = new_cap;
				_size = count;
			} else {
				size_type i = _size;
				T*	copy = copy_arr(_capacity);
				try {
					for (; i < count; ++i)
						allocator.construct(arr + i, value);
				} catch (...) {
					for (size_type j = 0; j < i; ++j)
						allocator.destroy(arr + j);
					if (_capacity > 0)
						allocator.deallocate(arr, _capacity);
					arr = copy;
					throw;
				}
				for (i = 0; i < _size; ++i)
					allocator.destroy(copy + i);
				allocator.deallocate(copy, _capacity);
				_size = count;
			}
		}
	}
	void		swap( vector& other ) {
		T* 			tmp = arr;
		size_type	tmp_capacity = _capacity;
		size_type	tmp_size = _size;
		arr = other.arr;
		other.arr = tmp;
		_capacity = other._capacity;
		other._capacity = tmp_capacity;
		_size = other._size;
		other._size = tmp_size;
	}

protected:

	/* Member objects */

	size_type		_capacity;
	size_type		_size;
	allocator_type	allocator;
	T*				arr;

	/* Utils */

	iterator	common_erase(size_type position, difference_type distance) {
		if (distance <= 0 || position == _size)
			return(arr + position);
		size_type	range_end = position + distance;
		T*			copy = copy_arr(_capacity);
		size_type	i = position;
		try {
			for (; i < range_end; ++i) {
				allocator.destroy(arr + i);
			}
			for (; i < _size; ++i) {
				allocator.construct(arr + i - distance, *(arr + i));
				allocator.destroy(arr + i);
			}
		} catch (...) {
			for (size_type j = 0; j < i - distance; ++j)
				allocator.destroy(arr + j);
			for (; i < _size; ++i)
				allocator.destroy(arr + i);
			if (_capacity > 0)
				allocator.deallocate(arr, _capacity);
			arr = copy;
		}
		for (i = 0; i < _size; ++i)
			allocator.destroy(copy + i);
		allocator.deallocate(copy, _capacity);
		_size = _size - distance;
		return (iterator(arr + position));
	}
	size_type	check_pos(iterator pos) {
		size_type	i = 0;
		iterator	it = begin();
		iterator	e = end();
		for (; it != e; ++it, ++i) {
			if (it == pos)
				return (i);
		}
		if (it == pos)
			return (i);
		throw std::out_of_range("ft::vector::insert: pos not found\n");
	}
	T*	copy_arr(size_type cap) {
		T* copy = NULL;
		if (cap != 0) {
			copy = allocator.allocate(cap);
			size_type	i = 0;
			try {
				for ( ; i < _size; ++i)
					allocator.construct(copy + i, arr[i]);
			}
			catch (...) {
				for (size_type j = 0; j < i; ++j)
					allocator.destroy(copy + j);
				allocator.deallocate(copy, cap);
				throw;
			}
		}
		return (copy);
	}
	template< class InputIt >
	difference_type	range_size(InputIt first, InputIt last) { return (ft::distance(first, last)); }
	void	delete_arr(T* array, size_type c, size_type s) {
		for (size_type i = 0; i < s; ++i)
			allocator.destroy(array + i);
		if (c > 0)
			allocator.deallocate(array, c);
	}
};

/*====================Non-member functions====================*/

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs ) {
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}
template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs ) {
	return (!(lhs == rhs));
}
template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
			   const ft::vector<T,Alloc>& rhs ) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs ) {
	return (!(rhs < lhs));
}
template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
			   const ft::vector<T,Alloc>& rhs ) {
	return (rhs < lhs);
}
template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs ) {
	return (!(lhs < rhs));
}
template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& lhs,
		  ft::vector<T,Alloc>& rhs ) {
	lhs.swap(rhs);
}
}



#endif /* vector_h */
