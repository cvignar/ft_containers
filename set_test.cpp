/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:54:18 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/23 21:08:21 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include "set.hpp"
#include "utils.hpp"
#include <typeinfo>

#ifndef NS
# define NS ft
#endif

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

template<class T>
struct print{
	void operator()(T n) {
		std::cout << " " << n;
	}
};
	
bool	char_array_compare(const char* s1, const char* s2) {
	size_t i = 0;
	for (; s1[i] != '\0' && s2[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			return (false);
	}
	return (s1[i] == '\0' && s2[i] == '\0');
}

int	main() {
	std::cout << std::endl << "SET TEST" << std::endl << std::endl;
	if (char_array_compare(typeid(NS::iterator_traits<NS::set<int>::iterator>::iterator_category).name(), "N2ft26bidirectional_iterator_tagE"))
		std::cout << "Namespace is ft." << std::endl;
	else if (char_array_compare(typeid(NS::iterator_traits<NS::set<int>::iterator>::iterator_category).name(), "NSt3__126bidirectional_iterator_tagE"))
		std::cout << "Namespace is std." << std::endl;
	std::cout << "CONSTRUCTOR TEST" << std::endl;
	{
		NS::set<int> first;                           // empty set of ints

		std::cout << "first contains: ";
		for (NS::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		int myints[]= {10,20,30,40,50};
		NS::set<int> second (myints,myints+5);        // range

		std::cout << "second contains: ";
		for (NS::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		NS::set<int> third (second);                  // a copy of second

		std::cout << "third contains: ";
		for (NS::set<int>::iterator it=third.begin(); it!=third.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		NS::set<int> fourth (second.begin(), second.end());  // iterator ctor.

		std::cout << "fourth contains: ";
		for (NS::set<int>::iterator it=fourth.begin(); it!=fourth.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		NS::set<int,classcomp> fifth;                 // class as Compare

		bool(*fn_pt)(int,int) = fncomp;
		NS::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

		std::cout << "fifth contains: ";
		for (NS::set<int>::iterator it=fifth.begin(); it!=fifth.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "COPY-ASSIGNMENT OPERATOR TEST" << std::endl;
	{
		int myints[]={ 12,82,37,64,15 };
		NS::set<int> first (myints,myints+5);   // set with 5 ints

		std::cout << "first contains: ";
		for (NS::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		NS::set<int> second;                    // empty set

		second = first;                          // now second contains the 5 ints

		std::cout << "second contains: ";
		for (NS::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		first = NS::set<int>();                 // and first is empty

		std::cout << "first contains: ";
		for (NS::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		  std::cout << *it << ' ';
		std::cout << std::endl;

		std::cout << "Size of first: " << int (first.size()) << std::endl;
		std::cout << "Size of second: " << int (second.size()) << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ITERATOR BEGIN AND END TEST" << std::endl;
	{

		int myints[] = {75,23,65,42,13};
		NS::set<int> myset (myints,myints+5);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
		NS::set<int>::const_iterator	cit = myset.begin();
		NS::set<int>::iterator	it = myset.begin();
		it++;
		std::cout << std::boolalpha << "cit == it : " << (cit == it) << std::endl;
		std::cout << std::boolalpha << "cit != it : " << (cit != it) << std::endl;
		std::cout << std::boolalpha << "it == cit : " << (it == cit) << std::endl;
		std::cout << std::boolalpha << "it != cit : " << (it != cit) << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CONST ITERATOR BEGIN AND END TEST" << std::endl;
	{
		int myints[] = {75,23,65,42,13};
		const NS::set<int> myset (myints,myints+5);

		std::cout << "myset contains:";
		for (NS::set<int>::const_iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "REVERSE ITERATORS RBEGIN AND REND TEST" << std::endl;
	{
		int myints[] = {21,64,17,78,49};
		NS::set<int> myset (myints,myints+5);

		NS::set<int>::reverse_iterator rit;

		std::cout << "myset contains:";
		for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		  std::cout << ' ' << *rit;

		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CONST REVERSE ITERATORS RBEGIN AND REND TEST" << std::endl;
	{
		int myints[] = {21,64,17,78,49};
		const NS::set<int> myset (myints,myints+5);

		NS::set<int>::const_reverse_iterator rit;

		std::cout << "myset contains:";
		for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		  std::cout << ' ' << *rit;

		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "EMPTY() TEST" << std::endl;
	{
		NS::set<int> myset;

		myset.insert(20);
		myset.insert(30);
		myset.insert(10);

		std::cout << "myset contains:";
		while (!myset.empty())
		{
		   std::cout << ' ' << *myset.begin();
		   myset.erase(myset.begin());
		}
		std::cout << std::endl;
		std::cout << std::boolalpha << "myset is empty: " << myset.empty() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SIZE() TEST" << std::endl;
	{
		NS::set<int> myints;
		std::cout << "0. size: " << myints.size() << std::endl;

		for (int i=0; i<10; ++i) myints.insert(i);
		std::cout << "1. size: " << myints.size() << std::endl;

		myints.insert (100);
		std::cout << "2. size: " << myints.size() << std::endl;

		myints.erase(5);
		std::cout << "3. size: " << myints.size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "MAX_SIZE() TEST" << std::endl;
	{
		int i;
		NS::set<int> myset;

		if (myset.max_size()>1000)
		{
		  for (i=0; i<1000; i++) myset.insert(i);
		  std::cout << "The set contains 1000 elements.\n";
		}
		else std::cout << "The set could not hold 1000 elements.\n";
		std::cout << "myset max_size = " << myset.max_size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "INSERT() TEST" << std::endl;
	{
		NS::set<int> myset;
		NS::set<int>::iterator it;
		NS::pair<NS::set<int>::iterator,bool> ret;

		// set some initial values:
		for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		ret = myset.insert(20);               // no new element inserted

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		if (ret.second==false) it=ret.first;  // "it" now points to element 20

		myset.insert (it,25);                 // max efficiency inserting
		myset.insert (it,24);                 // max efficiency inserting
		myset.insert (it,26);                 // no max efficiency inserting

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		int myints[]= {5,10,15};              // 10 already in set, not inserted
		myset.insert (myints,myints+3);

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ERASE() TEST" << std::endl;
	{
		NS::set<int> myset;
		NS::set<int>::iterator it;

		// insert some values:
		for (int i=1; i<10; i++) myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		it = myset.begin();
		++it;                                         // "it" points now to 20

		myset.erase (it);

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		myset.erase (40);

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		it = myset.find (60);
		myset.erase (it, myset.end());

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SWAP() TEST" << std::endl;
	{
		int myints[]={12,75,10,32,20,25};
		NS::set<int> first (myints,myints+3);     // 10,12,75
		NS::set<int> second (myints+3,myints+6);  // 20,25,32
		NS::set<int>::iterator it1 = first.begin();
		NS::set<int>::iterator it2 = second.begin();

		std::cout << "first contains:";
		for (; it1!=first.end(); ++it1)
		  std::cout << ' ' << *it1;
		std::cout << std::endl;

		std::cout << "second contains:";
		for (; it2!=second.end(); ++it2)
		  std::cout << ' ' << *it2;
		std::cout << std::endl;

		------it1;
		------it2;
		first.swap(second);

		std::cout << "first contains:";
		for (; it2!=first.end(); ++it2)
		  std::cout << ' ' << *it2;
		std::cout << std::endl;

		std::cout << "second contains:";
		for (; it1!=second.end(); ++it1)
		  std::cout << ' ' << *it1;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CLEAR() TEST" << std::endl;
	{
		NS::set<int> myset;

		myset.insert (100);
		myset.insert (200);
		myset.insert (300);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		myset.clear();

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		myset.insert (1101);
		myset.insert (2202);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "KEY_COMP() TEST" << std::endl;
	{
		NS::set<int> myset;
		int highest;

		NS::set<int>::key_compare mycomp = myset.key_comp();

		for (int i=0; i<=5; i++) myset.insert(i);

		std::cout << "myset contains:";

		highest=*myset.rbegin();
		NS::set<int>::iterator it=myset.begin();
		do {
		  std::cout << ' ' << *it;
		} while ( mycomp(*(++it),highest) );

		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "VALUE_COMP() TEST" << std::endl;
	{
		NS::set<int> myset;

		NS::set<int>::value_compare mycomp = myset.value_comp();

		for (int i=0; i<=5; i++) myset.insert(i);

		std::cout << "myset contains:";

		int highest=*myset.rbegin();
		NS::set<int>::iterator it=myset.begin();
		do {
		  std::cout << ' ' << *it;
		} while ( mycomp(*(++it),highest) );

		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "FIND() TEST" << std::endl;
	{
		NS::set<int> myset;
		NS::set<int>::iterator it;

		// set some initial values:
		for (int i=1; i<=5; i++) myset.insert(i*10);    // set: 10 20 30 40 50

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		it=myset.find(20);
		myset.erase (it);
		myset.erase (myset.find(40));

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "COUNT() TEST" << std::endl;
	{
		NS::set<int> myset;
		NS::set<int>::iterator it;

		// set some initial values:
		for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

		std::cout << "myset contains:";
		for (it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		for (int i=0; i<10; ++i)
		{
		  std::cout << i;
		  if (myset.count(i)!=0)
			std::cout << " is an element of myset.\n";
		  else
			std::cout << " is not an element of myset.\n";
		}
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "LOWER_BOUND() AND UPPER_BOUND() TEST" << std::endl;
	{
		NS::set<int> myset;
		NS::set<int>::iterator itlow,itup;

		for (int i=1; i<10; i++) myset.insert(i*10);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		itlow=myset.lower_bound (30);
		itup=myset.upper_bound (60);

		myset.erase(itlow,itup);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << std::endl << "LOWER_BOUND() AND UPPER_BOUND() TEST" << std::endl;
	{
		NS::set<int> myset;
		NS::set<int>::iterator itlow,itup;

		for (int i=1; i<10; i++) myset.insert(i*10);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		itlow=myset.lower_bound (30);
		itup=myset.upper_bound (60);

		myset.erase(itlow,itup);

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "EQUAL_RANGE() TEST" << std::endl;
	{
		NS::set<int> myset;

		for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

		std::cout << "myset contains:";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		  std::cout << ' ' << *it;
		std::cout << std::endl;

		NS::pair<NS::set<int>::const_iterator,NS::set<int>::const_iterator> ret;
		ret = myset.equal_range(30);

		std::cout << "the lower bound of equal_range(30) points to: " << *ret.first << std::endl;
		std::cout << "the upper bound of equal_range(30) points to: " << *ret.second << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "GET_ALLOCATOR() TEST" << std::endl;
	{
		NS::set<int> myset;
		int * p;
		unsigned int i;

		// allocate an array of 5 elements using myset's allocator:
		p=myset.get_allocator().allocate(5);

		// assign some values to array
		for (i=0; i<5; i++) p[i]=(i+1)*10;

		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << std::endl;

		myset.get_allocator().deallocate(p,5);
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "RELATIONAL OPERATORS TEST" << std::endl;
	{
		NS::set<int> alice;
		alice.insert(1);
		alice.insert(2);
		alice.insert(3);
		NS::set<int> bob;
		bob.insert(7);
		bob.insert(8);
		bob.insert(9);
		bob.insert(10);
		NS::set<int> eve;
		eve.insert(1);
		eve.insert(2);
		eve.insert(3);
	 
		std::cout << std::boolalpha;
	 
		// Compare non equal containers
		std::cout << "alice == bob returns " << (alice == bob) << std::endl;
		std::cout << "alice != bob returns " << (alice != bob) << std::endl;
		std::cout << "alice <  bob returns " << (alice < bob) << std::endl;
		std::cout << "alice <= bob returns " << (alice <= bob) << std::endl;
		std::cout << "alice >  bob returns " << (alice > bob) << std::endl;
		std::cout << "alice >= bob returns " << (alice >= bob) << std::endl;
	 
		std::cout << std::endl;
	 
		// Compare equal containers
		std::cout << "alice == eve returns " << (alice == eve) << std::endl;
		std::cout << "alice != eve returns " << (alice != eve) << std::endl;
		std::cout << "alice <  eve returns " << (alice < eve) << std::endl;
		std::cout << "alice <= eve returns " << (alice <= eve) << std::endl;
		std::cout << "alice >  eve returns " << (alice > eve) << std::endl;
		std::cout << "alice >= eve returns " << (alice >= eve) << std::endl;	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "NS::SWAP() TEST" << std::endl;
	{
		NS::set<int> alice;
		alice.insert(1);
		alice.insert(2);
		alice.insert(3);
		NS::set<int> bob;
		bob.insert(7);
		bob.insert(8);
		bob.insert(9);
		bob.insert(10);

		// Print state before swap
		std::cout << "alice:";
		std::for_each(alice.begin(), alice.end(), print<int>());
		std::cout << "\n" "bob  :";
		std::for_each(bob.begin(), bob.end(), print<int>());
		std::cout << std::endl;
	 
		std::cout << "-- SWAP\n";
		std::swap(alice, bob);
	 
		// Print state after swap
		std::cout << "alice:";
		std::for_each(alice.begin(), alice.end(), print<int>());
		std::cout << "\n" "bob  :";
		std::for_each(bob.begin(), bob.end(), print<int>());
		std::cout << std::endl;
	}
}
