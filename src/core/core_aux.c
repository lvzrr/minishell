/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:57:14 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 10:57:24 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	dump_tokenstream(char *mod, t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	if (!tokv)
		return ;
	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (t && t->s.data && (t->s.len || t->type == TOK_STRING_EMPTY))
			ft_printf(ANSI_BLUE"[%s] token: "ANSI_RESET"%s "
				ANSI_BLUE"(%s)\n"ANSI_RESET, mod, t->s.data,
				get_token_pretty(t->type));
		i++;
	}
}

void	read_l(t_string *prompt, t_vec *tokv)
{
	char		*s;
	t_string	line;

	s = readline(prompt->data);
	line = ft_tstr_from_cstr(s);
	free(s);
	ft_tstr_trim(&line, " \t\n\r");
	if (!line.len || !line.data)
	{
		ft_tstr_free(&line);
		*tokv = (t_vec){0};
		return ;
	}
	if (*line.data)
		add_history(line.data);
	*tokv = lex(&line);
	ft_tstr_free(&line);
}

bool	check_exit(t_vec *tokv)
{
	const t_tok	*tok;
	size_t		i;

	i = 0;
	while (i < tokv->size)
	{
		tok = ft_vec_get(tokv, i);
		if (tok && tok->s.data && tok->s.len
			&& !ft_strcmp(tok->s.data, "exit") && tok->type == TOK_IDENT)
			return (true);
		i++;
	}
	return (false);
}
