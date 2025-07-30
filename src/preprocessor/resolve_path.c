/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 22:09:49 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/28 22:12:51 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parser.h"

bool	exists_executable(t_tok *t)
{
	if (access(t->s.data, F_OK) == -1)
		return (err_file("no such file or directory\n", t->s.data),
			false);
	if (access(t->s.data, X_OK) == -1)
		return (err_file("not an executable or not enough perms\n",
				t->s.data), false);
	if (is_dir(t->s.data))
		return (err_file("is a directory\n", t->s.data), false);
	return (true);
}

char	*look4bin(char *name, t_data *data)
{
	char	**paths;
	char	*tmp_escape;
	char	*tmp;
	size_t	i;

	if (!data->path)
		return (err("fatal: no path\n"), NULL);
	paths = ft_split(data->path->data, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp_escape = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp_escape, name);
		ft_free((void **)&tmp_escape);
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
			return (free_split(paths), tmp);
		ft_free((void **)&tmp);
		++i;
	}
	return (free_split(paths), NULL);
}

static bool	resolve(t_tok *t, t_data *data)
{
	char	*path_lookup;

	if (!t->s.data || !*t->s.data)
		return (err("'' not a command\n"), false);
	if (!ft_strncmp(t->s.data, "./", 2) || *t->s.data == '/')
		return (exists_executable(t));
	path_lookup = look4bin(t->s.data, data);
	if (!path_lookup)
		return (ft_free((void **)&path_lookup),
			err_file("not a command\n", t->s.data), false);
	(ft_tstr_clear(&t->s), ft_tstr_pushstr(&t->s, path_lookup));
	return (ft_free((void **)&path_lookup), true);
}

bool	manage_builtin(t_tok *t)
{
	t_string	tmp;

	if (!ft_strncmp(t->s.data, "_sh__builtin_", 13))
		return (true);
	if (!ft_strcmp(t->s.data, "echo")
		|| !ft_strcmp(t->s.data, "cd")
		|| !ft_strcmp(t->s.data, "exit")
		|| !ft_strcmp(t->s.data, "pwd")
		|| !ft_strcmp(t->s.data, "env"))
	{
		tmp = ft_tstr_clone(&t->s);
		ft_tstr_clear(&t->s);
		ft_tstr_pushslice(&t->s, "_sh__builtin_", 13);
		ft_tstr_pushslice(&t->s, tmp.data, tmp.len);
		ft_tstr_free(&tmp);
		return (true);
	}
	return (false);
}

bool	resolve_path(t_vec *tokv, t_data *data)
{
	size_t	i;
	t_tok	*t;

	i = 0;
	while (i < tokv->size)
	{
		t = ft_vec_get_mut(tokv, i);
		if (t && ((i == 0 && t->type != TOK_LPAREN) || (i >= 1
					&& isstringtoken(t) && (isoperator(t - 1)
						|| (t - 1)->type == TOK_LPAREN))) && manage_builtin(t))
			;
		else if (t && ((i == 0 && t->type != TOK_LPAREN) || (i >= 1
					&& isstringtoken(t) && (isoperator(t - 1)
						|| (t - 1)->type == TOK_LPAREN))) && !resolve(t, data))
			return (false);
		if (t && t->type == TOK_REDIR_IN && !check_redir(t))
			return (false);
		++i;
	}
	if (data->debug)
		dump_tokenstream("PATH RESOLUTION", &data->tokv);
	return (true);
}
