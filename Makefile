# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/05/20 10:09:22 by kchaouki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_B = minishell_bonus

LIBFT = libft/libft.a

# parsing/quotes_handler.c
# execution/print_error.c

ANALYSER =  parsing/analyser/here_doc_error_case.c \
			parsing/analyser/syntax_error.c
		  

PARSING = parsing/create_tokens.c \
		  parsing/global_split_utils.c \
		  parsing/global_split.c \
		  $(ANALYSER)

SRCS = minishell.c \
	   minishell_utils.c \
	   execution/print_error.c \
	   $(PARSING) 

# SRCS_B =

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

RDL = -lreadline \
	  -L/goinfre/kchaouki/brew/opt/readline/lib \
	  -I/goinfre/kchaouki/brew/opt/readline/include

#-fsanitize=address
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
CCe = cc

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft && make clean -C libft 

%.o : %.c
	$(CCe) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) minishell.h
	$(CCe) $(FLAGS) $(RDL) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME_B): $(OBJS_B) minishell.h
	$(CCe) $(FLAGS) $(RDL) $(OBJS_B) $(LIBFT) -o $(NAME_B)

bonus: $(LIBFT) $(NAME_B)

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B) $(LIBFT)

re : fclean all

.PHONY: all clean fclean re