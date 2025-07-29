/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:22:35 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/29 23:25:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

t_node	*parse(t_vec *tokv, t_data *data)
{
	t_node	*tree;

	tree = parse_expr(tokv);
	if (tokv->size && tree)
		return (free_tree(tree), err("operators '&&' and '||' MUST "
				"be wrapped in parenthesis\n"), NULL);
	if (data->debug)
	{
		ft_fprintf(2, ANSI_MAGENTA"==TREE==\n"
			ANSI_RESET);
		print_tree(tree, 0);
	}
	return (tree);
}
