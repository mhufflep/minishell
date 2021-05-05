.PHONY: all clean fclean re create_dir

NAME	= libbdlst.a
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror
INCLUDE = -I./
	
OBJ_DIR = obj

SRCS	= 	bidirectional_list.c\
			bd_utils.c\
			#bd_lstmap.c \
			#bd_lstnew.c \
			#bd_lstsize.c \
			#bd_lstiter.c \
			#bd_lstlast.c \
			#bd_lstclear.c \
			#bd_lstsort.c \
			#bd_lstcopy.c \
			#bd_lstdelone.c \
			#bd_lstadd_back.c \
			#bd_lstadd_front.c \
			#bd_lstmax_cont_len.c

OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: create_dir $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

$(NAME): $(OBJS)
	@ar rcs $@ $?
	@echo "${NAME} created."

create_dir:
	@mkdir -p ${OBJ_DIR}

clean: 
	@rm -rf ${OBJS}

fclean: clean
	@rm -rf ${NAME}

re: fclean all 

.PHONY: all clean fclean re