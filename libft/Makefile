RM := rm -rf

NAME := libft.a

.PHONY: all clean fclean re

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

CC = cc
COMPILER_FLAGS = -Wall -Wextra -Werror
HEADERS = -I .
COMPILE = $(CC) $(COMPILER_FLAGS) $(HEADERS)

SRCS = addit_wordcount.c addit_search_and_replace.c addit_useful.c addit_createlinkedlist.c addit_list_remove_if.c ft_strcmp.c ft_print_program_name.c ft_memcmp.c ft_strlcat.c ft_memcpy.c ft_strlcpy.c ft_memmove.c ft_strlen.c ft_atoi.c ft_memset.c ft_strmapi.c ft_bzero.c ft_putchar_fd.c ft_strncmp.c ft_calloc.c ft_putendl_fd.c ft_strnstr.c ft_isalnum.c ft_putnbr_fd.c ft_strrchr.c ft_isalpha.c ft_putstr_fd.c ft_strtrim.c ft_isascii.c ft_split.c ft_substr.c ft_isdigit.c ft_strchr.c ft_tolower.c ft_isprint.c ft_strdup.c ft_toupper.c ft_itoa.c ft_striteri.c ft_memchr.c ft_strjoin.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

