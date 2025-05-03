//Eddie Tarango
//4/28/25
//Project 10

#include <stdio.h>

#define WORD_LEN 5
#define MAX_GUESSES 6

void read_word(char word[]);
void get_guess(char guess[]);
int is_valid_guess(char guess[]);
void to_lowercase(char word[]);
void display_feedback(char guesses[][WORD_LEN + 1], int count, char mystery[]);
int is_correct_guess(char guess[], char mystery[]);
int letter_in_word(char letter, char word[]);
void clear_input();

int main() {
	char mystery[WORD_LEN + 1];
	char guesses[MAX_GUESSES][WORD_LEN + 1];
	int guess_count = 0;
	int won = 0;
	
	read_word(mystery);
	
	while (guess_count < MAX_GUESSES && !won) {
		char guess[WORD_LEN + 2];
		
		get_guess(guess);
		to_lowercase(guess);
		
		int i;
		for (i = 0; i < WORD_LEN; i++) {
			guesses[guess_count][i] = guess[i];
		}
		guesses[guess_count][WORD_LEN] = '\0';
		
		display_feedback(guesses, guess_count + 1, mystery);
		
		if (is_correct_guess(guess, mystery)) {
			won = 1;
			break;
		}
		
		guess_count++;
	}
	
	if (won) {
		printf("Congratulations! You guessed the word.\n");
	} else {
		printf("Out of guesses! You lose!\n");
	}
	
	return 0;
}

void read_word(char word[]) {
	FILE *file = fopen("word.txt", "r");
	if (!file) {
		printf("Error: Could not open word.txt\n");
		word[0] = '\0';
		return;
	}
	
	int i = 0;
	while (i < WORD_LEN) {
	int ch = fgetc(file);
	if (ch == EOF || ch == '\n') break;
	word[i++] = (char) ch;
}
word[i] = '\0';

fclose(file);
}
void get_guess(char guess[]) {
	while (1) {
		printf("Enter your guess: ");
		fgets(guess, WORD_LEN + 2, stdin);
		
		int len = 0;
		while (guess[len] != '\n' && guess[len] != '\0') len++;
		if (guess[len] == '\n') {
		guess[len] = '\0';
		} else {
			clear_input();
		}
		
		if (is_valid_guess(guess)) {
			return;
		} else {
			printf("Invalid input. Please enter exactly 5 letters.\n");
		}
	}
}

int is_valid_guess(char guess[]) {
	int i;
	for (i = 0; guess[i] != '\0'; i++) {
		if(guess[i] < 'A' || (guess[i] > 'Z' && guess[i] < 'a') || guess[i] > 'z') {
		return 0;
		
	}
}
return i == WORD_LEN;
}

void to_lowercase(char word[]) {
	int i;
	for (i = 0; word[i] != '\0'; i++) {
	if (word[i] >= 'A' && word[i] <= 'Z') {
	word[i] = word[i] + ('a' - 'A');
	}
	}
}

void display_feedback(char guesses[][WORD_LEN + 1], int count, char mystery[]) {
	int g, i;
	for (g = 0; g < count; g++) {
		char line[WORD_LEN + 1];
		char pointers[WORD_LEN + 1];
		
		for(i = 0; i < WORD_LEN; i++) {
			if(guesses[g][i] == mystery[i]) {
			if (guesses[g][i] >= 'a' && guesses[g][i] <= 'z') {
				line[i] = guesses[g][i] - ('a' - 'A');
			} else {
				line[i] = guesses[g][i];
			}
			
			} else {
				line[i] = guesses[g][i];
			}
			pointers[i] = ' ';
		}
		line[WORD_LEN] = '\0';
		pointers[WORD_LEN] = '\0';
		for (i = 0; i < WORD_LEN; i++) {
			if (guesses[g][i] != mystery[i] &&
			letter_in_word(guesses[g][i], mystery)) {
			
			int j, already_used = 0;
			for (j = 0; j < WORD_LEN; j++) {
				if (guesses[g][j] == guesses[g][i] && mystery [j] == guesses[g][j]) {
					already_used = 1;
					break;
				}
			}
			
			if(!already_used) {
				pointers[i] = '^';
			}
		}
	}
	
	printf("%s\n", line);
	printf("%s\n", pointers);
}
}

int is_correct_guess(char guess[], char mystery[]) {
	int i; 
	for (i = 0; i < WORD_LEN; i++) {
		if (guess[i] != mystery [i]) return 0;
	}
	return 1;
}

int letter_in_word(char letter, char word[]) {
	int i;
	for (i = 0; i < WORD_LEN; i++) {
		if (letter == word[i]) return 1;
	}
	return 0;
}

void clear_input() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
