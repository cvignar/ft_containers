/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:52:40 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/23 21:08:23 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "stack.hpp"
#include "utils.hpp"
#include <deque>
#include "vector.hpp"
#include <vector>
#include <stack>
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
	std::cout << std::endl << "STACK TEST" << std::endl << std::endl;	
	if (char_array_compare(typeid(NS::iterator_traits<NS::vector<int>::iterator>::iterator_category).name(), "N2ft26random_access_iterator_tagE"))
		std::cout << "Namespace is ft." << std::endl;
	else if (char_array_compare(typeid(NS::iterator_traits<NS::vector<int>::iterator>::iterator_category).name(), "NSt3__126random_access_iterator_tagE"))
		std::cout << "Namespace is std." << std::endl;

	std::cout << std::endl << "CONSTRUCTOR TEST" << std::endl;
	{
		NS::vector<int> myvector (2,200);        // vector with 2 elements

		NS::stack<int> first;                    // empty stack

		NS::stack<int,std::deque<int> > second;  // empty stack using vector
		NS::stack<int,NS::vector<int> > third (myvector);

		std::cout << "size of first: " << first.size() << std::endl;
		std::cout << "size of second: " << second.size() << std::endl;
		std::cout << "size of third: " << third.size() << std::endl;

	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "EMPTY() TEST" << std::endl;
	{
		NS::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);

		while (!mystack.empty())
		{
		   sum += mystack.top();
		   mystack.pop();
		}

		std::cout << "total: " << sum << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "SIZE() TEST" << std::endl;
	{
		NS::stack<int> myints;
		std::cout << "0. size: " << myints.size() << std::endl;

		for (int i=0; i<5; i++) myints.push(i);
		std::cout << "1. size: " << myints.size() << std::endl;

		myints.pop();
		std::cout << "2. size: " << myints.size() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "TOP() TEST" << std::endl;
	{
		NS::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << std::endl;
	}
	std::cout << "—————————————————————————————————————————————" << std::endl;
	std::cout << std::endl << "PUSH() AND POP() TEST" << std::endl;
	{
		NS::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
		   std::cout << ' ' << mystack.top();
		   mystack.pop();
		}
		std::cout << std::endl;
	}
}
