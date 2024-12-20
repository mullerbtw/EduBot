#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "libs/EdubotLib.hpp"

#define LEFT 1
#define RIGHT 2

int main()
{
	using namespace std;

	EdubotLib *edubotLib = new EdubotLib();

	srand(time(NULL));

	if (edubotLib->connect())
	{
		edubotLib->sleepMilliseconds(200);

		while (edubotLib->isConnected())
		{
			edubotLib->move(0.1);

			do
			{
			// nothing (continues moving)
			} while (edubotLib->getSonar(3) > 0.2 || edubotLib->getSonar(0) > 0.2 || edubotLib->getSonar(6) > 0.2);

			edubotLib->sleepMilliseconds(2000);
			
			if (edubotLib->getSonar(3) <= 0.2 || edubotLib->getSonar(0) <= 0.2)
			{
				edubotLib->rotate(90);
			}

			if(edubotLib->getSonar(3) <= 0.2 || edubotLib->getSonar(6) <= 0.2)
			{
				edubotLib->rotate(-90);
			}

			if(edubotLib->getSonar(0) <= 0.2 || edubotLib->getSonar(6) <= 0.2)
			{
				do
				{
				// nothing (continues moving)
				} while (edubotLib->getSonar(3) > 0.2);
			}

			if((edubotLib->getSonar(0) > 0.2) && (edubotLib->getSonar(6)))
			{
				if((1 + (rand() % (2))) == LEFT)
				{
					edubotLib->rotate(-90)
				} else edubotLib->rotate(90);
			}

			edubotLib->sleepMilliseconds(2000);
		}

		edubotLib->disconnect();
	}
	else
		cout << "Could not connect to robot!" << endl;

	return 0;
	
}
