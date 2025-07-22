/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hot_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:16:18 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 20:20:35 by jaicastr         ###   ########.fr       */
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

static void	check_valgrind(t_data *data)
{
	t_var	*tmp;

	tmp = getvar("_", &data->env);
	if (tmp && ft_tstr_instr(&tmp->value, "valgrind") > 0)
	{
		ft_fprintf(2, ANSI_YELLOW"(˶°ㅁ°)!! Valgrind-chan? pls don't look"
			" (╥﹏╥), even though i don't leak (¬_¬\")\n"ANSI_RESET);
		data->under_valgrind = true;
	}
}

/*
*	Guarda variables de acceso frecuente como punteros
*	en la estructura global, NO LIBERAR, se liberan con
*	clear_env, NO LIBERAR DESDE NINGUN OTRO SITIO, solo
*	son una REFERENCIA, el owner de la structura es el
*	vector env de t_data.
*
* 	Son una copia suave, asi que cuidado, cualquier cosa
* 	con ellos que no sea lectura usar ft_tstr_clone()
*
*	Por favor no se me diga nada del mensaje de valgrind,
*	se me está yendo la cabeza? posiblemente, antes de
*	que me internen dejadme en paz.
*
*/

void	load_hot_vars(t_data *data)
{
	t_var	*tmp;

	tmp = getvar("PWD", &data->env);
	if (tmp)
		data->pwd = &tmp->value;
	else
		data->pwd = NULL;
	tmp = getvar("PATH", &data->env);
	if (tmp)
		data->path = &tmp->value;
	else
		data->path = NULL;
	tmp = getvar("USER", &data->env);
	if (tmp)
		data->username = &tmp->value;
	else
		data->username = NULL;
	check_valgrind(data);
}
