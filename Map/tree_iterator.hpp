#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "../common/iterator_traits.hpp"

// https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P

namespace ft
{
	template <typename T>
	struct node
	{
		T			data;
		node*		parent;
		node*		left;
		node*		right;
		int			height;

		node(const T& src = T()) :
			data(src),
			parent(NULL),
			left(NULL),
			right(NULL),
			height(1)
		{};
	};

	template <typename T>
	node<T>* rightmost(node<T>* node)
	{
		while (node->right != NULL)
			node = node->right;
		return (node);
	}

	template <typename T>
	node<T>* leftmost(node<T>* node)
	{
		while (node->left != NULL)
			node = node->left;
		return (node);
	}

	// tree_iterator hereda de iterator_traits, que toma como parámetro la clase base iterator (para poder especificar
	// el tipo de iterador).

	template <typename T, typename node_type>
	class tree_iterator : ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >
	{
		public:
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::iterator_category	iterator_category;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::value_type		value_type;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::difference_type	difference_type;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::reference			reference;
			typedef typename  ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >::pointer			pointer;

		private:
			node_type*	_node;

		public:

		///////////////////////////     Constructors      //////////////////////////////

			tree_iterator(node_type* src = NULL) :
				_node(src)
			{}

			tree_iterator(const tree_iterator &src)
			{
				*this = src;
			}


		///////////////////////////     Destructor     ////////////////////////////////

			~tree_iterator(void)
			{}


		///////////////////////     Operator overloads      ////////////////////////////

			tree_iterator& operator= (tree_iterator const &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_node = rhs._node;
				return (*this);
			}

			node_type* base() const
			{
				return (this->_node);
			}

			reference operator* (void) const
			{
				return (this->_node->data);
			}

			pointer operator-> (void) const
			{
				return (&this->_node->data);
				//return &this->operator*();
			}

			// Preincremento

			tree_iterator& operator++ (void)
			{
				if (this->_node->right != NULL)							// Si tiene hijo a la derecha llama a la función que devuelve el nodo más a la izquierda en el subárbol cuya raíz...
					this->_node = leftmost(this->_node->right);			// ...es dicho hijo, porque ese será el que va a continuación. Y si dicho hijo no tiene descendencia por su izquierda...
				else													// ...entonces es él mismo el que va a continuación, y será a él quien devuelva la función leftmost()
				{
					node_type*	child = this->_node;					// Crea una variable auxiliar para ir actualizandola con el hijo del nodo actual (que se irá moviendo hasta encontrar...
					this->_node = this->_node->parent;					// ...la posición deseada). El proceso es: se iguala la variable auxiliar al nodo original y este se mueve a la...
					while (this->_node && child == this->_node->right)	// ...posición de su padre. Entonces, mientras el auxiliar sea el hijo derecho del nodo original hay que seguir repitiendo.
					{													// Cuando esto deje de pasar es que hemos llegado al nodo que va a continuación y podemos hacer el return de esa posición.
						child = this->_node;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			}

			// Postincremento

			tree_iterator operator++ (int)
			{
				tree_iterator tmp(*this);								// Se crea un temporal. Se aumenta la posición del nodo actual. Y se devuelve el temporal que no estaba actualizado.
				++(*this);
				return (tmp);
			}

			// Predecremento

			tree_iterator& operator-- (void)							// El proceso es igual que el preincremento, pero invertido
			{
				if (this->_node->left != NULL)
					this->_node = rightmost(this->_node->left);
				else
				{
					node_type*	child = this->_node;
					this->_node = this->_node->parent;
					while (this->_node && child == this->_node->left)
					{
						child = this->_node;
						this->_node = this->_node->parent;
					}
				}
				return (*this);
			}

			// Postdecremento

			tree_iterator operator-- (int)
			{
				tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			template <class U>
			bool operator== (const tree_iterator<U, node_type> &rhs) const
			{
				return (this->_node == rhs._node);
				//return (this->_node == rhs.base());
			}

			template <class U>
			bool operator!= (const tree_iterator<U, node_type> &rhs) const
			{
				return (this->_node != rhs._node);
				//return (this->_node != rhs.base());
			}
	};
}

#endif
