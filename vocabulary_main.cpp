/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignar <cvignar@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:06:44 by cvignar           #+#    #+#             */
/*   Updated: 2023/01/23 21:08:30 by cvignar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "set.hpp"
#include "utils.hpp"
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <ctime>
#include <typeinfo>

#ifndef NS
# define NS	ft
#endif

#define YELLOW "\033[33m"
#define DEFAULT "\033[37m"

void	print_time(time_t& start, time_t& finish, std::string prompt, bool endl = true) {
	std::cout << prompt << " time = ";
	std::cout << (finish - start) * 1000000 / CLOCKS_PER_SEC << " usec ";
	if (endl) std::cout << std::endl;
}

void tokenize(std::string const &str, const char* delim, NS::vector<std::string> &out)
{
	char *token = strtok(const_cast<char*>(str.c_str()), delim);
	while (token != nullptr)
	{
		out.push_back(std::string(token));
		token = strtok(nullptr, delim);
	}
}

bool	char_array_compare(const char* s1, const char* s2) {
	size_t i = 0;
	for (; s1[i] != '\0' && s2[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			return (false);
	}
	return (s1[i] == '\0' && s2[i] == '\0');
}

int main(int argc, const char * argv[]) {

	std::cout << std::endl << "VOCABULARY TEST" << std::endl << std::endl;
	if (char_array_compare(typeid(NS::iterator_traits<NS::vector<int>::iterator>::iterator_category).name(), "N2ft26random_access_iterator_tagE"))
		std::cout << "Namespace is ft." << std::endl;
	else if (char_array_compare(typeid(NS::iterator_traits<NS::vector<int>::iterator>::iterator_category).name(), "NSt3__126random_access_iterator_tagE"))
		std::cout << "Namespace is std." << std::endl;

	time_t				start;
	time_t				finish;

	if (argc == 2) {
		NS::vector<std::string>	book;
		NS::map<std::string, std::string>	vocabulary;
		NS::map<std::string, std::string>	copy;
		NS::set<std::string>				set_vocabulary;
		std::stringstream		stm;
		std::ifstream			file(argv[1]);
		stm << file.rdbuf();
		const	char*	delim = "	\n !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

		start = clock();
		tokenize(stm.str(), delim, book);
		finish = clock();
		print_time(start, finish, "tokenize (strtok of file and NS::vector::push_back())");

		start = clock();
		for (NS::vector<std::string>::iterator it = book.begin();  it != book.end(); ++it)
			vocabulary.insert(NS::make_pair(*it, "word"));
		finish = clock();
		print_time(start, finish, "NS::map::insert(value)");

		std::cout << "map vocabulary content: " << std::endl;
		for (NS::map<std::string, std::string>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it)
			std::cout << it->first << ' ';
		std::cout << std::endl;

		start = clock();
		for (NS::vector<std::string>::iterator it = book.begin();  it != book.end(); ++it)
			set_vocabulary.insert(*it);
		finish = clock();
		print_time(start, finish, "NS::set::insert(value)");

		std::cout << "set vocabulary content: " << std::endl;
		for (NS::set<std::string>::iterator it = set_vocabulary.begin(); it != set_vocabulary.end(); ++it)
			std::cout << *it << ' ';
		std::cout << std::endl;

		NS::vector<std::string>::iterator	it = book.begin();
		start = clock();
		book.insert(it, "word");
		finish = clock();
		print_time(start, finish, "NS::vector::insert(iterator, value)");

		start = clock();
		book.insert(it, 10000, "word");
		finish = clock();
		print_time(start, finish, "NS::vector::insert(iterator, count, value)", true);

		start = clock();
		NS::map<std::string, std::string>::iterator to_erase = vocabulary.find("Harry");
		finish = clock();
		print_time(start, finish, "NS::map::find(\"Harry\")");

		start = clock();
		vocabulary.erase(to_erase);
		finish = clock();
		print_time(start, finish, "NS::map::erase(iterator)");

		start = clock();
		vocabulary.erase(vocabulary.begin(), vocabulary.end());
		finish = clock();
		print_time(start, finish, "NS::map::erase(begin, end)");

		start = clock();
		book.erase(book.begin());
		finish = clock();
		print_time(start, finish, "NS::vector::erase(iterator)");

		start = clock();
		book.erase(book.begin(), book.end());
		finish = clock();
		print_time(start, finish, "NS::vector::erase(begin, end)");

		file.close();
	}

	return 0;
}
