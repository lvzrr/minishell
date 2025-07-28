/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 23:55:18 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 23:56:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	_sh__builtin_exit(int argc, char **argv, t_data *data)
{
	(void)argc;
	(void)argv;
	data->exit = true;
	return (EXIT_SUCCESS);
}
