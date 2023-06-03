/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:09:19 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/03 23:16:52 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXECUTION_H
# define EXECUTION_H

#include "../minishell.h"

char	*valid_command_path(char **paths, char *cmd);
char	**get_paths(t_env *env);

int		input_redirection(char *infile);
int		output_redirection(char *outfile);
int		append_output(char *outfile);
void	here_doc(char *delimiter);

void	print_error(char *msg, char *arg, int status);


/*========= start expender =============*/
char		*remove_quotes(char *str);
t_tokens	*expantion_tokenizer(char *token);
char		*get_value(char *to_expand, t_env *env);
char		*expantion_quote_case(t_tokens **tmp, t_env *env, char *old, int exit_status);
char		*expantion_dollar_case(t_tokens **tmp, t_env *env, char *old, int exit_status);
char		**split_expended(char *token);

t_redis		*redis_expander(t_redis *redis, t_env *env, int exit_status);
/*========= end expender =============*/


# endif