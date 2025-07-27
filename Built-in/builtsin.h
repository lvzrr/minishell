/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:21:27 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 12:21:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTSINS_H
# define BUILTSINS_H

# include "vec.h"
# include "shell_data.h" 
#include <unistd.h>     // Para write()
#include <stdbool.h>    // Para bool, true, false

typedef int(*t_builtin_fn)(t_vec *argv, t_data *data);

typedef struct s_builtin
{
    char    *name;
    t_buildin_fn    fn;
} t_buildin;

int buildin_cd(t_vec *argv, t_data *data);
int buildin_echo(t_vec *argv, t_data *data);
int buildin_pwd(t_vec *argv, t_data *data);
int buildin_export(t_vec *argv, t_data *data);
int buildin_unset(t_vec *argv, t_data *data);
int buildin_env(t_vec *argv, t_data *data);
int buildin_exit(t_vec *argv, t_data *data);

#endif