NAME = fillit

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS = inc/fillit.h

SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = libft/libft.a

SOURCES = sources.c \
	   main.c \
	   fillit.c \
	   algo.c \
	   check_error.c \

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
		@make -C libft/
		@$(CC) $(OBJS) $(LIB_PATH) -o $(NAME)
		@echo "Compilation $(NAME) OK"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
		@make clean -C libft
		@rm -rf $(OBJ_PATH)

fclean : clean
		@rm -rf $(NAME)
		@rm -rf $(LIB_PATH)

re : fclean all
