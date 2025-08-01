/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:01:19 by jaicastr          #+#    #+#             */
/*   Updated: 2025/08/01 12:14:28 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	*flag_updater(t_data *datap)
{
	static t_data	*data;

	if (datap)
		data = datap;
	else
	{
		data->hdoc_terminate = true;
		return (data);
	}
	return (NULL);
}

static void	ctrl_c_hdoc(int signal)
{
	(void)signal;
	(void)flag_updater(NULL);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	hdoc_signal_setup(void)
{
	signal(SIGINT, ctrl_c_hdoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, s_handler);
}

void	signal_setup(void)
{
	signal(SIGPIPE, SIG_IGN);				//Añadido nuevo.
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, s_handler);
}

void	ctrl_c(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
