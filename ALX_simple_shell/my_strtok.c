/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:35:23 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/10 09:41:22 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, World! This is>an example.";
    char *token;

    // Tokenize the string using space (' ') as the delimiter
    token = strtok(str, " !>");

    // Loop through the tokens and print them
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " "); // Call strtok with NULL to continue tokenizing the same string
    }

    return 0;
}