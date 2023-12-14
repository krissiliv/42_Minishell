RM := rm -rf

NAME := minishell
LIBFTNAME := ./libft/libft.a

LDFLAGS = -Lminilibx-linux -L ./libft -lmlx -lXext -lX11 -lm

.PHONY: all clean fclean re libft

all: $(NAME)

clean:
	cd libft && $(MAKE) clean
	$(RM) $(OBJS)

fclean: clean
	cd libft && $(MAKE) fclean
	$(RM) $(NAME)

re: fclean all 

CC = cc
COMPILER_FLAGS = -Wall -Wextra -Werror -g 
HEADERS = -I .
COMPILE = $(CC) $(COMPILER_FLAGS) $(HEADERS) 

SRCS = minishell.c minishell_utils.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIBFTNAME):
	cd libft && $(MAKE) all

${NAME}: ${OBJS}
	@${MAKE} -C ./libft --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} $(LIBFTNAME) -o ${NAME} $(LDFLAGS)