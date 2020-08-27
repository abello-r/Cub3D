LIB_SRCS	= ft_memset.c ft_bzero.c ft_calloc.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_split.c
LIB_SRCS_B  = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
LIB_OBJS	= ${LIB_SRCS:.c=.o}
LIB_OBJS_B	= ${LIB_SRCS_B:.c=.o}
LIB_NAME	= libft.a
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
.c.o:
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}
${LIB_NAME}:	${LIB_OBJS}
			ar rc  ${LIB_NAME} ${LIB_OBJS}
			ranlib ${LIB_NAME}
bonus:		${LIB_OBJS} ${LIB_OBJS_B}
			ar rc ${LIB_NAME} ${LIB_OBJS} ${LIB_OBJS_B}
			ranlib ${LIB_NAME}
all:		${LIB_NAME}
clean:
			${RM} ${LIB_OBJS} ${LIB_OBJS_B}
fclean:		clean
			${RM} ${LIB_NAME}
re:			fclean bonus
.PHONY: bonus all clean fclean re
