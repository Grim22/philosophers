
NAME	= philo_one

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

SRCS += main.c
SRCS += m_init.c
SRCS += m_init_threads.c
SRCS += m_options.c
SRCS += m_end.c
SRCS += m_utils.c

SRCS += thread_philo.c
SRCS += thread_philo_forks.c
SRCS += thread_philo_status.c
SRCS += thread_philo_stop.c
SRCS += thread_death.c

#libft functions
SRCS += ft_strlen.c
SRCS += ft_atoi.c
SRCS += ft_putstr.c
SRCS += ft_itoa.c
SRCS += ft_isdigit.c
SRCS += ft_strjoin_back.c

# vpath %.c ./srcs/

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))

# --------- Compilation Rules -------- #

all: $(NAME)

fast:
	$(MAKE) re -j8

$(NAME):	$(OBJS)
			$(CC) -pthread $(CFLAGS) $(OBJS) -o $@
# 			@echo "$(_BOLD)$(_YELLOW)==> $@ linked$(_END)"

$(OBJS): 	$(DIR_OBJS)%.o: %.c| $(DIR_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@
# 			@echo "$(_BOLD)$(_GREEN)--> $@ made$(_END)"

$(DIR_OBJS):
	mkdir -p $@

clean:
	rm -rf $(DIR_OBJS)
# 	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

fclean: clean
	$(RM) $(NAME)
# 	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

re: fclean
	$(MAKE)

.PHONY:		all clean fclean re
# .SILENT:	$(OBJS) $(DIR_OBJS) $(NAME) $(LIBFT)
