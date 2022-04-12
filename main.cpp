#include "Vector/vector.hpp"
#include "Stack/stack.hpp"
#include "Map/map.hpp"

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <list>
#include <queue>

#ifndef NS
# define NS ft
#endif

#define STR(X) #X
#define ASSTR(X) STR(X)

int main()
{
	std::cout << "Testing " << ASSTR(NS) << " containers" << std::endl << std::endl;


	std::cout << "\n\n\n*************************************************************************" << std::endl;
	std::cout << "\t\t\t\tVector" << std::endl;
	std::cout << "*************************************************************************" << std::endl;

	{
		std::cout << "\n---------- FT Vector (Constructors and iterator) ----------" << std::endl;
		NS::vector<int> fill(4, 100);
		std::cout << "The contents of fill vector are:";
		for (NS::vector<int>::iterator it = fill.begin(); it != fill.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		fill.push_back(200);
		NS::vector<int> range(fill.begin(), fill.end());
		std::cout << "The contents of range vector are:";
		for (NS::vector<int>::iterator it = range.begin(); it != range.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		range.push_back(300);
		NS::vector<int> copy(range);
		std::cout << "The contents of copy vector are:";
		for (NS::vector<int>::iterator it = copy.begin(); it != copy.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;

		int myints[] = {16, 2, 77, 29};
		NS::vector<int> other(myints, myints + sizeof(myints) / sizeof(int));
		std::cout << "The contents of other vector are:";
		for (NS::vector<int>::iterator it = other.begin(); it != other.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (operator=)-------------" << std::endl;
		NS::vector<int> foo(3, 100);
		NS::vector<int> bar(5, 200);
		bar = foo;
		foo = NS::vector<int>();
		std::cout << "Size of foo: " << int(foo.size()) << std::endl;
		std::cout << "Size of bar: " << int(bar.size()) << std::endl;
		std::cout << "The contents of bar vector are:";
		for (NS::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	{
		std::cout << "\n---- FT Vector (iterator walk & comparison diferent iterators) ----" << std::endl;
		NS::vector<int> myvector;
		for (int i = 1; i <= 5; i++)
			myvector.push_back(i);
		std::cout << "myvector contains:";
		NS::vector<int>::iterator it = myvector.begin();
		NS::vector<int>::const_iterator cit = myvector.end();
		for (; it != cit; ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (reverse iterator walk)-------------" << std::endl;
		NS::vector<int> myvector(5);
		int i1 = 0;
		NS::vector<int>::reverse_iterator rit1 = myvector.rbegin();
		for (; rit1 != myvector.rend(); ++rit1)
			*rit1 = ++i1;
		std::cout << "myvector contains:";
		for (NS::vector<int>::iterator it1 = myvector.begin(); it1 != myvector.end(); ++it1)
			std::cout << ' ' << *it1;
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (size)-------------" << std::endl;
		NS::vector<int> myvector;
		std::cout << "size (should be 0):  " << myvector.size() << std::endl;
		for (int i = 0; i < 10; i++)
			myvector.push_back(i);
		std::cout << "size (should be 10): " << myvector.size() << std::endl;
		myvector.insert(myvector.end(), 10, 100);
		std::cout << "size (should be 20): " << myvector.size() << std::endl;
		myvector.pop_back();
		std::cout << "size (should be 19): " << myvector.size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (max_size)-------------" << std::endl;
		NS::vector<int> myvector;
		for (int i = 0; i < 100; i++)
			myvector.push_back(i);
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "max_size: " << myvector.max_size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (resize)-------------" << std::endl;
		NS::vector<int> myvector1;
		for (int i = 0; i < 10; i++)
			myvector1.push_back(i);
		std::cout << "myvector contains 10 elements:                           ";
		for (size_t i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;

		myvector1.resize(5);
		std::cout << "myvector contains 5 elements:                            ";
		for (size_t i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;

		myvector1.resize(8);
		std::cout << "myvector contains 8 elements, filled up with value 0:    ";
		for (size_t i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;

		myvector1.resize(11, 100);
		std::cout << "myvector contains 11 elements, filled up with value 100: ";
		for (size_t i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (capacity)-------------" << std::endl;
		NS::vector<int> myvector;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(1);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(2);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(3);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(4);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(5);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(6);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(7);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(8);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << std::endl;

		myvector.push_back(9);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
		std::cout << "capacity: " << myvector.capacity() << std::endl;
		std::cout << "size: " << myvector.size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (empty)-------------" << std::endl;
		NS::vector<int> myvector;
		std::cout << "Is my vector empty?: " << myvector.empty() << std::endl;
		for (int i = 1; i < 10; i++)
			myvector.push_back(i);
		std::cout << "size after pushing values 1 to 9 included: " << myvector.size() << std::endl;
		std::cout << "Is my vector empty?: " << myvector.empty() << std::endl;
		while (!myvector.empty())
			myvector.pop_back();
		std::cout << "size after pop back until empty:           " << myvector.size() << std::endl;
		std::cout << "Is my vector empty?: " << myvector.empty() << std::endl;
	}

	{
		std::cout << "\n--------- FT Vector (reserve) ---------" << std::endl;
		NS::vector<int> myvector;
		for (int i = 1; i < 10; i++)
			myvector.push_back(i);
		std::cout << "Initial capacity: " << myvector.capacity() << std::endl;

		myvector.reserve(5);
		std::cout << "Capacity should be the same: " << myvector.capacity() << std::endl;

		myvector.reserve(20);
		std::cout << "Capacity should be 20: " << myvector.capacity() << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (operator[])-------------" << std::endl;
		NS::vector<int> myvector1(10);
		for (unsigned i = 0; i < myvector1.size(); i++)
			myvector1[i] = i;
		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (at)-------------" << std::endl;
		NS::vector<int> myvector1(10);
		for (unsigned i = 0; i < myvector1.size(); i++)
			myvector1.at(i) = i;
		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1.at(i);

		myvector1.at(5) = 28;

		std::cout << "\nmyvector contains:";
		for (unsigned i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1.at(i);

		try
		{
			std::cout << myvector1.at(45);
		}
		catch(const std::exception& e)
		{
			std::cout << "\nlooking out of bounds";
		}
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (front/back)-------------" << std::endl;
		NS::vector<int> myvector1;
		myvector1.push_back(78);
		myvector1.push_back(42);
		myvector1.push_back(16);

		std::cout << "myvector.front() (should be 78):   " << myvector1.front() << std::endl;
		std::cout << "myvector.back()  (should be 16):   " << myvector1.back() << std::endl;

		myvector1.front() -= myvector1.back();
		std::cout << "myvector.front() (should be 62):   " << myvector1.front() << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (assign)-------------" << std::endl;
		NS::vector<int> first;

		first.assign(3, 100);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < first.size(); i++)
			std::cout << ' ' << first[i];
		std::cout << std::endl;
		std::cout << "Size of first: " << int(first.size()) << std::endl;
		std::cout << std::endl;

		first.assign(6, 200);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < first.size(); i++)
			std::cout << ' ' << first[i];
		std::cout << std::endl;
		std::cout << "Size of first: " << int(first.size()) << std::endl;
		std::cout << std::endl;

		NS::vector<int> second;
		NS::vector<int>::iterator it1;
		it1 = first.begin() + 1;
		second.assign(it1, first.end() - 1);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < second.size(); i++)
			std::cout << ' ' << second[i];
		std::cout << std::endl;
		std::cout << "Size of second: " << int(second.size()) << std::endl;
		std::cout << std::endl;

		int myints1[] = {1776, 7, 4};
		first.assign(myints1, myints1 + 3);
		//std::cout << first.at(0) << " " << first.at(1) << " " << first.at(2) << std::endl;
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < first.size(); i++)
			std::cout << ' ' << first[i];
		std::cout << std::endl;
		std::cout << "Size of first: " << int(first.size()) << std::endl;
	}

	{
		std::cout << "\n---------- FT Vector (push_back / pop_back) ----------" << std::endl;
		NS::vector<int> myvector1;
		int ints[] = {15, 78, 99, 45, 78, 99, 65, 0, 44};
		for (int i = 0; ints[i]; i++)
			myvector1.push_back(ints[i]);
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
		std::cout << "Size of myvector1:     " << int(myvector1.size()) << std::endl;
		std::cout << std::endl;

		myvector1.pop_back();
		myvector1.pop_back();
		std::cout << "myvector contains: ";
		for (size_t i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
		std::cout << "Size of myvector1:     " << int(myvector1.size()) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (clear)-------------" << std::endl;
		NS::vector<std::string> myvector1;
		myvector1.push_back("hola");
		myvector1.push_back("hi");
		myvector1.push_back("hello");
		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
		std::cout << "myvector1 size:       " << myvector1.size() << std::endl;
		myvector1.clear();
		std::cout << "CLEAR!" << std::endl;
		std::cout << "size after clear:     " << myvector1.size() << std::endl;
		myvector1.push_back("adios");
		myvector1.push_back("bye");
		std::cout << "myvector contains:";
		for (unsigned i = 0; i < myvector1.size(); i++)
			std::cout << ' ' << myvector1[i];
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (insert)-------------" << std::endl;

		NS::vector<int>::iterator it1;

		NS::vector<int> myvector1(3, 100);
		std::cout << "\nmyvector contains:";
		for (it1 = myvector1.begin(); it1 < myvector1.end(); it1++)
		    std::cout << ' ' << *it1;
		std::cout << std::endl;
		std::cout << "Its size is of     " << myvector1.size() << std::endl;

		std::cout << "\nmyvector contains:";
		for (it1 = myvector1.begin(); it1 < myvector1.end(); it1++)
		    std::cout << ' ' << *it1;
		std::cout << "\nIts size is of     " << myvector1.size() << std::endl;

		it1 = myvector1.begin();
		it1 = myvector1.insert(it1, 200);
		myvector1.insert(it1, 2, 300);
		std::cout << "\nmyvector contains:";
		for (it1 = myvector1.begin(); it1 < myvector1.end(); it1++)
		    std::cout << ' ' << *it1;
		std::cout << "\nIts size is of     " << myvector1.size() << std::endl;

		NS::vector<int> anothervector1(2, 400);
		it1 = myvector1.begin();
		myvector1.insert(it1 + 2, anothervector1.begin(), anothervector1.end());
		std::cout << "\nmyvector contains:";
		for (it1 = myvector1.begin(); it1 < myvector1.end(); it1++)
			std::cout << ' ' << *it1;
		std::cout << "\nIts size is of     " << myvector1.size() << std::endl;

		int myarray1[] = {501, 502, 503};
		myvector1.insert(myvector1.begin(), myarray1, myarray1 + 3);
		std::cout << "\nmyvector contains:";
		for (it1 = myvector1.begin(); it1 < myvector1.end(); it1++)
			std::cout << ' ' << *it1;
		std::cout << "\nIts size is of     " << myvector1.size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (erase)-------------" << std::endl;
		NS::vector<int> myvector;
		NS::vector<int>::iterator index;
		NS::vector<int>::iterator it1;
		NS::vector<int>::iterator it2;

		for (int i = 1; i <= 10; i++)
			myvector.push_back(i);
		index = myvector.begin();
		std::cout << "myvector contains:";
		for (; index != myvector.end(); index++)
			std::cout << ' ' << *index;

		myvector.erase(myvector.begin() + 5);
		std::cout << "\nmyvector contains:";
		for (unsigned i = 0; i < myvector.size(); ++i)
			std::cout << ' ' << myvector[i];

		myvector.erase(myvector.begin(), myvector.begin() + 3);
		std::cout << "\nmyvector contains:";
		for (unsigned i = 0; i < myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (swap)-------------" << std::endl;
		NS::vector<int> foo(3, 100);
		NS::vector<int> bar(5, 200);

		NS::vector<int>::iterator it1 = foo.begin();
		NS::vector<int>::iterator it2 = bar.begin();

		std::cout << "Size of foo before     " << foo.size() << std::endl;
		std::cout << "Capacity of foo before " << foo.capacity() << std::endl;
		std::cout << "Size of bar before     " << bar.size() << std::endl;
		std::cout << "Capacity of bar before " << bar.capacity() << std::endl;
		foo.swap(bar);
		std::cout << "SWAP!" << std::endl;
		std::cout << "Size of foo after      " << foo.size() << std::endl;
		std::cout << "Capacity of foo after  " << foo.capacity() << std::endl;
		std::cout << "Size of bar after      " << bar.size() << std::endl;
		std::cout << "Capacity of bar after  " << bar.capacity() << std::endl;

		std::cout << std::endl;
		std::cout << "foo contains:";
		for (; it2 != foo.end(); it2++)
			std::cout << ' ' << *it2;
		std::cout << std::endl;
		std::cout << "bar contains:";
		for (; it1 != bar.end(); it1++)
			std::cout << ' ' << *it1;
		std::cout << std::endl;

		// for (unsigned i = 0; i < foo.size(); i++)
		// 	std::cout << ' ' << foo[i];
		// std::cout << std::endl;
		// std::cout << "bar contains:";
		// for (unsigned i = 0; i < bar.size(); i++)
		// 	std::cout << ' ' << bar[i];
		// std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Vector (get_allocator)-------------" << std::endl;
		NS::vector<int> myvector;
		int             *p;
		unsigned int    i;

		p = myvector.get_allocator().allocate(5);
		for (i = 0; i < 5; i++)
			myvector.get_allocator().construct(&p[i], i);
		std::cout << "The manually allocated array contains:";
		for (i = 0; i < 5; i++)
			std::cout << ' ' << p[i];
		std::cout << std::endl;
		for (i = 0; i < 5; i++)
			myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p, 5);
	}

	{
		std::cout << "\n------------- FT Vector (Relational operators)-------------" << std::endl;
		NS::vector<int> foo(2, 200);
		NS::vector<int> bar(foo);
		if (foo == bar)
			std::cout << "foo and bar are equal" << std::endl;
		if (foo != bar)
			std::cout << "foo and bar are not equal" << std::endl;
		if (foo < bar)
			std::cout << "foo is less than bar" << std::endl;
		if (foo > bar)
			std::cout << "foo is greater than bar" << std::endl;
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar" << std::endl;
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar" << std::endl;
		std::cout << std::endl;
		NS::vector<int> baz;
		baz.push_back(200);
		baz.push_back(200);
		baz.push_back(300);
		baz.push_back(400);
		if (foo == baz)
			std::cout << "foo and baz are equal" << std::endl;
		if (foo != baz)
			std::cout << "foo and baz are not equal" << std::endl;
		if (foo < baz)
			std::cout << "foo is less than baz" << std::endl;
		if (foo > baz)
			std::cout << "foo is greater than baz" << std::endl;
		if (foo <= baz)
			std::cout << "foo is less than or equal to baz" << std::endl;
		if (foo >= baz)
			std::cout << "foo is greater than or equal to baz" << std::endl;
	}

	std::cout << "\n\n\n*************************************************************************" << std::endl;
	std::cout << "\t\t\t\tMap" << std::endl;
	std::cout << "*************************************************************************" << std::endl;

	{
		std::cout << "\n------------- FT Pair (constructor) -------------" << std::endl;
		NS::pair<std::string, double> product1;
		NS::pair<std::string, double> product2("tomatoes", 2.30);
		NS::pair<std::string, double> product3(product2);
		product2.first = "shoes";
		product2.second = 39.90;
		std::cout << "The price of " << product1.first << " is $" << product1.second << std::endl;
		std::cout << "The price of " << product2.first << " is $" << product2.second << std::endl;
		std::cout << "The price of " << product3.first << " is $" << product3.second << std::endl;
	}

	{
		std::cout << "\n------------- FT Pair (operator=) -------------" << std::endl;
		NS::pair<std::string, int> planet, homeplanet;
		planet = NS::make_pair("Earth", 6371);
		homeplanet = planet;
		std::cout << "Home planet (should be Earth): " << homeplanet.first << std::endl;
		std::cout << "Planet radius in km (should be 6371): " << homeplanet.second << std::endl;
	}

	{
		std::cout << "\n------------- FT Pair (make_pair) -------------" << std::endl;
		NS::pair<int, int> foo;
		NS::pair<int, int> bar;
		NS::pair<double, std::string> boo;
		foo = NS::make_pair(10, 20);
		bar = NS::make_pair(10.5, 'A'); // implicit conversion to 65
		boo = NS::make_pair(20.5, "hello");
		std::cout << "foo: " << foo.first << ", " << foo.second << std::endl;
		std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;
		std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;
	}

	{
		std::cout << "\n------------- FT Pair (relational operators) -------------" << std::endl;
		NS::pair<int, char> foo(10, 'z');
		NS::pair<int, char> bar(10, 'z');
		if (foo == bar)
			std::cout << "foo and bar are equal" << std::endl;
		if (foo != bar)
			std::cout << "foo and bar are not equal" << std::endl;
		if (foo < bar)
			std::cout << "foo is less than bar" << std::endl;
		if (foo > bar)
			std::cout << "foo is greater than bar" << std::endl;
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar" << std::endl;
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar" << std::endl;
		std::cout << std::endl;
		NS::pair<int, char> baz(10, 'a');
		if (foo == baz)
			std::cout << "foo and baz are equal" << std::endl;
		if (foo != baz)
			std::cout << "foo and baz are not equal" << std::endl;
		if (foo < baz)
			std::cout << "foo is less than baz" << std::endl;
		if (foo > baz)
			std::cout << "foo is greater than baz" << std::endl;
		if (foo <= baz)
			std::cout << "foo is less than or equal to baz" << std::endl;
		if (foo >= baz)
			std::cout << "foo is greater than or equal to baz" << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (construct) -------------" << std::endl;
		NS::map<char, int> first;
		std::cout << "First map is :" <<std::endl;
		for (NS::map<char, int>::iterator i = first.begin(); i != first.end(); i++)
			std::cout << i->first << "\t" << i->second << std::endl;
		first['a'] = 10;
		first['b'] = 30;
		first['c'] = 50;
		first['d'] = 70;

		NS::map<char, int> second(first.begin(), first.end());
		std::cout << "Second map is :" <<std::endl;
		for (NS::map<char, int>::iterator i = second.begin(); i != second.end(); i++)
			std::cout << i->first << "\t" << i->second << std::endl;

		NS::map<char, int> third(second);
		std::cout << "Third map is :" <<std::endl;
		for (NS::map<char, int>::iterator i = third.begin(); i != third.end(); i++)
			std::cout << i->first << "\t" << i->second << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (operator=) -------------" << std::endl;
		NS::map<char, int> first;
		NS::map<char, int> second;
		first['x'] = 8;
		first['y'] = 16;
		first['z'] = 32;
		second = first;
		first = NS::map<char, int>();
		std::cout << "Size of first (should now be 0):                " << first.size() << std::endl;
		std::cout << "Size of second (should now contain 3 elements): " << second.size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (operator[]) -------------" << std::endl;
		NS::map<char, std::string> mymap;
		mymap['a'] = "an element";
		mymap['b'] = "another element";
		mymap['c'] = mymap['b'];
		std::cout << "mymap['a'] is " << mymap['a'] << std::endl;
		std::cout << "mymap['b'] is " << mymap['b'] << std::endl;
		std::cout << "mymap['c'] is " << mymap['c'] << std::endl;
		std::cout << "mymap['d'] is " << mymap['d'] << std::endl;
		std::cout << "mymap now contains " << mymap.size() << " elements." << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (empty) -------------" << std::endl;
		NS::map<char, int> mymap;
		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;
		std::cout << "Is map  empty (should be 0)?     " << mymap.empty() << std::endl;
		while (!mymap.empty())
		{
			std::cout << "Erasing pair " << mymap.begin()->first << " => " << mymap.begin()->second << std::endl;
			mymap.erase(mymap.begin());
		}
		std::cout << "Is map now empty (should be 1)?  " << mymap.empty() << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (size) -------------" << std::endl;
		NS::map<char, int> mymap;
		std::cout << "Size of mymap:   " << mymap.size() << std::endl;
		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;
		std::cout << "Size of mymap:   " << mymap.size() << std::endl;
		mymap.erase(mymap.begin());
		std::cout << "Size of mymap:   " << mymap.size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (max_size) -------------" << std::endl;
		NS::map<int, int> mymap;
		std::cout << "The maximum size our map could grow up to is " << mymap.max_size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (insert) -------------" << std::endl;
		NS::map<char, int> mymap;
		mymap.insert(NS::pair<char, int>('a', 100));
		mymap.insert(NS::make_pair('z', 200));
		NS::pair<NS::map<char, int>::iterator, bool> ret = mymap.insert(NS::pair<char, int>('z', 500));
		if (ret.second == false)
			std::cout << "element 'z' already existed with a value of " << ret.first->second << std::endl;
		std::cout << "mymap is of size (should be 2): " << mymap.size() << std::endl << std::endl;

		NS::map<char, int>::iterator it = mymap.begin();
		mymap.insert(it, NS::pair<char, int>('b', 300));
		mymap.insert(it, NS::pair<char, int>('c', 400));
		std::cout << "mymap now contains a, b, c and z:" << std::endl;
		for (it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;

		NS::map<char, int> anothermap;
		anothermap.insert(mymap.begin(), mymap.end());
		std::cout << "\nanothermap now also contains a, b, c and z:" << std::endl;
		for (NS::map<char, int>::iterator i = anothermap.begin(); i != anothermap.end(); i++)
		{
			std::cout << i->first << " => " << i->second << std::endl;
		}

		std::cout << "\nlastmap contains (check how is printed in order):" << std::endl;
		NS::map<char, int> lastmap;
		lastmap.insert(NS::pair<char, int>('n', 200));
		NS::map<char, int>::iterator root = lastmap.begin();
		lastmap.insert(NS::pair<char, int>('s', 100));
		lastmap.insert(NS::pair<char, int>('f', 500));
		lastmap.insert(NS::pair<char, int>('j', 400));
		lastmap.insert(NS::pair<char, int>('b', 300));
		lastmap.insert(NS::pair<char, int>('r', 700));
		lastmap.insert(NS::pair<char, int>('d', 600));
		lastmap.insert(NS::pair<char, int>('y', 800));
		for (NS::map<char, int>::iterator ite = lastmap.begin(); ite != lastmap.end(); ite++)
		{
			std::cout << ite->first << " => " << ite->second << std::endl;
		}

		std::cout << std::endl;
		std::cout << "lastmap root is: " << root->first << " => " << root->second << std::endl;
	}

		{
		std::cout << "\n------------- FT Map (erase) -------------" << std::endl;
		NS::map<int, char> mymap;
		mymap[10] = 'a';
		mymap[8] = 'b';
		mymap[5] = 'c';
		mymap[2] = 'd';
		mymap[13] = 'e';
		mymap[7] = 'f';
		mymap[6] = 'g';
		mymap[9] = 'h';
		mymap.erase(mymap.find(10));				// Erase position
		mymap.erase(5);								// Erase key
		mymap.erase(mymap.find(7), mymap.end());	// Erase range
		std::cout << "Map should now only contain d and g" << std::endl;
		for (NS::map<int, char>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		{
			std::cout << it->first << " => " << it->second << std::endl;
		}
	}

	{
		std::cout << "\n------------- FT Map (swap) -------------" << std::endl;
		NS::map<char, int> foo, bar;
		foo['x'] = 100;
		foo['y'] = 200;
		bar['a'] = 11;
		bar['b'] = 22;
		bar['c'] = 33;
		foo.swap(bar);
		std::cout << "foo contains now (should be 3 elements):" << std::endl;
		for (NS::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;
		std::cout << "bar contains now (should be 2 elements):" << std::endl;
		for (NS::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (clear) -------------" << std::endl;
		NS::map<char, int> mymap;
		mymap['x'] = 100;
		mymap['y'] = 200;
		mymap['z'] = 300;
		std::cout << "mymap size: " <<  mymap.size() << std::endl;
		std::cout << "mymap contains:" << std::endl;
		for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << "  " << it->first << " => " << it->second << std::endl;
		mymap.clear();
		std::cout << "CLEAR!" << std::endl;
		std::cout << "mymap size: " <<  mymap.size() << std::endl;
		std::cout << "mymap contains:" << std::endl;
		for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (key_comp) -------------" << std::endl;
		std::map<char,int> mymap;
		std::map<char,int>::key_compare mycomp = mymap.key_comp();
		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;
		std::cout << "browsing mymap using its key_comp funciton object:" << std::endl;
		char highest = mymap.rbegin()->first;     // key value of last element
		std::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while (mycomp((*it++).first, highest));
	}

	{
		std::cout << "\n------------- FT Map (value_comp subclass) -------------" << std::endl;
		std::map<char,int> mymap;
		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;
		std::cout << "mymap contains:\n";
		std::pair<char,int> highest = *mymap.rbegin();          // last element
		std::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while (mymap.value_comp()(*it++, highest));
	}

	{
		std::cout << "\n------------- FT Map (find) -------------" << std::endl;
		NS::map<char, int> mymap;
		NS::map<char, int>::iterator it;
		mymap['a'] = 50;
		mymap['c'] = 100;
		mymap['d'] = 150;
		mymap['b'] = 200;
		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase(it);
		std::cout << "mymap size: " <<  mymap.size() << std::endl;
		std::cout << "elements in mymap:" << std::endl;
		std::cout << "  a => " << mymap.find('a')->second << std::endl;
		std::cout << "  c => " << mymap.find('c')->second << std::endl;
		std::cout << "  d => " << mymap.find('d')->second << std::endl;
		std::cout << "b => end() iterator ? (should be 1): " << (mymap.find('b') == mymap.end()) << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (count) -------------" << std::endl;
		NS::map<char, int> mymap;
		mymap['a'] = 101;
		mymap['c'] = 202;
		mymap['f'] = 303;
		std::cout << "mymap contains:" << std::endl;
		for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;
		for (char c = 'a'; c < 'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c) > 0)
				std::cout << " is an element of mymap." << std::endl;
			else
				std::cout << " is not an element of mymap." << std::endl;
		}
	}

	{
		std::cout << "\n--------- FT Map (upper & lower bounds) ----------" << std::endl;
		NS::map<char, int> mymap;
		NS::map<char, int>::iterator itlow, itup;
		mymap['a'] = 20;
		mymap['c'] = 40;
		mymap['e'] = 60;
		mymap['g'] = 80;
		mymap['i'] = 100;
		std::cout << "mymap contains " << std::endl;
		for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << "  " << it->first << " => " << it->second << std::endl;
		std::cout << "lower_bound(c):  " << mymap.lower_bound('c')->first << std::endl;
		std::cout << "lower_bound(d):  " << mymap.lower_bound('d')->first << std::endl;
		std::cout << "upper_bound(c):  " << mymap.upper_bound('c')->first << std::endl;
		std::cout << "upper_bound(d):  " << mymap.upper_bound('d')->first << std::endl;

		itlow = mymap.lower_bound('c');
		itup = mymap.upper_bound('g');
		mymap.erase(itlow, itup);
		std::cout << "\nRange [c - g] erased. Map should now contains \'a\' and \'i\'" << std::endl;
		for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;
	}

	{
		std::cout << "\n------------- FT Map (equal_range) -------------" << std::endl;
		NS::map<char, int> mymap;
		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;
		std::cout << "mymap contains " << std::endl;
		for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;

		NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator> ret;
		ret = mymap.equal_range('b');
		std::cout << "lower bound to b points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << std::endl;
		std::cout << "upper bound to b points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << std::endl;
	}


	std::cout << "\n\n*************************************************************************" << std::endl;
	std::cout << "\t\t\t\tStack" << std::endl;
	std::cout << "*************************************************************************" << std::endl;

	{
		std::cout << "\n------------- FT Stack (Constructor)-------------" << std::endl;
		NS::vector<int> myvector(2,200);
		NS::stack<int> first;
		NS::stack<int, NS::vector<int> > second;
		NS::stack<int, NS::vector<int> > third(myvector);

		std::cout << "size of first:  " << first.size() << std::endl;
		std::cout << "size of second: " << second.size() << std::endl;
		std::cout << "size of third   " << third.size() << std::endl;
		std::cout << std::endl;
		std::cout << "third.top() is: " << third.top() << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (empty)-------------" << std::endl;
		NS::stack<std::string> mystack;
		std::cout << "Is mysyack empty?:            " << mystack.empty() << std::endl;
		mystack.push("hola");
		mystack.push("hi");
		mystack.push("hello");
		mystack.push("salut");
		mystack.push("hallo");
		mystack.push("ciao");
		std::cout << "mystack size is now: " << mystack.size() << std::endl;
		std::cout << "Is mystack empty?:            " << mystack.empty() << std::endl;
		while (!mystack.empty())
			mystack.pop();
		std::cout << "mystack size is now: " << mystack.size() << std::endl;
		std::cout << "Is mystack empty?:            " << mystack.empty() << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (Size)-------------" << std::endl;
		NS::stack<int> myints;
		std::cout << "mystack size is: " << myints.size() << std::endl;
		for (int i = 0; i < 5; i++)
			myints.push(i);
		std::cout << "mystack size is: " << myints.size() << std::endl;
		myints.pop();
		std::cout << "mystack size is: " << myints.size() << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (Top)-------------" << std::endl;
		NS::stack<int> mystack;
		mystack.push(10);
		mystack.push(20);
		mystack.top() -= 5;
		std::cout << "mystack.top() is now:      " << mystack.top() << std::endl;
		const NS::stack<int> const_stack(mystack);
		std::cout << "const_stack.top() is also: " << const_stack.top() << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (Push/Pop)-------------" << std::endl;
		NS::stack<int> mystack;
		for (int i = 0; i < 5; ++i)
			mystack.push(i);
		std::cout << "size is now: " << mystack.size() << std::endl;
		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << " ...size is now: " << mystack.size() << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (operator== / operator!=)-------------" << std::endl;
		NS::stack<int, NS::vector<int> > s1, s2, s3;
		s1.push(1);
		s1.push(2);

		s2.push(1);
		s2.push(2);

		s3.push(1);
		s3.push(2);
		s3.push(3);

		if (s1 == s2)
			std::cout << "The stacks s1 and s2 are equal." << std::endl;
		if (s1 != s2)
			std::cout << "The stacks s1 and s2 are not equal." << std::endl;

		if (s1 == s3)
			std::cout << "The stacks s1 and s3 are equal." << std::endl;
		if (s1 != s3)
			std::cout << "The stacks s1 and s3 are not equal." << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (operator>= / operator<)-------------" << std::endl;
		NS::stack<int, NS::vector<int> > s1, s2, s3;
		s1.push(2);
		s1.push(4);
		s1.push(6);
		s1.push(8);

		s2.push(5);
		s2.push(10);

		s3.push(2);
		s3.push(4);
		s3.push(6);
		s3.push(8);

		if (s1 < s2)
			std::cout << "The stack s1 is less than the stack s2." << std::endl;
		if (s1 >= s2)
			std::cout << "The stack s1 is greater than or equal to the stack s2." << std::endl;
		if (s1 < s3)
			std::cout << "The stack s1 is less than the stack s3." << std::endl;
		if (s1 >= s3)
			std::cout << "The stack s1 is greater than or equal to the stack s3." << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (operator<= / operator>)-------------" << std::endl;
		NS::stack<int> s1, s2, s3;
		s1.push(5);
		s1.push(10);

		s2.push(1);
		s2.push(2);

		s3.push(5);
		s3.push(10);

		if (s1 <= s2)
			std::cout << "The stack s1 is less than or equal to the stack s2." << std::endl;
		if (s1 > s2)
			std::cout << "The stack s1 is greater than the stack s2." << std::endl;
		if (s1 <= s3)
			std::cout << "The stack s1 is less than or equal to the stack s3." << std::endl;
		if (s1 > s3)
			std::cout << "The stack s1 is greater than the stack s3." << std::endl;
	}

	{
		std::cout << "\n------------- FT Stack (deque compatibility)-------------" << std::endl;
		NS::stack<int, std::deque<int> > myints;
		std::cout << "myints size: " << myints.size() << std::endl;
		for (int i = 0; i < 5; i++)
			myints.push(i);
		std::cout << "myints size: " << myints.size() << std::endl;
		myints.pop();
		std::cout << "myints size: " << myints.size() << std::endl;
	}

		{
		std::cout << "\n------------- FT Stack (list compatibility)-------------" << std::endl;
		NS::stack<int, std::list<int> > myints;
		std::cout << "myints size: " << myints.size() << std::endl;
		for (int i = 0; i < 5; i++)
			myints.push(i);
		std::cout << "myints size: " << myints.size() << std::endl;
		myints.pop();
		std::cout << "myints size: " << myints.size() << std::endl;
	}

}

