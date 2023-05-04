/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_owntest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:31:26 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/04 15:36:39 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct treenode {
	int value;
	struct treenode *left;
	struct treenode *right;
} treenode;

treenode *create_node(int value)
{
	treenode *result = malloc(sizeof(treenode));
	if (result)
		return (NULL);
	result->left = NULL;
	result->right = NULL;
	result->value = value;
	return (result);
}



int main()
{
	treenode *n1 = create_node(1);
	treenode *n2 = create_node(2);
	treenode *n3 = create_node(3);
	treenode *n4 = create_node(4);
	treenode *n5 = create_node(5);
}