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

	lastslash = ft_strrchr(pwd->data, '/');
	if (lastslash)
		ft_tstr_pushstr(prompt, lastslash + 1);
	else
		ft_tstr_pushslice(prompt, pwd->data, pwd->len);
}

void	default_prompt(t_data *data)
{
	if (data->prompt.len)
		ft_tstr_clear(&data->prompt);
	if (data->username && data->pwd)
	{
		ft_tstr_pushstr(&data->prompt, ANSI_MAGENTA);
		ft_tstr_pushslice(&data->prompt, data->username->data,
					data->username->len);
		ft_tstr_pushstr(&data->prompt, ANSI_RESET);
		ft_tstr_push(&data->prompt, '@');
		append_path_currdir(&data->prompt, data->pwd);
		ft_tstr_pushstr(&data->prompt, " $ ");
	}
	else if (!data->username && data->pwd)
	{
		append_path_currdir(&data->prompt, data->pwd);
		ft_tstr_pushstr(&data->prompt, " $ ");
	}
	else
	{
		append_path_currdir(&data->prompt, data->pwd);
		ft_tstr_pushstr(&data->prompt, " $ ");
	}
}

void	hdoc_prompt(t_data *data)
{
	ft_tstr_clear(&data->prompt);
	ft_tstr_pushstr(&data->prompt, "hdoc > ");
}
