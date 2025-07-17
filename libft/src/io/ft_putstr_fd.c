/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft.h"

void	ft_putstr_fd(const char *str, int fd)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		write(fd, &(str[i++]), 1);
}
