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
	else if (t == TOK_SUBSTITUTION)
		return ("TOK_SUBSTITUTION");
	else
		return (get_token_pretty_1(t));
}

const char	*get_token_pretty_1(t_toktype t)
{
	if (t == TOK_LR)
		return ("TOK_LR");
	if (t == TOK_AMPER)
		return ("TOK_AMPER");
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
	else if (t == TOK_SPACE)
		return ("TOK_SPACE");
	else if (t == TOK_STRING_EMPTY)
		return ("TOK_STRING_EMPTY");
	else if (t == TOK_SUBS_START)
		return ("TOK_SUBS_START");
	else if (t == TOK_REDIR_IN)
		return ("TOK_REDIR_IN");
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
	else if (t == TOK_REDIR_TO)
		return ("TOK_REDIR_TO");
	else if (t == TOK_REDIR_NN)
		return ("TOK_REDIR_NN");
	else if (t == TOK_APPEND_TO)
		return ("TOK_APPEND_TO");
	else if (t == TOK_REDIR_FROM_FD)
		return ("TOK_REDIR_FROM_FD");
	else if (t == TOK_APPEND_FROM_FD)
		return ("TOK_APPEND_FROM_FD");
	else if (t == TOK_WRITE_IN)
		return ("TOK_WRITE_IN");
	else
		return ("TOK_UNKNOWN");
}
