/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:21:26 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 01:22:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	_sh__builtin_pwd(int argc, char **argv, t_data *data)
{
	(void)argv;
	if (argc)
		return (ft_fprintf(2, ANSI_RED"pwd: too many arguments\n"
				ANSI_RESET), EXIT_FAILURE);
	if (!data->pwd || !data->pwd->data)
		return (ft_fprintf(2, ANSI_RED"pwd: pwd not found\n"
				ANSI_RESET), EXIT_FAILURE);
	else
	{
		write(1, data->pwd->data, data->pwd->len);
		write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
