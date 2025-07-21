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

static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != NULL)
		ft_free((void **)&(split[i++]));
	ft_free((void **)&split);
}

static void	load_default_env(t_data *data)
{
	t_var	var;
	char	*dir;

	data->env = ft_vec(3, sizeof(t_var));
	var.name = ft_tstr_from_cstr("PATH");
	var.value = ft_tstr_from_cstr(
			"/usr/local/sbin/:/usr/local/bin:/usr/bin:/bin");
	ft_vec_push(&data->env, &var, 1);
	var.name = ft_tstr_from_cstr("SHLVL");
	var.value = ft_tstr_from_cstr("1");
	ft_vec_push(&data->env, &var, 1);
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
	var.name = ft_tstr_from_cstr("_");
	var.value = ft_tstr_from_cstr("./minishell");
	ft_vec_push(&data->env, &var, 1);
}

void	load_env(t_data *data, char **envp)
{
	t_var	var;
	char	**tmp;
	size_t	i;

	i = 0;
	if (!envp || !*envp)
	{
		load_default_env(data);
		return ;
	}
	data->env = ft_vec(10, sizeof(t_var));
	while (envp[i])
	{
		tmp = ft_split(envp[i++], '=');
		if (!tmp)
			continue ;
		var = (t_var)
		{
			.name = ft_tstr_from_cstr(tmp[0]),
			.value = ft_tstr_from_cstr(tmp[1]),
		};
		free_split(tmp);
		ft_vec_push(&data->env, &var, 1);
	}
	increase_shell_lvl(&data->env);
}
