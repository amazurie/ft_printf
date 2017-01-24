/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:39:52 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/12 14:22:22 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_flags(char **format, t_arg *sargs)
{
	if (**format != '#' && **format != '-' && **format != '+' && **format != ' '
			&& **format != '0')
		return (1);
	if (**format == '#')
		sargs->alternate = 1;
	else if (**format == '0')
		sargs->zero_padding = 1;
	else if (**format == '-')
		sargs->left_adjust = 1;
	else if (**format == '+')
		sargs->is_sign = 1;
	else if (**format == ' ')
		sargs->blank = 1;
	else
		return (1);
	if (sargs->left_adjust)
		sargs->zero_padding = 0;
	(*format)++;
	if (**format != '#' && **format != '-' && **format != '+' && **format != ' '
			&& **format != '0')
		return (1);
	return (parse_flags(format, sargs));
}

void	set_flags(t_arg *sargs)
{
	sargs->alternate = 0;
	sargs->left_adjust = 0;
	sargs->is_sign = 0;
	sargs->sign = 0;
	sargs->blank = 0;
	sargs->zero_padding = 0;
	sargs->length = 0;
	sargs->prec = 0;
	sargs->is_prec = 0;
	sargs->width = 0;
}

static int	parse_prec(char **format, va_list *args, t_arg *sargs)
{
	int	parg;

	if (**format != '.')
		return (parse_width(format, args, sargs));
	if (**format == '.')
		sargs->is_prec = 1;
	if (**format == '.' && *(*format + 1) == '*')
	{
		if ((parg = va_arg(*args, int)) >= 0)
			sargs->prec = parg;
		else
			sargs->is_prec = 0;
	}
	if (**format == '.' && *(*format + 1) == '*')
		(*format) += 2;
	else if (**format == '.')
	{
		sargs->prec = 0;
		while ((*format)++ && **format >= '0' && **format <= '9')
			sargs->prec = sargs->prec * 10 + **format - '0';
	}
	return (parse_width(format, args, sargs));
}

int		parse_width(char **format, va_list *args, t_arg *sargs)
{
	int	warg;

	if (**format != '*' && !(**format >= '0' && **format <= '9') && **format != '.')
		return (1);
	if (**format >= '0' && **format <= '9')
		sargs->width = 0;
	if (**format == '*')
	{
		warg = va_arg(*args, int);
		if (warg < 0)
		{
			sargs->left_adjust = 1;
			sargs->zero_padding = 0;
			sargs->width = -warg;
		}
		else
			sargs->width = warg;
		(*format)++;
	}
	else
		while (**format >= '0' && **format <= '9')
		{
			sargs->width = sargs->width * 10 + **format - '0';
			(*format)++;
		}
	return (parse_prec(format, args, sargs));
}

int		parse_length(char **format, t_arg *sargs)
{
	if (**format != 'h' && **format != 'l' && **format != 'j' && **format != 'z')
		return (1);
	if ((**format == 'h' && *(*format + 1) == 'h') || (**format == 'l'
				&& *(*format + 1) == 'l'))
	{
		if (**format == 'h' && sargs->length < '1')
			sargs->length = '1';
		if (**format == 'l' && sargs->length < '4')
			sargs->length = '4';
		(*format) += 2;
	}
	else
	{
		if (**format == 'h' && sargs->length < '2')
			sargs->length = '2';
		else if (**format == 'l' && sargs->length < '3')
			sargs->length = '3';
		else if (**format == 'j' && sargs->length < '5')
			sargs->length = '5';
		else if (**format == 'z' && sargs->length < '6')
			sargs->length = '6';
		(*format)++;
	}
	return (parse_length(format, sargs));
}
