.PHONY: all clean fclean re bonus libft libbdlst create_dir debug_sh
.SILENT: libft libbdlst

NAME			= msh
LIBFT_NAME		= libft.a
LIBBDLST_NAME	= libbdlst.a


######################### CC && FLAGS ########################

CC		= gcc 	# clang
DEBUG	= -g 	# -fsanitize=address

CFLAGS	= -Wall -Wextra -Werror
ifdef (BONUS)
CFLAGS += -D BONUS=1
endif

TERMCAP 		= -ltermcap
LIBFT_FLAGS		= -L $(LFT_DIR) -lft
LIBBDLST_FLAGS	= -L $(LBDLST_DIR) -lbdlst
INCLUDE_FLAGS 	= -I $(INC_DIR) -I $(LFT_DIR) -I $(GNL_DIR) -I $(LBDLST_DIR)

######################### DIRECTORIES ########################

SRC_DIR		= src
OBJ_DIR		= obj
LFT_DIR		= libft
INC_DIR		= include
LBDLST_DIR	= libbdlst
GNL_DIR		= get_next_line

######################### SOURCES ############################

SOURCES			=	array_utils.c \
					clean.c \
					cmd_cd.c \
					cmd_clear.c \
					cmd_echo.c \
					cmd_env.c \
					cmd_exit.c \
					cmd_export.c \
					cmd_history.c \
					cmd_not_found.c \
					cmd_pwd.c \
					cmd_unset.c \
					cmd_usercmd.c \
					cmd_utils.c \
					cursor.c \
					dir_utils.c \
					dollar.c \
					env_copy.c \
					env_get.c \
					env_update.c \
					env_utils.c \
					error.c \
					execute.c \
					fds.c \
					history.c \
					init.c \
					key_actions.c \
					key_arrows.c \
					key_signals.c \
					key_utils.c \
					lexer.c \
					main.c \
					main_functions.c \
					parse_redirect.c \
					parser.c \
					parser_utils.c \
					pipes.c \
					pipes_utils.c \
					readline.c \
					redirects.c \
					shell_exit.c \
					shell_split.c \
					signal.c \
					term_utils.c \
					termcaps.c \
					tilda.c \

HEADER_FILES	=	msh.h \
					builtin.h \
					shell_keys.h \
					get_next_line.h \

GNL_SRC			=	get_next_line.c



######################## OBJECT FILES ########################

GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_SRC:.c=.o))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))


######################## HEADERS #############################

HEADERS = $(addprefix $(INC_DIR)/, $(HEADER_FILES))

######################## INSTRUCTIONS ########################

debug: all

all: libft libbdlst create_dir $(GNL_OBJ) $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

test: libft libbdlst
	gcc -g src/test.c $(LBDLST_DIR)/$(LIBBDLST_NAME) $(LFT_DIR)/$(LIBFT_NAME) $(INCLUDE_FLAGS)

libft:
	@$(MAKE) -C $(LFT_DIR) bonus

libbdlst:
	@$(MAKE) -C $(LBDLST_DIR)

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(CC) $(DEBUG) $(CFLAGS) -c $< $(INCLUDE_FLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) $(GNL_OBJ)
	@$(CC) $(DEBUG) $(CFLAGS) -c $< $(INCLUDE_FLAGS) $() -o $@

$(NAME): $(OBJECTS) $(GNL_OBJ) $(HEADERS)
	@$(CC) $(DEBUG) $(CFLAGS) $(GNL_OBJ) $(OBJECTS) $(LIBFT_FLAGS) $(LIBBDLST_FLAGS) $(TERMCAP) -o $@ 
	@echo "${NAME} created."

clean:
	@$(MAKE) clean -C $(LFT_DIR) --no-print-directory
	@$(MAKE) clean -C $(LBDLST_DIR) --no-print-directory 
	@rm -rf $(OBJ_DIR)/*.o

fclean: clean
	@$(MAKE) fclean -C $(LFT_DIR) --no-print-directory
	@$(MAKE) fclean -C $(LBDLST_DIR) --no-print-directory
	@rm -rf ${NAME}
	@echo "${NAME} has been deleted."


clean_bonus:
	@rm -rf $(OBJ_DIR)/*.o

bonus: clean_bonus
	@$(MAKE) BONUS=1 all --no-print-directory

run: all
	./msh

re: fclean all
