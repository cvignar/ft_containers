/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:51:05 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/23 21:08:17 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "map.hpp"
#include "utils.hpp"
#include <typeinfo>

#ifndef NS
# define NS ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

template<class T, class U>
struct print{
	void operator()(typename NS::pair<T, U> n) {
		std::cout << " " << n.first << '(' << n.second << ')';
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
	std::cout << std::endl << "MAP TEST" << std::endl << std::endl;
	if (char_array_compare(typeid(NS::iterator_traits<NS::map<int, int>::iterator>::iterator_category).name(), "N2ft26bidirectional_iterator_tagE"))
		std::cout << "Namespace is ft." << std::endl;
	else if (char_array_compare(typeid(NS::iterator_traits<NS::map<int, int>::iterator>::iterator_category).name(), "NSt3__126bidirectional_iterator_tagE"))
		std::cout << "Namespace is std." << std::endl;
	std::cout << "CONSTRUCTOR TEST" << std::endl;
	{
		NS::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		std::cout << "first contains: ";
		for (NS::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
			std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		NS::map<char,int> second (first.begin(),first.end());
		std::cout << "second contains: ";
		for (NS::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
			std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		NS::map<char,int> third (second);
		std::cout << "third contains: ";
		for (NS::map<char, int>::iterator it = third.begin(); it != third.end(); ++it)
			std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		NS::map<char,int,classcomp> fourth;                 // class as Compare
		std::cout << "fourth contains: ";
		for (NS::map<char, int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
			std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		bool(*fn_pt)(char,char) = fncomp;
		NS::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
		std::cout << "fifth contains: ";
		for (NS::map<char, int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "COPY-ASSIGNMENT OPERATOR TEST" << std::endl;
	{
		NS::map<char,int> first;
		NS::map<char,int> second;

		first['x']=8;
		first['y']=16;
		first['z']=32;

		second=first;                // second now contains 3 ints
		first=NS::map<char,int>();  // and first is now empty

		std::cout << "Size of first: " << first.size() << std::endl;
		std::cout << "Size of second: " << second.size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ITERATOR BEGIN AND END TEST" << std::endl;
	{

		NS::map<char,int> mymap;
		mymap[48] = 48;
		mymap[49] = 49;
		mymap[50] = 50;

		// show content:
		std::cout << "mymap contains: ";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
		NS::map<char, int>::const_iterator	cit = mymap.begin();
		NS::map<char, int>::iterator	it = mymap.begin();
		it++;
		std::cout << std::boolalpha << "cit == it : " << (cit == it) << std::endl;
		std::cout << std::boolalpha << "cit != it : " << (cit != it) << std::endl;
		std::cout << std::boolalpha << "it == cit : " << (it == cit) << std::endl;
		std::cout << std::boolalpha << "it != cit : " << (it != cit) << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CONST ITERATOR BEGIN AND END TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		mymap[48] = 48;
		mymap[49] = 49;
		mymap[50] = 50;

		std::cout << "mymap contains: ";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		const NS::map<char,int>	mymap1(mymap);

		// show content:
		std::cout << "const mymap1 contains: ";
		for (NS::map<char,int>::const_iterator it=mymap1.begin(); it!=mymap1.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "REVERSE ITERATORS RBEGIN AND REND TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		mymap[48] = 48;
		mymap[49] = 49;
		mymap[50] = 50;

		// show content:
		std::cout << "mymap contains: ";
		for (NS::map<char,int>::reverse_iterator it=mymap.rbegin(); it!=mymap.rend(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CONST REVERSE ITERATORS RBEGIN AND REND TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		mymap[48] = 48;
		mymap[49] = 49;
		mymap[50] = 50;

		std::cout << "mymap contains: ";
		for (NS::map<char,int>::reverse_iterator it=mymap.rbegin(); it!=mymap.rend(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		const NS::map<char,int>	mymap1(mymap);

		// show content:
		std::cout << "const mymap1 contains: ";
		for (NS::map<char,int>::const_reverse_iterator it=mymap1.rbegin(); it!=mymap1.rend(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "EMPTY() TEST" << std::endl;
	{
		NS::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		while (!mymap.empty())
		{
		  std::cout << mymap.begin()->first << "-" << mymap.begin()->second << ' ';
		  mymap.erase(mymap.begin());
		}
		std::cout << std::endl;
		std::cout << std::boolalpha << "mymap is empty: " << mymap.empty() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SIZE() TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		mymap['a']=101;
		mymap['b']=202;
		mymap['c']=302;

		std::cout << "mymap contains: ";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		std::cout << "mymap.size() is " << mymap.size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "MAX_SIZE() TEST" << std::endl;
	{
		int i;
		NS::map<int,int> mymap;

		if (mymap.max_size()>1000)
		{
		  for (i=0; i<1000; i++) mymap[i]=0;
		  std::cout << "The map contains 1000 elements.\n";
		}
		else std::cout << "The map could not hold 1000 elements.\n";
		std::cout << "mymap max_size = " << mymap.max_size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "OPERATOR[] TEST" << std::endl;
	{
		NS::map<char,std::string> mymap;

		mymap['a']="an element";
		mymap['b']="another element";
		mymap['c']=mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << std::endl;
		std::cout << "mymap['b'] is " << mymap['b'] << std::endl;
		std::cout << "mymap['c'] is " << mymap['c'] << std::endl;
		std::cout << "mymap['d'] is " << mymap['d'] << std::endl;

		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "AT() TEST" << std::endl;
	{
		NS::map<std::string,int> mymap;
		mymap["alpha"] = 0;
		mymap["beta"] = 0;
		mymap["gamma"] = 0;

		mymap.at("alpha") = 10;
		mymap.at("beta") = 20;
		mymap.at("gamma") = 30;

		std::cout << "mymap contains: ";
		for (NS::map<std::string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		try {
			std::cout << "mymap.at(\"teta\"): " << mymap.at("teta");
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "INSERT() TEST" << std::endl;
	{
		NS::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( NS::pair<char,int>('a',100) );
		mymap.insert ( NS::pair<char,int>('z',200) );

		NS::pair<NS::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( NS::pair<char,int>('z',500) );
		if (ret.second==false) {
		  std::cout << "element 'z' already existed";
		  std::cout << " with a value of " << ret.first->second << std::endl;
		}

		// second insert function version (with hint position):
		NS::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, NS::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, NS::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		NS::map<char,int> anothermap;
		anothermap.insert(mymap.begin(),mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "ERASE() TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		NS::map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;

		std::cout << "mymap contains: ";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		it=mymap.find('b');
		mymap.erase (it);                   // erasing by iterator
		std::cout << "mymap contains: ";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		mymap.erase ('c');                  // erasing by key
		std::cout << "mymap contains: ";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range
		std::cout << "mymap contains: ";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SWAP() TEST" << std::endl;
	{
		NS::map<char,int> foo,bar;
		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;
		NS::map<char,int>::iterator it1=foo.begin();
		NS::map<char,int>::iterator it2=bar.begin();

		std::cout << "foo contains:\n";
		for (; it1!=foo.end(); ++it1)
		  std::cout << it1->first << "-" << it1->second << ' ';
		std::cout << std::endl;
		std::cout << "bar contains:\n";
		for (; it2!=bar.end(); ++it2)
		  std::cout << it2->first << "-" << it2->second << ' ';
		std::cout << std::endl;

		----it1;
		------it2;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (; it2!=foo.end(); ++it2)
		  std::cout << it2->first << "-" << it2->second << ' ';
		std::cout << std::endl;
		std::cout << "bar contains:\n";
		for (; it1!=bar.end(); ++it1)
		  std::cout << it1->first << "-" << it1->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "CLEAR() TEST" << std::endl;
	{
		NS::map<char,int> mymap;

		mymap['x']=100;
		mymap['y']=200;
		mymap['z']=300;

		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		mymap.clear();

		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		mymap['a']=1101;
		mymap['b']=2202;

		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "KEY_COMP() TEST" << std::endl;
	{
		NS::map<char,int> mymap;

		NS::map<char,int>::key_compare mycomp = mymap.key_comp();

		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first;     // key value of last element

		NS::map<char,int>::iterator it = mymap.begin();
		do {
		  std::cout << it->first << "-" << it->second << ' ';
		} while ( mycomp((*it++).first, highest) );
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "VALUE_COMP() TEST" << std::endl;
	{
		NS::map<char,int> mymap;

		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;

		std::cout << "mymap contains:\n";

		NS::pair<char,int> highest = *mymap.rbegin();          // last element

		NS::map<char,int>::iterator it = mymap.begin();
		do {
		  std::cout << it->first << "-" << it->second << ' ';
		} while ( mymap.value_comp()(*it++, highest) );
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "FIND() TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		NS::map<char,int>::iterator it;

		mymap['a']=50;
		mymap['b']=100;
		mymap['c']=150;
		mymap['d']=200;

		it = mymap.find('b');
		if (it != mymap.end())
		  mymap.erase (it);

		// print content:
		std::cout << "elements in mymap:" << std::endl;
		std::cout << "a-" << mymap.find('a')->second << ' ';
		std::cout << "c-" << mymap.find('c')->second << ' ';
		std::cout << "d-" << mymap.find('d')->second << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "COUNT() TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		char c;

		mymap ['a']=101;
		mymap ['c']=202;
		mymap ['f']=303;
		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		for (c='a'; c<'h'; c++)
		{
		  std::cout << c;
		  if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
		  else
			std::cout << " is not an element of mymap.\n";
		}
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "LOWER_BOUND() AND UPPER_BOUND() TEST" << std::endl;
	{
		NS::map<char,int> mymap;
		NS::map<char,int>::iterator itlow,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;
		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;

		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)

		mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		  std::cout << it->first << "-" << it->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "EQUAL_RANGE() TEST" << std::endl;
	{
		NS::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		NS::pair<NS::map<char,int>::iterator,NS::map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound of equal_range(\'b\') points to: ";
		std::cout << ret.first->first << "-" << ret.first->second << ' ';
		std::cout << std::endl;
		std::cout << "upper bound of equal_range(\'b\') points to: ";
		std::cout << ret.second->first << "-" << ret.second->second << ' ';
		std::cout << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "GET_ALLOCATOR() TEST" << std::endl;
	{
		int psize;
		NS::map<char,int> mymap;
		NS::pair<const char,int>* p;

		// allocate an array of 5 elements using mymap's allocator:
		p=mymap.get_allocator().allocate(5);

		// assign some values to array
		psize = sizeof(NS::map<char,int>::value_type)*5;

		std::cout << "The allocated array has a size of " << psize << " bytes.\n";

		mymap.get_allocator().deallocate(p,5);
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "RELATIONAL OPERATORS TEST" << std::endl;
	{
		NS::map<int, char> alice;
		alice[1] = 'a';
		alice[2] = 'b';
		alice[3] = 'c';
		NS::map<int, char> bob;
		bob[7] = 'Z';
		bob[8] = 'Y';
		bob[9] = 'X';
		bob[10] = 'W';
		NS::map<int, char> eve;
		eve[1] = 'a';
		eve[2] = 'b';
		eve[3] = 'c';
	 
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
		std::cout << "alice >= eve returns " << (alice >= eve) << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "NS::SWAP() TEST" << std::endl;
	{
		NS::map<int, char> alice;
		alice[1] = 'a';
		alice[2] = 'b';
		alice[3] = 'c';
		NS::map<int, char> bob;
		bob[7] = 'Z';
		bob[8] = 'Y';
		bob[9] = 'X';
		bob[10] = 'W';
	 
		// Print state before swap
		std::cout << "alice:";
		std::for_each(alice.begin(), alice.end(), print<int, char>());
		std::cout << std::endl << "bob  :";
		std::for_each(bob.begin(), bob.end(), print<int, char>());
		std::cout << std::endl;
	 
		std::cout << "-- SWAP" << std::endl;
		NS::swap(alice, bob);
	 
		// Print state after swap
		std::cout << "alice:";
		std::for_each(alice.begin(), alice.end(), print<int, char>());
		std::cout << std::endl << "bob  :";
		std::for_each(bob.begin(), bob.end(), print<int, char>());
		std::cout << std::endl;
	}
}
