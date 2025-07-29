/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:59:05 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/29 18:59:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_OP && node->u.op)
	{
		free_tree(node->u.op->lhs);
		free_tree(node->u.op->rhs);
		ft_free((void **)&node->u.op);
	}
	else if (node->type == NODE_CMD && node->u.cmd)
	{
		if (node->u.cmd->argv)
			free_split(node->u.cmd->argv);
		if (node->u.cmd->redir_v.data)
		{
			clean_tokenstream(&node->u.cmd->redir_v);
			ft_vec_free(&node->u.cmd->redir_v);
		}
		ft_free((void **)&node->u.cmd);
	}
	ft_free((void **)&node);
}
