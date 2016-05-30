#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

int main()
{
	
	int initial_time = 0;
	int current_time = 0;
	int ratio = 1000;

	int seconds = 0;
	int decimes = 0;
	int minutes = 0;

	while (1)
	{
		int current_time = GetTickCount();

		if (current_time >= (initial_time + ratio))
		{
			
			printf("%i:%i%i\n", minutes, decimes, seconds);
			seconds++;

			if (seconds > 9)
			{
				seconds = 0;
				++decimes;
			}

			if (decimes > 5)
			{
				decimes = 0;
				++minutes;
			}

			
			initial_time = current_time;		
		}
		
	}

}