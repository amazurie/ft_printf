/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 11:16:36 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/25 12:07:37 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	handle_int(va_list *args, t_arg *sargs, char **buff)
{
	intmax_t	n;
	size_t		len;

	sargs->sign = 0;
	n = get_flags(args, sargs);
	if (sargs->is_sign && n >= 0)
		sargs->sign = "+";
	else if (sargs->blank && n >= 0 && !sargs->is_sign)
		sargs->sign = " ";
	else if (n < 0)
		sargs->sign = "-";
	n = (n < 0) ? -n : n;
	len = print_num(n, "0123456789", sargs, buff);
	return (len);
}

size_t	handle_uint(va_list *args, t_arg *sargs, char **buff)
{
	intmax_t	n;
	size_t		len;

	n = get_uflags(args, sargs);
	len = print_num(n, "0123456789", sargs, buff);
	return (len);
}

size_t	handle_octet(va_list *args, t_arg *sargs, char **buff)
{
	uintmax_t	n;
	size_t		len;

	n = get_uflags(args, sargs);
	if (sargs->is_sign && !n && sargs->is_prec && sargs->prec == 0)
	{
		len = 0;
		if (sargs->width > 0)
			sargs->width -= 1;
		if (sargs->width != 0 && !sargs->left_adjust)
			len += fill_nchar(buff, (sargs->zero_pad) ? '0' : ' ',
					sargs->width);
		len += fill_nchar(buff, '0', 1);
		if (sargs->width != 0 && sargs->left_adjust)
			len += fill_nchar(buff, ' ', sargs->width);
		return (len);
	}
	if (sargs->alternate && (n || (sargs->is_prec && sargs->prec == 0)))
	{
		if (sargs->is_prec && sargs->prec > 0)
			sargs->prec -= 1;
		sargs->sign = "0";
		return (print_num(n, "01234567", sargs, buff));
	}
	return (print_num(n, "01234567", sargs, buff));
}

size_t	handle_hex(char format, va_list *args, t_arg *sargs, char **buff)
{
	long	n;

	n = get_uflags(args, sargs);
	if (format == 'x' && sargs->alternate && n)
	{
		sargs->sign = "0x";
		return (print_num(n, "0123456789abcdef", sargs, buff));
	}
	else if (format == 'x')
	{
		return (print_num(n, "0123456789abcdef", sargs, buff));
	}
	sargs->sign = (sargs->alternate && n) ? "0X" : 0;
	return (print_num(n, "0123456789ABCDEF", sargs, buff));
}

size_t	handle_pointer(va_list *args, t_arg *sargs, char **buff)
{
	intmax_t	n;
	size_t		len;

	sargs->length = '6';
	n = get_uflags(args, sargs);
	sargs->sign = "0x";
	len = print_num(n, "0123456789abcdef", sargs, buff);
	return (len);
}
