/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:13:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/13 16:13:56 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	arg_handle(char **format, va_list *args, t_arg *sargs, char **buff)
{
	size_t	len;

	if (**format == '\0')
		return (0);
	parse_flags(format, sargs);
	parse_width(format, args, sargs);
	parse_length(format, sargs);
	if (!*format)
		return (0);
	if (**format == '#' || **format == '-' || **format == '+' || **format == ' '
		|| **format == '0' || **format == '*' || (**format >= '0' && **format <= '9') ||
		**format == '.' || **format == 'h' || **format == 'l' || **format == 'j' ||
		**format == 'z')
		return (arg_handle(format, args, sargs, buff));
	return (set_arr(format, args, sargs, buff));
}

static size_t	inner(va_list *args, char *format, char **buff)
{
	char	*arg;
	size_t	len;
	t_arg	sargs;

	len = 0;
	if (!(arg = ft_strchr(format, '%')))
		len = buffcat(buff, format);
	else
	{
		len = buffncat(buff, format, ft_strlen_chr(format, '%'));
		format += ft_strlen_chr(format, '%');
	}
	if (!arg)
		return (len);
	set_flags(&sargs);
	format++;
	len += arg_handle(&format, args, &sargs, buff);
	return ((len + inner(args, format, buff)));
}

int				ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	len;
	char	*str;
	char	*buff;

	if (!format)
		return (0);
	buff = (char *)ft_memalloc(1000);
	va_start(args, format);
	str = (char *)format;
	len = inner(&args, str, &buff);
	len += ft_strlen(buff);
	ft_putstr(buff);
	va_end(args);
	free(buff);
	return (len);
}
