#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	first;
		second_type	second;


		///////////////////////////     Constructors      //////////////////////////////

		pair() :
			first(),
			second()
		{}

		pair(const T1& x, const T2& y) :
			first(x),
			second(y)
		{}

		template<class U1, class U2>
		pair(const pair<U1, U2>& p)	:
			first(p.first),
			second(p.second)
		{}


		///////////////////////////     Desstructor      //////////////////////////////

		pair& operator= (const pair& rhs)
		{
			if (&rhs != this)
			{
				first = rhs.first;
				second = rhs.second;
			}
			return (*this);
		}
	};


	/////////////////////////////     Make pair   ////////////////////////////////

	template<class T1, class T2>
	pair<T1,T2>	make_pair (T1 k, T2 v)
	{
		return (pair<T1, T2>(k, v));
	}


	///////////////////////     Non-member function overloads      ////////////////////////

	template<class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T1, class T2>
	bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
	}

	template<class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class T1, class T2>
	bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif
