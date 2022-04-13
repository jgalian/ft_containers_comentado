#ifndef VECTOR_ITERATOR
# define VECTOR_ITERATOR

#include "../common/iterator_traits.hpp"
#include <vector>

namespace ft
{
	template <typename Iterator>
	class vector_iterator : public ft::iterator_traits<Iterator>
	{
		public:
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::vector_iterator<Iterator>						self;

		private:
			pointer	_ptr;

		public:

		/////////////////////////     Constructors      /////////////////////////////////

			vector_iterator()
			{}

			template <class Iter>
			vector_iterator(const vector_iterator<Iter>& it) :
				_ptr(it.get_ptr())
			{}

			vector_iterator(const pointer pt) :
				_ptr(pt)
			{}


		///////////////////////////     Destructor      ////////////////////////////////

			~vector_iterator()
			{}


		//////////////////////////       Getter        /////////////////////////////////

			pointer get_ptr() const
			{
				return (this->_ptr);
			}


		/////////////////////     Operator overloads      /////////////////////////

			self& operator= (const self& it)
			{
				if (this != &it)
					this->_ptr = it._ptr;
				return (*this);
			}

			// Devuelve la dirección de _ptr, es decir, un puntero a la dirección del elemento concreto
			//  https://www.cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/

			pointer operator-> () const
			{
				return (this->_ptr);
			}

			// Devuelve una refencia al elemento _ptr, es decir, el contenido del elemento concreto
			// https://www.cplusplus.com/reference/iterator/reverse_iterator/operator*/

			reference operator* (void) const
			{
				return (*this->_ptr);
			}

			reference operator[] (difference_type n) const
			{
				return (this->_ptr + n);
				//return (this->_ptr[i]);
			}

			// Pre-incremento

			self& operator++ (void)
			{
				++this->_ptr;
				return (*this);
			}

			// Post-incremento

			self operator++ (int)
			{
				self tmp(*this);
				++this->_ptr;
				return(tmp);
			}

			self& operator+= (difference_type n)
			{
				this->_ptr += n;
				return (*this);
			}

			// Pre-decremento

			self& operator-- (void)
			{
				--this->_ptr;
				return (*this);
			}

			// Post-decremento

			self operator-- (int)
			{
				self tmp(*this);
				--this->_ptr;
				return(tmp);
			}

			self& operator-= (difference_type n)
			{
				this->_ptr -= n;
				return (*this);
			}

			self operator+ (difference_type n) const
			{
				return (self(this->_ptr + n));
			}

			self operator- (difference_type n) const
			{
				return (self(this->_ptr - n));
			}

	};


	///////////////////////     Non-member function overloads      ////////////////////////

	// Las funciones no miembro de la clase no cuentan con el parámetro oculto this. Tampoco pueden
	// acceder directamente a las variables y funciones privadas o protegidas. No se usan invocándolas
	// desde un objeto de la clase ( objeto.funcion() ) sino llamándolas directamente ( funcion() ).

	template <class It1, class It2>
	bool operator== (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() == rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator!= (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() != rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator< (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() < rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator<= (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() <= rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator> (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() > rhs.get_ptr());
	}

	template <class It1, class It2>
	bool operator>= (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
	{
		return (lhs.get_ptr() >= rhs.get_ptr());
	}

	template <class It>
	vector_iterator<It>	operator+ (typename vector_iterator<It>::difference_type n,
		const vector_iterator<It>& it)
	{
		return (it.get_ptr() + n);
	}

	template <class It1, class It2>
	typename vector_iterator<It1>::difference_type	operator- (const vector_iterator<It1>& lhs,
		const vector_iterator<It2>& rhs)
	{
		return(lhs.get_ptr() - rhs.get_ptr());
	}

}

#endif
