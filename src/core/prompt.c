/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:31:37 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/19 00:32:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	append_path_currdir(t_string *prompt, t_string *pwd)
{
	char	*lastslash;

	if (!pwd)
	{
		ft_tstr_pushstr(prompt, "????");
		return ;
	}
	lastslash = ft_strrchr(pwd->data, '/');
	if (lastslash)
		ft_tstr_pushstr(prompt, lastslash + 1);
	else
		ft_tstr_pushslice(prompt, pwd->data, pwd->len);
}

void	try_user(t_data *data)
{
	t_var	*user;

	user = getvar("USER", &data->env, data);
	if (!user || !user->value.data)
	{
		ft_tstr_pushslice(&data->prompt, "?????", 5);
		ft_tstr_pushstr(&data->prompt, "\001"ANSI_RESET"\002");
		return ;
	}
	ft_tstr_pushstr(&data->prompt, user->value.data);
	ft_tstr_pushstr(&data->prompt, "\001"ANSI_RESET"\002");
}

void	pushcolor(t_string *toput, t_data *data)
{
	if (!data || !toput || !data->lastcommand_res.value.data)
		return ;
	if (!ft_strcmp(data->lastcommand_res.value.data, "0"))
		ft_tstr_pushstr(&data->prompt, "\001"ANSI_MAGENTA"\002");
	else
		ft_tstr_pushstr(&data->prompt, "\001"ANSI_RED"\002");
}

void	default_prompt(t_data *data)
{
	if (data->prompt.len)
		ft_tstr_clear(&data->prompt);
	if (data->username && data->pwd)
	{
		pushcolor(&data->prompt, data);
		ft_tstr_pushslice(&data->prompt, data->username->data,
			data->username->len);
		ft_tstr_pushstr(&data->prompt, "\001"ANSI_RESET"\002");
		(ft_tstr_push(&data->prompt, '@'), ft_tstr_pushslice(&data->prompt,
				data->hostname.data, data->hostname.len));
		ft_tstr_push(&data->prompt, ' ');
		append_path_currdir(&data->prompt, data->pwd);
	}
	else
	{
		pushcolor(&data->prompt, data);
		try_user(data);
		(ft_tstr_push(&data->prompt, '@'), ft_tstr_pushslice(&data->prompt,
				data->hostname.data, data->hostname.len));
		ft_tstr_push(&data->prompt, ' ');
		append_path_currdir(&data->prompt, data->pwd);
	}
	ft_tstr_pushstr(&data->prompt, "\001"ANSI_MAGENTA"\002"" $ "
		"\001"ANSI_RESET"\002");
}

void	hdoc_prompt(t_data *data)
{
	ft_tstr_clear(&data->prompt);
	ft_tstr_pushstr(&data->prompt, "hdoc > ");
}
