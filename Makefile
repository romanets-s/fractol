NAME = fractol
SRC = main.c init.c key_hook.c mouse_hook.c tree_fun.c fractals.c draw.c
SRCO = $(SRC:.c=.o)
INCLUDES = fractol.h
#FLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lmlx -framework OpenGL -framework AppKit -g
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SRCO)
	@make -C libft
	@gcc $(FLAGS) -o $(NAME) $(SRCO) $(LIBFT) $(LIBFLAGS)
	@echo "\033[32;1m<fractol>  | done"

.c.o:
	@gcc $(FLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@echo "\033[32;1m<libft>    | clean succes"
	@rm -f $(SRCO)
	@echo "\033[32;1m<fractol>  | clean succes"

fclean: clean
	@make fclean -C libft
	@echo "\033[32;1m<libft>    | fclean succes"
	@rm -f $(NAME)
	@echo "\033[32;1m<fractol>  | fclean succes"

re: fclean all
	@echo "\033[32;1m<fractol>  | re succes"
