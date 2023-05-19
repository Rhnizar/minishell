
NAME = minishell

SRCS = main.c test.c

SRCS_B = main.c test.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

DFINE = -D BONUS=100

FLAGS = -Wall -Wextra -Werror

CCe = cc

%.o : %.c
    ifeq ($(filter %.o,$@),)    # Check if the target does not end with ".o"
        $(CCe) $(FLAGS) $(DFINE) -c $< -o $@
    else
        $(CCe) $(FLAGS) -D bonus=0 $(DFINE) -c $< -o $@
    endif


%.o : %.c
	ifeq ($(filter bonus,$(MAKECMDGOALS)), bonus)
		$(CCe) $(FLAGS) -D BONUS=100 $(DFINE) -c $< -o $@
	else
		$(CCe) $(FLAGS) $(DFINE) -c $< -o $@
	endif

# %.o : %.c
# 	$(CCe) $(FLAGS) $(DFINE) -c $< -o $@

all : $(NAME)

bonus : $(OBJS_B)
	$(CCe) $(FLAGS) $(OBJS_B) -o $(NAME)
$(NAME) : $(OBJS) main.h
	$(CCe) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
re : fclean all