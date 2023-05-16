# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 15:39:56 by kchaouki          #+#    #+#              #
#    Updated: 2023/05/16 10:25:07 by rrhnizar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NAME_B = minishell_bonus

LIBFT = libft/libft.a

SRCS_M = minishell.c minishell_utils.c global_split.c global_split_utils.c

SRCS_B = minishell_bonus.c check_syntax.c

OBJS_M = $(SRCS_M:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

#-fsanitize=address

RDL = -lreadline

FLAGS = -Wall -Wextra -Werror -fsanitize=address

CCe = cc

DFINE = -D BONUS=100
DFINE2 = 0

ifeq ($(MAKECMDGOALS), bonus)
    override DFINE = -D BONUS=200
	override DFINE2 = 1
endif

# ifeq ($(DFINE2), 1)
# 	make fclean
# endif

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft && make clean -C libft

%.o : %.c
	$(CCe) $(FLAGS) $(DFINE) -c $< -o $@

$(NAME): $(OBJS_M) minishell.h
	$(CCe) $(FLAGS) $(RDL) $(OBJS_M) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(NAME_B)

$(NAME_B) : $(OBJS_B) minishell.h
	$(CCe) $(FLAGS) $(RDL) $(OBJS_B) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJS_M) $(OBJS_B)

fclean: clean 
	rm -rf $(NAME) $(NAME_B) $(LIBFT) && make clean -C libft

re : fclean all

.PHONY: all clean fclean re