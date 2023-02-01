/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:52:55 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/23 21:08:26 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include "utils.hpp"
#include <vector>
#include <typeinfo>
#ifndef NS
# define NS	ft
#endif

bool	char_array_compare(const char* s1, const char* s2) {
	size_t i = 0;
	for (; s1[i] != '\0' && s2[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			return (false);
	}
	return (s1[i] == '\0' && s2[i] == '\0');
}

int	main() {
	std::cout << std::endl << "VECTOR TEST" << std::endl << std::endl;
	if (char_array_compare(typeid(NS::iterator_traits<NS::vector<int>::iterator>::iterator_category).name(), "N2ft26random_access_iterator_tagE"))
		std::cout << "Namespace is ft." << std::endl;
	else if (char_array_compare(typeid(NS::iterator_traits<NS::vector<int>::iterator>::iterator_category).name(), "NSt3__126random_access_iterator_tagE"))
		std::cout << "Namespace is std." << std::endl;

	std::cout << "CONSTRUCTOR TEST" << std::endl;
	{
		// constructors used in the same order as described above:
		NS::vector<int> first;                                // empty vector of ints

		std::cout << "The contents of first are:";
		for (NS::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::vector<int> second (4,100);                       // four ints with value 100

		std::cout << "The contents of second are:";
		for (NS::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::vector<int> third (second.begin(),second.end());  // iterating through second

		std::cout << "The contents of third are:";
		for (NS::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::vector<int> fourth (third);                       // a copy of third

		std::cout << "The contents of fourth are:";
		for (NS::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		NS::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
		
		std::cout << "The contents of fifth are:";
		for (NS::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "COPY_ASSIGNMENT OPERATOR TEST" << std::endl;
	{
		NS::vector<int> foo (3,0);
		NS::vector<int> bar (5,0);

		bar = foo;
		foo = NS::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << std::endl;
		std::cout << "Size of bar: " << int(bar.size()) << std::endl;

	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ITERATORS BEGIN AND END TEST" << std::endl;
	{
		NS::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);

		std::cout << "myvector contains:";
		for (NS::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
		NS::vector<int>::const_iterator	cit = myvector.begin();
		NS::vector<int>::iterator		it = myvector.begin();
		it++;
		std::cout << std::boolalpha << "cit == it : " << (cit == it) << std::endl;
		std::cout << std::boolalpha << "cit != it : " << (cit != it) << std::endl;
		std::cout << std::boolalpha << "it == cit : " << (it == cit) << std::endl;
		std::cout << std::boolalpha << "it != cit : " << (it != cit) << std::endl;

		std::cout << std::boolalpha << "cit > it : " << (cit > it) << std::endl;
		std::cout << std::boolalpha << "cit < it : " << (cit < it) << std::endl;
		std::cout << std::boolalpha << "it > cit : " << (it > cit) << std::endl;
		std::cout << std::boolalpha << "it < cit : " << (it < cit) << std::endl;

		std::cout << std::boolalpha << "cit >= it : " << (cit >= it) << std::endl;
		std::cout << std::boolalpha << "cit <= it : " << (cit <= it) << std::endl;
		std::cout << std::boolalpha << "it >= cit : " << (it >= cit) << std::endl;
		std::cout << std::boolalpha << "it <= cit : " << (it <= cit) << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CONST ITERATORS BEGIN AND END TEST" << std::endl;
	{
		int myints[] = {1,2,3,4,5};
		const NS::vector<int> myvector(myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "myvector contains:";
		for (NS::vector<int>::const_iterator it = myvector.begin() ; it != myvector.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "REVERSE_ITERATORS RBEGIN AND REND TEST" << std::endl;
	{
		NS::vector<int> myvector (5);  // 5 default-constructed ints

		int i=0;

		NS::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
		  *rit = ++i;

		std::cout << "myvector contains:";
		for (NS::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CONST REVERSE ITERATORS RBEGIN AND REND TEST" << std::endl;
	{
		int myints[] = {1,2,3,4,5};
		const NS::vector<int> myvector(myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "myvector contains:";
		for (NS::vector<int>::const_reverse_iterator it = myvector.rbegin(); it != myvector.rend(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SIZE() TEST" << std::endl;
	{
		NS::vector<int> myints;
		std::cout << "0. size: " << myints.size() << std::endl;

		for (int i=0; i<10; i++) myints.push_back(i);
		std::cout << "1. size: " << myints.size() << std::endl;

		myints.insert (myints.end(),10,100);
		std::cout << "2. size: " << myints.size() << std::endl;

		myints.pop_back();
		std::cout << "3. size: " << myints.size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "MAX_SIZE() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);

		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "max_size: " << myvector.max_size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "RESIZE() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		// set some initial content:
		for (int i=1;i<10;i++) myvector.push_back(i);

		myvector.resize(5);
		std::cout << "myvector contains:";
		for (unsigned i=0;i<myvector.size();i++)
		  std::cout << ' ' << myvector[i];
		myvector.resize(8,100);
		std::cout << std::endl << "myvector contains:";
		for (unsigned i=0;i<myvector.size();i++)
		  std::cout << ' ' << myvector[i];
		myvector.resize(12);
		std::cout << std::endl << "myvector contains:";
		for (unsigned i=0;i<myvector.size();i++)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CAPACITY() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);

		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "max_size: " << myvector.max_size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "EMPTY() TEST" << std::endl;
	{
		NS::vector<int> myvector;
		int sum (0);

		for (int i=1;i<=10;i++) myvector.push_back(i);

		while (!myvector.empty())
		{
		   sum += myvector.back();
		   myvector.pop_back();
		}

		std::cout << std::boolalpha << "myvector is empty: " << myvector.empty() <<
		std::endl << "total: " << sum << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "RESERVE() TEST" << std::endl;
	{
		NS::vector<int>::size_type sz;

		NS::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i=0; i<100; ++i) {
		  foo.push_back(i);
		  if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << std::endl;
		  }
		}

		NS::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for (int i=0; i<100; ++i) {
		  bar.push_back(i);
		  if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << std::endl;
		  }
		}
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "OPERATOR[] TEST" << std::endl;
	{
		NS::vector<int> myvector (10);   // 10 zero-initialized elements

		NS::vector<int>::size_type sz = myvector.size();

		// assign some values:
		for (unsigned i=0; i<sz; i++) myvector[i]=i;
		std::cout << "myvector contains:";
		for (unsigned i=0; i<sz; i++)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;

		// reverse vector using operator[]:
		for (unsigned i=0; i<sz/2; i++)
		{
		  int temp;
		  temp = myvector[sz-1-i];
		  myvector[sz-1-i]=myvector[i];
		  myvector[i]=temp;
		}

		std::cout << "myvector contains:";
		for (unsigned i=0; i<sz; i++)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "AT() TEST" << std::endl;
	{
		NS::vector<int> myvector (10);   // 10 zero-initialized ints

		// assign some values:
		for (unsigned i=0; i<myvector.size(); i++)
		  myvector.at(i)=i;
		// trying to reach unexisting element
		try {
			std::cout << myvector.at(10);
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
		  std::cout << ' ' << myvector.at(i);
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "FRONT() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();

		std::cout << "myvector.front() is now " << myvector.front() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "BACK() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();

		std::cout << "myvector.back() is now " << myvector.back() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "DATA() TEST" << std::endl;
	{
		NS::vector<int> myvector (5);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;

		int* p = myvector.data();

		*p = 10;
		++p;
		*p = 20;
		p[2] = 100;

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ASSIGN() TEST" << std::endl;
	{
		NS::vector<int> first;
		NS::vector<int> second;
		NS::vector<int> third;

		first.assign(7,100);             // 7 ints with a value of 100
		std::cout << "first contains:";
		for (unsigned i=0; i<first.size(); ++i)
		  std::cout << ' ' << first[i];
		std::cout << std::endl;

		NS::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first
		std::cout << "second contains:";
		for (unsigned i=0; i<second.size(); ++i)
		  std::cout << ' ' << second[i];
		std::cout << std::endl;

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.
		std::cout << "third contains:";
		for (unsigned i=0; i<third.size(); ++i)
		  std::cout << ' ' << third[i];
		std::cout << std::endl;

		std::cout << "Size of first: " << int (first.size()) << std::endl;
		std::cout << "Size of second: " << int (second.size()) << std::endl;
		std::cout << "Size of third: " << int (third.size()) << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "PUSH_BACK() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		for (int i = 0; i < 40000; ++i)
		  myvector.push_back (i);
		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
		std::cout << "myvector[39999] = " << myvector[39999] << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "POP_BACK TEST" << std::endl;
	{
		NS::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		while (!myvector.empty())
		{
		  sum+=myvector.back();
		  myvector.pop_back();
		}
		std::cout << "The elements of myvector add up to " << sum << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "INSERT() TEST" << std::endl;
	{
		NS::vector<int> myvector (3,100);
		NS::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		NS::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ERASE() TEST" << std::endl;
	{
		NS::vector<int> myvector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector.push_back(i);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;

		// erase the 6th element
		myvector.erase (myvector.begin()+5);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SWAP() TEST" << std::endl;
	{
		NS::vector<int> foo (3,100);   // three ints with a value of 100
		NS::vector<int> bar (5,200);   // five ints with a value of 200

		NS::vector<int>::iterator it1 = foo.begin();
		NS::vector<int>::iterator it2 = bar.begin();

		std::cout << "foo contains:";
		for (; it1 != foo.end(); ++it1)
		  std::cout << ' ' << *it1;
		std::cout << std::endl;

		std::cout << "bar contains:";
		for (; it2 != bar.end(); ++it2)
		  std::cout << ' ' << *it2;
		std::cout << std::endl;

		foo.swap(bar);

		----------it2;
		std::cout << "foo contains:";
		for (; it2 != foo.end(); ++it2)
		  std::cout << ' ' << *it2;
		std::cout << std::endl;

		------it1;
		std::cout << "bar contains:";
		for (; it1 != bar.end(); ++it1)
		  std::cout << ' ' << *it1;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CLEAR() TEST" << std::endl;
	{
		NS::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;

		myvector.clear();
		myvector.push_back (1101);
		myvector.push_back (2202);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
		  std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "GET_ALLOCATOR TEST" << std::endl;
	{
		NS::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "RELATIONAL OPERATORS TEST" << std::endl;
	{
		NS::vector<int> foo (3,100);   // three ints with a value of 100
		NS::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}
	std::cout << std::endl << "NS::SWAP TEST" << std::endl;
	{
		NS::vector<int> foo (3,100);   // three ints with a value of 100
		NS::vector<int> bar (5,200);   // five ints with a value of 200

		std::cout << "foo contains:";
		for (NS::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::swap(foo, bar);

		std::cout << "bar contains:";
		for (NS::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
}
