#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

namespace ft
{
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;								// Que tipo de iterador es: en nuestro caso "random_access_iterator_tag".
		typedef T			value_type;										// Type of values that can be obtained by dereferencing the iterator (void for output iterators)
		typedef Distance	difference_type;								// A type that can be used to identify distance between iterators (defaults to: ptrdiff_t)
		typedef Pointer		pointer;										// Defines a pointer to the type iterated over "value_type" (defaults to: T*)
		typedef Reference	reference;										// Defines a reference to the type iterated over "value_type" (defaults to: T&)
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category; 
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef const T							value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}

#endif
