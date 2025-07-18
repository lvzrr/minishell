/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:50:08 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/18 19:50:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

size_t	look4hdoc(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			++i;
			continue ;
		}
		if (t->type == TOK_HDOC)
			return (i);
		i++;
	}
	return (SIZE_MAX);
}

t_vec	check_heredoc(t_vec *tokv)
{
	size_t	i;
	t_tok	*t;
	t_vec	tokenseq_end;

	i = 0;
	while (i + 1 < tokv->size)
	{
		t = (t_tok *)ft_vec_get(tokv, i);
		if (!t || !t->s.data || !t->s.len)
		{
			++i;
			continue ;
		}
		if (t->type == TOK_HDOC)
		{
			tokenseq_end = ft_vec(tokv->size - i, sizeof(t_tok));
			vec_push_tokens_from(&tokenseq_end, tokv, i + 1);
			collapse_at(tokv, t);
			collapse_at(tokv, t);
			return (tokenseq_end);
		}
		i++;
	}
	return ((t_vec){0});
}

static bool	hdoc_loop(t_vec *hdoc_exit, size_t idx,
	t_vec *tokv, t_data *data)
{
	t_vec	hdoc_ret;

	while (1)
	{
		read_l(&data->prompt, &hdoc_ret);
		if (!hdoc_ret.size)
			return (clean_tokenstream(hdoc_exit),
				default_prompt(data), true);
		join_seq(&hdoc_ret);
		if (check_vec_eq(&hdoc_ret, hdoc_exit))
			return (clean_tokenstream(&hdoc_ret),
				clean_tokenstream(hdoc_exit), default_prompt(data)
				, true);
		else
		{
			vec_push_tokens(tokv, &hdoc_ret, idx++);
			if (data->debug)
				dump_tokenstream("HDOC STREAM", tokv);
		}
	}
}

bool	heredoc_routine(t_vec *tokv, t_data *data)
{
	size_t	idx;
	t_vec	hdoc_exit;

	if (!tokv || !tokv->size || !tokv->data)
		return (true);
	idx = look4hdoc(tokv);
	hdoc_exit = check_heredoc(tokv);
	if (!hdoc_exit.size
		&& ((t_tok *)ft_vec_peek_last(tokv))->type == TOK_HDOC)
		return (ft_fprintf(2, ANSI_RED"syntax error: "
				ANSI_RESET"no hdoc terminator\n"), false);
	else if (!hdoc_exit.size)
		return (true);
	hdoc_prompt(data);
	hdoc_loop(&hdoc_exit, idx, tokv, data);
	if (data->debug)
		dump_tokenstream("HDOC OUT", tokv);
	return (true);
}
