/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	main(int argc, char **argv, char **envp)
{
	t_string	line;
	t_vec		tokv;
	char		*s;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		s = readline("$ ");
		line = ft_tstr_from_cstr(s);
		free(s);
		ft_tstr_trim(&line, " \t\n\r");
		add_history(line.data);
		ft_printf("got '%s'\n", line.data);
		tokv = lex(&line);
		for (size_t i = 0; i < tokv.size; i++)
		{
			t_tok *tmp = (t_tok *)ft_vec_get_mut(&tokv, i);
			ft_tstr_free(&tmp->s);
		}
		ft_vec_free(&tokv);
		if (!ft_strcmp("exit", line.data))
		{
			ft_tstr_free(&line);
			rl_clear_history();
			return (0);
		}
		ft_tstr_free(&line);
	}
}
