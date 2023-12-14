RM := rm -rf

NAME := minishell
FT_PRINTFNAME := ./ft_printf/libftprintf.a

LDFLAGS = -Lminilibx-linux -L ./libft -lmlx -lXext -lX11 -lm

.PHONY: all clean fclean re ft_printf

all: $(NAME)

clean:
	cd ft_printf && $(MAKE) clean
	$(RM) $(OBJS)

fclean: clean
	cd ft_printf && $(MAKE) fclean
	$(RM) $(NAME)

re: fclean all 

CC = cc
COMPILER_FLAGS = -Wall -Wextra -Werror -g 
HEADERS = -I .
COMPILE = $(CC) $(COMPILER_FLAGS) $(HEADERS) 

SRCS = minishell.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(FT_PRINTFNAME):
	cd ft_printf && $(MAKE) all

${NAME}: ${OBJS}
	@${MAKE} -C ./ft_printf --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} $(FT_PRINTFNAME) -o ${NAME} $(LDFLAGS)