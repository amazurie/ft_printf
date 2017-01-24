/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 11:17:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/12 17:23:38 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		set_arr(char **format, va_list *args, t_arg *sargs, char **buff)
{
	size_t len;

	len = ((**format) == '%') ? handle_modulo(sargs, buff) : 0;
	len = ((**format) == 's') ? handle_str(args, sargs, buff) : len;
	len = ((**format) == 'S') ? handle_wstr(args, sargs, buff) : len;
	len = ((**format) == 'c') ? handle_char(args, sargs, buff) : len;
	len = ((**format) == 'C') ? handle_wchar(args, sargs, buff) : len;
	len = ((**format) == 'i') ? handle_int(args, sargs, buff) : len;
	len = ((**format) == 'u') ? handle_uint(args, sargs, buff) : len;
	len = ((**format) == 'd') ? handle_int(args, sargs, buff) : len;
	len = ((**format) == 'X') ? handle_hexa(format, args, sargs, buff) : len;
	len = ((**format) == 'x') ? handle_hexa(format, args, sargs, buff) : len;
	len = ((**format) == 'o') ? handle_octet(args, sargs, buff) : len;
	sargs->length = (**format == 'O' || **format == 'D' || **format == 'U'
			|| **format == 'p') ? '3' : sargs->length;
	len = ((**format) == 'O') ? handle_octet(args, sargs, buff) : len;
	len = ((**format) == 'D') ? handle_int(args, sargs, buff) : len;
	len = ((**format) == 'U') ? handle_uint(args, sargs, buff) : len;
	len = ((**format) == 'p') ? handle_pointer(args, sargs, buff) : len;
	len = print_invalid(format, sargs, len, buff);
	return (len);
}
