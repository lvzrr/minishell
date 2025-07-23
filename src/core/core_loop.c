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
	ft_tstr_trim(&data->oneliner_s, " \t\n\r");
	if (!data->oneliner_s.len || !data->oneliner_s.data
		|| !*data->oneliner_s.data)
		return ;
	lex(&data->oneliner_s, &data->tokv);
	if (!data->tokv.size)
		clean_tokenstream(&data->tokv);
	if (data->debug)
		dump_tokenstream("LEXER", &data->tokv);
	post_process(&data->tokv, data);
	if (data->debug)
		dump_tokenstream("PARSER", &data->tokv);
	if (!heredoc(&data->tokv, data))
	{
		clean_tokenstream(&data->tokv);
		return ;
	}
	// TODO: aqui pasarle al constructor del AST
	// tokv antes de limpiarla
	clean_tokenstream(&data->tokv);
}

/*
 *	Estas dos funciones son para norminette,
 *	miran si deben limpiarl el vector y salir
 *	o continuar respectivamente, en base a una
 *	flag "trigger" arbitraria, son esencialmente
 *	una macro, pero como no dejan pues toca funcion
 */

static bool	check_clean_and_exit(bool ret, bool trigger, t_vec *tokv)
{
	if (ret == trigger)
	{
		rl_clear_history();
		if (tokv->alloc_size)
			clean_tokenstream(tokv);
		return (true);
	}
	return (false);
}

static bool	opt_clean(bool ret, bool trigger, t_vec *tokv)
{
	if (ret == trigger)
	{
		if (tokv->alloc_size)
			clean_tokenstream(tokv);
		return (true);
	}
	return (false);
}

/*
*	Funcion que maneja la lógica principal de la
*	shell en modo normal
*
* 	NOTA:
* 	el vector de tokens vive durante toda la ejecución
* 	del programa, es decir, reusamos el mismo malloc
* 	hasta el final, donde se libera.
*
*/

void	core_loop(t_data *data)
{
	while (1)
	{
		clean_tokenstream(&data->tokv);
		if (check_clean_and_exit(read_l(&data->prompt, &data->tokv, true),
				false, &data->tokv))
			return ;
		if (!data->tokv.size)
			continue ;
		if (data->debug)
			dump_tokenstream("LEXER", &data->tokv);
		if (opt_clean(post_process(&data->tokv, data), false, &data->tokv))
			continue ;
		if (data->debug)
			dump_tokenstream("PARSER", &data->tokv);
		if (check_clean_and_exit(check_exit(&data->tokv), true, &data->tokv))
			return ;
		if (opt_clean(heredoc(&data->tokv, data), false, &data->tokv))
			continue ;
		// TODO: aqui pasarle al constructor del AST
		// tokv antes de limpiarla
	}
}
