/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:01:19 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 16:01:20 by jaicastr         ###   ########.fr       */
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
