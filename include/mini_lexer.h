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
# include "ctype.h"
# include "vec.h"

typedef enum e_toktype
{
	TOK_STRING_TOEXPAND,
	TOK_IDENT,
	TOK_STRING_DQ,
	TOK_STRING_SQ,
	TOK_DQ,
	TOK_SQ,
	TOK_LR,
	TOK_RAPPEND,
	TOK_HDOC,
	TOK_RR,
	TOK_AND,
	TOK_PIPE,
	TOK_EQ,
	TOK_OR,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_LCURLY,
	TOK_RCURLY,
	TOK_DOLLAR,
	TOK_SCOLON,
}	t_toktype;

typedef struct s_tok
{
	t_toktype	type;
	t_string	s;
}	t_tok;

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
void		remove_scape(t_string *s, size_t offst);
void		try_lexas_ident(t_string *s, t_vec *out,
				size_t *offst);
void		try_lexas_op(t_string *s, t_vec *out,
				size_t *offst);
bool		try_lexas_qs(t_string *s, t_vec *out,
				size_t *offst);
t_vec		lex(t_string *s);
#endif
