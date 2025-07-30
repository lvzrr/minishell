/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:36:11 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 02:45:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
*
*	esto no se deberia de liberar,
*	ya que lo llamaremos directamente
*	en el argumento de execve, y por
*	lo tanto no cuenta como "leak".
*
*	NOTA:
*	la segunda llamada a memcpy copia
*	el terminador basicamente, para VAR=1
*
*	- copiamos el nombre (VAR)
*	- copiamos el valor (VAR 1\0)
*	- inyectamos un '=' (VAR=1\0)
*
*	execve(cmd[0], cmd, env2envp(&data->env))
*
*/

char	**env2envp(t_vec *env)
{
	char	**envp;
	t_var	*cv;
	size_t	i;

	if (!env || !env->size)
		return (NULL);
	envp = ft_calloc(env->size + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < env->size)
	{
		cv = ft_vec_get_mut(env, i);
		if (!cv)
			break ;
		envp[i] = ft_alloc(cv->name.len + cv->value.len + 2);
		if (!envp[i])
			return (free_split(envp), NULL);
		ft_memcpy(envp[i], cv->name.data, cv->name.len);
		ft_memcpy(envp[i] + cv->name.len + 1, cv->value.data,
			cv->value.len + 1);
		envp[i++][cv->name.len] = '=';
	}
	return (envp);
}
