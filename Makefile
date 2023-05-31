# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/05/31 20:17:21 by kchaouki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAME_B = minishell_bonus

LIBFT = libft/libft.a

PARSING = parsing/parser.c \
		  parsing/analyzer/syntax_error.c \
		  parsing/analyzer/here_doc_error_case.c \
		  parsing/analyzer/check_separators.c \
		  parsing/quotes_handler.c \
		  parsing/create_tokens.c \
		  parsing/global_split_utils.c \
		  parsing/global_split.c \
		  parsing/init_cmds.c \
		  parsing/parsing_utils.c \
		  parsing/shared_utils_define.c \
		  parsing/shared_utils_define2.c \
	 	  parsing/environment.c \
		  parsing/expention/expantion_utils.c \
		  parsing/expention/args_expantion.c \
		  parsing/print_error.c
# parsing/expention/redis_expantion.c


SRCS_M = minishell.c $(PARSING) \
		 parsing/define_mandatory.c \
		 parsing/synt_error_mandatory.c

SRCS_B = minishell.c $(PARSING) \
		 parsing/define_bonus.c \
		 parsing/synt_error_bonus.c \
		 parsing/analyzer/analyzer_bonus.c

OBJS_M = $(SRCS_M:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

#-fsanitize=address

RDL = -lreadline \
	  -L/goinfre/kchaouki/brew/opt/readline/lib \
  	  -I/goinfre/kchaouki/brew/opt/readline/include
# -L/goinfre/rrhnizar/brew/opt/readline/lib
# -I/goinfre/rrhnizar/brew/opt/readline/include

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

CCe = cc

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft && make clean -C libft
%.o : %.c
	$(CCe) $(FLAGS) $(DFINE) -c $< -o $@

$(NAME): $(OBJS_M) minishell.h
	$(CCe) $(FLAGS) $(OBJS_M) $(RDL) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(NAME_B)

$(NAME_B) : $(OBJS_B) minishell.h
	$(CCe) $(FLAGS) $(OBJS_B) $(RDL) $(LIBFT) -o $(NAME_B)

clean:
	rm -rf $(OBJS_M) $(OBJS_B)

fclean: clean 
	rm -rf $(NAME) $(NAME_B) $(LIBFT) && make clean -C libft

re : fclean all

.PHONY: all clean fclean re
