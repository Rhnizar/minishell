# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/05/22 21:26:32 by kchaouki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME_B = minishell_bonus

LIBFT = libft/libft.a

# parsing/quotes_handler.c
# execution/print_error.c

EXECUTION = execution/print_error.c

ANALYSER_M =  parsing/analyser_mandatory/here_doc_error_case.c \
			  parsing/analyser_mandatory/syntax_error_m.c \
			  parsing/analyser_mandatory/check_separators.c  

ANALYSER_B =  parsing/analyser/here_doc_error_case.c \
			  parsing/analyser/syntax_error.c \
			  parsing/analyser/check_separators.c

SHARED_PARSING = parsing/create_tokens.c \
		 		 parsing/global_split_utils.c \
		 		 parsing/global_split.c

SHARED = minishell.c \
	   	 

PARSING_M = $(SHARED_PARSING) $(ANALYSER_M)

PARSING_B = $(SHARED_PARSING) $(ANALYSER_B)


# SRCS = minishell_mandatory.c
SRCS = minishell.c \
	   minishell_utils.c \
	   $(PARSING_M) $(EXECUTION)

SRCS_B = minishell.c \
		 minishell_utils.c \
		 $(PARSING_B) $(EXECUTION)

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