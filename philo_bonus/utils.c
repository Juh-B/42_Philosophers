/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:54:04 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/26 12:26:45 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_philo(t_philo *philo)
{
	if ((current_time(philo->table) - philo->last_meal_time) > \
	philo->table->time_to_die)
	{
		print_msg(philo, DIED);
		sem_post(philo->table->ckeck_meal_sem);
		clean_all(philo->table);
		exit(1);
	}
}

void	waiting_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(500);
	while (*(int16_t *)philo->table->forks_sem < 2)
	{
		sem_wait(philo->table->ckeck_meal_sem);
		monitor_philo(philo);
		sem_post(philo->table->ckeck_meal_sem);
	}
}

void	full_philo(t_philo *philo)
{
	clean_all(philo->table);
	exit(0);
}

long	current_time(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed", table);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long time, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = current_time(table);
	while (current_time(table) - start < time)
	{
		if (table->end_simulation)
			break ;
		elapsed = current_time(table) - start;
		if (elapsed >= time)
			break ;
		remaining = time - elapsed;
		if (remaining > 5)
			usleep((remaining * 100) / 2);
		else
			usleep(100);
	}
}
