
NAME	= minishell

# ---------------- CC ---------------- #

CC	= clang

ifeq ($(PARSING), yes)
	CFLAGS += -D DEBUG_PARSING
endif

ifeq ($(err), no)
	CFLAGS += -Wall
	CFLAGS += -Wextra
else
	CFLAGS += -Wall
	CFLAGS += -Wextra
	CFLAGS += -Werror
endif

ifeq ($(debug), 0)
	CFLAGS += -g3
else ifeq ($(debug), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
else ifeq ($(debug), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -ansi
	CFLAGS += -pedantic
else ifeq ($(debug), 3)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -ansi
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -ansi
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
	CFLAGS += -Weverything
endif

# ---------------- SRC --------------- #

# Parsing Sources
SRCS += parsing.c

SRCS += p_split_buf.c
SRCS += p_split_buf2.c
SRCS += p_split_buf_utils.c

SRCS += p_split_cmd.c
SRCS += p_split_cmd2.c
SRCS += p_split_cmd3.c
SRCS += p_split_cmd_utils.c

SRCS += p_lexer.c
SRCS += p_lexer_fsm.c
SRCS += p_lexer_fsm2.c

SRCS += p_clean_quotes.c
SRCS += p_clean_quotes2.c

SRCS += p_parsing_utils.c
SRCS += p_fill_cmdpath_argv.c

# Built in Sources
SRCS += built_in.c
SRCS += built_cd.c
SRCS += built_cd_utils.c
SRCS += built_echo.c
SRCS += built_pwd.c
SRCS += built_env.c
SRCS += built_export.c
SRCS += built_exit.c

# Main Sources
SRCS += main.c
SRCS += m_init.c
SRCS += m_del.c
SRCS += m_del2.c
SRCS += m_env_utils.c
SRCS += m_executable_utils.c
SRCS += m_error.c
SRCS += m_redirs.c
SRCS += m_traitement.c
SRCS += m_executable_cmd.c
SRCS += m_expansion.c
SRCS += m_expansion2.c
SRCS += m_expansion_utils.c

vpath %.c ./srcs/
vpath %.c ./srcs/parsing/
vpath %.c ./srcs/builtin/
vpath %.c ./srcs/execution/

# ---------------- INC --------------- #

INCLUDES 	=	./includes/
HEAD 		= $(INCLUDES)mshell.h $(INCLUDES)parsing.h
ALL_INC		=  -I$(INCLUDES) -I$(LIBFT_DIR)

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))

# ---------------- LIB --------------- #

LIBFT_DIR 	= ./libft/
LIBFT 		= $(LIBFT_DIR)libft.a
LIB_LINK	= -L$(LIBFT_DIR) -lft

# --------- Compilation Rules -------- #

all: $(NAME)

fast:
	$(MAKE) re -j8

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(ALL_INC) $(LIB_LINK) -o $@
# 			@echo "$(_BOLD)$(_YELLOW)==> $@ linked$(_END)"

$(OBJS): 	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@ $(ALL_INC)
# 			@echo "$(_BOLD)$(_GREEN)--> $@ made$(_END)"

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT): FORCE
# 	@echo "$(_BOLD)$(_GREEN)--> Creating $@...$(_END)"
	$(MAKE) -C $(LIBFT_DIR)
# 	@echo "$(_BOLD)$(_YELLOW)--> $@ made$(_END)"


FORCE:

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -R $(DIR_OBJS)
# 	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
# 	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

re: fclean
	$(MAKE)

.PHONY:		all exec clean fclean re bonus
# .SILENT:	$(OBJS) $(DIR_OBJS) $(NAME) $(LIBFT)
