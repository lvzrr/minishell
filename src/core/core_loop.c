/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:36:58 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 09:41:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	dump_tokenstream(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (t && t->s.data && t->s.len)
			ft_printf(ANSI_BLUE"token: "ANSI_RESET"%s\n", t->s.data);
		i++;
	}
}

static void	read_l(t_string *prompt, t_vec *tokv)
{
	char		*s;
	t_string	line;

	s = readline(prompt->data);
	line = ft_tstr_from_cstr(s);
	free(s);
	ft_tstr_trim(&line, " \t\n\r");
	add_history(line.data);
	*tokv = lex(&line);
	ft_tstr_free(&line);
}

void	core_loop(t_data *data)
{
	t_vec		tokv;
	size_t		i;

	while (1)
	{
		read_l(&data->prompt, &tokv);
		if (data->debug)
			dump_tokenstream(&tokv);
		i = 0;
		while (i < tokv.size)
		{
			if (!ft_strcmp(((t_tok *)ft_vec_get(&tokv, i++))->s.data, "exit"))
			{
				clean_tokenstream(&tokv);
				rl_clear_history();
				return ;
			}
		}
		// TODO: aqui pasarle al constructor del AST
		// tokv antes de limpiarla
		clean_tokenstream(&tokv);
	}
}
