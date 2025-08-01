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
*
*	Nota:
*	la segunda regla es rara, pero es como hace zsh las cosas,
*	asi que yo no me pronuncio.
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
	else if (idx + 1 < tokv->size && t->type == TOK_DOLLAR
		&& (t + 1)->type == TOK_STRING_DQ)
		t->type = TOK_IDENT;
	else if (t->type == TOK_DOLLAR && idx + 1 == tokv->size)
		collapse_at(tokv, idx);
	else if (t->type == TOK_DOLLAR && idx + 1 < tokv->size
		&& ((t + 1)->type != TOK_IDENT && (t + 1)->type != TOK_LPAREN))
		collapse_at(tokv, idx);
	else if (t->type == TOK_DOLLAR && idx + 1 < tokv->size
		&& (t + 1)->type == TOK_LPAREN)
		t->type = TOK_SUBS_START;
}

/*
 *	Como la minishell no soporta expansion de sustituciones,
 *	y probablemente alguien intente usarlas, por lo menos avisamos
 *	y hacemos algo util con la secuencia, ya que la string puede tener
 *	info valiosa para el usuario, no es lo mejor, por que puede dejar
 *	una string vacia en el stream, pero la vida es dura, quien avisa
 *	no es traidor
 */

static void	warn_subs_behaviour(t_tok *t)
{
	size_t	pos;

	pos = 0;
	while (t->s.len > 1 && pos < t->s.len)
	{
		if (pos + 1 < t->s.len && t->s.data[pos] == '$'
			&& t->s.data[pos + 1] == '(' && ft_strchr(t->s.data + pos, ')'))
		{
			ft_fprintf(2, ANSI_YELLOW"(┛ಠДಠ)┛彡┻━┻ WARNING:"
				" substitution will be parsed as a variable and will"
				" be expanded as such (ง •̀_•́)ง‼\n"ANSI_RESET);
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
	warn_subs_behaviour(t);
	while (t->s.len > 1 && pos < t->s.len)
	{
		if (t->s.data[pos] == '$')
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

bool	detect_vars(t_vec *tokv, t_data *data)
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
			&& (t + 1)->type != TOK_SPACE && i > 1 && (t - 2)->type != TOK_HDOC)
			var_recon(tokv, t, i);
		else if (t->type == TOK_STRING_DQ && i > 1 && (t - 2)->type != TOK_HDOC)
			var_recon_instr(t);
		if (t->type == TOK_DOLLAR)
			t->type = TOK_IDENT;
		i++;
	}
	if (data->debug)
		dump_tokenstream("PRE_EXPANSION", tokv);
	return (expand_vars(tokv, data));
}
