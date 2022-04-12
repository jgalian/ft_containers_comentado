#ifndef ENABLE_IF
# define ENABLE_IF

// Se basa en el concepto de SFINAE (Substitution Failure Is Not An Error). Este es un concepto que
// se aplica durante la resolución, por parte del compilador, de las sobrecargas de plantillas de
// función. Cuando la sustitución del tipo de datos falla, esa sobrecarga o especialización
// concreta se elimina del set de opciones que el compilador chequea para encontrar la más adecuada,
// y evita dar un error de compilación.
// Enable_if se usa junto con algún type_traits (como is_integral,  o is_object, o is_pointer...) para
// chequear que el tipo de dato sea como tiene que ser. Si se cumple la condición se crea un objeto
// que contine la variable type, que corresponde al tipo de dato que se chequeaba. Si no se cumple,
// no se genera esa variable y la plantilla no se puede construir, por lo que no se tiene en cuenta
// por el compilador para ser elegida.

// https://www.cplusplus.com/reference/type_traits/enable_if/
// https://docs.microsoft.com/es-es/cpp/standard-library/enable-if-class?view=msvc-170

namespace ft
{
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef	T	type;
	};
}

#endif
