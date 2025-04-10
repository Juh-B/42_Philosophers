/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mensagem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:18:24 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/10 11:40:43 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, t_philo_status status)
{
	long	elapsed;

	elapsed = current_time() - philo->table->start_simulation;
	pthread_mutex_init(&philo->table->print_msg_mtx, NULL);
	// if (FIRST_FORK == status && !simulation_finished(philo->table))
	//   printf("%-6ld %s%d%s has taken the FIRST fork\n", elapsed, WHITE_B, philo->id, RESET);
	// else if (SECOND_FORK == status && !simulation_finished(philo->table))
	//   printf("%-6ld %s%d%s has taken the SECOND fork\n", elapsed, WHITE_B, philo->id, RESET);
	if ((FIRST_FORK == status || SECOND_FORK == status) &&
		!(philo->table->end_simulation))
		printf("%-6ld %s%d%s has taken a fork\n", elapsed, WHITE_B,
			philo->id, RESET);
	else if (EATING == status && !(philo->table->end_simulation))
		printf("%-6ld %s%d%s is eating%s\n", elapsed, WHITE_B,
			philo->id, GREEN_B, RESET);
		// printf("%-6ld %s%d%s is eating%s - %d Meal\n", elapsed, WHITE_B, philo->id, GREEN_B, RESET, philo->meals_eaten);
	else if (SLEEPING == status && !(philo->table->end_simulation))
		printf("%-6ld %s%d%s is sleeping%s\n", elapsed, WHITE_B,
			philo->id, CYAN_B, RESET);
	else if (THINKING == status && !(philo->table->end_simulation))
		printf("%-6ld %s%d%s is thinking%s\n", elapsed, WHITE_B, philo->id,
			YELLOW_B, RESET);
	else if (DIED == status)
		printf("%-6ld %s%d died%s\n", elapsed, RED_B, philo->id, RESET);
	pthread_mutex_destroy(&philo->table->print_msg_mtx);
}
