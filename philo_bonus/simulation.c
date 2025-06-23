#include "philo_bonus.h"

void	monitor_philo(t_philo *philo)
{
	if ((current_time(philo->table) - philo->last_meal_time) > philo->table->time_to_die)
	{
		print_msg(philo, DIED);
		sem_post(philo->table->ckeck_meal_sem);
		clean_all(philo->table);
		exit(1);
	}
}

void	waiting_forks(t_philo *philo)
{
	while (*(int16_t *)philo->table->forks_sem < 2)
	{
		sem_wait(philo->table->ckeck_meal_sem);
		monitor_philo(philo);
		sem_post(philo->table->ckeck_meal_sem);
	}
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		waiting_forks(philo);
		sem_wait(philo->table->forks_sem);
		print_msg(philo, FIRST_FORK);
		sem_wait(philo->table->forks_sem);
		print_msg(philo, SECOND_FORK);
		sem_wait(philo->table->ckeck_meal_sem);
		monitor_philo(philo);
		philo->last_meal_time = current_time(philo->table);
		philo->meals_eaten++;
		sem_post(philo->table->ckeck_meal_sem);
		print_msg(philo, EATING);
		precise_sleep(philo->table->time_to_eat, philo->table);
		sem_post(philo->table->forks_sem);
		sem_post(philo->table->forks_sem);
		if (philo->table->nbr_meals > 0 && philo->meals_eaten >= philo->table->nbr_meals)
		{
			clean_all(philo->table);
			exit(0);
		}
		print_msg(philo, SLEEPING);
		precise_sleep(philo->table->time_to_sleep, philo->table);
		print_msg(philo, THINKING);
	}
}

void	parent_process(t_table *table)
{
	int	i;
	int	j;
	int status;

	i = 0;
	status = 0;
	while (i < table->nbr_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			j = 0;
			while (j < table->nbr_philos)
			{
				kill(table->philos[j].pid, SIGKILL);
				j++;
			}
			break;
		}
		i++;
	}
}

void	simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid < 0)
			error_exit("Fork failed", table);
		if (table->philos[i].pid == 0)
			philo_routine(&table->philos[i]);
		i++;
	}
	parent_process(table);
}
