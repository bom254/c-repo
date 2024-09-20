#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// Struct to store the Bingo card numbers
struct BingoCard {
	int numbers[25];
};

// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Function to create a new Bingo card and shuffle the number
struct BingoCard createBingoCard() {
	struct BingoCard card;
	int possibleNumbers[25];
	for (int i=0; i<25; ++i) {
		possibleNumbers[i] = i + 1;
	}
	for(int i=0; i<25; ++i) {
		int j = generateRandomNumber(i, 24);
		int temp = possibleNumbers[i];
		possibleNumbers[i] = possibleNumbers[j];
		possibleNumbers[j] = temp;
	}
	for(int i=0; i<25; ++i) {
		card.numbers[i] = possibleNumbers[i];
	}
	return card;
}

// Function to mark the drawn number on a Bingo card
void drawNumberAndMark(struct BingoCard* card, int number) {
	for(int i=0; i<25; ++i) {
		if(card -> numbers[i] == number) {
			card -> numbers[i] = 0;
		}
	}
}

// function to check if a bingo card has achieved a Bingo pattern
int hasBingo(struct BingoCard card) {
	for(int i=0; i<5; ++i) {
		// Check rows for Bingo
		if(card.numbers[i*5] == 0
			&&card.numbers[i*5+1] == 0
			&&card.numbers[i*5+2] == 0
			&&card.numbers[i*5+3] == 0
			&&card.numbers[i*5+4] == 0) {
				return 1;
			}

		// Check columns for Bingo
		if(card.numbers[i] == 0 && card.numbers[i+5] == 0
			&&card.numbers[i+10] == 0
			&&card.numbers[i+15] == 0
			&&card.numbers[i+20] == 0) {
			return 1;
		}
	}

	// check diagonals for Bingo
	if((card.numbers[0] == 0 && card.numbers[6] == 0
                        &&card.numbers[12] == 0 &&card.numbers[18] == 0
			&&card.numbers[24] == 0 )
			|| (card.numbers[4] == 0 &&card.numbers[8] == 0
			&&card.numbers[12] == 0
			&&card.numbers[16] == 0
			&&card.numbers[20] == 0)) {
			return 1;
	}

	// No Bingo pattern found
	return 0;
}

// Function to display the Bingo card
void displayCard(struct BingoCard card) {
	for(int i=0; i<25; ++i) {
		// Display numbers or 'X' for drawn numbers
		if(card.numbers[i] != 0) {
			printf("%d\t", card.numbers[i]);
		}
		else{
			printf("X\t");
		}

		// Move to the next line after every 5 minutes
		if((i+1) % 5 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

int main() {
	srand(time(NULL));  // Seed the random number generator
	printf("Welcome to Bingo!\n");

	// Create Bingo cards for both players
	struct BingoCard player1Card = createBingoCard();
        struct BingoCard player2Card = createBingoCard();

	// Tracks the current player
	int currentPlayer = 1;

	// Main game loop
	while(1) {
		// Get the current player's card
		struct BingoCard currentCard = (currentPlayer == 1) ? player1Card : player2Card;

		// Generate a random number between 1 and 25
		int drawnNumber = generateRandomNumber(1, 25);

		// Mark the drawn numbers on both players cards
		drawNumberAndMark(&player1Card, drawnNumber);
		drawNumberAndMark(&player2Card, drawnNumber);

		printf("\n?Player %d - Draw Number: %d\n", currentPlayer, drawnNumber);

		// Display both players cards
		printf("Player 1's cards:\n");
		displayCard(player1Card);
		printf("----------------------\n");
		printf("Player 2's Card:\n");
		displayCard(player2Card);
		printf("---------------------\n");

		// Check if the current player has achieved Bingo
		if(hasBingo(currentCard)) {
			// Exit the game loop
			printf("\nPlayer %d has achieved Bingo: Congratulations", currentPlayer);
			break;
		}

		// Switch to the other player for the next round
		currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}
	return 0;
}


