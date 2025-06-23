/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:19:34 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 16:41:00 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died(t_table *table, int *count)
{
	int	i;

	i = 0;
	*count = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&table->table_mtx);
		if ((current_time() - table->philos[i].last_meal_time) > \
			table->time_to_die)
		{
			print_msg(&table->philos[i], DIED);
			pthread_mutex_lock(&table->monitor_mtx);
			table->end_simulation = 1;
			pthread_mutex_unlock(&table->monitor_mtx);
			pthread_mutex_unlock(&table->table_mtx);
			return (1);
		}
		if (table->nbr_meals > 0 && \
			table->philos[i].meals_eaten >= table->nbr_meals)
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
			pthread_mutex_lock(&table->monitor_mtx);
			table->end_simulation = 1;
			pthread_mutex_unlock(&table->monitor_mtx);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_msg(philo, FIRST_FORK);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_msg(philo, SECOND_FORK);
	pthread_mutex_lock(&philo->table->table_mtx);
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->table_mtx);
	print_msg(philo, EATING);
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
	print_msg(philo, SLEEPING);
	precise_sleep(philo->table->time_to_sleep, philo->table);
	print_msg(philo, THINKING);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->table->monitor_mtx);
		if (philo->table->end_simulation)
		{
			pthread_mutex_unlock(&philo->table->monitor_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->table->monitor_mtx);
		if (philo->table->nbr_philos == 1)
		{
			print_msg(philo, FIRST_FORK);
			break ;
		}
		routine(philo);
	}
	return (NULL);
}

void	simulation(t_table *table)
{
	int	i;

	if (pthread_create(&table->monitor, NULL, monitor_dinner, table) != 0)
		error_exit("Failed to create thread");
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, philo_routine, \
		&table->philos[i]) != 0)
			error_exit("Failed to create thread");
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		error_exit("Failed to join thread");
	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			error_exit("Failed to join thread");
		i++;
	}
}
