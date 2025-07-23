/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 05:52:16 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/17 05:52:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_lexer.h"
#include "mini_parser.h"

/*
*	Esta funcion limpia todos los
*	elementos del vector, limpiando
*	antes la string que contienen dentro
*/

void	clean_tokenstream(t_vec *v)
{
	while (v->size)
		collapse_at(v, 0);
}

/*
*	Esto existe solo por la norminette, que la
*	linea donde la llamo es muy grande si no
*/

static void	clean_err(char *str, t_vec *out)
{
	write(2, str, ft_strlen(str));
	clean_tokenstream(out);
}

/*
*	Esta funcion tb existe solo por norminette,
*	pone las cuentas de los parentesis en su
*	sitio para detectar cuando estan mal
*	cerrados.
*/

static void	manage_paren(t_tok *t, size_t *paren_l)
{
	if (!t || !t->s.data || !t->s.len)
		return ;
	if (t->type == TOK_LPAREN)
		(*paren_l)++;
	else if (t->type == TOK_RPAREN)
		(*paren_l)--;
}

/*
*	funcion principal del lexer, devuelve el vector
*	dando a la funcion que la llame la pertenencia
*	de la estructura, le das un string, come por
*	secciones con una pseudo-maquina de estados,
*	que realmente son funciones que si no les toca
*	lo suyo pasan a la siguiente, y devuelve un vector
*	diferente que contiene tokens que hay en esa string
*/

bool	lex(t_string *s, t_vec *tokv)
{
	size_t	offst;
	size_t	paren_l;

	if (!s || !s->len)
		return (false);
	paren_l = 0;
	offst = 0;
	while (offst < s->len)
	{
		try_lexas_spc(s, tokv, &offst);
		if (offst == SIZE_MAX)
			return (clean_tokenstream(tokv), false);
		if (!try_lexas_qs(s, tokv, &offst))
			return (clean_tokenstream(tokv), false);
		try_lexas_ident(s, tokv, &offst);
		try_lexas_comment(s, &offst);
		try_lexas_op(s, tokv, &offst);
		manage_paren((t_tok *)ft_vec_peek_last(tokv), &paren_l);
	}
	if (paren_l != 0)
		return (clean_err(ANSI_RED"error: "ANSI_RESET"unclosed paren\n", tokv),
			false);
	return (true);
}
