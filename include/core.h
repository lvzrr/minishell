/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:01:14 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 11:01:16 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "tstr.h"
# include "vec.h"
# include "unistd.h"

// TODO: poner aqui el path, el
// env, etc...
typedef struct s_data
{
	t_string	prompt;
	char		**envp;
	bool		debug;
}	t_data;

void	dump_tokenstream(t_vec *tokv);
void	read_l(t_string *prompt, t_vec *tokv);
void	core_loop(t_data *data);
bool	check_exit(t_vec *tokv);
void	clean_data(t_data *data);
t_data	getopts(int argc, char **argv, char **envp);
#endif
