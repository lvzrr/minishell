/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:26:51 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/23 20:28:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/*
*	Si la cagamos, por lo menos que sea con gracia
*
*	Si es la segunda vez que se llama a esta funcion,
*	salimos y nos olvidamos.
*/

void	s_handler(int signal)
{
	t_data	*data;

	(void)signal;
	data = flag_updater(NULL);
	if (!data->segfault)
		data->segfault = true;
	else
		exit(EXIT_FAILURE);
	ft_printf(ANSI_RED"SEGFAULT\n"ANSI_RESET);
	clean_data(data);
	exit(EXIT_FAILURE);
}

void	signal_child_running(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
}
