NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE)


SRCS =  ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_substr.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_strjoin.c \
		ft_split.c \
		ft_itoa.c \
		ft_strtrim.c \
		ft_convert.c \
		ft_2convert.c \
		ft_printf.c \
		get_next_line.c \
		ft_malloc.c \
		ft_free.c \
		garbage.c \

BSRCS =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

INCLUDE = .

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${BSRCS:.c=.o}

rm = rm -f


%.o : %.c
	${CC} $(CFLAGS) -c $< -o $@

${NAME}: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

all: ${NAME}

bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	@rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean $(NAME)
.PHONY: all clean fclean re bonus