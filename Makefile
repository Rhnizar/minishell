# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/05/03 16:31:48 by kchaouki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# NAME_B = minishell_bonus

LIBFT = libft/libft.a

SRCS = test.c expansion.c

# SRCS_B = 

OBJS = $(SRCS:.c=.o)

# OBJS_B = $(SRCS_B:.c=.o)

RDL = -lreadline

FLAGS = -Wall -Wextra -Werror

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