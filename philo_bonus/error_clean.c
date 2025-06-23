/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:52:53 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/23 16:59:33 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_exit(char *str, t_table *table)
{
	printf("%sError%s\n%s\n", RED_B, RESET, str);
	clean_all(table);
	exit(EXIT_FAILURE);
}

void	clean_all(t_table *table)
{
	if (!table)
		return ;
	if (table->philos)
		free(table->philos);
	clean_sem(table);
}

void	clean_sem(t_table *table)
{
	sem_close(table->forks_sem);
	sem_close(table->print_msg_sem);
	sem_close(table->ckeck_meal_sem);
	sem_close(table->death_sem);
	sem_unlink("/fork_sem");
	sem_unlink("/msg_sem");
	sem_unlink("/ckeck_meal_sem");
	sem_unlink("/death_sem");
}
