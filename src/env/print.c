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

void	print_env(t_data *data, bool print_fast)
{
	const t_var	*var;
	size_t		i;
	size_t		fd;

	fd = 1;
	if (print_fast)
		fd = 2;
	i = 0;
	if (print_fast)
		ft_fprintf(fd, ANSI_MAGENTA"==ENV=="ANSI_RESET"\n");
	while (i < data->env.size)
	{
		var = ft_vec_get(&data->env, i++);
		ft_fprintf(fd, ANSI_MAGENTA"%s"ANSI_RESET"=\"%s\"\n",
			var->name.data, var->value.data);
	}
	if (!print_fast)
		return ;
	ft_fprintf(fd, ANSI_MAGENTA"==END OF ENV==\n"ANSI_RESET);
	ft_fprintf(fd, ANSI_MAGENTA"==FAST ACCESS ENV=="ANSI_RESET"\n");
	ft_fprintf(fd, ANSI_MAGENTA"PWD="ANSI_RESET"%s\n", data->pwd->data);
	ft_fprintf(fd, ANSI_MAGENTA"PATH="ANSI_RESET"%s\n", data->path->data);
	ft_fprintf(fd, ANSI_MAGENTA"==END OF FAST ACCESS ENV=="ANSI_RESET"\n");
}
