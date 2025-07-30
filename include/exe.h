/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:13:25 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/30 13:31:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "mini_parser.h"
# include "core.h"

typedef struct s_node	t_node;

typedef struct s_pipes
{
	int		stdin_fd;
	int		pipefd[2];
}	t_pipes;

bool	run(t_node *tree, t_data *data, t_node *tree_head, int f);
void	*match(char *s);
bool	run_builtin(t_node *tree, t_data *data, t_node *head, int f);
bool	run_normal_builtin(t_node *tree, t_data *data, t_node *head, int f);
int		ft_ternary(bool x);
void	child_cleanup(t_node *tree, t_data *data, char **envp);
pid_t	fork_left(t_node *tree, t_data *data, t_node *head, t_pipes *p);
pid_t	fork_right(t_node *tree, t_data *data, t_node *head, t_pipes *p);
void	make_redirs(t_vec *redir_v, int _stdin);
void	redir_to_fd(t_tok *t);
void	append_from(t_tok *t);
void	_redir_nn(t_tok *t);
#endif
