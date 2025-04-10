/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:20:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/10 11:39:08 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	convert_arg(char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		error_exit("Wrong input values!\nPlease, use only positive numbers.");
	while (ft_isdigit(str[i]))
		i++;
	number = ft_atoi(str);
	if (str[i] == '\0' && (number > 0 && number <= 2147483647))
		return (number);
	else if (!ft_isdigit(str[i]))
		error_exit("The input isn't a correct digit.\nUse only numbers.");
	else if (number == 0 || number > 2147483647)
		error_exit("The value needs to be between 1 and INT_MAX (2147483647).");
	return (0);
}

void	verif_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (convert_arg(argv[i]))
		{
			if (i >= 2 && i <= 4)
			{
				if (convert_arg(argv[i]) <= 60)
					error_exit("Use timestamps greater than 60ms.");
			}
			i++;
		}
		else
			error_exit("Wrong input values!");
	}
}
