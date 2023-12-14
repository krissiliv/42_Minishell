RM := rm -rf

NAME := libftprintf.a
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
COMPILER_FLAGS = -Wall -Wextra -Werror
HEADERS = -I .
COMPILE = $(CC) $(COMPILER_FLAGS) $(HEADERS)

SRCS = ft_printf.c ft_printf_d_int.c ft_printf_ptradr.c ft_printf_unsdec.c ft_printf_char.c ft_printf_hexlu.c ft_printf_string.c ft_putnbr_base.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIBFTNAME):
	cd libft && $(MAKE) all

$(NAME): $(LIBFTNAME) $(OBJS)
	cp $(LIBFTNAME) $(NAME)
	ar rcs $@ $(OBJS)