/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:19:30 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 01:20:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_data	getopts(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	data = (t_data){0};
	data.envp = envp;
	data.prompt = ft_tstr_from_cstr("$ ");
	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--debug"))
			data.debug = true;
		if (!ft_strcmp(argv[i], "--help"))
			data.phelp = true;
		else if (!ft_strcmp(argv[i], "-c"))
		{
			data.oneliner = true;
			if (i + 1 < argc)
				data.oneliner_s = ft_tstr_from_cstr(argv[i + 1]);
			else
				ft_printf(ANSI_RED"error: "ANSI_RESET"no input\n");
		}
		i++;
	}
	return (data);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->prompt.data)
		ft_tstr_free(&data->prompt);
	if (data->oneliner_s.data)
		ft_tstr_free(&data->oneliner_s);
	if (data->env.data)
		clean_env(&data->env);
}
