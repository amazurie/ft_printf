/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:03:20 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/11 13:20:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t		get_flags(va_list *args, t_arg *sargs)
{
	intmax_t n;

	n = va_arg(*args, intmax_t);
	if (sargs->length == '1')
		n = (char)n;
	else if (sargs->length == '2')
		n = (short int)n;
	else if (sargs->length == '3')
		n = (long int)n;
	else if (sargs->length == '4')
		n = (long long int)n;
	else if (sargs->length == '5')
		n = (intmax_t)n;
	else if (sargs->length == '6')
		n = (size_t)n;
	else
		n = (int)n;
	return (n);
}

uintmax_t		get_uflags(va_list *args, t_arg *sargs)
{
	uintmax_t n;

	n = va_arg(*args, uintmax_t);
	if (sargs->length == '1')
		n = (unsigned char)n;
	else if (sargs->length == '2')
		n = (unsigned short int)n;
	else if (sargs->length == '3')
		n = (unsigned long int)n;
	else if (sargs->length == '4')
		n = (unsigned long long int)n;
	else if (sargs->length == '5')
		n = (intmax_t)n;
	else if (sargs->length == '6')
		n = (size_t)n;
	else
		n = (unsigned int)n;
	return (n);
}
