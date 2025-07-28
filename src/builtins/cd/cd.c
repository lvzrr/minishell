/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:13:56 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 02:14:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	_sh__builtin_cd(int argc, char **argv, t_data *data)
{
	char	*new;

	if (!data || !data->pwd)
		return (EXIT_FAILURE);
	if (argc > 1)
		return (ft_fprintf(2, ANSI_RED"cd error: "ANSI_RESET
				"too many arguments\n"), EXIT_FAILURE);
	if (argc == 0)
	{
		new = getenv("HOME");
		if (!new)
			return (ft_fprintf(2, ANSI_RED"cd error: "ANSI_RESET
					"no $HOME\n"), EXIT_FAILURE);
		argv = &new;
		argc = 1;
	}
	if (chdir(argv[0]) == -1)
		return (ft_fprintf(2, ANSI_RED"cd error: "ANSI_RESET
				"no such file or directory\n"), EXIT_FAILURE);
	new = getcwd(NULL, 0);
	if (!new)
		return (ft_fprintf(2, "cd: getcwd\n"), EXIT_FAILURE);
	(ft_tstr_clear(data->pwd), ft_tstr_pushstr(data->pwd, new));
	return (free(new), default_prompt(data), EXIT_SUCCESS);
}
