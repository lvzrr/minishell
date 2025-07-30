/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:46:19 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 19:47:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	parse_and_run(t_data *data)
{
	t_node	*tree;

	tree = NULL;
	tree = parse(&data->tokv, data);
	if (!tree)
		return ;
	run(tree, data, tree, -1);
	free_tree(tree);
}
