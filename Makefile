CC     = g++
CFLAGS = -Wall -Wextra -Werror -g -Os -I include -lboost_system -lboost_thread

NAME = lab7
SRC  = chip utils
SRCS = $(addsuffix .cpp, $(SRC))
OBJS = $(addsuffix .o,   $(SRC))
SRCS_PREFIXED = $(addprefix src/, $(SRCS))

SRC_PATH      = src/
OBJS_DIR      = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_PREFIXED): $(SRCS_PREFIXED)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SRCS_PREFIXED)
	mv *.o $(OBJS_DIR)

all: $(OBJS_PREFIXED)
	$(CC) $(CFLAGS) main.cpp $(OBJS_PREFIXED) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all