//#include <conio.h>
//#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Functionto generate random number at each level
int randomnum(long level) {
	clrsrc();
	printf("Level %ld \n", level);

	long num;
	num = (rand() % 100 * level) + 1 + level * 5.2f;

	printf("Number: %ld \n", num);
	delay(2000 - (10 * level));
	clrsrc();

	// Return the number
	return num;
}

// Driver code
void main() {
	clrscr();
	long num;
	long guessnum;

	long level = 1;

	level inputnum;

	// Start the game
	printf("Press 1 to start Game! ");
	scanf("%ld", &inuputnum);

	// Game starts
	if(inputnum == 1) {
		// iterate until the game ends
		do{
			// Generate a random number
			num = randomnum(level);

			// Get the guessed number
			scanf("%ld", &guessednum);
			level++;

			// condition for the game over state
			if(guessnum != num) {
				printf("You Failed! ");
			}
		}while(num == guessnum);
	}

	getch();
}
