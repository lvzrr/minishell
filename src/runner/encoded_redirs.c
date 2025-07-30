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
*	  A ver, estas se van al
*	  último ':', que es el que
*	  inyectamos en el encoding,
*	  entonces, si lo de antes es
*	  un número lo dejamos (atoi para solo),
*	  pero si no, hay que terminar la
*	  string el el ':' artificial,
*	  ya que si no no leeriamos el
*	  archivo que toca.
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
