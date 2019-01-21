CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADERS = fillit.h

SRCS = sources.c \
	   main.c \
	   fillit.c \
	   algo.c \
	   check_error.c \

NAME = fillit

all : $(NAME)

$(NAME) : $(OBJS)
		make -C libft/
		$(CC) $(CFLAGS) -o $(NAME) $(SRCS) -L. libft/libft.a

clean :
		cd libft && make clean

fclean : clean
		rm -f $(NAME)
		cd libft && make fclean

re : fclean all
