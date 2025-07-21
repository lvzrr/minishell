/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:10:29 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 21:11:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
*	Otra funcion que solo existe por culpa de norminette
*	carga el path desde donde se ha llamado a la shell,
*	si no se ha hecho desde ./ y se ha llamado desde el
*	$PATH, lo guarda
*/

void	load_invocation_helper(t_data *data, t_var oldvar)
{
	t_var	var;

	var.name = ft_tstr_from_cstr("_");
	if (data->invocation && *data->invocation == '.')
	{
		var.value = ft_tstr_clone(&oldvar.value);
		ft_tstr_push(&var.value, '/');
		ft_tstr_pushstr(&var.value, data->invocation);
	}
	else
		var.value = ft_tstr_from_cstr(data->invocation);
	ft_vec_push(&data->env, &var, 1);
}
