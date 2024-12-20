#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "libs/EdubotLib.hpp"

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

			if (edubotLib->getSonar(3) <= 0.02)
			{
				if (1 + (rand() % (2)) == 1)
					edubotLib->rotate(-90);
				else
					// if (1 + (rand() % (2)) == 2)
					edubotLib->rotate(90);
			}

			edubotLib->sleepMilliseconds(2000);
		}

		edubotLib->disconnect();
	}
	else
		cout << "Could not connect to robot!" << endl;

	return 0;
}