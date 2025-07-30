/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:13:25 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 13:31:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "mini_parser.h"
# include "core.h"

typedef struct s_node	t_node;

bool	run(t_node *tree, t_data *data, t_node *tree_head);
void	*match(char *s);
bool	run_builtin(t_node *tree, t_data *data, t_node *head);
bool	run_normal_builtin(t_node *tree, t_data *data, t_node *head);
#endif
