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
 *	Estas funciones actualizan la variable
 *	$SHELL o la crean, por que si no cuando
 *	le pasemos el env a los programas los
 *	ejecutables van a ver que estan bajo otra
 *	shell e intentar cosas raras a veces
 */

static void	set_shell_noenv(t_data *data)
{
	t_var	*var;
	t_var	new;
	char	*dot;

	new.name = ft_tstr_from_cstr("SHELL");
	var = getvar("_", &data->env);
	if (var)
	{
		new.value = ft_tstr_from_cstr(var->value.data);
		dot = ft_strrchr(new.value.data, '.');
		if (dot)
		{
			remove_char(&new.value, dot - new.value.data);
			remove_char(&new.value, dot - new.value.data);
		}
	}
	else
		new.value = ft_tstr_from_cstr(data->invocation);
	ft_vec_push(&data->env, &new, 1);
}

void	set_shell_var(t_data *data)
{
	t_var	*var;
	t_var	new;
	char	*dot;

	var = getvar("SHELL", &data->env);
	if (var)
	{
		ft_tstr_clear(&var->name);
		ft_tstr_pushstr(&var->name, "PARENTSHELL");
		new.name = ft_tstr_from_cstr("SHELL");
		var = getvar("_", &data->env);
		new.value = ft_tstr_clone(&var->value);
		dot = ft_strrchr(new.value.data, '.');
		if (dot)
		{
			remove_char(&new.value, dot - new.value.data);
			remove_char(&new.value, dot - new.value.data);
		}
		ft_vec_push(&data->env, &new, 1);
	}
	else
		set_shell_noenv(data);
}

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
