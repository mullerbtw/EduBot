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
			// enquanto sonar da frente, direita ou esquerda estiverem a mais de 20cm de obstáculo

			edubotLib->sleepMilliseconds(2000);

			// se sonar da frente & sonar da esquerda estiverem a menos de 20cm de obstáculo
			if (edubotLib->getSonar(3) <= 0.2 && edubotLib->getSonar(0) <= 0.2)
			{
				edubotLib->rotate(90); // vira pra direita
			}
			
			// se sonar da frente & sonar da direita estiverem a menos de 20cm de obstáculo
			if(edubotLib->getSonar(3) <= 0.2 && edubotLib->getSonar(6) <= 0.2)
			{
				edubotLib->rotate(-90); // vira pra esquerda
			}

			// se sonar da esquerda & sonar da direita estiverem a menos de 20cm de obstáculo
			if(edubotLib->getSonar(0) <= 0.2 && edubotLib->getSonar(6) <= 0.2)
			{
				do
				{
				// nothing (continues moving)
				} while (edubotLib->getSonar(3) > 0.2);
			}

			// se sonar da esquerda & sonar da direita estiverem a mais de 20cm de obstáculo
			if((edubotLib->getSonar(0) > 0.2) && (edubotLib->getSonar(6) > 0.2)) // esse segundo parâmetro tá faltando algo
			{
				if((1 + (rand() % (2))) == LEFT) // direção aleatória
				{
					edubotLib->rotate(-90) // vira pra esquerda
				} else edubotLib->rotate(90); // senão vai pra direita
			}

			edubotLib->sleepMilliseconds(2000);
		}

		edubotLib->disconnect();
	}
	else
		cout << "Could not connect to robot!" << endl;

	return 0;
	
}
