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

void	load_pwd(char *new, t_data *data)
{
	t_string	name;
	t_string	value;

	if (!data->pwd)
	{
		name = ft_tstr_from_cstr("PWD");
		value = ft_tstr_from_cstr(new);
		load_var(&name, &value, data);
		ft_tstr_free(&name);
		ft_tstr_free(&value);
		load_hot_vars(data);
		return ;
	}
	(ft_tstr_clear(data->pwd), ft_tstr_pushstr(data->pwd, new));
}

int	_sh__builtin_cd(int argc, char **argv, t_data *data)
{
	char	*new;

	if (!data)
		return (err_file("no state passed\n", "cd"), EXIT_FAILURE);
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
	load_pwd(new, data);
	return (free(new), EXIT_SUCCESS);
}
