/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 03:11:57 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 03:15:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_env(t_vec *env)
{
	const t_var	*var;
	size_t		i;

	i = 0;
	ft_fprintf(2, ANSI_MAGENTA"==ENV=="ANSI_RESET"\n");
	while (i < env->size)
	{
		var = ft_vec_get(env, i++);
		ft_fprintf(2, ANSI_MAGENTA"%s"ANSI_RESET"=%s\n",
			var->name.data, var->value.data);
	}
	ft_fprintf(2, ANSI_MAGENTA"==END OF ENV==\n"ANSI_RESET);
}
