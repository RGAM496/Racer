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

				// Crear objetos alojados din�micamente.
				virtual C* generate() = 0;
		};


		template <class C, class D = C>
		class Instance
		: virtual public Interface<D>
		{
			public:

				// Crear objetos alojados din�micamente.

				D* generate() {
					return new C();
				}
		};


		// Funci�n para crear din�micamente un objeto.
		template <class C, class D>
		D* new_dynamic() {
			return new C();
		}


	}
}


#endif // URJR_CLASS_GENERATOR_H
