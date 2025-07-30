/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:59:05 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 14:59:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

pid_t	fork_left(t_node *tree, t_data *data, t_node *head, t_pipes *p)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		if (p->stdin_fd != -1)
			(dup2(p->stdin_fd, STDIN_FILENO), close(p->stdin_fd));
		(dup2(p->pipefd[1], STDOUT_FILENO), close(p->pipefd[0]),
			close(p->pipefd[1]));
		run(tree->u.op->lhs, data, head, -1);
		ret = ft_atoi(data->lastcommand_res.value.data);
		child_cleanup(head, data, NULL);
		exit(ret);
	}
	return (pid);
}

pid_t	fork_right(t_node *tree, t_data *data, t_node *head, t_pipes *p)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		(dup2(p->pipefd[0], STDIN_FILENO), close(p->pipefd[1]),
			close(p->pipefd[0]));
		run(tree->u.op->rhs, data, head, -1);
		ret = ft_atoi(data->lastcommand_res.value.data);
		child_cleanup(head, data, NULL);
		exit(ret);
	}
	return (pid);
}
