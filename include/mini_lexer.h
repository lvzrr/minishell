/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:22:14 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:22:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_LEXER_H
# define MINI_LEXER_H

# include <stdbool.h>
# include "tstr.h"
# include "macros.h"
# include "io.h"
# include "ctype.h"
# include "vec.h"

typedef struct s_var
{
	t_string	name;
	t_string	value;
}	t_var;

typedef enum e_toktype
{
	TOK_IDENT,
	TOK_STRING,
	TOK_STRING_DQ,
	TOK_STRING_SQ,
	TOK_STRING_EMPTY,
	TOK_DQ,
	TOK_SQ,
	TOK_LR,
	TOK_RAPPEND,
	TOK_REDIR,
	TOK_HDOC,
	TOK_RR,
	TOK_AND,
	TOK_AMPER,
	TOK_PIPE,
	TOK_EQ,
	TOK_OR,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_LCURLY,
	TOK_RCURLY,
	TOK_DOLLAR,
	TOK_SCOLON,
	TOK_VAR,
	TOK_STRING_TOEXPAND,
	TOK_REDIR_NN,
	TOK_REDIR_IN,
	TOK_WRITE_IN,
	TOK_TILDE,
	TOK_REDIR_TO,
	TOK_APPEND_TO,
	TOK_REDIR_FROM_FD,
	TOK_APPEND_FROM_FD,
	TOK_SUBSTITUTION,
	TOK_SUBS_START,
	TOK_SPACE,
}	t_toktype;

typedef struct s_tok
{
	t_toktype	type;
	t_string	s;
}	t_tok;

void		try_lexas_comment(t_string *s, size_t *offst);
size_t		goto_next(t_string *s, size_t offst);
size_t		eat_string_sq(t_string *s, size_t offst);
size_t		eat_string_dq(t_string *s, size_t offst);
size_t		eat_op(t_string *s, size_t offst);
size_t		eat_ident(t_string *s, size_t offst);
bool		isvalidident(char c);
bool		isvalidop(char c);
t_toktype	get_token_type_1(t_string *s);
t_toktype	get_token_type_1_2(t_string *s);
t_toktype	get_token_type_2(t_string *s);
void		remove_char(t_string *s, size_t offst);
void		clean_tokenstream(t_vec *v);
bool		isunsupported(char c);
void		try_lexas_ident(t_string *s, t_vec *out,
				size_t *offst);
void		try_lexas_op(t_string *s, t_vec *out,
				size_t *offst);
bool		try_lexas_qs(t_string *s, t_vec *out,
				size_t *offst);
void		try_lexas_spc(t_string *s, t_vec *out,
				size_t *offst);
bool		lex(t_string *s, t_vec *tokv);
const char	*get_token_pretty(t_toktype t);
const char	*get_token_pretty_1(t_toktype t);
const char	*get_token_pretty_2(t_toktype t);
const char	*get_token_pretty_3(t_toktype t);
void		free_tok(void *v);
#endif
