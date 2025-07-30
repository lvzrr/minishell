/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:30:28 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 13:31:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	*match(char *s)
{
	if (!ft_strncmp(s + 13, "echo", 4))
		return (_sh__builtin_echo);
	if (!ft_strncmp(s + 13, "pwd", 3))
		return (_sh__builtin_pwd);
	if (!ft_strncmp(s + 13, "env", 3))
		return (_sh__builtin_env);
	return (NULL);
}

int	ft_ternary(bool x)
{
	if (x)
		return (0);
	return (1);
}

void	child_cleanup(t_node *tree, t_data *data, char **envp)
{
	if (tree)
		free_tree(tree);
	if (data)
		clean_data(data);
	if (envp)
		free_split(envp);
}

bool	run_builtin(t_node *tree, t_data *data, t_node *head, int _stdin)
{
	int	ret;

	if (!ft_strncmp(tree->u.cmd->argv[0] + 13, "cd", 2))
	{
		ret = _sh__builtin_cd(tree->u.cmd->argc - 1,
				tree->u.cmd->argv + 1, data);
		if (ret == EXIT_FAILURE)
			return (false);
	}
	else if (!ft_strncmp(tree->u.cmd->argv[0] + 13, "exit", 4))
	{
		ret = _sh__builtin_exit(tree->u.cmd->argc - 1,
				tree->u.cmd->argv + 1, data);
		return (false);
	}
	else
		return (run_normal_builtin(tree, data, head, _stdin));
}
