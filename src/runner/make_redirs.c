/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:23:16 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 15:24:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

/*
*	TIENE PREVALENCIA LA ULTIMA REDIRECCION,
*	recrear multiples redirecciones en cadena
*	es demasiado.
*
*	(por lo menos las de igual tipo, si hay una
*	a stdin y otra a stdout si que se puede)
*/

void	redir_from(t_tok *t, int _stdin)
{
	int	fd;

	if (!t || !t->s.data)
		return ;
	fd = open(t->s.data, O_RDONLY);
	if (fd == -1)
	{
		err_file("couldn't open file\n", t->s.data);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (_stdin != -1)
		close(_stdin);
}

void	redir_to(t_tok *t)
{
	int	fd;

	if (!t || !t->s.data)
		return ;
	fd = open(t->s.data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		err_file("couldn't open file\n", t->s.data);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	append(t_tok *t)
{
	int	fd;

	if (!t || !t->s.data)
		return ;
	fd = open(t->s.data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		err_file("couldn't open file\n", t->s.data);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	make_redirs(t_vec *redir_v, int _stdin)
{
	size_t	i;
	t_tok	*t;

	if (!redir_v || !redir_v->size || !redir_v->alloc_size)
		return ;
	i = 0;
	while (i < redir_v->size)
	{
		t = ft_vec_get_mut(redir_v, i);
		if (t->type == TOK_REDIR_TO)
			redir_to(t);
		else if (t->type == TOK_REDIR_FROM_FD)
			redir_to_fd(t);
		else if (t->type == TOK_APPEND_TO)
			append(t);
		else if (t->type == TOK_APPEND_FROM_FD)
			append_from(t);
		else if (t->type == TOK_REDIR_IN)
			redir_from(t, _stdin);
		else if (t->type == TOK_REDIR_NN)
			_redir_nn(t);
		++i;
	}
}
