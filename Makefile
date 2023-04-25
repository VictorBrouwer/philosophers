NAME		:=	philo

OBJ_DIR		:=	./obj
SRC_DIR 	:=	./src
INC_DIR		:=	./include

CFLAGS	= -Wextra -Wall -Werror

ifdef DEBUG
CFLAGS +=-fsanitize=thread
endif

INCLUDE		:= $(addprefix -I,$(INC_DIR))

SRCS		:= 		main.c \
					multithread.c \
					error_handling.c \
					tasks.c \
					death.c \
					time.c \
					sleep.c \
					eat.c \

OBJS		:= 		$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
DEP			:=		$(OBJS:%.o=%.d)

#===============================================#
#=================== RECIPES ===================#
#===============================================#
-include $(DEP)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: clean all

debug:
	$(MAKE) DEBUG=1

rebug: fclean
	$(MAKE) debug

.PHONY: all, clean, fclean, re
