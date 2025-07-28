/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:36:49 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 01:42:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define NO_FAST_ACCESS false

int	_sh__builtin_env(int argc, char **argv, t_data *data)
{
	(void)argv;
	if (!data)
		return (EXIT_FAILURE);
	if (argc == 0)
		return (print_env(data, NO_FAST_ACCESS), EXIT_SUCCESS);
	ft_fprintf(2, ANSI_RED"env error:"ANSI_RESET"invalid option or usage\n");
	return (EXIT_FAILURE);
}
