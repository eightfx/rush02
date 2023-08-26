CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = rush-02
SRC = *.c
OBJ = $(SRC:%.c=%.out)



all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS)  $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)
