/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:17:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/10 11:25:16 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *str)
{
	printf("%sError%s\n%s\n", RED_B, RESET, str);
	exit(EXIT_FAILURE);
}

void	clean_all(t_table *table)
{
	int	i;

	i = 0;
	if (table->forks)
	{
		while (i < table->nbr_philos)
		{
			pthread_mutex_destroy(&table->forks[i].fork);
			i++;
		}
		free(table->forks);
	}
	if (table->philos)
		free(table->philos);
	pthread_mutex_destroy(&table->print_msg_mtx);
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->monitor_mtx);
}
