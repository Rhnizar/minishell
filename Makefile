# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/05/16 22:35:45 by kchaouki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# NAME_B = minishell_bonus

LIBFT = libft/libft.a

# EXECUTION = execution/print_error.c execution/expansion.c
# PARSING = parsing/environment.c parsing/expansion.c 
PARSING = ft_free.c parsing/quotes_handler.c parsing/error_checker.c parsing/parsing_utils.c execution/print_error.c

SRCS = minishell.c $(PARSING)

# SRCS_B = 

OBJS = $(SRCS:.c=.o)

# OBJS_B = $(SRCS_B:.c=.o)

RDL = -lreadline

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

# bonus: $(LIBFT) $(NAME_B)

# $(NAME_B) : $(OBJS_B)
# 	$(CCe) $(FLAGS) $(OBJS_B) $(LIBFT) -o $(NAME_B)

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B) $(LIBFT)

re : fclean all

.PHONY: all clean fclean re