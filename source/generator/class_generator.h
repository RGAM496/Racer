#ifndef URJR_CLASS_GENERATOR_H
#define URJR_CLASS_GENERATOR_H

namespace urjr
{
	namespace ClassGenerator
	{


		template <class C>
		class Interface
		{
			public:

				// Crear objetos alojados dinámicamente.
				virtual C* generate() = 0;
		};


		template <class C, class D = C>
		class Instance
		: virtual public Interface<D>
		{
			public:

				// Crear objetos alojados dinámicamente.

				D* generate() {
					return new C();
				}
		};


		// Función para crear dinámicamente un objeto.
		template <class C, class D>
		D* new_dynamic() {
			return new C();
		}


	}
}


#endif // URJR_CLASS_GENERATOR_H
