/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:09:19 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/08 09:12:21 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXECUTION_H
# define EXECUTION_H

char	*valid_command_path(char **paths, char *cmd);
char	**get_paths(char **env);


int		input_redirection(char *infile);
int		output_redirection(char *outfile);
int		append_output(char *outfile);

void	print_error(char *msg, char *arg, int status);


# endif