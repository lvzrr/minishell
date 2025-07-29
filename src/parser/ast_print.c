/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:01:48 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/29 20:02:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	print_indent(int depth)
{
	while (depth-- > 0)
		write(2, "  ", 2);
}

void	print_argv(char **argv)
{
	size_t	i;

	i = 0;
	write(2, "[", 1);
	while (argv && argv[i])
	{
		if (i > 0)
			write(2, ", ", 2);
		ft_fprintf(2, "%s", argv[i]);
		i++;
	}
	write(2, "] ", 2);
}

void	print_redirs(t_vec *v)
{
	size_t	i;

	i = 0;
	write(2, "[", 1);
	while (i < v->size)
	{
		if (i > 0)
			write(2, ", ", 2);
		ft_fprintf(2, "[%s, '%s']", get_token_pretty(
				((t_tok *)v->data + i)->type),
			((t_tok *)v->data + i)->s.data);
		i++;
	}
	write(2, "] ", 2);
}

void	print_tree(t_node *node, int depth)
{
	if (!node)
	{
		print_indent(depth);
		write(2, "(null)\n", 8);
		return ;
	}
	if (node->type == NODE_CMD)
	{
		print_indent(depth);
		ft_fprintf(2, ANSI_MAGENTA"CMD: "ANSI_RESET);
		print_argv(node->u.cmd->argv);
		ft_fprintf(2, ANSI_MAGENTA"REDIRS: "ANSI_RESET);
		print_redirs(&node->u.cmd->redir_v);
		(ft_fprintf(2, ANSI_MAGENTA"ARGC: "ANSI_RESET"%d",
				node->u.cmd->argc), write(2, "\n", 1));
	}
	else if (node->type == NODE_OP)
	{
		print_indent(depth);
		ft_fprintf(2, ANSI_MAGENTA"OP: %s\n"ANSI_RESET,
			get_token_pretty(node->u.op->op));
		print_tree(node->u.op->lhs, depth + 1);
		print_tree(node->u.op->rhs, depth + 1);
	}
}
