#ifndef URJR_RANDOM_GENERATOR_H
#define URJR_RANDOM_GENERATOR_H

#include <vector>
#include <initializer_list>
#include <random>
#include <chrono>
#include <cmath>


namespace urjr
{
	namespace RandomGenerator
	{


		template <class E>
		class Discrete
		{
			protected:

				struct C {
					E item;
					double peso;
				};

				std::vector <E> v;
				std::discrete_distribution <size_t> *distribution;

				// Genera un número al azar que corresponderá al índice.
				template <typename URNG>
				size_t generate (URNG &generator) {
					return (*distribution) (generator);
				}

			public:

				Discrete (std::initializer_list <C> il) {
					std::vector<double> p;
					for (const C *i = begin (il); i != end (il); ++i) {
						v.push_back (i->item);
						p.push_back (i->peso);
					}
					distribution = new std::discrete_distribution <size_t> (p.begin(), p.end());
				}

				~Discrete () {
					delete distribution;
				}

				template <typename URNG>
				E& operator () (URNG &generator) {
					size_t i = generate (generator);
					return v[i];
				}
		};


		template <class RealType = double>
		class UniformReal
		: virtual public std::uniform_real_distribution <RealType>
		{
			protected:

				RealType
					a,
					b;

			public:

				UniformReal (RealType a = RealType(0), RealType b = RealType(1))
				: std::uniform_real_distribution <RealType> (a, nextafter(b, std::numeric_limits<double>::max()))
				{
					this->a = a;
					this->b = b;
				}

				template <class URNG>
				RealType operator () (URNG &generator, RealType c, RealType d) {
					RealType e;
					e = std::uniform_real_distribution <RealType> ::operator () (generator);
					e = (e - a) / (b - a) * (d - c) + c;
					return e;
				}
		};


		template <class URNG>
		void time_seed (URNG &generator) {
			auto s =
				std::chrono::high_resolution_clock::now().time_since_epoch().count();
				//std::chrono::system_clock::now().time_since_epoch().count();
			generator.seed (s);
		}


	}
}


#endif // URJR_RANDOM_GENERATOR_H
