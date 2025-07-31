NAME        := minishell
SRCDIR      := src
BUILDDIR    := build
SRC         := src/core/signals.c\
			src/core/signals2.c\
			src/core/prompt.c\
			src/core/heredoc.c\
			src/core/core_aux.c\
			src/core/parse_and_run.c\
			src/core/core_loop.c\
			src/core/token_vec_helpers.c\
			src/core/token_vec_helpers_2.c\
			src/parser/parser.c\
			src/parser/ast.c\
			src/parser/ast_helpers.c\
			src/parser/ast_print.c\
			src/parser/ast_free.c\
			src/preprocessor/redir_collapse_helpers.c\
			src/preprocessor/varexp_helpers.c\
			src/preprocessor/catch_forbidden.c\
			src/preprocessor/expand_helpers.c\
			src/preprocessor/redir_checker.c\
			src/preprocessor/errors.c\
			src/preprocessor/export.c\
			src/preprocessor/isstringtoken.c\
			src/preprocessor/unset.c\
			src/preprocessor/pre_process.c\
			src/preprocessor/wilcard.c\
			src/preprocessor/sanitize_input.c\
			src/preprocessor/collapser.c\
			src/preprocessor/recognition.c\
			src/preprocessor/expand_vars.c\
			src/preprocessor/resolve_path.c\
			src/preprocessor/redir_collapse.c\
			src/env/var_loader.c\
			src/env/clear.c\
			src/env/print.c\
			src/env/hot_vars.c\
			src/env/env2envp.c\
			src/env/load.c\
			src/env/helpers.c\
			src/utils/main_utils.c\
			src/utils/help.c\
			src/main.c\
			src/lexer/eaters.c\
			src/lexer/tok_infer.c\
			src/lexer/try_lexas.c\
			src/lexer/display.c\
			src/lexer/lex.c\
			src/lexer/sequences.c\
			src/lexer/sanitize.c\
			src/runner/encoded_redirs.c\
			src/runner/pipes.c\
			src/runner/run.c\
			src/runner/make_redirs.c\
			src/runner/run_helpers.c\
			src/builtins/env/env.c\
			src/builtins/exit/exit.c\
			src/builtins/cd/cd.c\
			src/builtins/echo/builtin_echo_helpers.c\
			src/builtins/echo/builtin_echo.c\
			src/builtins/pwd/pwd.c
OBJ         := build/core/signals.o\
			build/core/signals2.o\
			build/core/prompt.o\
			build/core/heredoc.o\
			build/core/core_aux.o\
			build/core/parse_and_run.o\
			build/core/core_loop.o\
			build/core/token_vec_helpers.o\
			build/core/token_vec_helpers_2.o\
			build/parser/parser.o\
			build/parser/ast.o\
			build/parser/ast_helpers.o\
			build/parser/ast_print.o\
			build/parser/ast_free.o\
			build/preprocessor/redir_collapse_helpers.o\
			build/preprocessor/varexp_helpers.o\
			build/preprocessor/catch_forbidden.o\
			build/preprocessor/expand_helpers.o\
			build/preprocessor/redir_checker.o\
			build/preprocessor/errors.o\
			build/preprocessor/export.o\
			build/preprocessor/isstringtoken.o\
			build/preprocessor/unset.o\
			build/preprocessor/pre_process.o\
			build/preprocessor/wilcard.o\
			build/preprocessor/sanitize_input.o\
			build/preprocessor/collapser.o\
			build/preprocessor/recognition.o\
			build/preprocessor/expand_vars.o\
			build/preprocessor/resolve_path.o\
			build/preprocessor/redir_collapse.o\
			build/env/var_loader.o\
			build/env/clear.o\
			build/env/print.o\
			build/env/hot_vars.o\
			build/env/env2envp.o\
			build/env/load.o\
			build/env/helpers.o\
			build/utils/main_utils.o\
			build/utils/help.o\
			build/main.o\
			build/lexer/eaters.o\
			build/lexer/tok_infer.o\
			build/lexer/try_lexas.o\
			build/lexer/display.o\
			build/lexer/lex.o\
			build/lexer/sequences.o\
			build/lexer/sanitize.o\
			build/runner/encoded_redirs.o\
			build/runner/pipes.o\
			build/runner/run.o\
			build/runner/make_redirs.o\
			build/runner/run_helpers.o\
			build/builtins/env/env.o\
			build/builtins/exit/exit.o\
			build/builtins/cd/cd.o\
			build/builtins/echo/builtin_echo_helpers.o\
			build/builtins/echo/builtin_echo.o\
			build/builtins/pwd/pwd.o
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -I./include -I./libft/include
LDFLAGS     := libft/libft.a -lreadline -lhistory

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft libft.a
	$(CC) $(OBJ) $(LDFLAGS) -o $@

clean:
	$(MAKE) -C libft clean
	rm -rf $(BUILDDIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)
.PHONY: all re fclean clean
MAKEFLAGS += --no-print-directory
