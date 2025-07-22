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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	// signal_setup();
	data = getopts(argc, argv, envp);
	(void)flag_updater(&data);
	load_env(&data, envp, argv[0]);
	if (data.debug)
		print_env(&data);
	if (data.phelp)
	{
		phelp();
		return (clean_data(&data), EXIT_SUCCESS);
	}
	if (!data.oneliner)
		core_loop(&data);
	else
		handle_oneliner(&data);
	return (clean_data(&data), EXIT_SUCCESS);
}
