/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 23:32:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 23:34:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"

/*
*	Estas funciones en cascada solo sirven para --debug
*	son para ver los tokens en vez de ver los numeros
*/

const char	*get_token_pretty(t_toktype t)
{
	if (t == TOK_STRING_TOEXPAND)
		return ("TOK_STRING_TOEXPAND");
	else if (t == TOK_IDENT)
		return ("TOK_IDENT");
	else if (t == TOK_STRING)
		return ("TOK_STRING");
	else if (t == TOK_STRING_DQ)
		return ("TOK_STRING_DQ");
	else if (t == TOK_STRING_SQ)
		return ("TOK_STRING_SQ");
	else if (t == TOK_DQ)
		return ("TOK_DQ");
	else if (t == TOK_SQ)
		return ("TOK_SQ");
	else if (t == TOK_SUBSHELL)
		return ("TOK_SUBSHELL");
	else
		return (get_token_pretty_1(t));
}

const char	*get_token_pretty_1(t_toktype t)
{
	if (t == TOK_LR)
		return ("TOK_LR");
	else if (t == TOK_RAPPEND)
		return ("TOK_RAPPEND");
	else if (t == TOK_REDIR)
		return ("TOK_REDIR");
	else if (t == TOK_HDOC)
		return ("TOK_HDOC");
	else if (t == TOK_RR)
		return ("TOK_RR");
	else if (t == TOK_AND)
		return ("TOK_AND");
	else if (t == TOK_PIPE)
		return ("TOK_PIPE");
	else if (t == TOK_EQ)
		return ("TOK_EQ");
	else
		return (get_token_pretty_2(t));
}

const char	*get_token_pretty_2(t_toktype t)
{
	if (t == TOK_OR)
		return ("TOK_OR");
	else if (t == TOK_LPAREN)
		return ("TOK_LPAREN");
	else if (t == TOK_RPAREN)
		return ("TOK_RPAREN");
	else if (t == TOK_LCURLY)
		return ("TOK_LCURLY");
	else if (t == TOK_RCURLY)
		return ("TOK_RCURLY");
	else if (t == TOK_DOLLAR)
		return ("TOK_DOLLAR");
	else if (t == TOK_SCOLON)
		return ("TOK_SCOLON");
	else
		return (get_token_pretty_3(t));
}

const char	*get_token_pretty_3(t_toktype t)
{
	if (t == TOK_VAR)
		return ("TOK_VAR");
	else if (t == TOK_SPACE)
		return ("TOK_SPACE");
	else if (t == TOK_STRING_SQ_NOEXPAND)
		return ("TOK_STRING_SQ_NOEXPAND");
	else if (t == TOK_STRING_EMPTY)
		return ("TOK_STRING_EMPTY");
	else
		return ("TOK_UNKNOWN");
}
