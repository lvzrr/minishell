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

bool	check_forbidden_unset(t_tok *t, size_t i)
{
	if ((t + i)->type == TOK_IDENT && !ft_strcmp((t + i)->s.data, "PATH"))
		return (err("cannot unset $PATH, variable is protected\n"), false);
	if ((t + i)->type == TOK_IDENT && !ft_strcmp((t + i)->s.data, "PWD"))
		return (err("cannot unset $PWD, variable is protected\n"), false);
	if ((t + i)->type == TOK_IDENT && !ft_strcmp((t + i)->s.data, "USER"))
		return (err("cannot unset $USER, variable is protected\n"), false);
	return (true);
}
