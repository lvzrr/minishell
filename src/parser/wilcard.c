/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:19:14 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 17:20:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	wildcard_helper(t_vec *tokv, size_t i, DIR *directory,
	struct dirent *dir_entry)
{
	size_t			c;
	t_string		holder;

	c = 0;
	dir_entry = (struct dirent *) 1;
	while (dir_entry)
	{
		dir_entry = readdir(directory);
		if (!dir_entry || *dir_entry->d_name == '.')
			continue ;
		holder = ft_tstr_from_cstr(dir_entry->d_name);
		(tok_push_indexed(tokv, &holder, i++), tok_push_space(tokv, i++));
		(ft_tstr_free(&holder), dir_entry = readdir(directory));
		++c;
	}
	closedir(directory);
	if (!c)
		return (false);
	return (true);
}

bool	expand_wildcard(t_tok *t, t_vec *tokv, size_t i)
{
	struct dirent	*dir_entry;
	DIR				*directory;

	directory = opendir(".");
	if (!directory)
	{
		(ft_tstr_clear(&t->s), t->type = TOK_STRING_EMPTY);
		return (false);
	}
	collapse_at(tokv, i);
	dir_entry = NULL;
	return (wildcard_helper(tokv, i, directory, dir_entry));
}
