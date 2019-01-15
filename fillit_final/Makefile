CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADERS = fillit.h

SRCS = main.c \
	   fillit.c \
	   algo.c \
	   check_error.c \
	   aff_tetro.c

OBJS = 	$(SRCS:.c=.o)

NAME = fillit

all : $(NAME)

$(NAME) : $(OBJS)
		make -C libft/
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L. libft/libft.a

clean :
		rm *.o
		rm libft/*.o

fclean : clean
		rm -f $(NAME)
		rm -f libft/libft.a

re : fclean all
