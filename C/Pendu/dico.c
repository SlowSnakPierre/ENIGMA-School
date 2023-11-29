#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Structure to hold the dictionary
 * words: number of words in the dictionary
 * wordList: array of words
 */
typedef struct Dictionary {
    // Number of words in the dictionary
    unsigned int words;
    // Array of words
    char** wordList;
} Dictionary;

/*
 * Create a new dictionary
 * size: number of words in the dictionary
 */
Dictionary* newDictionary(unsigned int size) {
    // Allocate memory for the dictionary
    Dictionary* dict = malloc(sizeof(Dictionary));
    // Set the number of words in the dictionary
    dict->words = size;
    // Allocate memory for the array of words
    dict->wordList = malloc(size * sizeof(char *));

    // Return the dictionary
    return dict;
}

/*
 * Free the dictionary
 * dict: dictionary to free
 */
void freeDictionary(Dictionary* dict) {
    // Free each word in the dictionary
    unsigned int i;
    // Loop through each word in the dictionary
    for (i = 0; i < dict->words; i++)
        // Free the word
        free(dict->wordList[i]);

    // Free the array of words
    free(dict->wordList);

    // Free the dictionary
    free(dict);
}

/*
 * Read a file and return its contents
 * filePath: path to the file
 */
char* readRaw(const char* filePath) {
    // Open the file
    FILE* input = fopen(filePath, "rb");
    // Allocate memory for the file contents
    char* fileContents = NULL;

    // If the file exists
    if (input) {
        // Get the length of the file
        fseek(input, 0, SEEK_END);
        // Get the length of the file
        int fileLength = ftell(input);
        // Reset the file pointer
        fseek(input, 0, SEEK_SET);

        // Allocate memory for the file contents
        fileContents = calloc(fileLength + 1, sizeof(char));
        // Read the file contents into the allocated memory
        fread(fileContents, sizeof(char), fileLength, input);

        // Close the file
        fclose(input);
    }

    return fileContents;
}

/*
 * Split a string into words
 * str: string to split
 */
Dictionary* splitWords(char* str) {
    // Count the number of words in the string
    unsigned int numberOfWords = 1;
    // Loop through each character in the string
    char* tmp;

    // Loop through each character in the string
    for (tmp = str; *tmp; tmp++)
        // If the character is a space or a newline
        if (*tmp == '\n')
            // Increment the number of words
            numberOfWords++;

    // Create a new dictionary
    Dictionary* dict = newDictionary(numberOfWords);
    // Make a mutable copy of the string
    char* mutable = str;
    // Loop through each word in the string
    unsigned int currentWord = 0;
    // Loop through each word in the string
    char* token;

    // Loop through each word in the string
    for (token = strtok(mutable, " \n\r"); token; token = strtok(NULL, " \n\r")) {
        // Allocate memory for the word
        dict->wordList[currentWord] = calloc(1, strlen(token) + 1);
        // Copy the word into the allocated memory
        strcpy(dict->wordList[currentWord], token);
        // Increment the current word
        currentWord++;
    }

    // Free the string
    free(str);

    // Return the dictionary
    return dict;
}

/*
 * Get a random word from a dictionary
 * dict: dictionary to get the word from
 */
char* dictionaryRandomWord(Dictionary* dict) {
    // Seed the random number generator
    srand(time(NULL));
    // Get a random number between 0 and the number of words in the dictionary
    unsigned int word = rand() % dict->words;

    // Allocate memory for the word
    char* chosenWord = calloc(1, strlen(dict->wordList[word]) + 1);
    // Copy the word into the allocated memory
    strcpy(chosenWord, dict->wordList[word]);

    // Free the dictionary
    freeDictionary(dict);

    // Return the word
    return chosenWord;
}

/*
 * Get a random word from a file
 * filePath: path to the file
 */
char* getRandomWord() {
    // Split the words in the file into a dictionary
    return dictionaryRandomWord(splitWords(readRaw("../wordList.txt")));
}