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

void	default_prompt(t_data *data)
{
	ft_tstr_clear(&data->prompt);
	ft_tstr_pushstr(&data->prompt, "$ ");
}

void	hdoc_prompt(t_data *data)
{
	ft_tstr_clear(&data->prompt);
	ft_tstr_pushstr(&data->prompt, "hdoc > ");
}
