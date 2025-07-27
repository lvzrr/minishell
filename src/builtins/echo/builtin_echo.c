/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:06:26 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 20:06:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	setflags(char *flag, bool *com_n, bool *com_e)
{
	if (*flag != '-')
		return ;
	flag++;
	while (*flag)
	{
		if (*flag == 'n')
			*com_n = true;
		else if (*flag == 'e')
			*com_e = true;
		else if (*flag == 'E')
			*com_e = false;
		else
			break ;
		flag++;
	}
}

void	write_normal(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (i < argc - 1)
			write(1, " ", 1);
		++i;
	}
}

bool	write_notscaped(char *string)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(string);
	while (string[i])
	{
		if (string[i] == '\\')
		{
			if (manage_scape(string, &i, len))
				return (true);
		}
		else
			write(1, string + i++, 1);
	}
	return (false);
}

bool	write_e(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		write_notscaped(argv[i]);
		if (i < argc - 1)
			write(1, " ", 1);
		++i;
	}
	return (false);
}

/*Usamos esta función para determinar las flags y escapes que nos envían y
discriminarlas para poder escribirlas apropiadamente.
Con com_tf parseamos las flags para, una vez terminadas de evaluar todas, 
imprimir el resto de ordenes acorde a las flags recibidas.
A priori Shell el comando echo solo trata las flags que aparecen antes del 
primer argumento que hay que imprimir*/

int	_sh__builtin_echo(int argc, char **argv, t_data *data)
{
	bool	com_n;
	bool	com_e;
	int		i;

	(void)data;
	com_n = false;
	com_e = false;
	if (!argc || !argv)
		return (write(1, "\n", 1), 0);
	i = 0;
	while (i < argc && argv[i][0] == '-' && argv[i][1])
		setflags(argv[i++], &com_n, &com_e);
	argc -= i;
	argv += i;
	if (!com_e)
		write_normal(argc, argv);
	else
		if (write_e(argc, argv))
			return (0);
	if (!com_n)
		return (write(1, "\n", 1), 0);
	return (0);
}
