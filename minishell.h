/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/26 13:00:35 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing/parsing.h"

# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:\
/usr/local/munki"
# define ENSFD ": No such file or directory\n"
# define ECNF ": command not found\n"
# define EPD ": Permission denied\n"
# define ESYNTX "minishell: syntax error near unexpected token `"
# define EAMBGRD ": ambiguous redirect"

typedef enum e_redirtypes
{
	FILE_APPEND,
	HEREDOC,
	FILE_IN,
	FILE_OUT,
	OR,
	AND,
	PIPE
}	t_rtype;

typedef struct s_global
{
	int			exit_status;
	int			pipe[2];
	t_env		*env;
	t_cmdshell	*all_commands;
}			t_global;

///////////////// end struct ///////////
int		len_first_split(char *str);
int		char_in_string(char c, char *ref);
char	*join_to_str(char *str, char c);
char	**my_split(char *str);

void	free_double_ptr(char **str);

//		tokens funtions
void	create_tokens(t_tokens **lst, char *str);
void	free_tokens(t_tokens *tokens);
int		count_tokens(t_tokens *tokens);


int		check_syntax(char *str, char *ref);
char	**fill_with_null(int len);
int		count_quote(char *str, int r);
char	**split_quote(char *str, int r);

////// utils global split ///////
int		find_separator(char **sep, char *str);
int		str_in_string(char *str);
// void		init_check(t_check	*check, char *read_line);
int		init_check(t_check	*check, char *read_line);
// t_tokens	*split_and_fill_list(char *output);
int		split_and_fill_list(char *output, t_tokens **tokens);
void	dq_sq(t_check *check, int *i, int *dq_or_sq);
void	check_quote(t_check *check, int *i);
void	check_space_tab(t_check *check, int *i);

///////// utils fill struct commands /////
// int			check_quote_cmd(char *str);
// int			check_sep_or_red(char *str, char **str_to_check);
// void		init_cmd(t_cmds **cmds, t_tokens *tokens);
// t_cmdshell	*fill_list_cmds(t_cmdshell *lst, t_tokens *token);
// int			check_subshell(char *str);

////////////////////  next  idea the define ////////
int		init_global(t_global *glob);
int		init_struct_cmds(t_cmds **cmds);
int		init_struct_utils(t_utils **utils);

///////////////// shared utils define /////////////

void	check_node1(t_cmds **cmd, t_tokens *tmp, t_utils *utils);
void	fill_list_redis(t_redis **lst, char *str, int type);
void	fill_list_args(t_args **lst, char *str);
void	free_redis(t_redis *redis);
void	free_args(t_args *args);
void	add_cmd_to_list(t_cmdshell **lst, t_cmds *cmds);

////////////// in file define bonus //////////////
void		check_define(t_cmds *cmds, t_tokens *tokens, t_utils *utils);
t_tokens	*fill_struct_cmds(t_cmds *cmds, t_tokens *tokens, t_utils *utils);

/////////// environment //////////////
t_env		*create_env(char **envp);






void		print_error(char *msg, char *arg, int status);

// analyzer aka "syntax error check"

t_tokens		*analyzer(t_tokens *tokens, int	*exit_status);
t_syntax_check	fill_syntax_check(t_tokens *all_tokens, t_tokens *token);
int				syntax_error_handler(t_tokens *tokens);
int				is_separator(char *token, char **sep);
void			syntx_error(char *arg);
void			here_doc_befor_error(t_tokens *tokens, int index);
int				check_separators(t_syntax_check	check, int *par, int *i_par);
int				check_redirections(t_syntax_check check);
int				check_operators(t_syntax_check check);
int				is_builtin(char *token);
int				is_quote(char c);
char			*quotes_handler(char *token);
char			*handle_subshell(t_tokens **tmp);
char			*join_with_space(char *old, char *arg);


int	fill_global_struct(t_global **global, char *line, char **environment);

# endif