/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:29:24 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 12:30:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSER_H
# define MINI_PARSER_H

# include "mini_lexer.h"

typedef struct s_node	t_node;

typedef enum e_node_t
{
	N_ASSIGN,
	N_CMD,
	N_EXP,
}	t_nodetype;

typedef struct s_exp
{
	t_node		*lhs;
	t_node		*rhs;
	t_toktype	op;
}	t_exp;

typedef struct s_assign
{
	t_tok		varname;
	t_string	value;
}	t_assign;

// args = strings, pre-expanded
typedef struct s_cmd
{
	t_tok		varname;
	t_vec		args;
}	t_cmd;

typedef union u_u
{
	t_assign	assign;
	t_exp		exp;
	t_cmd		cmd;
}	t_u;

typedef struct s_node
{
	t_nodetype	type;
	t_u			u;
}	t_node;

void	collapse_at(t_vec *tokv, t_tok *t);
void	collapse_to_delim(t_vec *tokv, t_tok *t);
void	join_seq(t_vec *tokv);
void	detect_vars(t_vec *tokv);
void	del_unused(t_vec *tokv, size_t idx);
bool	omit_hdoc(t_vec *tokv);
#endif
