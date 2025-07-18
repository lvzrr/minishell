/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_infer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:42:09 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 08:42:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"

t_toktype	get_token_type_1(t_string *s)
{
	if (!s || s->len != 1)
		return (0xff);
	if (*s->data == '<')
		return (TOK_LR);
	else if (*s->data == '>')
		return (TOK_RR);
	else if (*s->data == '&')
		return (TOK_AND);
	else if (*s->data == '|')
		return (TOK_PIPE);
	else if (*s->data == '(')
		return (TOK_LPAREN);
	else if (*s->data == ')')
		return (TOK_RPAREN);
	else if (*s->data == '{')
		return (TOK_LCURLY);
	else if (*s->data == '}')
		return (TOK_RCURLY);
	else if (*s->data == '$')
		return (TOK_DOLLAR);
	else if (*s->data == ';')
		return (TOK_SCOLON);
	else
		return (0xff);
}

t_toktype	get_token_type_1_2(t_string *s)
{
	if (!s || s->len != 1)
		return (0xff);
	if (*s->data == '=')
		return (TOK_EQ);
	else
		return (0xff);
}

t_toktype	get_token_type_2(t_string *s)
{
	char	a;
	char	b;

	if (!s || s->len != 2)
		return (0xff);
	a = s->data[0];
	b = s->data[1];
	if (a == '>' && b == '>')
		return (TOK_RAPPEND);
	else if (a == '<' && b == '<')
		return (TOK_HDOC);
	else if (a == '&' && b == '&')
		return (TOK_AND);
	else if (a == '|' && b == '|')
		return (TOK_OR);
	else if (a == '>' && b == '&')
		return (TOK_REDIR);
	else
		return (0xff);
}
