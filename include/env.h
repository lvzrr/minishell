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

typedef struct s_var
{
	t_string	name;
	t_string	value;
}	t_var;

void	*load_env(t_data *data, char **envp, char *invocation);
void	clean_env(t_vec *env);
void	print_env(t_data *data);
void	load_hot_vars(t_data *data);
t_var	*getvar(char *name, t_vec *env);
void	load_invocation_helper(t_data *data, t_var oldvar);
#endif
