/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:40:14 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/13 12:29:17 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <stdio.h>
# include <locale.h>

typedef struct	s_arg
{
	int		alternate;
	int		left_adjust;
	int		is_sign;
	char	*sign;
	int		blank;
	int		zero_padding;
	int		length;
	size_t	width;
	int		is_prec;
	size_t	prec;
}				t_arg;

int				ft_printf(const char *format, ...);
void			set_flags(t_arg *sargs);
int				parse_flags(char **format, t_arg *sargs);
int				parse_width(char **format, va_list *args, t_arg *sargs);
int				parse_length(char **format, t_arg *sargs);
int				set_arr(char **format, va_list *args, t_arg *sargs, char **buff);
size_t			handle_str(va_list *args, t_arg *sargs, char **buff);
size_t			handle_char(va_list *args, t_arg *sargs, char **buff);
size_t			handle_modulo(t_arg *sargs, char **buff);
size_t			handle_int(va_list *args, t_arg *sargs, char **buff);
size_t			handle_uint(va_list *args, t_arg *sargs, char **buff);
size_t			handle_wchar(va_list *args, t_arg *sargs, char **buff);
size_t			handle_wstr(va_list *args, t_arg *sargs, char **buff);
size_t			print_num(intmax_t n, char *base, t_arg*sargs, char **buff);
intmax_t		get_flags(va_list *args, t_arg *sargs);
uintmax_t		get_uflags(va_list *args, t_arg *sargs);
size_t			handle_octet(va_list *args, t_arg *sargs, char **buff);
size_t			handle_hexa(char **format, va_list *args, t_arg *sargs, char **buff);
size_t			handle_pointer(va_list *args, t_arg *sargs, char **buff);
size_t			print_invalid(char **format, t_arg *sargs, int len, char **buff);
size_t			fill_nstr_buff(char **buff, char *s, size_t n);
size_t			fill_nchar_buff(char **buff, char c, size_t n);
size_t			print_buff(char **buff);
size_t			buffcat(char **buff, char *s);
size_t			buffncat(char **buff, char *s, size_t n);

#endif