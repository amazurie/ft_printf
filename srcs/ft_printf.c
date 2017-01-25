/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:13:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/25 12:07:09 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	arg_hand(char **form, va_list *args, t_arg *sargs, char **buff)
{
	if (**form == '\0')
		return (0);
	parse_flags(form, sargs);
	parse_width(form, args, sargs);
	parse_length(form, sargs);
	if (!*form)
		return (0);
	if (**form == '#' || **form == '-' || **form == '+' || **form == ' '
		|| **form == '0' || **form == '*' || (**form >= '0' && **form <= '9') ||
		**form == '.' || **form == 'h' || **form == 'l' || **form == 'j' ||
		**form == 'z')
		return (arg_hand(form, args, sargs, buff));
	return (set_arr(form, args, sargs, buff));
}

static size_t	inner(va_list *args, char *form, char **buff)
{
	char	*arg;
	size_t	len;
	t_arg	sargs;

	len = 0;
	if (!(arg = ft_strchr(form, '%')))
		len = buffcat(buff, form);
	else
	{
		len = buffncat(buff, form, ft_strlen_chr(form, '%'));
		form += ft_strlen_chr(form, '%');
	}
	if (!arg)
		return (len);
	set_flags(&sargs);
	form++;
	len += arg_hand(&form, args, &sargs, buff);
	return ((len + inner(args, form, buff)));
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
