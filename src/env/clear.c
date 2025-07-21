/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:58:56 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 03:02:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_var(t_var *var)
{
	if (!var)
		return ;
	ft_tstr_free(&var->name);
	ft_tstr_free(&var->value);
}

void	clean_env(t_vec *env)
{
	t_var	*var;
	size_t	i;

	i = 0;
	while (i < env->size)
	{
		var = ft_vec_get_mut(env, i++);
		free_var(var);
	}
	ft_vec_free(env);
}
