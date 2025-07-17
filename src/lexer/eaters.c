/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eaters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:23:33 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 02:23:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

size_t	goto_next(t_string *s, size_t offst)
{
	static char		*errmsg;
	static size_t	errl;

	if (!s || !s->data)
		return (offst);
	if (!errmsg)
	{
		errmsg = ANSI_RED"syntax error: "ANSI_RESET" unsupported symbol\n"
			"hint: Use utf-8 encoding and no arithmetics, as this project "
			"isn't supposed to support it\n";
		errl = ft_strlen(errmsg);
	}
	while (offst < s->len
		&& ft_isspace(s->data[offst]))
		offst++;
	if (isunsupported(s->data[offst]))
		return ((void)write(2, errmsg, errl), SIZE_MAX);
	if (s->data[offst] == '\\' && offst == s->len - 1)
		offst++;
	if (s->data[offst] == '\\' && offst + 1 < s->len
		&& s->data[offst + 1] == '\\')
		offst++;
	return (offst);
}

size_t	eat_string_sq(t_string *s, size_t offst)
{
	static char		*errmsg;
	static size_t	errl;

	if (!s || !s->data)
		return (offst);
	if (!errmsg)
	{
		errmsg = ANSI_RED"syntax error: "ANSI_RESET"unclosed \'\n";
		errl = ft_strlen(errmsg);
	}
	++offst;
	while (offst < s->len - 1 && s->data[offst] != '\'')
	{
		if (s->data[offst] == '\\')
		{
			remove_scape(s, offst++);
			continue ;
		}
		offst++;
	}
	if (offst < s->len && s->data[offst] == '\'')
		return (++offst);
	write(2, errmsg, errl);
	return (SIZE_MAX);
}

size_t	eat_string_dq(t_string *s, size_t offst)
{
	static char		*errmsg;
	static size_t	errl;

	if (!s || !s->data)
		return (offst);
	if (!errmsg)
	{
		errmsg = ANSI_RED"syntax error: "ANSI_RESET"unclosed \"\n";
		errl = ft_strlen(errmsg);
	}
	++offst;
	while (offst < s->len - 1 && s->data[offst] != '\"')
	{
		if (s->data[offst] == '\\')
		{
			remove_scape(s, offst++);
			continue ;
		}
		offst++;
	}
	if (offst < s->len && s->data[offst] == '\"')
		return (++offst);
	write(2, errmsg, errl);
	return (SIZE_MAX);
}

size_t	eat_ident(t_string *s, size_t offst)
{
	if (!s || !s->data)
		return (offst);
	while (offst < s->len && isvalidident(s->data[offst]))
	{
		if (s->data[offst] == '\\')
		{
			remove_scape(s, offst++);
			continue ;
		}
		if (ft_isspace(s->data[offst])
			&& ((offst >= 1 && s->data[offst - 1] != '\\') || offst == 0))
			return (offst);
		if ((s->data[offst] == '\'' || s->data[offst] == '\"')
			&& offst >= 1 && s->data[offst - 1] != '\\')
			return (offst);
		offst++;
	}
	return (offst);
}

size_t	eat_op(t_string *s, size_t offst)
{
	char	c;

	if (!s || !s->data || offst >= s->len)
		return (offst);
	c = s->data[offst++];
	if (offst < s->len && s->data[offst] == c
		&& (c == '&' || c == '|' || c == '<' || c == '>'))
		offst++;
	return (offst);
}
