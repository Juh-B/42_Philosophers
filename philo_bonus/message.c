/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:53:34 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/26 12:18:06 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	printing(t_philo *philo, t_philo_status status, long elapsed)
{
	if ((FIRST_FORK == status || SECOND_FORK == status))
		printf("%-6ld %s%d%s has taken a fork\n", elapsed, WHITE_B, \
			philo->id, RESET);
	else if (EATING == status)
		printf("%-6ld %s%d%s is eating%s\n", elapsed, WHITE_B, \
			philo->id, GREEN_B, RESET);
	else if (SLEEPING == status)
		printf("%-6ld %s%d%s is sleeping%s\n", elapsed, WHITE_B, \
			philo->id, CYAN_B, RESET);
	else if (THINKING == status)
		printf("%-6ld %s%d%s is thinking%s\n", elapsed, WHITE_B, \
			philo->id, YELLOW_B, RESET);
	else if (DIED == status)
	{
		printf("%-6ld %s%d died%s\n", elapsed, RED_B, philo->id, RESET);
		philo->table->end_simulation = 1;
	}
}

void	print_msg(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	if (sem_wait(philo->table->death_sem) != 0)
		return ;
	elapsed = current_time(philo->table) - philo->table->start_simulation;
	sem_wait(philo->table->print_msg_sem);
	printing(philo, status, elapsed);
	sem_post(philo->table->print_msg_sem);
	if (status != DIED)
		sem_post(philo->table->death_sem);
}
