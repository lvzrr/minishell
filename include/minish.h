/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:56 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:14:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# include "lft.h"
# include "mini_lexer.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// TODO: poner aqui el path, el
// env, etc...
typedef struct s_data
{
	t_string	prompt;
	char		**envp;
	bool		debug;
}	t_data;

void	core_loop(t_data *data);

#endif
