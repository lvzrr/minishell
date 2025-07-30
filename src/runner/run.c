/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:55:09 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 11:55:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

bool	run_cmd(t_node *tree, t_data *data, t_node *head)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env2envp(&data->env);
	pid = fork();
	if (pid == -1)
		return (err("fork failed\n"), false);
	if (pid == 0)
	{
		execve(tree->u.cmd->argv[0], tree->u.cmd->argv,
			envp);
		(clean_data(data), free_split(envp), free_tree(head));
		exit(1);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (err("waitpid failed\n"), false);
	return (free_split(envp), WIFEXITED(status) && !WEXITSTATUS(status));
}

bool	run(t_node *tree, t_data *data, t_node *head)
{
	if (tree->type == NODE_OP)
	{
		if (tree->u.op->op == TOK_AND)
		{
			if (!run(tree->u.op->lhs, data, head))
				return (false);
			if (!run(tree->u.op->rhs, data, head))
				return (false);
			return (true);
		}
		else if (tree->u.op->op == TOK_OR)
		{
			if (!run(tree->u.op->lhs, data, head))
				if (!run(tree->u.op->rhs, data, head))
					return (false);
			return (true);
		}
	}
	else
		return (run_cmd(tree, data, head));
	return (true);
}
