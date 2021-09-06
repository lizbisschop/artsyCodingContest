NAME = brainz

SRCS = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c main.c

FLAGS = -Wall -Werror -Wextra

OBJ = $(SRCS:.c=.o)

INCL = -I ./gnl/get_next_line.h

ifdef DEBUG
FLAGS += -fsanitize=address -fno-omit-frame-pointer -g
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $^ $(INCL) libft.a -lm -o $(NAME) -g

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
