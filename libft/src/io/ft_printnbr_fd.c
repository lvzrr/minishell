/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:41 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft.h"

void	ft_printnbr_fd(int n, int fd, int *len)
{
	char	o;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		*len += 11;
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
		*len = *len + 1;
	}
	if (n >= 10)
	{
		ft_printnbr_fd(n / 10, fd, len);
		ft_printnbr_fd(n % 10, fd, len);
	}
	else
	{
		o = (n % 10) + '0';
		*len = *len + 1;
		write(fd, &o, 1);
	}
}
