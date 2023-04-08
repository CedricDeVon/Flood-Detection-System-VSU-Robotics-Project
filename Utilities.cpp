#include <Arduino.h>
#include "Utilities.h"

char* Utilities::convert(unsigned int number, int size)
{
		int currentIndex = size - 1;
		char *characterString = new char[size];
		unsigned int digits = number;
		while (currentIndex >= 0)
		{
			characterString[currentIndex] = (char) ((digits % 10) + 48);
			digits /= 10;
			currentIndex -= 1;
		}
  	return characterString;
}

	