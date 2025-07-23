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
*/

void	s_handler(int signal)
{
	t_data	*data;

	(void)signal;
	data = flag_updater(NULL);
	ft_printf(ANSI_RED"SEGFAULT\n"ANSI_RESET);
	clean_data(data);
	exit(EXIT_FAILURE);
}
