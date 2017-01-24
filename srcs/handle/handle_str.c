/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 11:16:43 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/24 15:20:01 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	handle_str(va_list *args, t_arg *sargs, char **buff)
{
	char	*str;
	size_t	len;
	size_t	strlen;

	if (sargs->length == '3')
		return (handle_wstr(args, sargs, buff));
	strlen = 0;
	if (!(str = va_arg(*args, char*)))
		str = "(null)";
	len = (sargs->is_prec && sargs->prec < ft_strlen(str)) ? sargs->prec : ft_strlen(str);
	if (sargs->width && !sargs->left_adjust && sargs->width > len)
		strlen += fill_nchar_buff(buff, (sargs->zero_padding) ? '0' : ' ', sargs->width - len);
	strlen += buffncat(buff, str, len);
	if (sargs->width && sargs->left_adjust && sargs->width > len)
		strlen += fill_nchar_buff(buff, ' ', sargs->width - len);
	return (strlen);
}

size_t	handle_char(va_list *args, t_arg *sargs, char **buff)
{
	size_t	len;

	len = 0;
	if (sargs->length == '3')
		return (handle_wchar(args, sargs, buff));
	sargs->width -= (sargs->width) ? 1 : 0;
	if (sargs->width && !sargs->left_adjust)
		len += fill_nchar_buff(buff, (sargs->zero_padding) ? '0' : ' ', sargs->width);
	len += fill_nchar_buff(buff, va_arg(*args, int), 1);
	if (sargs->width && sargs->left_adjust)
		len += fill_nchar_buff(buff, ' ', sargs->width);
	return (len);
}

size_t	handle_modulo(t_arg *sargs, char **buff)
{
	size_t	len;

	len = 0;
	if (sargs->width != 0 && !sargs->left_adjust)
		len += fill_nchar_buff(buff, (sargs->zero_padding) ? '0' : ' ', sargs->width - 1);
	len += fill_nchar_buff(buff, '%', 1);
	if (sargs->width != 0 && sargs->left_adjust)
		len += fill_nchar_buff(buff, ' ', sargs->width - 1);
	return (len);
}

size_t	handle_wchar(va_list *args, t_arg *sargs, char **buff)
{
	wchar_t	chr;
	size_t	len;
	size_t	strlen;

	strlen = print_buff(buff);
	chr = va_arg(*args, wchar_t);
	if (chr <= 0x7F)
		len = 1;
	else if (chr <= 0x7FF)
		len = 2;
	else if (chr <= 0xFFFF)
		len = 3;
	else if (chr <= 0x10FFFF)
		len = 4;
	if (sargs->width && !sargs->left_adjust && sargs->width > len)
		ft_putnchar(((sargs->zero_padding) ? '0' : ' '), sargs->width - len);
	if (chr >= 0x10FFFF)
		return (-1);
	ft_putwchar(chr);
	if (sargs->width && sargs->left_adjust && sargs->width > len)
		ft_putnchar(' ', sargs->width - len);
	if (sargs->width > len)
		len += sargs->width - len;
	return (len + strlen);
}

size_t	handle_wstr(va_list *args, t_arg *sargs, char **buff)
{
	wchar_t	*s;
	size_t	len;
	size_t	strlen;

	strlen = print_buff(buff);
	if (!(s = va_arg(*args, wchar_t*)))
		s = L"(null)";
	len = (sargs->is_prec && sargs->prec < ft_wstrlen(s)) ? ft_wstrnlen(s, sargs->prec, 0) : ft_wstrlen(s);
	if (!sargs->left_adjust && sargs->width > len)
		ft_putnchar(((sargs->zero_padding) ? '0' : ' '), sargs->width - len);
	ft_putnwstr(s, len);
	if (sargs->left_adjust && sargs->width > len)
		ft_putnchar(' ', sargs->width - len);
	if (sargs->width > len)
		len += sargs->width - len;
	return (len + strlen);
}
