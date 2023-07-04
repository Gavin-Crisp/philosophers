NAME = philo

SDIR = srcs
HDIR = headers
ODIR = objs

SRCS = $(shell find $(SDIR) -name "*.c" -type f)
OBJS = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRCS))

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compling $@ from objects..."
	@cc $(CFLAGS) -lpthread -o $@ $^
	@echo "Done!"

$(ODIR)/%.o: $(SDIR)/%.c
	@echo "Compiling $< to object..."
	@mkdir -p $(@D)
	@cc $(CFLAGS) -I$(HDIR) -o $@ -c $<

clean:
	@echo "Cleaning $(NAME)..."
	@rm -rfv $(ODIR)
	@echo "Done!"

fclean:
	@echo "Fully cleaning $(NAME)..."
	@rm -rfv $(ODIR) $(NAME)
	@echo "Done!"

re: fclean all
