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

/*
*	Pone los tokens en STDERR, con el correspondiente
*	módulo donde se encuentran.
*/

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
		if (t)
			ft_fprintf(2, ANSI_BLUE"[%s] token %u: "ANSI_RESET"%s "
				ANSI_BLUE"(%s)\n"ANSI_RESET, mod, i, t->s.data,
				get_token_pretty(t->type));
		i++;
	}
}

/*
*	Ayuda a leer una linea, limpiar el principio y el final
*	si, la opcion addhist es true, lo guarda en la historia,
*	eso esta hacho para que en los heredocs no se guarde
*/

bool	read_l(t_string *prompt, t_vec *tokv, bool addhist)
{
	char		*s;
	t_string	line;

	s = readline(prompt->data);
	if (s == NULL && addhist)
		return (false);
	line = ft_tstr_from_cstr(s);
	free(s);
	ft_tstr_trim(&line, " \t\n\r");
	if (!line.len || !line.data)
	{
		ft_tstr_free(&line);
		clean_tokenstream(tokv);
		return (true);
	}
	if (*line.data && addhist)
		add_history(line.data);
	lex(&line, tokv);
	ft_tstr_free(&line);
	return (true);
}

bool	read_l_hdoc(t_string *prompt, t_string *line)
{
	char		*s;

	s = readline(prompt->data);
	if (s == NULL)
	{
		ft_tstr_clear(line);
		return (false);
	}
	ft_tstr_pushstr(line, s);
	free(s);
	if (!line->data)
	{
		ft_tstr_clear(line);
		return (false);
	}
	return (true);
}

void	check_exit(t_vec *tokv, t_data *data)
{
	const t_tok	*tok;
	size_t		i;

	i = 0;
	while (i < tokv->size)
	{
		tok = ft_vec_get(tokv, i);
		if (tok && tok->s.data && tok->s.len
			&& !ft_strcmp(tok->s.data, "_sh__builtin_exit")
			&& tok->type == TOK_IDENT)
			data->exit = true;
		i++;
	}
}
