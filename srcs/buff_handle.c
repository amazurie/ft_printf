/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:30:06 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/31 14:06:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_buff(char **buff)
{
	size_t len;

	len = ft_strlen(*buff);
	ft_putstr(*buff);
	ft_bzero(*buff, len);
	return (len);
}

size_t	buffcat(char **buff, char *s)
{
	size_t	len;

	len = 0;
	if (ft_strlen(*buff) + ft_strlen(s) < 1000)
		ft_strcat(*buff, s);
	else if (ft_strlen(s) < 1000)
	{
		len = print_buff(buff);
		ft_strcat(*buff, s);
	}
	else
	{
		len = print_buff(buff) + ft_strlen(s);
		ft_putstr(s);
	}
	return (len);
}

size_t	buffncat(char **buff, char *s, size_t n)
{
	size_t	len;

	len = 0;
	if (ft_strlen(*buff) + ft_strlen(s) < 1000)
		ft_strncat(*buff, s, n);
	else if (ft_strlen(s) < 1000)
	{
		len = print_buff(buff);
		ft_strncat(*buff, s, n);
	}
	else
	{
		len = print_buff(buff) + ((ft_strlen(s) >= n) ? n : ft_strlen(s));
		ft_putnstr(s, n);
	}
	return (len);
}

size_t	fill_nstr_buff(char **buff, char *s, size_t n)
{
	char	*buf;
	size_t	len;

	len = 0;
	if (ft_strlen(*buff) + n < 1000)
		buf = ft_strncat(*buff, s, n);
	else if (n < 1000)
	{
		len = print_buff(buff);
		*buff = ft_strncat(*buff, s, n);
	}
	else
	{
		len = print_buff(buff) + n;
		ft_putnstr(s, n);
	}
	return (len);
}

size_t	fill_nchar(char **buff, char c, size_t n)
{
	size_t	len;

	len = 0;
	if (!c && n == 1)
	{
		len = print_buff(buff) + n;
		ft_putnchar(c, n);
	}
	if (ft_strlen(*buff) + n < 1000)
		while (ft_strlen(*buff) < ft_strlen(*buff) + n--)
			buff[0][ft_strlen(*buff) + n] = c;
	else if (n < 1000)
	{
		len = print_buff(buff);
		while (n--)
			buff[0][n] = c;
	}
	else
	{
		len = print_buff(buff) + n;
		ft_putnchar(c, n);
	}
	return (len);
}
