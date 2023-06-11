#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// int isMatch(const char *str, const char *pattern) {
//     // Mark the position of the last asterisk character in the pattern
//     const char *last_s = NULL;
//     const char *last_p = NULL;

//     while (*str != '\0') {
//         if (*pattern == *str) {
//             // If the characters match, move to the next character in both strings
//             str++;
//             pattern++;
//         } else if (*pattern == '*') {
//             // If we encounter an asterisk, mark the current positions
//             // and move to the next character in the pattern
//             last_s = str;
//             last_p = pattern;
//             pattern++;
//         } else if (last_p != NULL) {
//             // If the characters don't match and we have encountered an asterisk,
//             // go back to the last marked positions
//             pattern = last_p + 1;
//             str = last_s + 1;
//             last_s++;
//         } else {
//             // If the characters don't match and there is no asterisk,
//             // the pattern doesn't match the string
//             return false;
//         }
//     }

//     // Skip any remaining asterisks in the pattern
//     while (*pattern == '*') {
//         pattern++;
//     }

//     // If we have reached the end of both the string and pattern,
//     // the pattern matches the string
//     return *pattern == '\0';
// }

int is_match(const char *str, const char *pattern)
{
    int	last_s;
    int last_p;
    int str_i;
    int pattern_i;

	last_p = -1;
	last_s = -1;
    str_i = 0;
    pattern_i = 0;
    while (str[str_i] != '\0') {
        if (pattern[pattern_i] == str[str_i])
		{
            str_i++;
            pattern_i++;
        }
		else if (pattern[pattern_i] == '*')
		{
            // If we encounter an asterisk, mark the current positions
            // and move to the next character in the pattern
            last_s = str_i;
            last_p = pattern_i;
            pattern_i++;
        }
		else if (last_p != -1)
		{
            // If the characters don't match and we have encountered an asterisk,
            // go back to the last marked positions
            pattern_i = last_p + 1;
            str_i = last_s + 1;
            last_s++;
        }
		else 
            return (0);
    }
    while (pattern[pattern_i] == '*')
        pattern_i++;
    return (pattern[pattern_i] == '\0');
}

// int	skip_asterisk(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] == '*')
// 		i++;
// 	return (i);
// }
// int	is_match(char *str, char *pattern)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == pattern[j])
// 		{
// 			i++;
// 			j++;
// 		}
// 		else if (pattern[j] == '*')
// 			j += skip_asterisk(&pattern[j]);
// 		else if (last_j != (int)strlen(pattern))
// 		{
// 			j = last_j + 1;
// 			i = last_i + 1;
// 			last_i++; 
// 		}
// 		else
// 			return (0);
// 	}
// 	return (pattern[i] == '\0');
// }


int main() {
    char *str = "hello world";
    char *pattern = "he*d";
    int match = isMatch(str, pattern);

    if (match) {
        printf("Pattern matches the string.\n");
    } else {
        printf("Pattern does not match the string.\n");
    }

    return 0;
}