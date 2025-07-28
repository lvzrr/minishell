/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:22:54 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 02:23:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	increase_shell_lvl(t_vec *env)
{
	t_var	*var;
	size_t	lvl;
	char	*new_val;
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		var = ft_vec_get_mut(env, i++);
		if (!ft_strncmp(var->name.data, "SHLVL", 5))
		{
			lvl = ft_atoul(var->value.data);
			ft_tstr_free(&var->value);
			new_val = ft_utoa_base(++lvl, "0123456789");
			var->value = ft_tstr_from_cstr(new_val);
			ft_free((void **)&new_val);
		}
	}
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != NULL)
		ft_free((void **)&(split[i++]));
	ft_free((void **)&split);
}

static void	var_init(t_data *data, char *a, char *b)
{
	t_var	var;

	var.name = ft_tstr_from_cstr(a);
	var.value = ft_tstr_from_cstr(b);
	ft_vec_push(&data->env, &var, 1);
}

/*
 *  TODO: buscar el usuario en
 * /etc/passwd parseando /proc/self
 */

static void	load_default_env(t_data *data)
{
	t_var	var;
	char	*dir;

	data->env = ft_vec(3, sizeof(t_var));
	var_init(data, "SHLVL", "1");
	var_init(data, "PATH",
		"/usr/local/sbin/:/usr/local/bin:/usr/bin:/bin");
	dir = getcwd(NULL, 0);
	var.name = ft_tstr_from_cstr("PWD");
	if (dir)
	{
		var.value = ft_tstr_from_cstr(dir);
		free(dir);
	}
	else
		var.value = ft_tstr_from_cstr("/");
	ft_vec_push(&data->env, &var, 1);
	load_invocation_helper(data, var);
}

/*
*	NOTE:
*	esto sólo devuelve null por que quería meter
*	una línea mas y necesitaba la tupla del return
*	con norminette.
*
*	No usar el resultado de esta función en ningun
*	momento. Es solo que para las variables de accesso
*	rápido no tenia sentido usar otra funcion.
*/

void	*load_env(t_data *data, char **envp, char *inv)
{
	t_var	var;
	char	**tmp;
	size_t	i;

	i = 0;
	data->invocation = inv;
	if (!envp || !*envp)
	{
		load_default_env(data);
		return (load_hot_vars(data), NULL);
	}
	data->env = ft_vec(10, sizeof(t_var));
	while (envp[i])
	{
		tmp = ft_split(envp[i++], '=');
		if (!tmp)
			continue ;
		var = (t_var){.name = ft_tstr_from_cstr(tmp[0]),
			.value = ft_tstr_from_cstr(tmp[1])};
		free_split(tmp);
		ft_vec_push(&data->env, &var, 1);
	}
	return (increase_shell_lvl(&data->env), load_hot_vars(data), NULL);
}
