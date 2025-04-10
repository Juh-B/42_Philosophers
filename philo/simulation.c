/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:19:34 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/10 13:11:57 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_table *table, int *count)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&table->table_mtx);
		if ((current_time() - table->philos[i].last_meal_time) > \
			table->time_to_die)
		{
			print_msg(&table->philos[i], DIED);
			table->end_simulation = 1;
			pthread_mutex_unlock(&table->table_mtx);
			return (1);
		}
		if (table->nbr_meals > 0 && table->philos[i].meals_eaten >= \
			table->nbr_meals)
			(*count)++;
		pthread_mutex_unlock(&table->table_mtx);
		i++;
	}
	return (0);
}

static void	*monitor_dinner(void *arg)
{
	t_table	*table;
	int		nbr_philos_full;

	table = (t_table *)arg;
	while (!table->end_simulation)
	{
		nbr_philos_full = 0;
		if (philo_died(table, &nbr_philos_full))
			return (NULL);
		if (table->nbr_meals > 0 && nbr_philos_full == table->nbr_philos)
		{
			table->end_simulation = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	*philo_rotine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(philo->table->end_simulation))
	{
		if (philo->table->nbr_philos == 1)
		{
			print_msg(philo, FIRST_FORK);
			break ;
		}
		pthread_mutex_lock(&philo->first_fork->fork);
		print_msg(philo, FIRST_FORK);
		pthread_mutex_lock(&philo->second_fork->fork);
		print_msg(philo, SECOND_FORK);
		philo->last_meal_time = current_time();
		philo->meals_eaten++;
		print_msg(philo, EATING);
		precise_sleep(philo->table->time_to_eat, philo->table);
		pthread_mutex_unlock(&philo->second_fork->fork);
		pthread_mutex_unlock(&philo->first_fork->fork);
		print_msg(philo, SLEEPING);
		precise_sleep(philo->table->time_to_sleep, philo->table);
		print_msg(philo, THINKING);
	}
	return (NULL);
}

void	simulation(t_table *table)
{
	int	i;

	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_create(&table->philos[i].thread_id, NULL, philo_rotine,
			&table->philos[i]);
		i++;
	}
	pthread_join(table->monitor, NULL);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	// return (table->end_simulation);
}
