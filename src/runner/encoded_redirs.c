/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoded_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:22:43 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 16:22:50 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

/*
*	me acabo de dar cuenta de que en el
*	delirio lo he escrito en ingles, no lo
*	voy a cambiar, un beso.
*
*	echo hello 2> hello.txt
*
*	tok:
*	"hello:2"
*
*	THESE WORK BC ATOI STOPS
*	AT NON-NUMERIC VALUES
*
*	so 1:2 we read 2 first to the end,
*	then the fist part, in the case
*	of 1>&2, in case is file:N, then
*	we zero the : making it a fake terminator
*/

void	redir_to_fd(t_tok *t)
{
	int		fd_in;
	int		fd;
	char	*tozero;

	if (!t || !t->s.data)
		return ;
	tozero = ft_strrchr(t->s.data, ':');
	fd_in = ft_atoi(tozero + 1);
	if (tozero)
		*tozero = 0;
	fd = open(t->s.data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		err_file("couldn't open file\n", t->s.data);
		exit(1);
	}
	dup2(fd, fd_in);
	close(fd);
}

void	append_from(t_tok *t)
{
	int		fd_in;
	int		fd;
	char	*tozero;

	if (!t || !t->s.data)
		return ;
	tozero = ft_strrchr(t->s.data, ':');
	fd_in = ft_atoi(tozero + 1);
	if (tozero)
		*tozero = 0;
	fd = open(t->s.data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		err_file("couldn't open file\n", t->s.data);
		exit(1);
	}
	dup2(fd, fd_in);
	close(fd);
}

void	_redir_nn(t_tok *t)
{
	int		fd;
	int		fd2;
	char	*colon;

	if (!t || !t->s.data)
		return ;
	colon = ft_strrchr(t->s.data, ':');
	fd = ft_atoi(colon + 1);
	fd2 = ft_atoi(t->s.data);
	dup2(fd2, fd);
}
