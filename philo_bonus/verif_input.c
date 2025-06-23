/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:54:12 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 16:54:14 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	convert_arg(char *str, t_table *table)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		error_exit("Wrong input values!\n"VALID_NBR, table);
	while (ft_isdigit(str[i]))
		i++;
	number = ft_atoi(str);
	if (str[i] == '\0' && (number > 0 && number <= 2147483647))
		return (number);
	else if (!ft_isdigit(str[i]))
		error_exit("The input isn't a correct digit.\n"VALID_NBR, table);
	else if (number == 0 || number > 2147483647)
		error_exit(VALID_NBR, table);
	return (0);
}

void	verif_input(int argc, char **argv, t_table *table)
{
	int		i;
	long	value;

	i = 1;
	while (i < argc)
	{
		value = convert_arg(argv[i], table);
		if (i >= 2 && i <= 4 && value <= 60)
			error_exit("Use timestamps greater than 60ms.", table);
		i++;
	}
}
