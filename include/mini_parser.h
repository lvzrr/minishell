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
# include "core.h"
# include "conv.h"
# include "env.h"
# include <dirent.h>

typedef struct s_node	t_node;

typedef struct s_data
{
	t_string	prompt;
	char		**envp;
	bool		debug;
	bool		oneliner;
	bool		phelp;
	bool		hdoc_terminate;
	bool		under_valgrind;
	bool		exit;
	bool		segfault;
	char		*invocation;
	t_string	oneliner_s;
	t_vec		tokv;
	t_vec		env;
	t_string	*path;
	t_string	*username;
	t_string	*pwd;
}	t_data;

typedef enum e_nodetype
{
	NODE_OP,
	NODE_CMD,
}	t_nodetype;

typedef struct s_node	t_node;
typedef struct s_opnode	t_opnode;
typedef struct s_cmd	t_cmd;

/*
 *	Union del nodo per se,
 *	esto es lo que tiene la "chicha"
 *	del arbol.
 *
 * 	podemos tener:
 * 		- un comando
 * 		- una subshell (podemos no soportarlas,
 * 						pero ya que pillamos parentesis
 * 						pues por que no, ya veremos)
 *
 * 		- un operador con dos ramas, ej (echo "hello" | cat -e):
 *				     TOK_PIPE
 *					/		 \
 * 		echo "hello"		  cat -e
 *
 * 		aunque estas ramas pueden ser otros
 * 		operadores, etc
 */

typedef union u_node
{
	t_cmd		*cmd;
	t_opnode	*op;
}	t_u;

/*
 *	el comando y sus respectivas
 *	redirecciones
 */

typedef struct s_cmd
{
	t_vec		redir_v;
	char		**argv;
	size_t		argc;
}	t_cmd;

/*
 *	tipo de nodo + nodo,
 *	lo mismo, primero se mira
 *	el tipo y luego se llama
 *	a la funcion correspondiente
 *	encima del nodo.
 */

typedef struct s_node
{
	t_nodetype	type;
	t_u			u;
}	t_node;

/*
 *	Nodo de operacion, el diagrama
 *	está arriba.
 */

typedef struct s_opnode
{
	t_toktype	op;
	t_node		*rhs;
	t_node		*lhs;
}	t_opnode;

void	collapse_at(t_vec *tokv, size_t i);
void	collapse_to_delim(t_vec *tokv, t_tok *t);
bool	pre_process(t_vec *tokv, t_data *data);
bool	detect_vars(t_vec *tokv, t_data *data);
void	del_unused(t_vec *tokv, size_t idx);
void	omit_hdoc(t_vec *tokv);
bool	expand_vars(t_vec *tokv, t_data *data);
ssize_t	get_dollar_notscaped(t_tok *t, size_t *offset);
void	remove_scaping_singledollar(t_tok *t);
void	delete_subs(t_vec *tokv, size_t start);
bool	manage_redirs(t_vec *tokv);
bool	isstringtoken(t_tok	*t);
bool	try_collapse_redir(t_tok *t, t_vec *tokv, size_t i);
bool	catch_forbidden(t_vec *tokv);
bool	isredirect(t_toktype t);
bool	rr(t_tok *t, t_vec *tokv, size_t i);
bool	rl(t_tok *t, t_vec *tokv, size_t i);
bool	rapp(t_tok *t, t_vec *tokv, size_t i);
bool	rd_nn(t_tok *t, t_vec *tokv, size_t i);
bool	is_preceded_by_ident(t_tok *t);
bool	delete_redundant(t_vec *tokv, size_t i);
size_t	varexp_parser(t_tok **t, t_vec *tokv, t_data *data, size_t *i);
void	clean_operators(t_vec *tokv);
bool	isoperator(t_tok *t);
void	expand_string(t_tok *t, t_data *data);
void	expand_var(t_tok *t, t_data *data);
void	look_and_insert(t_tok *t, size_t pos,
			t_string *vname, t_data *data);
bool	check_interpret(t_tok *t, size_t i);
bool	pre_clean(t_vec *tokv);
bool	unset_builtin(t_tok *t, t_vec *tokv, t_data *data, size_t i);
void	syntax_err(char *msg);
bool	expand_wildcard(t_tok *t, t_vec *tokv, size_t i);
void	err_file(char *msg, char *fname);
size_t	getcmdlen(t_vec *tokv);
t_vec	create_redirs(t_tok *t, t_vec *tokv);
t_node	*parse_cmd(t_vec *tokv);
t_node	*parse_paren_expr(t_vec *tokv);
t_node	*parse_expr(t_vec *tokv);
void	free_tree(t_node *node);
void	print_tree(t_node *node, int depth);
void	err(char *msg);
#endif
