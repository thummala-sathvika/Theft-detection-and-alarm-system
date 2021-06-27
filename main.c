#include <avr/io.h>//header to enable data flow control over pins

#define F_CPU 1000000//telling controller crystal frequency

#include <util/delay.h>//header to enable delay function in program

int check();

volatile int alarm = 0;

volatile int chec = 0;

int main(void)

{

	DDRD = 0;//PORTD as input

	DDRC = 0;//PORTC as input

	DDRB = 0xFF;//PORTB as output

	while(1)

	{

		if ((bit_is_set(PIND,0)))

		{

			alarm=1;//after vibration set ALARM bit

		}

		if (bit_is_clear(PINC,4))

		{

			if (bit_is_clear(PINC,2))

			{

				if (bit_is_clear(PINC,1))

				{

					if ((bit_is_set(PINC,0))&&(bit_is_set(PINC,3)))

					{

						_delay_ms(220);

						check();

						//if only keys5,3 and 2 are pressed execute CHECK loop

					}

				}

			}

		}

		if (alarm==1)//If ALARM bit is set

		{

			PORTB |=(1<<PINB0);//turn on LED

			PORTB &=~(1<<PINB1);//turn on BUZZER

		}

		if (alarm==0)//if ALARM bit is not set

		{

			PORTB |=(1<<PINB1);//turn OFF LED

			PORTB &=~(1<<PINB0);//turn OFF buzzer

		}

	}

}

int check()

{

	if (bit_is_clear(PINC,4))

	{

		if (bit_is_clear(PINC,2))

		{

			if (bit_is_clear(PINC,1))

			{

				if ((bit_is_set(PINC,0))&&(bit_is_set(PINC,3)))

				{

					if (chec==1)

					{

						alarm=0;

						//if the buttons are stills pressed after 5sec put reset ALARM bit.

					}

					if (chec==0)

					{

						for (int i=0;i<15;i++)

						{

							_delay_ms(220);

							//check for bits clearance after 5 sec

						}

						chec=1;

						check();

					}

				}

				else

				{

					chec=0;

				}

			}

		}

	}

}
