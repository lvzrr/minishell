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

bool	run_normal_builtin(t_node *tree, t_data *data, t_node *head, int _stdin)
{
	int		ret;
	pid_t	pid;
	int		status;
	int		(*f)(int, char **, t_data *);

	pid = fork();
	if (pid == -1)
		return (err("fork failed\n"), false);
	if (pid == 0)
	{
		if (_stdin != -1)
			(dup2(_stdin, STDIN_FILENO), close(_stdin));
		make_redirs(&tree->u.cmd->redir_v, _stdin);
		ret = EXIT_FAILURE;
		f = match(tree->u.cmd->argv[0]);
		if (f)
			ret = f(tree->u.cmd->argc - 1, tree->u.cmd->argv + 1, data);
		(child_cleanup(head, data, NULL), exit(ret));
	}
	signal_child_running();
	if (waitpid(pid, &status, 0) == -1)
		return (signal_setup(), err("waitpid failed\n"), false);
	load_last_result(WEXITSTATUS(status), data);
	return (signal_setup(), WIFEXITED(status) && !WEXITSTATUS(status));
}

bool	run_cmd(t_node *tree, t_data *data, t_node *head, int _stdin)
{
	pid_t	pid;
	int		status;
	char	**envp;

	if (!ft_strncmp(tree->u.cmd->argv[0], "_sh__builtin_", 13))
		return (run_builtin(tree, data, head, _stdin));
	envp = env2envp(&data->env);
	pid = fork();
	if (pid == -1)
		return (err("fork failed\n"), false);
	if (pid == 0)
	{
		if (_stdin != -1)
			(dup2(_stdin, STDIN_FILENO), close(_stdin));
		make_redirs(&tree->u.cmd->redir_v, _stdin);
		execve(tree->u.cmd->argv[0], tree->u.cmd->argv,
			envp);
		(child_cleanup(head, data, envp), exit(1));
	}
	signal_child_running();
	if (waitpid(pid, &status, 0) == -1)
		return (signal_setup(), free_split(envp), err("waitpid\n"), false);
	load_last_result(WEXITSTATUS(status), data);
	return (signal_setup(), free_split(envp),
		WIFEXITED(status) && !WEXITSTATUS(status));
}

bool	run_pipeline(t_node *tree, t_data *data, t_node *head, int _stdin)
{
	t_pipes	p;
	pid_t	left_pid;
	pid_t	right_pid;
	int		status_left;
	int		status_right;

	p.stdin_fd = _stdin;
	if (pipe(p.pipefd) == -1)
		return (err("pipe failed\n"), false);
	left_pid = fork_left(tree, data, head, &p);
	if (left_pid == -1)
		return (err("fork failed\n"), false);
	right_pid = fork_right(tree, data, head, &p);
	if (right_pid == -1)
		return (err("fork failed\n"), false);
	(close(p.pipefd[0]), close(p.pipefd[1]));
	if (p.stdin_fd != -1)
		close(p.stdin_fd);
	(waitpid(left_pid, &status_left, 0), waitpid(right_pid, &status_right, 0));
	load_last_result(WEXITSTATUS(status_right), data);
	return (WIFEXITED(status_left) && !WEXITSTATUS(status_left)
		&& WIFEXITED(status_right) && !WEXITSTATUS(status_right));
}

bool	run(t_node *tree, t_data *data, t_node *head, int _stdin)
{
	if (tree->type == NODE_OP)
	{
		if (tree->u.op->op == TOK_AND)
		{
			if (!run(tree->u.op->lhs, data, head, _stdin))
				return (false);
			if (!run(tree->u.op->rhs, data, head, _stdin))
				return (false);
			return (true);
		}
		else if (tree->u.op->op == TOK_OR)
		{
			if (!run(tree->u.op->lhs, data, head, _stdin))
				if (!run(tree->u.op->rhs, data, head, _stdin))
					return (false);
			return (true);
		}
		else if (tree->u.op->op == TOK_PIPE)
			return (run_pipeline(tree, data, head, _stdin));
	}
	else
		return (run_cmd(tree, data, head, _stdin));
	return (true);
}
