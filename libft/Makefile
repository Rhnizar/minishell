# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 18:50:25 by rrhnizar          #+#    #+#              #
#    Updated: 2022/10/17 13:29:38 by rrhnizar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra -I.

CC = gcc $(FLAGS)

SRCS =	ft_bzero.c \
		ft_atoi.c \
		ft_strlen.c \
       	ft_memchr.c \
       	ft_strlcpy.c \
       	ft_isprint.c \
	   	ft_strlcat.c \
	   	ft_isdigit.c \
	   	ft_isalnum.c \
	   	ft_isascii.c \
		ft_isalpha.c \
	   	ft_memcpy.c \
	   	ft_memmove.c \
	   	ft_memset.c \
	   	ft_strchr.c \
	   	ft_strncmp.c \
	   	ft_strrchr.c \
	   	ft_tolower.c \
	   	ft_toupper.c \
		ft_memcmp.c \
		ft_strdup.c \
		ft_calloc.c \
	   	ft_strnstr.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_strmapi.c \
		ft_itoa.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

BSRCS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(BSRCS:.c=.o)

$(NAME) : $(OBJS)
		$(CC) -c $(SRCS)
		ar crs $(NAME) $(OBJS)

all : $(NAME)

bonus : all $(BOBJS)
	 	$(CC) -c $(BSRCS)
		ar crs $(NAME) $(OBJS) $(BOBJS)

print_msg :
	@echo "deleted ..."

clean: print_msg
		@rm -f *.o

fclean: clean
		@rm -f $(NAME)

re : fclean all