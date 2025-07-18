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

	if (!tokv || !tokv->size || !tokv->data)
		return ;
	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (t && t->s.data && t->s.len)
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
	if (line.len <= 1 || !line.data)
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

t_data	getopts(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.envp = envp;
	data.prompt = ft_tstr_from_cstr("$ ");
	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--debug"))
			data.debug = true;
		else if (!ft_strcmp(argv[i], "-c"))
		{
			data.oneliner = true;
			if (i + 1 < argc)
				data.oneliner_s = ft_tstr_from_cstr(argv[i + 1]);
			else
				ft_printf(ANSI_RED"error: "ANSI_RESET"no input\n");
		}
		i++;
	}
	return (data);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->prompt.data)
		ft_tstr_free(&data->prompt);
	if (data->oneliner_s.data)
		ft_tstr_free(&data->oneliner_s);
}
