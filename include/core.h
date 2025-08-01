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
# include "builtin.h"
# include "exe.h"
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data	t_data;
typedef struct s_hdoc
{
	t_vec	*hdoc_exit;
	t_vec	*hdoc_ret;
}	t_hdoc;

void		dump_tokenstream(char *s, t_vec *tokv);
bool		read_l(t_string *prompt, t_vec *tokv, bool addaddh);
void		core_loop(t_data *data);
void		check_exit(t_vec *tokv, t_data *data);
void		clean_data(t_data *data);
void		handle_oneliner(t_data *data);
t_data		getopts(int argc, char **argv, char **envp);
void		signal_setup(void);
void		ctrl_c(int s);
bool		check_vec_eq(t_vec *a, t_vec *b);
void		vec_push_hdoc(t_vec *a, t_string *b, size_t *idx);
void		vec_push_tokens_from(t_vec *a, t_vec *b, size_t w);
void		tok_push_space(t_vec *a, size_t idx);
void		vec_push_indexed(t_vec *a, t_string *b, size_t *idx);
void		vec_deep_copy(t_vec *a, t_vec *b, size_t s);
bool		copy_helper(t_vec *a, t_tok *b, t_vec *c, size_t idx);
t_string	check_heredoc(t_vec *tokv, size_t s);
bool		heredoc_routine(t_vec *tokv, t_data *data, size_t idx);
bool		heredoc(t_vec *tokv, t_data *data);
void		hdoc_prompt(t_data *data);
void		default_prompt(t_data *data);
void		*flag_updater(t_data *datap);
bool		read_l_hdoc(t_string *prompt, t_string *line);
void		hdoc_signal_setup(void);
void		phelp(void);
void		s_handler(int signal);
void		tok_push_indexed(t_vec *a, t_string *b, size_t idx);
void		signal_child_running(void);
void		parse_and_run(t_data *data);
t_string	get_hostname(void);
t_data		*fetch_state(t_data *data);
void		copy_helper_nocollapse(t_vec *a, t_tok *b, t_vec *c, size_t idx);
#endif
