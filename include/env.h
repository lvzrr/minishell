/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 03:02:27 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/21 03:02:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "core.h"
# include "conv.h"

typedef struct s_data	t_data;

void	*load_env(t_data *data, char **envp, char *invocation);
void	clean_env(t_vec *env);
void	print_env(t_data *data, bool print_fast);
void	load_hot_vars(t_data *data);
t_var	*getvar(char *name, t_vec *env, t_data *data);
void	load_invocation_helper(t_data *data, t_var oldvar);
void	set_shell_var(t_data *data);
void	load_var(t_string *name, t_string *value, t_data *data);
void	free_var(t_var *var);
char	**env2envp(t_vec *env);
void	check_valgrind(t_data *data);
#endif
