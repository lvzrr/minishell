/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static t_data	getopts(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	data.envp = envp;
	data.debug = false;
	data.prompt = ft_tstr_from_cstr("ft_sh $ ");
	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "--debug"))
			data.debug = true;
		i++;
	}
	return (data);
}

static void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->prompt.data)
		ft_tstr_free(&data->prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data = getopts(argc, argv, envp);
	core_loop(&data);
	clean_data(&data);
}
