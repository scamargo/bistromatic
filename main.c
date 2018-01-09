/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 13:29:51 by scamargo          #+#    #+#             */
/*   Updated: 2018/01/09 11:21:14 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#define BUFF_SIZE 32

int	parse_sum(char **p_str);
int parse_number(char **p_str);

//TODO: handle negative
int parse_number(char **p_str)
{
	int result;
	int factor;

	factor = 1;
	if(**p_str == '-')
	{
		factor = -1;
		(*p_str)++;
	}
	result = 0;
	while (**p_str >= '0' && **p_str <= '9')
	{
		result = result * 10 + **p_str - '0';
		(*p_str)++;
	}
	return (result * factor);
}

int parse_factor(char **p_str)
{
	int		result;

	//make sure this is number
	if ((**p_str >= '0' && **p_str <= '9') || **p_str == '-')
	{
		result = parse_number(p_str);
		return (result);
	}
	else if (**p_str == '(')
	{
		(*p_str)++;
		result = parse_sum(p_str);
		(*p_str)++; // assume this is close ')'
		return (result);
	}
	return (-1000000); //TODO: throw error if it gets here??
}

int	parse_product(char **p_str)
{
	int		fac1;
	int		fac2;
	int		is_mult;
	int		is_div;

	fac1 = parse_factor(p_str);
	printf("fac1: %d\n", fac1);
	while (**p_str == '*' || **p_str == '/' || **p_str == '%')
	{
		is_mult = (**p_str == '*') ? 1 : 0;
		is_div = (**p_str == '/') ? 1: 0;
		(*p_str)++;
		fac2 = parse_factor(p_str);
		if (is_mult)
			fac1 *= fac2;
		else if (is_div)
			fac1 *= fac2;
		else
			fac1 %= fac2;
	}
	return (fac1);
}

int	parse_sum(char **p_str)
{
	int		pro1;
	int		pro2;
	int		is_add;
	char	*str_copy;

	pro1 = parse_product(p_str);
	printf("pro1: %d\n", pro1);
	str_copy = *p_str;
	while (**p_str == '+' || (**p_str == '-' && !ft_isdigit(*(++str_copy))))
	{
		is_add = (**p_str == '+') ? 1 : 0;
		(*p_str)++;
		pro2 = parse_product(p_str);
		pro1 = (is_add) ? pro1 + pro2 : pro1 - pro2;
		str_copy = *p_str;
	}
	return (pro1);
}

int	set_buffer(t_array *buff)
{
	char	in_buff[BUFF_SIZE + 1];
	int		reader;
	int		i;

	buff->size = 20;
	buff->used = 0;
	if (!(buff->str = ft_memalloc(buff->size * sizeof(char))))
		return (0);
	while ((reader = read(0, in_buff, BUFF_SIZE)))
	{
		if (reader == -1)
			return (0);
		in_buff[reader] = '\0';
		i = 0;
		while (in_buff[i])
			arr_insert(buff, in_buff[i++]);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		result;
	int		input_size;
	int		base_size;
	t_array	buff;

	if (argc != 3)
		return (1);
	base_size = ft_strlen(argv[1]);
	// TODO: validate input
	input_size = ft_atoi(argv[2]);
	if (!set_buffer(&buff))
		return (1);
	result = parse_sum(&(buff.str));
	// TODO: display in correct base
	ft_putnbr(result);
	return (0);
}
