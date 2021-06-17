.PHONY: all clean fclean re create_dir

NAME	= libft.a
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror
INCLUDE = -I./

OBJ_DIR = obj
SRC_DIR = src

SRCS	=	ft_atoi.c		ft_bzero.c		ft_isalnum.c \
			ft_isalpha.c	ft_isascii.c	ft_isdigit.c \
			ft_isprint.c	ft_memccpy.c	ft_memcpy.c \
			ft_memmove.c	ft_memset.c		ft_strchr.c \
			ft_strlcat.c	ft_strncmp.c	ft_strrchr.c \
			ft_tolower.c	ft_toupper.c	ft_memchr.c \
			ft_memcmp.c		ft_strlen.c		ft_strlcpy.c \
			ft_strnstr.c 	ft_calloc.c		ft_strdup.c \
			ft_putchar_fd.c	ft_itoa.c 		ft_substr.c \
			ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c \
			ft_strjoin.c	ft_strtrim.c 	ft_strmapi.c \
			ft_realloc_str.c ft_split.c		ft_strjoin_sep.c \
			ft_isspace.c	ft_isempty.c \

SRCS_B	= 	ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstclear.c \
			ft_lstcopy.c \
			ft_lstdelone.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstmax_cont_len.c

OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_B	= $(addprefix $(OBJ_DIR)/, $(SRCS_B:.c=.o))

all: create_dir $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

create_dir:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	@rm -rf $(NAME)
	
re: fclean all 

$(NAME): $(OBJS)
	@ar rcs $@ $?

bonus: all bonus_ar

bonus_ar: $(OBJS) $(OBJS_B)
	@ar rcs $(NAME) $?
	@echo 'bonus ${NAME} created.'

.PHONY: all clean fclean re bonus