/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here
extern question questions[NUM_QUESTIONS];
// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
char* tokenize(char *input);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    // track current active player
    int curr_player = 0;
    // track question category and value
    char * category = malloc(MAX_LEN);
    int value;
    int curr_question;
    // track answer
    char * answer = malloc(MAX_LEN);
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    for (int i = 0; i < NUM_PLAYERS; i++){
        players[i].score = 0;
        
        printf("Please enter your name: \n");
        scanf("%s", (char *) &players[i].name);
    }
    // initialize each of the players in the array

    // Execute the game until all questions are answered
    while (!all_answered())
    {
        //clears screen
        system("clear");
        // Display all unanswered questions
        display_choices();

        //prompt player to choose question
        printf("Player %d: %s\n", curr_player + 1, players[curr_player].name);
        printf("please choose a category: \n");
        scanf("%s", category);
        printf("please choose a value: \n");
        scanf("%d", &value);

        //clears screen
        system("clear");

        //display question
        curr_question = display_question(category, value);

        //prompt player to give answer
        printf("Please enter you answer: \n");
        scanf("%s", answer);
        
        //check if answer is correct
        
        answer = tokenize(answer);

        if (strcmp(questions[curr_question].answer, answer)){
            printf("Correct");
            players[curr_player].score += value;
        } else {
            printf("Incorrect");
        }

        //cleanup
        questions[curr_question].answered = true;

        curr_player += 1;

        if (curr_player == NUM_PLAYERS){
            curr_player = 0;
        }
    }

    // Display the final results and exit
    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}

char* tokenize(char *input){

    char *str;
    char *answer;
    if ((str = strtok(input, " ")) != NULL){
        if (strcmp(str, "who") != 0 || strcmp(str, "what") != 0){
            return "";
        } 
    }
    if ((str = strtok(NULL, " ")) != NULL){
        if (strcmp(str, "is") != 0){
            return "";
        }
    }
    answer = strtok(NULL, "\n");
    return answer;
}

void show_results(player *players, int num_players){
    int name_length = 0;
    int score = 0;
    int winner = 0;

    for (int i = 0; i < num_players; i++){
        if ((int) strlen(players[i].name) > name_length){
            name_length = strlen(players[i].name);
        }

        if (players[i].score > score){
            score = players[i].score;
            winner = i;
        }
    }

    printf("Final Scores: \n");
    for (int i = 0; i < num_players; i++){
        printf("%*s: %d\n", name_length + 1, players[i].name, players[i].score);
    }

    printf("Winner is: %s", players[winner].name);
}
