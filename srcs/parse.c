/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:39:52 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/24 16:36:34 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			parse_flags(char **form, t_arg *sargs)
{
	if (**form != '#' && **form != '-' && **form != '+' && **form != ' '
			&& **form != '0')
		return (1);
	if (**form == '#')
		sargs->alternate = 1;
	else if (**form == '0')
		sargs->zero_pad = 1;
	else if (**form == '-')
		sargs->left_adjust = 1;
	else if (**form == '+')
		sargs->is_sign = 1;
	else if (**form == ' ')
		sargs->blank = 1;
	else
		return (1);
	if (sargs->left_adjust)
		sargs->zero_pad = 0;
	(*form)++;
	if (**form != '#' && **form != '-' && **form != '+' && **form != ' '
			&& **form != '0')
		return (1);
	return (parse_flags(form, sargs));
}

void		set_flags(t_arg *sargs)
{
	sargs->alternate = 0;
	sargs->left_adjust = 0;
	sargs->is_sign = 0;
	sargs->sign = 0;
	sargs->blank = 0;
	sargs->zero_pad = 0;
	sargs->length = 0;
	sargs->prec = 0;
	sargs->is_prec = 0;
	sargs->width = 0;
}

static int	parse_prec(char **form, va_list *args, t_arg *sargs)
{
	int	parg;

	if (**form != '.')
		return (parse_width(form, args, sargs));
	if (**form == '.')
		sargs->is_prec = 1;
	if (**form == '.' && *(*form + 1) == '*')
	{
		if ((parg = va_arg(*args, int)) >= 0)
			sargs->prec = parg;
		else
			sargs->is_prec = 0;
	}
	if (**form == '.' && *(*form + 1) == '*')
		(*form) += 2;
	else if (**form == '.')
	{
		sargs->prec = 0;
		while ((*form)++ && **form >= '0' && **form <= '9')
			sargs->prec = sargs->prec * 10 + **form - '0';
	}
	return (parse_width(form, args, sargs));
}

int			parse_width(char **form, va_list *args, t_arg *sargs)
{
	int	warg;

	if (**form != '*' && !(**form >= '0' && **form <= '9') && **form != '.')
		return (1);
	if (**form >= '0' && **form <= '9')
		sargs->width = 0;
	if (**form == '*')
	{
		if ((warg = va_arg(*args, int)) < 0)
		{
			sargs->left_adjust = 1;
			sargs->zero_pad = 0;
			sargs->width = -warg;
		}
		else
			sargs->width = warg;
		(*form)++;
	}
	else
		while (**form >= '0' && **form <= '9')
		{
			sargs->width = sargs->width * 10 + **form - '0';
			(*form)++;
		}
	return (parse_prec(form, args, sargs));
}

int			parse_length(char **form, t_arg *sargs)
{
	if (**form != 'h' && **form != 'l' && **form != 'j' && **form != 'z')
		return (1);
	if ((**form == 'h' && *(*form + 1) == 'h') || (**form == 'l'
				&& *(*form + 1) == 'l'))
	{
		if (**form == 'h' && sargs->length < '1')
			sargs->length = '1';
		if (**form == 'l' && sargs->length < '4')
			sargs->length = '4';
		(*form) += 2;
	}
	else
	{
		if (**form == 'h' && sargs->length < '2')
			sargs->length = '2';
		else if (**form == 'l' && sargs->length < '3')
			sargs->length = '3';
		else if (**form == 'j' && sargs->length < '5')
			sargs->length = '5';
		else if (**form == 'z' && sargs->length < '6')
			sargs->length = '6';
		(*form)++;
	}
	return (parse_length(form, sargs));
}
