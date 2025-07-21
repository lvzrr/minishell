/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:01:14 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 19:51:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "tstr.h"
# include "vec.h"
# include "mini_parser.h"
# include "mini_lexer.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// TODO: poner aqui el path, el
// env, etc...
typedef struct s_data
{
	t_string	prompt;
	char		**envp;
	bool		debug;
	bool		oneliner;
	bool		phelp;
	t_string	oneliner_s;
}	t_data;

typedef struct s_hdoc
{
	t_vec	*hdoc_exit;
	t_vec	*hdoc_ret;
}	t_hdoc;

void	dump_tokenstream(char *s, t_vec *tokv);
void	read_l(t_string *prompt, t_vec *tokv, bool addaddh);
void	core_loop(t_data *data);
bool	check_exit(t_vec *tokv);
void	clean_data(t_data *data);
void	handle_oneliner(t_data *data);
t_data	getopts(int argc, char **argv, char **envp);
void	signal_setup(void);
void	ctrl_c(int s);
bool	check_vec_eq(t_vec *a, t_vec *b);
void	vec_push_tokens(t_vec *a, t_vec *b, size_t *idx);
void	vec_push_tokens_from(t_vec *a, t_vec *b, size_t w);
t_vec	check_heredoc(t_vec *tokv, size_t s);
bool	heredoc_routine(t_vec *tokv, t_data *data, size_t idx);
bool	heredoc(t_vec *tokv, t_data *data);
void	hdoc_prompt(t_data *data);
void	default_prompt(t_data *data);
void	phelp(void);
#endif
