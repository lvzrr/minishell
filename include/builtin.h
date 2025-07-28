/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:21:27 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 22:52:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "vec.h"
# include "core.h"
# include "cstr.h"
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data	t_data;

int		_sh__builtin_cd(int argc, char **argv, t_data *data);
int		_sh__builtin_echo(int argc, char **argv, t_data *data);
int		_sh__builtin_pwd(int argc, char **argv, t_data *data);
int		_sh__builtin_export(int argc, char **argv, t_data *data);
int		_sh__builtin_unset(int argc, char **argv, t_data *data);
int		_sh__builtin_env(int argc, char **argv, t_data *data);
int		_sh__builtin_exit(int argc, char **argv, t_data *data);
int		_sh__builtin_exit(int argc, char **argv, t_data *data);

// helpers echo

bool	manage_scape(char *string, size_t *i, size_t len);

#endif