/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:37:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/24 15:06:30 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		print_num(intmax_t n, char *base, t_arg *sargs, char **buff)
{
	size_t	len;
	size_t	lennbase;
	size_t	strlen;
	char	*tmp;

	strlen = 0;
	lennbase = ft_lennbase(n, base);
	len = (sargs->prec > lennbase) ? sargs->prec : lennbase;
	len += (sargs->sign) ? ft_strlen(sargs->sign) : 0;
	if (!n && sargs->width && sargs->is_prec && !sargs->prec)
		sargs->width += lennbase;
	if (sargs->sign && sargs->zero_padding && !sargs->is_prec)
		strlen += buffcat(buff, sargs->sign);
	if (sargs->width != 0 && !sargs->left_adjust && sargs->width > len)
		strlen += fill_nchar_buff(buff, (sargs->zero_padding && !sargs->is_prec) ? '0' : ' ', sargs->width - len);
	if (sargs->sign && (!sargs->zero_padding || sargs->is_prec))
		strlen += buffcat(buff, sargs->sign);
	if (sargs->is_prec && sargs->prec > lennbase)
		strlen += fill_nchar_buff(buff, '0', sargs->prec - lennbase);
	if (n || !sargs->is_prec || sargs->prec)
	{
		tmp = ft_itoa_base(n, base);
		strlen += buffcat(buff, ft_itoa_base(n, base));
		free(tmp);
	}
	else
		len = 0;
	if (sargs->width != 0 && sargs->left_adjust && sargs->width > len)
		strlen += fill_nchar_buff(buff, ' ', sargs->width - len);
	return (strlen);
}

size_t		print_invalid(char **format, t_arg *sargs, int ret, char **buff)
{
	size_t	len;

	if (**format == '%' || **format == 's' || **format == 'S' || **format == 'c'
			|| **format == 'C' || **format == 'i' || **format == 'u' ||
			**format == 'd' || **format == 'p' || **format == 'X' ||
			**format == 'x' || **format == 'o' || **format == 'O' ||
			**format == 'D' || **format == 'U')
	{
		(*format)++;
		return (ret);
	}
	len = 0;
	if (sargs->width != 0 && !sargs->left_adjust && sargs->width > 1)
		len += fill_nchar_buff(buff, (sargs->zero_padding) ? '0' : ' ', sargs->width - 1);
	if (**format)
		len += fill_nchar_buff(buff, **format, 1);
	if (sargs->width != 0 && sargs->left_adjust && sargs->width > 1)
		len += fill_nchar_buff(buff, ' ', sargs->width - 1);
	if (*(format + 1) && **format)
		(*format)++;
	return (ret + len);
}
