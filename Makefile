RM := rm -rf

NAME := minishell
LIBFTNAME := ./libft/libft.a

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

SRCS = bridge_to_builtins.c cd.c echo.c env.c error.c exit_atoi.c exit.c expander.c export.c find_cmd.c finish.c get_env.c heredocs.c input_parser.c input_parser_ft_split_w_quotes.c input_parser_utils.c main.c pipex_multipipe.c pipex_multipipe_interpreter.c print_prompt.c pwd.c simple_cmd_execution.c unset.c  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIBFTNAME):
	cd libft && $(MAKE) all

${NAME}: ${OBJS}
	@${MAKE} -C ./libft --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} $(LIBFTNAME) -o ${NAME} $(LDFLAGS) -lreadline