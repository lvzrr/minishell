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

#include "core.h"

void	handle_oneliner(t_data *data)
{
	t_vec		tokv;

	ft_tstr_trim(&data->oneliner_s, " \t\n\r");
	tokv = lex(&data->oneliner_s);
	if (data->debug)
		dump_tokenstream("LEXER", &tokv);
	join_seq(&tokv);
	if (data->debug)
		dump_tokenstream("PARSER", &tokv);
	// TODO: aqui pasarle al constructor del AST
	// tokv antes de limpiarla
	clean_tokenstream(&tokv);
}

void	core_loop(t_data *data)
{
	t_vec		tokv;

	while (1)
	{
		read_l(&data->prompt, &tokv);
		if (data->debug)
			dump_tokenstream("LEXER", &tokv);
		join_seq(&tokv);
		if (data->debug)
			dump_tokenstream("PARSER", &tokv);
		if (check_exit(&tokv))
		{
			clean_tokenstream(&tokv);
			rl_clear_history();
			return ;
		}
		if (!heredoc_routine(&tokv, data))
		{
			clean_tokenstream(&tokv);
			continue ;
		}
		// TODO: aqui pasarle al constructor del AST
		// tokv antes de limpiarla
		clean_tokenstream(&tokv);
	}
}
