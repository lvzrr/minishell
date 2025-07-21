NAME        := minishell
SRCDIR      := src
BUILDDIR    := build

rwildcard   = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRC         := $(call rwildcard,$(SRCDIR)/,*.c)

OBJ         := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRC))

CC          := clang
CFLAGS      := -Wall -Wextra -Werror -I./include -I./libft/include
LDFLAGS     := libft/libft.a -lreadline -lhistory

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft libft.a
	$(CC) $(OBJ) $(LDFLAGS) -o $@ -g3

clean:
	$(MAKE) -C libft clean
	rm -rf $(BUILDDIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)
.PHONY: all re fclean
