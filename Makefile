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

SRCS = main.c input_parser.c input_parser_utils.c input_parser_ft_split_w_quotes.c find_cmd.c heredocs.c pipex_multipipe.c pipex_multipipe_interpreter.c simple_cmd_execution.c expander.c finish.c error.c print_prompt.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIBFTNAME):
	cd libft && $(MAKE) all

${NAME}: ${OBJS}
	@${MAKE} -C ./libft --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} $(LIBFTNAME) -o ${NAME} $(LDFLAGS) -lreadline