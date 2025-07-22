/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:04:13 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 01:04:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

/*
*	reconoce variables en el stream, pero que no esten
*	en dobles comillas, cualquier secuencia como $"hola" o
*	$ solo, retira el dollar e interpreta lo que haya detras
*/

static void	var_recon(t_vec *tokv, t_tok *t, size_t idx)
{
	if (t->type == TOK_DOLLAR && idx + 1 < tokv->size
		&& (t + 1)->type == TOK_IDENT)
	{
		ft_memswap(t, t + 1, sizeof(t_tok));
		t->type = TOK_VAR;
		collapse_at(tokv, idx + 1);
	}
	else if (t->type == TOK_DOLLAR && idx + 1 == tokv->size)
		collapse_at(tokv, idx);
	else if (t->type == TOK_DOLLAR && idx + 1 < tokv->size
		&& ((t + 1)->type != TOK_IDENT && (t + 1)->type != TOK_LPAREN))
		collapse_at(tokv, idx);
	else if (t->type == TOK_DOLLAR && idx + 1 < tokv->size
		&& (t + 1)->type == TOK_LPAREN)
		t->type = TOK_SUBSH_START;
}

/*
 *	Como la minishell no soporta expansion de subshells,
 *	y probablemente alguien intente usarlas, por lo menos avisamos
 */

static void	warn_subshell_behaviour(t_tok *t)
{
	size_t	pos;

	pos = 0;
	while (t->s.len > 1 && pos < t->s.len)
	{
		if (pos + 1 < t->s.len && t->s.data[pos] == '$'
			&& t->s.data[pos + 1] == '(' && ft_strchr(t->s.data + pos, ')'))
		{
			ft_fprintf(2, ANSI_YELLOW"WARNING: subshell will be parsed"
				" as a variable and will be expanded as such\n"ANSI_RESET);
		}
		pos++;
	}
}

/*
*	Busca dólares en cada string doble del stream, si las hay,
*	mira que no esten escapadas, si estan escapadas, quita el
*	escape para que quede solo el dollar sin cambiar el sentito
*	del token, si un string doble tiene un $ como primer carácter
*	y no tiene espacios, interpreta el token como una variable
*	directamente.
*/

static void	var_recon_instr(t_tok *t)
{
	size_t	pos;

	pos = 0;
	warn_subshell_behaviour(t);
	while (t->s.len > 1 && pos < t->s.len)
	{
		if (pos == 0 && t->s.data[pos] == '$' && ft_s_isblob(t->s.data + 1))
		{
			t->type = TOK_VAR;
			remove_char(&t->s, pos);
			return ;
		}
		if (pos >= 1)
		{
			t->type = TOK_STRING_TOEXPAND;
			return ;
		}
		pos++;
	}
}

/*
*	Simplemente recorre el array buscando cosas que poder
*	interpretar y los manda a las funciones de arriba.
*/

void	detect_vars(t_vec *tokv)
{
	t_tok	*t;
	size_t	i;

	i = 0;
	while (i < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (i + 1 < tokv->size && t->type == TOK_DOLLAR
			&& (t + 1)->type != TOK_SPACE)
			var_recon(tokv, t, i);
		else if (t->type == TOK_STRING_DQ)
			var_recon_instr(t);
		if (t->type == TOK_DOLLAR)
			t->type = TOK_IDENT;
		i++;
	}
}

/*
*	Cuando estamos dentro de un heredoc y se introduce la
*	secuencia '<<', hay que interpretarla como un string
*	normal, asi que recorre todo en busca de ese token y si lo
*	hay le cambia el tipo a un identificador para que so
*	corra otro heredoc a partir de él.
*/

bool	omit_hdoc(t_vec *tokv)
{
	size_t		i;
	size_t		c;
	t_tok		*t;

	i = 0;
	c = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			i++;
			continue ;
		}
		if (t->type == TOK_HDOC)
		{
			t->type = TOK_IDENT;
			c++;
		}
		i++;
	}
	return (c > 0);
}
