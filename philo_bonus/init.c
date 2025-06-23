#include "philo_bonus.h"

static void	init_table(t_table *table, int argc, char **argv)
{
	table->nbr_philos = convert_arg(argv[1], table);
	table->time_to_die = convert_arg(argv[2], table);
	table->time_to_eat = convert_arg(argv[3], table);
	table->time_to_sleep = convert_arg(argv[4], table);
	if (argc == 6)
		table->nbr_meals = convert_arg(argv[5], table);
	else
		table->nbr_meals = 0;
	table->nbr_forks = table->nbr_philos;
	table->start_simulation = current_time(table);
	table->end_simulation = 0;
	table->forks_sem = sem_open("/fork_sem", O_CREAT, 0644, table->nbr_forks);
	table->ckeck_meal_sem = sem_open("/ckeck_meal_sem", O_CREAT, 0644, 1);
	table->print_msg_sem = sem_open("/msg_sem", O_CREAT, 0644, 1);
	table->death_sem = sem_open("/death_sem", O_CREAT, 0644, 1);
	if (table->forks_sem == SEM_FAILED || table->ckeck_meal_sem == SEM_FAILED ||
		table->print_msg_sem == SEM_FAILED || table->death_sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}
}

static void	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		error_exit("Malloc failed", table);
	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_simulation;
		table->philos[i].table = table;
		table->philos[i].pid = 0;
		i++;
	}
}

void	init_structs(t_table *table, int argc, char **argv)
{
	init_table(table, argc, argv);
	init_philos(table);
}
