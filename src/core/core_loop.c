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

/*
*	Funcion que maneja la flag '-c'
*	TODO:
*	abstraerla para que pase norminette
*/

void	handle_oneliner(t_data *data)
{
	t_vec		tokv;

	ft_tstr_trim(&data->oneliner_s, " \t\n\r");
	if (!data->oneliner_s.len || !data->oneliner_s.data
		|| !*data->oneliner_s.data)	
		return ;
	tokv = lex(&data->oneliner_s);
	if (!tokv.size)
		clean_tokenstream(&tokv);
	if (data->debug)
		dump_tokenstream("LEXER", &tokv);
	post_process(&tokv, data);
	if (data->debug)
		dump_tokenstream("PARSER", &tokv);
	if (!heredoc(&tokv, data))
	{
		clean_tokenstream(&tokv);
		return ;
	}
	// TODO: aqui pasarle al constructor del AST
	// tokv antes de limpiarla
	clean_tokenstream(&tokv);
}

/*
*	Funcion que maneja la lógica principal de la
*	shell en modo normal
*	TODO:
*	abstraerla para que pase norminette
*	también cambiar clean_tokenstream para que
*	limpie el vector pero no lo cree todo el rato,
*	reusar el mismo vector siempre vaya
*/

void	core_loop(t_data *data)
{
	t_vec		tokv;

	tokv = (t_vec){0};
	while (1)
	{
		if (!read_l(&data->prompt, &tokv, true))
		{
			rl_clear_history();
			if (tokv.alloc_size)
				clean_tokenstream(&tokv);
			return ;
		}
		if (!tokv.size)
			continue ;
		if (data->debug)
			dump_tokenstream("LEXER", &tokv);
		if (!post_process(&tokv, data))
		{
			clean_tokenstream(&tokv);
			continue ;
		}
		if (data->debug)
			dump_tokenstream("PARSER", &tokv);
		if (check_exit(&tokv))
		{
			clean_tokenstream(&tokv);
			rl_clear_history();
			return ;
		}
		if (!heredoc(&tokv, data))
		{
			clean_tokenstream(&tokv);
			continue ;
		}
		// TODO: aqui pasarle al constructor del AST
		// tokv antes de limpiarla
		clean_tokenstream(&tokv);
	}
}
