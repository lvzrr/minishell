/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:59 by jaicastr          #+#    #+#             */
/*   Updated: 2025/07/16 17:14:02 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H
# include <unistd.h>
# include <stdlib.h>

int				ft_atoi(const char *str);
ssize_t			ft_atol(const char *str);
float			ft_atof(const char *s);
double			ft_atod(const char *s);
int				ft_atoi_base(char *str, char *base, int base_len);
char			*ft_itoa(int n);
char			*ft_itoa_base(int n, char *base);
char			*ft_utoa_base(size_t n, char *base);
size_t			ft_atoul(const char *str);
#endif
