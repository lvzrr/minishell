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

/*
*	llamamos a gnl otra vez para que devuelva eof,
*	y se libere el buffer interno.
*/

t_string	get_hostname(void)
{
	t_string	hostname;
	int			fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (ft_tstr_from_cstr("????"));
	hostname = get_next_line(fd);
	get_next_line(fd);
	ft_tstr_trim(&hostname, "\n");
	(ft_fgetc(fd, true), close(fd));
	return (hostname);
}

t_data	getopts(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	data = (t_data){0};
	data.envp = envp;
	data.exit = false;
	data.tokv = ft_vec(10, sizeof(t_tok));
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
	return (load_env(&data, envp, argv[0]), default_prompt(&data), data);
}

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->under_valgrind)
		ft_fprintf(2, ANSI_GREEN"I cast no leaks! ヽ(｀Д´)⊃━☆ﾟ. * ･ ｡ﾟ \n"
			ANSI_RESET);
	if (data->prompt.data)
		ft_tstr_free(&data->prompt);
	if (data->oneliner_s.data)
		ft_tstr_free(&data->oneliner_s);
	if (data->env.data)
		clean_env(&data->env);
	clean_tokenstream(&data->tokv);
	ft_vec_free(&data->tokv);
	free_var(&data->lastcommand_res);
	ft_tstr_free(&data->hostname);
}
