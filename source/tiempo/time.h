#ifndef URJR_TIEMPO_H
#define URJR_TIEMPO_H

#ifdef DEBUG_TIEMPO
	#include <iostream>
	#include <conio.h>
	#define debug(expr) std::cout << expr << std::endl
	#define test(x) debug ("\t" #x " = " << x)
	#define debug_press_key() _getch()
#else
	#define debug(expr) {}
	#define test(x) {}
	#define debug_press_key() {}
#endif


namespace urjr
{
	namespace Time
	{


		/** Envía una señal cada vez que se cumple el periodo de tiempo
		 *  designado. Debe indicarse manualmente cuánto debe incrementar el
		 *  conteo del tiempo en cada llamada.
		 */
		template <class T>
		class Tick
		{
			private:

				T
					period,
					count;

			public:

				// Establece el periodo de tiempo.
				void set_period (const T& p) {
					period = p;
				}

				// Reinicia el contador de tiempo.
				void reset () {
					count = 0;
				}

				// Devuelve true si se cumplió el periodo de tiempo.
				// 'delta' indica el incremento de tiempo.
				bool tick (const T &delta) {
					count += delta;

					if (count >= period)
					{
						count -= period;
						return true;
					}

					return false;
				}

				// Realiza la misma tarea que 'tick'.
				bool operator () (const T &delta) {
					return tick (delta);
				}

				// Constructor predeterminado.
				Tick ()
				: count (0)
				{}

				// Constructor que establece el periodo.
				Tick (const T& p)
				: period (p)
				, count (0)
				{}
		};


		/** Itera un valor dado 'v' en el intervalo [0,v], uniformemente.
		 *  Se puede indicar la duración de la acción.
		 */
		template <class V, class T = double>
		class UniformIterator
		{
			private:

				const V
					UP,
					DOWN,
					bottom;

				V	top,
					actual_value,
					direction;
				T	period;

			public:

				void set_top (const V &new_top) {
					actual_value = top = new_top;
				}

				void set_period (const T &new_period) {
					period = new_period;
				}

				void switch_direction () {
					direction *= DOWN;
				}

				void go_up () {
					direction = UP;
				}

				void go_down () {
					direction = DOWN;
				}

				V iterate (const T &delta) {
					if ((direction == UP && actual_value < top)
					|| (direction == DOWN && actual_value > bottom))
					{
						actual_value += direction * delta / period * top;
						if (actual_value > top)
							actual_value = top;
						else if (actual_value < bottom)
							actual_value = bottom;
					}
					return actual_value;
				}

				V operator () (const T &delta) {
					return iterate (delta);
				}

				UniformIterator ()
				: UP (1)
				, DOWN (-1)
				, bottom (0)
				, direction (UP)
				{}

				UniformIterator (const V &top, const T &period)
				: UniformIterator()
				{
					set_top (top);
					set_period (period);
				}
		};


	}
}


#undef debug
#undef test
#undef debug_press_key

#endif // URJR_TIEMPO_H
