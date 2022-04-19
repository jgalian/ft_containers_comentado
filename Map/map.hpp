#ifndef MAP_HPP
#define MAP_HPP

# include "../common/reverse_iterator.hpp"
# include "../common/enable_if.hpp"
# include "../common/is_integral.hpp"
# include "../common/lexicographical_compare.hpp"
# include "../common/equal.hpp"
# include "pair.hpp"
# include "tree_iterator.hpp"

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>,
		class Alloc = std::allocator<ft::node<ft::pair<const Key,T> > > >
	class map
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const key_type, mapped_type>						value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::template rebind<value_type>::other	node_allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef ft::node<value_type>										node_type;
			typedef node_type*													node_ptr;
			typedef ft::tree_iterator<value_type, node_type>					iterator;
			typedef ft::tree_iterator<const value_type, node_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef std::ptrdiff_t												difference_type;
			typedef size_t														size_type;
			class	value_compare : public std::binary_function<value_type, value_type, bool>
			{																					// https://www.cplusplus.com/reference/map/map/value_comp/
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

				protected:													
					Compare	comp;

				public:
					value_compare(Compare c) :
						comp(c)
					{}

					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			node_ptr		_root;
			allocator_type	_alloc;
			size_type		_size;
			key_compare		_key_cmp;
			value_compare	_val_cmp;

		public:

		/////////////////////////     Constructors      /////////////////////////////////

			// Este es el constructor por defecto. No recibe parámetros.
			// Construye un objeto del tipo key_compare, que us usado por el contenedor para comparar las claves. Por
			// defecto es un objeto de tipo "less". Para usarlo se le pasan dos claves y devuelve "true" si la primera
			// debe ir antes que la segunda y "false" en el resto de casos.
			// También construye por defecto otro objeto de tipo allocator_type (para gestionar la memoria). Este objeto
			// se usa primero para reservar memoria para el elemento raíz. Y después para construir el nodo raíz con el
			// metodo construct() que recibe como primer parámetro un puntero al espacio reservado en la instrucción
			// anterior y como segundo el objeto que se debe construir en el espacio apuntado.

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_root(),
				_alloc(alloc),
				_size(0),
				_key_cmp(comp),
				_val_cmp(_key_cmp)
			{
				this->_root = this->_alloc.allocate(1);
				this->_alloc.construct(this->_root, node_type());
			}

			// Constuye un map con los elementos en el rango determinado por los iteradores "first" y "last".
			// Es como el constructor anterior solo que hace una inserción de elmentos.

			template <class InputIterator>
			map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_root(),
				_alloc(alloc),
				_size(0),
				_key_cmp(comp),
				_val_cmp(_key_cmp)
			{
				this->_root = this->_alloc.allocate(1);
				this->_alloc.construct(this->_root, node_type());
				this->insert(first, last);
			}

			// Constructor copia

			map(const map& src) :
				_root(),
				_alloc(allocator_type()),
				_size(0),
				_key_cmp(key_compare()),
				_val_cmp(_key_cmp)
			{
				this->_root = this->_alloc.allocate(1);
				this->_alloc.construct(this->_root, node_type());
				*this = src;
			}


		///////////////////////////     Destructor      /////////////////////////////////

			virtual ~map(void)
			{
				this->clear();
				this->_alloc.deallocate(this->_root, 1);
			}


		///////////////////////////     Operator=      /////////////////////////////////

			map& operator= (map const &rhs)
			{
				if (this != &rhs)
				{
					this->clear();
					this->insert(rhs.begin(), rhs.end());
				}
				return (*this);
			}


		///////////////////////////     Iterators      /////////////////////////////////

			// Devuelve el resultado de llamar al constructor iterator() que es un alias para tree_iterator
			// al que se le pasa como parámetro la función leftmost(), que devuelve la posición más a la
			// izquierda del árbol.

			iterator begin(void)
			{
				return (iterator(leftmost(this->_root)));
			}

			const_iterator begin(void) const
			{
				return (const_iterator(leftmost(this->_root)));
			}

			// Igual que begin() pero en este caso devuelve la posición final, la más a la derecha.

			iterator end(void)
			{
				return (iterator(rightmost(this->_root)));
			}

			const_iterator end(void) const
			{
				return (const_iterator(rightmost(this->_root)));
			}

			reverse_iterator rbegin(void)
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin(void) const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend(void)
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend(void) const
			{
				return (const_reverse_iterator(this->begin()));
			}


		///////////////////////////     Capacity      /////////////////////////////////

			bool empty(void) const
			{
				return (this->_size == 0 ? true : false);
			}

			size_type size(void) const
			{
				return (this->_size);
			}

			size_type max_size(void) const
			{
				return (this->_alloc.max_size());
			}


		/////////////////////////     Element access      /////////////////////////////

			// https://www.cplusplus.com/reference/map/map/operator[]/
			// Si se encuentra la clave pasada, se devuelve una referencia al valor que corresponde
			// a dicha clave. Y si no se encuentra se inserta un nuevo elemento con esa clave y se
			// devulve una referencia al valor correspondiente, aunque no tenga nada asignado.
			// Siempre se aumenta size en 1.

			mapped_type& operator[] (const key_type& k)
			{
				return (this->insert(value_type(k, mapped_type()))).first->second;
			}

			// Funciona igual que la de arriba menos cuando no se encuentra la clave, que lanza una
			// excepción.

			// mapped_type& at(const key_type& k)
			// {																	// retroactively added to c++98 standard
			// 	iterator it = this->find(k);
			// 	if (it == this->end())
			// 		throw std::out_of_range("No such key.");
			// 	return ((*it).second);
			// }

			// const mapped_type& at(const key_type& k) const
			// {																	// idem
			// 	const_iterator it = this->find(k);
			// 	if (it == this->end())
			// 		throw std::out_of_range("No such key.");
			// 	return ((*it).second);
			// }


		////////////////////////////     Modifiers      ///////////////////////////////

			// https://www.cplusplus.com/reference/map/map/insert/
			// Esta primera versión de insert recibe como parámetro un objeto de tipo value_type (que
			// es un alias para un pair compuesto por clave-valor) y devuelve un objeto de tipo pair
			// compuesto de un iterador y un valor booleano. El iterador apuntará al nuevo elemento
			// insertado o a un elemento que ya existía previamente con esa clave. Y el booleano será
			// "true" si se ha insertado un nuevo objeto o "false" si ya existía un elemento con dicha
			// clave y por tanto no se ha hecho la inserción.
			// Lo primero que debe hacer la función es chequear si ya existe una clave igual que la que
			// se ha pasado como parámetro. Porque en el mapa las claves deben ser únicas. Y si ya
			// existe no se hará la inserción y se devolverá un puntero al elemento donde se encontro
			// dicha clave.
			// En cplusplus indican que una manera alternativa de insertar es con map::operator[]

			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool> ret;							// Par donde guardamos los valores de retorno
				ret.first = this->find(val.first);						// Si la clave pasada existe se guarda la posición. Si no, find() devuelve end()
				if (ret.first == this->end())							// Si devolvió end() porque la clave no existía se mete en el if
				{
					node_ptr	newnode = this->_alloc.allocate(1);		// Se reserva sitio para crear un nuevo nodo
					this->_alloc.construct(newnode, node_type(val));	// Se crea el nuevo nodo con los valores pasados como parámetro a la función insert()
					this->_add_node(newnode);							// Se inserta el nodo creado en el mapa
					ret.first = iterator(newnode);						// Se guarda el primer valor del par de retorno con el iterador al nuevo nodo insertado
					ret.second = true;
				}
				else
					ret.second = false;
				return (ret);
			}

			// La posición indicada como parámetro no fuerza a que el elemento sea insertado ahí, puesto que
			// en un mapa la inserción se hace siguiendo un criterio de ordenación. Es solo una sugerencia.
			// Así que en realidad solo se llama a la función anterior con el valor y devuelve un puntero al
			// nuevo elemento insertado o a la posición del elemento con dicha clave que ya existía previamente.

			iterator insert(iterator position, const value_type& val)
			{
				static_cast<void>(position);
				return this->insert(val).first;
			}

			// Se va llamando en bucle a la primera de las funciones insert hasta que se termine de recorrer
			// el intervalo indicado

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			}

			// https://www.cplusplus.com/reference/map/map/erase/
			// Reduce el tamaño del mapa por el número de elementos eliminados, que son destruidos.

			void erase(iterator position)
			{
				this->_del_node(position.base());
			}

			size_type erase(const key_type& k)
			{
				iterator it = this->find(k);

				if (it == this->end())
					return (0);
				this->_del_node(it.base());
				return (1);									// Devuelve el número de elementos eliminados
			}

			void erase(iterator first, iterator last)
			{
				while (first != last) this->erase(first++);
			}

			// https://www.cplusplus.com/reference/map/map/swap/
			// Cambia el contenido del mapa por el del parámetro pasado, que debe ser otro mapa del mismo
			// tipo, aunque los tamaños pueden no ser iguales. Los iteradores y punteros existentes deben
			// permanecer válidos (excepto los que apuntan al final del mapa).
			// Lo que se hace es cambiar los valores necesarios usando un temporal como paso intermedio.

			void swap(map& x)
			{
				node_ptr		tmp_root = this->_root;
				key_compare		tmp_cmp = this->_key_cmp;
				allocator_type	tmp_alloc = this->_alloc;
				size_type		tmp_size = this->_size;

				this->_root = x._root;
				x._root = tmp_root;
				this->_key_cmp = x._key_cmp;
				x._key_cmp = tmp_cmp;
				this->_alloc = x._alloc;
				x._alloc = tmp_alloc;
				this->_size = x._size;
				x._size = tmp_size;
			}

			void clear(void)
			{
				node_ptr endnode = this->end().base();			
				endnode->parent->right = NULL;					
				this->_recursive_clear(this->_root);
				this->_root = endnode;
				this->_size = 0;
			}


		////////////////////////////     Observers      ///////////////////////////////

			// Devuelve una copia del objeto key_compare usado por el mapa para comparar las claves. Este
			// objeto se genera durante la construcción del mapa y es el tercer parámetro de la plantilla.

			key_compare key_comp(void) const
			{
				return (this->_key_cmp);
				//return (key_compare());						
			}

			value_compare value_comp(void) const
			{
				return (this->_val_cmp);
				//return (value_compare(key_compare()));
			}


		////////////////////////////     Operations      ///////////////////////////////

			// Busca en el mapa un elemento con la clave pasada como parámetro y devuelve un iterador al mismo
			// si lo encuentra. Si no, devuelve un iterador a map::end
			// Primero crea un puntero a nodo que inicializa con la raíz del mapa pasado como this.
			// Luego inicia el bucle para recorrer los elementos y buscar si hay coincidencia. Primero se chequea
			// que no se haya llegado al final (que exista el elemento actual), y luego que la clave del
			// elemento actual sea diferente a la pasada. Para hacer esto último se usa _key_cmp() que es como
			// llamar a less. Less es una "class object function", que son instancias de una clase con una
			// función miembro operator(). Esta función miembro permite al objeto ser usado con la misma
			// sintaxis que una llamada a función. En este caso retorna 1 si el primer parámetro es menor
			// que el segundo.

			iterator find(const key_type& k)
			{
				node_ptr	curr = this->_root;

				while (curr && (this->_key_cmp(curr->data.first, k) || this->_key_cmp(k, curr->data.first)))
				{
					if (this->_key_cmp(k, curr->data.first))	// Si la clave pasada es < que la del elemento actual mueve este hacia la izquierda
						curr = curr->left;
					else
						curr = curr->right;						// En caso contrario a la derecha
				}
				if (curr)										// Cuando el bucle termina, si current existe es que ha encontrado una coincidencia
					return (iterator(curr));
				else
					return (this->end());
			}

			const_iterator find(const key_type& k) const
			{
				node_ptr	curr = this->_root;

				while (curr && (this->_key_cmp(curr->data.first, k) || this->_key_cmp(k, curr->data.first)))
				{
					if (this->_key_cmp(k, curr->data.first))
						curr = curr->left;
					else
						curr = curr->right;
				}
				if (curr)
					return (const_iterator(curr));
				else
					return (this->end());
			}

			size_type count(const key_type& k) const
			{
				return (find(k) != this->end() ? 1 : 0);
			}

			// Devuelve un iterador apuntando al primer elemento en el contenedor cuya clave no es más pequeña
			// (es decir, es igual o más grande) de la que se pasa como parámetro.

			iterator lower_bound(const key_type& k)
			{
				iterator	it_beg = this->begin();
				iterator	it_end = this->end();

				while (it_beg != it_end)
				{
					if (!this->_key_cmp(it_beg->first, k))		// _key_cmp() funciona como less(). Devuelve 1 si el 1er parámetro es menor que el 2o
						break;									// Así que cuando encuentre uno que no sea más pequeño (que sea = o >) saldrá del bucle
					++it_beg;
				}
				return (it_beg);
			}

			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator	it_beg = this->begin();
				const_iterator	it_end = this->end();

				while (it_beg != it_end)
				{
					if (!this->_key_cmp(it_beg->first, k))
						break;
					++it_beg;
				}
				return (it_beg);
			}

			// Devuelve un iterador apuntando al primer elemento en el contenedor cuya clave va detrás
			// de la que se pasa como parámetro. Es decir, en un mapa ordenado de menor a mayor, devolvería
			// un iterador al primer elemento cuya clave es mayor que la pasada.

			iterator upper_bound(const key_type& k)
			{
				iterator	it_beg = this->begin();
				iterator	it_end = this->end();

				while (it_beg != it_end)
				{
					if (this->_key_cmp(k, it_beg->first))		// Devuelve 1 si el 1er parámetro es menor que el 2o
						break;									// Solo entra al bucle cuando el 2o elemento es mayor que la clave pasada
					++it_beg;
				}
				return (it_beg);
			}

			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator	it_beg = this->begin();
				const_iterator	it_end = this->end();

				while (it_beg != it_end)
				{
				if (this->_key_cmp(k, it_beg->first))
						break;
					++it_beg;
				}
				return (it_beg);
			}

			// Se supone que devuelve el rango de elementos que contienen la clave pasada como parámetro.
			// Pero como en el mapa no puede haber claves repetidas, como mucho habrá 1 elemento igual.
			// La función devuelve un objeto de tipo pair, cuyo primer elemento es el equivalente a lo que
			// devuelve lower_bound (un iterador al 1er elemento que no es menor que el pasado), y como
			// segundo elemento sería el equivalente a upper_bound (un iterador al 1er elemento mayor que
			// el que se ha pasado como parámetro). Si no hay un elemento que coincida los dos miembros
			// del pair serán iguales.

			ft::pair<iterator,iterator> equal_range(const key_type& k)
			{
				ft::pair<iterator, iterator> ret;

				ret.first = this->lower_bound(k);
				ret.second = this->upper_bound(k);
				return (ret);
			}

			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
			{
				ft::pair<const_iterator, const_iterator> ret;

				ret.first = this->lower_bound(k);
				ret.second = this->upper_bound(k);
				return (ret);
			}


		////////////////////////////     Allocator      ///////////////////////////////

			allocator_type get_allocator(void) const
			{
				return (this->_alloc);
			}


		//////////////////////////     Extra function      /////////////////////////////

			// lastmap.print_tree(lastmap.get_root(), 0);

			void print_tree(node_ptr root, int space)
			{
				// Base case
				if (root == NULL)
					return;

				// Increase distance between levels
				space += 10;

				// Process right child first
				print_tree(root->right, space);

				// Print current node after space
				// count
				std::cout << std::endl;
				for (int i = 10; i < space; i++)
					std::cout << " ";
				std::cout << root->data.first << "\n";

				// Process left child
				print_tree(root->left, space);
			}

		/////////////////////////     Getter      ///////////////////////////

			node_ptr get_root()
			{
				return (_root);
			}


		////////////////////////     Private functions      ///////////////////////////

		private:

			// https://www.youtube.com/watch?v=gcULXE7ViZw&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=36
			// Va haciendo llamadas recursivas para borrar el árbol (o subárbol) a partir del nodo dado.
			// Si como argumento se pasa la raíz se borrará el árbol entero.

			void _recursive_clear(node_ptr curr)
			{
				if (curr == NULL)
					return ;
				this->_recursive_clear(curr->left);
				this->_recursive_clear(curr->right);
				this->_alloc.deallocate(curr, 1);
			}

			// Primero se comprobaría si el mapa está vació. En ese caso simplemente habría que
			// asignar el nuevo nodo a la raíz. En caso contrario se crea un nuevo puntero
			// apuntando a la raíz para usarlo como iterador e ir recorriendo el árbol hasta
			// encontrar la posición en la que se debe insertar el nuevo nodo. En un árbol de
			// tipo BST (binary search tree) cada nodo tiene solo dos posibles hijos. En los de
			// la izquierda estarán los valores más pequeños que el de la reíz del nodo, y en la
			// la derecha estarán los que sean más grandes. No se pueden repetir los valores de
			// la clave (dentro del par que guarda como datos cada nodo).
			// Para encontrar la posición solo hay que ir preguntando si el valor (en este caso
			// de la clave) es mayor o menor que el del nodo pasado como parámetro. Si es menor
			// hay que mover el puntero hacia el nodo de la izquierda (de modo que la raíz de
			// ese nodo que actua como iterador sea ahora el nodo que había a la izquierda). Y si
			// es mayor, pues lo mismo pero hacia la derecha. Y así sucesivamente hasta que se
			// Así hasta que llegues a un sitio vacío (el puntero-iterador apunte a NULL). Y ese
			// será el lugar donde habrá que insertar el valor. Y habrá que sumar uno a _size.

			void _add_node(node_ptr to_add)
			{
				node_ptr*	parent = &this->_root;					// Puntero a node_ptr inicializado con la raíz del árbol
				node_ptr*	curr = &this->_root;					// Puntero a node_ptr inicializado con la raíz del árbol
				node_ptr	endnode = rightmost(this->_root);		// Node_ptr incializado con la dirección del nodo más a la derecha (el último=) del árbol
				bool		which_direction;						// Boolean para ver si hay que ir hacia la izquierda o la derecha

				++this->_size;										// Se aumenta el tamaño del árbol
				while (*curr && *curr != endnode)					// La primera vez no entra pero luego creo que entra siempre
				{
					parent = curr;									// Cada vez que entra al bucle se igualan, pero curr cambia antes de salir y parent no
					which_direction = _val_cmp(to_add->data, (*curr)->data);	// _val_cmp es una comparación de tipo less() que devuelve 1 si el 1er parám es < que el 2o
					curr = (which_direction ? &(*curr)->left : &(*curr)->right);	// Si antes dio 1 guarda en curr la dirección del nodo de la izq, si no de la dcha
				}
				if (*curr == NULL)									// Entra cuando llega a un sitio donde insertar el nuevo elemento, y no es el último lugar del árbol
				{
					to_add->parent = *parent;						// Se enlaza el nuevo nodo con el nodo padre que le corresponde
					*curr = to_add;									// Se le asigna a la dirección donde apunta curr la del nuevo nodo (curr había...
				}													// ...sido asignado en el bucle a la correspondiente posición vacía en el árbol según su clave)
				else
				{													// Entra cuando hay que insertar al final del árbol, porque hay que actulizar tb el endnode (no como en el if)
					*curr = to_add;									// Cambia el nodo vacío anclado al árbol por el nodo que hay que insertar
					to_add->parent = endnode->parent;				// Pone como padre el padre del último nodo (en la primera inserción es NULL)
					endnode->parent = rightmost(to_add);			// Pone como padre del ultimo nodo (que ahora es el nodo vacío) el nuevo nodo
					rightmost(to_add)->right = endnode;				// Pone como hijo hacia la derecha al último nodo (que ahora es el nodo vacío)
				}
			}

			// https://www.youtube.com/watch?v=gcULXE7ViZw&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=36
			// Si el nodo a borrar no tiene hijos o tiene solo 1 el proceso es fácil, porque solo hay
			// que enlazar su hijo (que puede tener a su vez los hijos que sea) con su padre. Si tiene
			// 2 hijos la cosa es más complicada y es cuando entraría en el else. En el árbol de ejemplo
			// de abajo, si queremos borrar el 5 (que tiene 2 hijos) hay que sustituirlo por el 6 (para
			// que se mantengan las propiedades de un árbol binario de búsqueda de a la izquierda más
			// pequeño y a la derecha más grande) que es el más a la izquierda de la rama derecha del
			// nodo a borrar.
			//
			//						10
			//				  5           12
			//			  2   	  4
			//				   7     9
			//				 6

			void _del_node(node_ptr to_del)
			{
				if (!to_del->left)											// Si el nodo a borrar no tiene hijo a la izquierda...
				{
					if (!to_del->parent)									// Si no tiene padre (es la raíz)...
						this->_root = to_del->right;						// ...se sustituye el nodo a borrar por su hijo derecho como raíz del árbol
					else if (to_del == to_del->parent->left)				// Si el nodo a borrar tiene padre y está a la izquierda de su padre...
						to_del->parent->left = to_del->right;				// ...se sustituye el nodo a borrar por el de la derecha (que puede estar poblado o no)
					else													// Si el nodo a borrar tiene padre y está a la derecha de su padre...
						to_del->parent->right = to_del->right;				// ...se sustituye el nodo a borrar por el de la derecha (que puede estar poblado o no)
					if (to_del->right)										// Si el nodo de la derecha del nodo a borrar existe...
						to_del->right->parent = to_del->parent;				// ...se enlaza al padre del nodo a borrar, para que no se quede descolgado tras su eliminación
				}
				else if (!to_del->right)									// El mismo proceso que arriba pero si el nodo a borrar no tiene hijo a la derecha
				{															// Cuando el nodo a borrar no tiene hijos o tiene sólo a un lado, es muy fácil
					if (!to_del->parent)									// El problema es cuando tiene dos hijos
						this->_root = to_del->left;
					else if (to_del == to_del->parent->left)
						to_del->parent->left = to_del->left;
					else
						to_del->parent->right = to_del->left;
					to_del->left->parent = to_del->parent;
				}
				else														// Si entra aquí es porque el nodo a borrar tiene hijos tanto a derecha como a izquierda
				{
					node_ptr	successor = leftmost(to_del->right);		// El nodo que debe ocupar la posición del nodo borrado es el más a la izquierda de la rama derecha de este
					if (!(to_del == successor->parent))						// Si el sucesor NO es hijo directo del nodo a borrar entra en el if
					{
						if (successor == successor->parent->left)			// Si el sucesor está situado a la izquierda de su propio padre ...
							successor->parent->left = successor->right;		// ...el nodo a la derecha del padre del sucesor pasaría a estar directamente a la derecha del sucesor
						else												// CREO QUE AQUÍ NO ENTRARÍA NUNCA porque para no entrar en el if anterior el sucesor tendria que estar a la
							successor->parent->right = successor->right;	// dcha de su propio padre y eso solo puede ser si es hijo directo (y no entraría al if anterior del anterior)
						if (successor->right != NULL)						// Si el sucesor tiene hijo a la derecha (a la izq no podría porque entonces sería ese el sucesor)...
							successor->right->parent = successor->parent;	// este hijo pasa a ser ahora hijo del que era el abuelo.
						successor->right = to_del->right;					// Y como el sucesor va a ocupar el sitio del nodo a borrar, se apunta el dcho del sucesor al dcho de este
						successor->right->parent = successor;				// Y se actuliza tb el padre del nodo a la dcha del nodo a borrar por el del sucesor, que ahora va a ser su padre
					}
					if (!to_del->parent)									// Si el nodo a borrar no tiene padre (es la raíz)...
						this->_root = successor;							// ..se sustituye la raíz por el sucesor
					else if (to_del == to_del->parent->left)				// Si el nodo a borrar está a la izquierda de su padre...
						to_del->parent->left = successor;					// ...se actualiza ese enlace para que ahora el padre, por su izquierda, tenga al sucesor
					else													// Si no entró en el if anterior es porque el nodo a borrar está a la derecha de su padre y entonces...
						to_del->parent->right = successor;					// ...hay que actualizar el enclace para que ahora el padre, por su derecha, tenga al sucesor
					successor->parent = to_del->parent;						// Se actualiza el enlace para que ahora el padre del sucesor sea el padre que tenía el nodo a borrar
					successor->left = to_del->left;							// Se actualiza el enlace para que ahora el nodo a la izquierda del sucesor sea el que tenía el nodo a borrar
					successor->left->parent = successor;					// Y se actualiza tb este otro enlace
				}
				--this->_size;
				this->_alloc.deallocate(to_del, 1);							// Se elimina finalmente el nodo a borrar
			}

	};


	////////////////////////////     Non member overloads      ///////////////////////////////

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
