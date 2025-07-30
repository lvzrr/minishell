/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:22:50 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/26 00:23:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	isoperator(t_tok *t)
{
	if (!t)
		return (false);
	return (t->type == TOK_AND || t->type == TOK_OR || t->type == TOK_SCOLON
		|| t->type == TOK_PIPE || t->type == TOK_AMPER);
}
