/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:31:22 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/31 21:32:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

void	check_forbidden_unset(t_tok *t, size_t i, t_data *data)
{
	if ((t + i)->type == TOK_IDENT && !ft_strcmp((t + i)->s.data, "PATH"))
		(warn("unsetting sensible variable\n"), data->path = NULL);
	else if ((t + i)->type == TOK_IDENT && !ft_strcmp((t + i)->s.data, "PWD"))
		(warn("unsetting sensible variable\n"), data->pwd = NULL);
	else if ((t + i)->type == TOK_IDENT && !ft_strcmp((t + i)->s.data, "USER"))
		(warn("unsetting sensible variable\n"), data->username = NULL);
}
