/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isstringtoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 03:06:12 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/23 03:07:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	isstringtoken(t_tok	*t)
{
	t_toktype	ty;

	ty = t->type;
	return (ty == TOK_STRING_SQ || ty == TOK_STRING_DQ
		|| ty == TOK_STRING || ty == TOK_IDENT || ty == TOK_STRING_EMPTY);
}
