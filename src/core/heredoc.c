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
			return (tokv->size = tokv->size - (tokv->size - i), tokenseq_end);
		}
		i++;
	}
	return ((t_vec){0});
}

static bool	hdoc_loop(t_vec *hdoc_ret, t_vec *hdoc_exit,
	t_vec *tokv, t_data *data)
{
	while (1)
	{
		read_l(&data->prompt, hdoc_ret);
		join_seq(hdoc_ret);
		if (check_vec_eq(hdoc_ret, hdoc_exit))
		{
			ft_tstr_clear(&data->prompt);
			ft_tstr_pushstr(&data->prompt, "ft_sh $ ");
			return (clean_tokenstream(hdoc_ret),
				clean_tokenstream(hdoc_exit), true);
		}
		else
		{
			vec_push_tokens(tokv, hdoc_ret);
			clean_tokenstream(hdoc_ret);
		}
	}
}

bool	heredoc_routine(t_vec *tokv, t_data *data)
{
	t_vec	hdoc_exit;
	t_vec	hdoc_ret;

	hdoc_exit = check_heredoc(tokv);
	if (!hdoc_exit.size
		&& ((t_tok *)ft_vec_peek_last(tokv))->type == TOK_HDOC)
		return (ft_fprintf(2, ANSI_RED"syntax error: "
				ANSI_RESET"no hdoc terminator\n"), false);
	else if (!hdoc_exit.size)
		return (true);
	if (data->debug)
		dump_tokenstream("HDOC", &hdoc_exit);
	ft_tstr_clear(&data->prompt);
	ft_tstr_pushstr(&data->prompt, "hdoc > ");
	hdoc_loop(&hdoc_ret, &hdoc_exit, tokv, data);
	if (data->debug)
		dump_tokenstream("HDOC OUT", tokv);
	return (true);
}
