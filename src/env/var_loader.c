/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:26:36 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/24 21:32:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
*	Funcion que busca variables en el entorno
*/

t_var	*getvar(char *name, t_vec *env)
{
	t_var		*v;
	size_t		i;

	i = 0;
	while (i < env->size)
	{
		v = ft_vec_get_mut(env, i++);
		if (v && !ft_strcmp(name, v->name.data))
			return (v);
	}
	return (NULL);
}

/*
*	Las variables se cogen de los tstr de dentro del stream
*	de tokens, asi que se clonan, ya que el stream de tokens
*	se libera por su cuenta, y al pasarlas al env, este también
*	se libera solo al final del programa.
*/

void	load_var(t_string *name, t_string *value, t_vec *env)
{
	t_var		*v;
	t_var		newv;

	v = getvar(name->data, env);
	if (v)
	{
		ft_tstr_clear(&v->value);
		ft_tstr_pushslice(&v->value, value->data, value->len);
		return ;
	}
	newv = (t_var){.name = ft_tstr_clone(name), .value = ft_tstr_clone(value)};
	ft_vec_push(env, &newv, 1);
}
