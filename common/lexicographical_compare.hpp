#ifndef LEXICOGRAPHICALCOMPARE_HPP
# define LEXICOGRAPHICALCOMPARE_HPP

// Devuelve true si cuando se encuentre el primer elemento distinto, el elemento del primer
// rango es menor alfabéticamente hablando. Si alguno de los rangos llega al final antes que
// el otro y no se han encontrado diferencias antes, se considera menor el que ha acabado primero.
// La función está desarrollada en https://www.cplusplus.com/reference/algorithm/lexicographical_compare

namespace ft
{
	template<class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif
