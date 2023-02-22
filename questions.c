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
#include "questions.h"
#include <sys/types.h>

// Initializes the array of questions for the game

question questions[NUM_QUESTIONS];

void initialize_game(void)
{
    FILE *file = fopen("question_list.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    for (int i = 0; i < NUM_QUESTIONS; i++){
        strncpy(questions[i].category, categories[i%3], sizeof(questions[i].category));
        questions[i].answered = false;
        questions[i].value = i%3 * 100 + 100;
        read = getline(&line, &len, file);
        strncpy(questions[i].question, line, sizeof(questions[i].question));
        read = getline(&line, &len, file);
        strncpy(questions[i].answer, line, sizeof(questions[i].answer));
    }
    // initialize each question struct and assign it to the questions array
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_choices(void)
{
    for(int i = 0; i < NUM_CATEGORIES; i++){
        printf("%s", categories[i]);
        for (int i = 0; i < NUM_QUESTIONS; i++){
            if (!questions[i].answered && strcmp(questions[i].category, categories[i])){
                printf("%d\n", questions[i].value);
            }
        }
    }
    printf("\n");
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
int display_question(char *category, int value)
{
    int num = 0;
    for (int i = 0; i < NUM_QUESTIONS; i++){
        if (strcmp(category, questions[i].category) && (value == questions[i].value)){
            printf("%s", questions[i].question);
            num = i;
        }
    }
    return num;
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; i++){
        if (strcmp(category, questions[i].category) && (value == questions[i].value) && (strcmp(answer, questions[i].answer))){
            return true;
        }
    }
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    for (int i = 0; i < NUM_QUESTIONS; i++){
        if (strcmp(category, questions[i].category) && (value == questions[i].value) && (questions[i].answered)){
            return true;
        }
    }
    // lookup the question and see if it's already been marked as answered
    return false;
}

bool all_answered(){
    for (int i = 0; i < NUM_QUESTIONS; i++){
        if (!questions[i].answered){
            return false;
        }
    }
    return true;
}
