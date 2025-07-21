/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequences.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 06:42:14 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 06:45:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"

/*
*	Carácteres válidos para palabras sueltas
*	dentro del comando
*/

bool	isvalidident(char c)
{
	return (c == '_' || c == '/'
		|| c == '.' || c == '-'
		|| c == '@' || c == '~'
		|| c == '\\' || c == '*'
		|| c == '\'' || c == '\"'
		|| c == '+' || ft_isalnum(c));
}

/*
*	Esto esta para casos como la ñ,
*	+, etc ..., para que no se rompa
*	cuando le metes cosas no-ascii o
*	operaciones que no soportamos, lo
*	interpreta como una palabra suelta y ya
*/

bool	isunsupported(char c)
{
	return (!isvalidident(c) && !isvalidop(c));
}

/*
*	Operadores, poco que explicar aquí
*/

bool	isvalidop(char c)
{
	return (c == '&' || c == '|'
		|| c == '=' || c == '<'
		|| c == '>' || c == ';'
		|| c == '$' || c == '?'
		|| c == ')' || c == '(');
}
