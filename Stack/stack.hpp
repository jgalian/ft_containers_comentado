#ifndef STACK_HPP
# define STACK_HPP

# include <cstddef>
# include "../Vector/vector.hpp"

// Stack es un tipo de adaptador de contenedor, no un contenedor en sí mismo. Lo que hace un
// adaptador de contenedor es que toma un tipo de contenedor y le impone una serie de
// restricciones para acotar su funcionalidad. En este caso, por ejemplo, debajo del stack
// lo que funciona es un contenedor al que se le han limitado las funcionalidades para que
// se comporte como lo haría un stack (solo se pueden añadir y quitar elementos por un extremo,
// con un comportamiento LIFO - Last In First Out).
// El contenedor usado como base debe ser capaz de soportar las funciones back(), push_back(),
// pop_back(), empty() y size(). Y los contenedores de la stl que cumplen estos requisitos son:
// vector, deque y list. Stack por defecto usa deque, pero en el subject nos piden que usemos
// vector.

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef	T 			value_type;
			typedef Container 	container_type;
			typedef	size_t 		size_type;

		protected:
			container_type _c;

		public:

		/////////////////////////     Constructors      /////////////////////////////////

			explicit stack(const container_type& ctnr = container_type()) :
				_c(ctnr)
			{}

			stack(const stack<T, Container>& src) :
				_c(src._c)
			{}


		/////////////////////////     Destructor      //////////////////////////////////

			~stack()
			{}


		///////////////////////     Operator= overload      ///////////////////////////

			stack<T, Container>& operator= (const stack<T, Container>& src)
			{
				this->_c = src._c;
				return (*this);
			}


		///////////////////////     Member functions      ///////////////////////////

			bool empty() const
			{
				return (this->_c.empty());
			}

			size_type size() const
			{
				return (this->_c.size());
			}

			value_type& top()
			{
				return (this->_c.back());
			}

			const value_type& top() const
			{
				return (this->_c.back());
			}

			void push(const value_type& val)
			{
				this->_c.push_back(val);
			}

			void pop()
			{
				this->_c.pop_back();
			}


		///////////   Friend declaration for nom member function overloads   ///////////

		// Se declaran aquí como friend porque se trata de funciones no miembro que se van
		// a definir fuera de la clase, pero tienen que acceder a una variable
		// privada de la clase.

			template <class U, class Cont>
			friend bool	operator== (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator!= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator<  (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator<= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator>  (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

			template <class U, class Cont>
			friend bool	operator>= (const stack<U,Cont>& lhs, const stack<U,Cont>& rhs);

	};


	/////////////////////     Non member function overloads      /////////////////////////

	// Las funciones declaradas como frind dentro de la clase se definen aquí

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c == rhs._c);
	}

	template <class T, class Container>
	bool	operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c != rhs._c);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c < rhs._c);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c <= rhs._c);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c > rhs._c);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c >= rhs._c);
	}

}

#endif
