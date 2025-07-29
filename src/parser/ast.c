/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:29:48 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/29 17:30:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

t_node	*parse_cmd(t_vec *tokv)
{
	t_tok	*tok;
	t_node	*node;
	size_t	cmdlen;
	size_t	i;

	node = ft_alloc(sizeof(t_node));
	node->type = NODE_CMD;
	cmdlen = getcmdlen(tokv);
	if (cmdlen == 0)
		return (ft_free((void **)&node), err("expected command\n"),
			NULL);
	node->u.cmd = ft_calloc(1, sizeof(t_cmd));
	node->u.cmd->argv = ft_calloc(cmdlen + 1, sizeof(char *));
	tok = ft_vec_get_mut(tokv, 0);
	i = 0;
	while (tokv->size && i < cmdlen)
	{
		node->u.cmd->argv[i++] = ft_strdup(tok->s.data);
		node->u.cmd->argc++;
		collapse_at(tokv, 0);
	}
	if (tokv->size && isredirect(tok->type))
		node->u.cmd->redir_v = create_redirs(tok, tokv);
	return (node);
}

t_node	*parse_paren_expr(t_vec *tokv)
{
	t_tok	*tok;
	t_node	*node;

	tok = ft_vec_get_mut(tokv, 0);
	if (!tok || tok->type != TOK_LPAREN)
		return (err("expected '('\n"), NULL);
	node = ft_alloc(sizeof(t_node));
	node->type = NODE_OP;
	collapse_at(tokv, 0);
	node->u.op = ft_calloc(1, sizeof(t_opnode));
	node->u.op->lhs = parse_expr(tokv);
	if (!node->u.op->lhs)
		return (free_tree(node), err("no lhs\n"), NULL);
	if (!tokv->size || (tok->type != TOK_AND && tok->type != TOK_OR))
		return (free_tree(node), err_file("unexpected op\n", tok->s.data),
			NULL);
	node->u.op->op = tok->type;
	collapse_at(tokv, 0);
	node->u.op->rhs = parse_expr(tokv);
	if (!node->u.op->rhs)
		return (free_tree(node), err("no rhs\n"), NULL);
	if (!tokv->size || tok->type != TOK_RPAREN)
		return (free_tree(node), err("expected ')'\n"), NULL);
	return (collapse_at(tokv, 0), node);
}

t_node	*parse_expr(t_vec *tokv)
{
	t_tok	*tok;

	tok = ft_vec_get_mut(tokv, 0);
	if (!tok)
		return (err("unexpected EOF\n"), NULL);
	if (tok->type == TOK_LPAREN)
		return (parse_paren_expr(tokv));
	else if (isstringtoken(tok))
		return (parse_cmd(tokv));
	else
		return (err("unexpected token\n"), NULL);
}
