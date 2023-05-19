#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** split_string(const char* input_string, int* length) {
    const char* split_chars = "|<>()*&";
    const char* current_word_start = input_string;
    int word_count = 0;
    int within_quotes = 0;

    // Count the number of words
    for (int i = 0; input_string[i] != '\0'; i++) {
        if (input_string[i] == '\'' || input_string[i] == '"') {
            within_quotes = !within_quotes;
        }
        else if (strchr(split_chars, input_string[i]) && !within_quotes) {
            word_count++;
        }
    }

    // Allocate memory for the array of strings
    char** result = (char**)malloc((word_count + 1) * sizeof(char*));

    int word_index = 0;

    // Split the string
    for (int i = 0; input_string[i] != '\0'; i++) {
        if (input_string[i] == '\'' || input_string[i] == '"') {
            within_quotes = !within_quotes;
        }
        else if (strchr(split_chars, input_string[i]) && !within_quotes) {
            int word_length = &input_string[i] - current_word_start;
            result[word_index] = (char*)malloc((word_length + 1) * sizeof(char));
            strncpy(result[word_index], current_word_start, word_length);
            result[word_index][word_length] = '\0';
            word_index++;
            current_word_start = &input_string[i] + 1;
        }
    }

    // Handle the last word
    int last_word_length = &input_string[strlen(input_string)] - current_word_start;
    if (last_word_length > 0) {
        result[word_index] = (char*)malloc((last_word_length + 1) * sizeof(char));
        strncpy(result[word_index], current_word_start, last_word_length);
        result[word_index][last_word_length] = '\0';
    }

    *length = word_count + 1;
    return result;
}

void free_split_string(char** split_result, int length) {
    for (int i = 0; i < length; i++) {
        free(split_result[i]);
    }
    free(split_result);
}

int main(int ac, char **av) {
	if (ac < 2)
		return (1);
    const char* input_string = av[1];
    int length;
    char** result = split_string(input_string, &length);

    printf("Split result:\n");
    for (int i = 0; i < length; i++) {
        printf("%s\n", result[i]);
    }

    free_split_string(result, length);

    return 0;
}