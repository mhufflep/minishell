.PHONY: all clean fclean re bonus libft create_dir
.SILENT: libft

NAME = minishell
LIBFT_NAME = libft.a

######################### CC && FLAGS ########################

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_FLAGS		= -L $(LFT_DIR) -lft
INCLUDE_FLAGS 	= -I $(INC_DIR) -I $(LFT_DIR) -I $(GNL_DIR)

######################### DIRECTORIES ########################

SRC_DIR = src
OBJ_DIR = obj
LFT_DIR = libft
INC_DIR = include
GNL_DIR = get_next_line

######################### SOURCES ############################

SOURCES = main.c

HEADER_FILES =	minishell.h \
				get_next_line.h

GNL_SRC =	get_next_line.c

######################## OBJECT FILES ########################

GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))


######################## HEADERS #############################

HEADERS = $(addprefix $(INC_DIR)/, $(HEADER_FILES))

######################## INSTRUCTIONS ########################

all: libft create_dir $(GNL_OBJ) $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

libft:
	@$(MAKE) -C $(LFT_DIR) bonus

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(GNL_OBJ)
	@$(CC) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(NAME): $(OBJECTS) $(GNL_OBJ) $(HEADERS) 
	@$(CC) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIBFT_FLAGS) -o $@ 
	@echo "${NAME} created"

clean:
	@$(MAKE) clean -C $(LFT_DIR) --no-print-directory 
	@rm -rf $(OBJ_DIR)/*.o

fclean: clean
	@$(MAKE) fclean -C $(LFT_DIR) --no-print-directory
	@rm -rf ${NAME}
	@echo "${NAME} has been deleted"


clean_bonus:
	@rm -rf $(OBJ_DIR)/*.o

bonus: clean_bonus
	@$(MAKE) BONUS=1 all --no-print-directory

re: fclean all
