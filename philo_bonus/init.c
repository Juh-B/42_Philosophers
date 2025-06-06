#include "philo_bonus.h"

static void  init_table(t_table *table, int argc, char **argv)
{
  table->nbr_philos = convert_arg(argv[1]);
  table->time_to_die = convert_arg(argv[2]);
  table->time_to_eat = convert_arg(argv[3]);
  table->time_to_sleep = convert_arg(argv[4]);
  if (argc == 6)
    table->nbr_meals = convert_arg(argv[5]);
  else
    table->nbr_meals = 0;
  table->nbr_forks = table->nbr_philos;
  table->start_simulation = current_time();
  table->end_simulation = 0;
  table->forks_sem = sem_open("/fork_sem", O_CREAT, 0644, table->nbr_forks);
  table->print_msg_sem = sem_open("/msg_sem", O_CREAT, 0644, 1);
  table->monitor_sem = sem_open("/monit_sem", O_CREAT, 0644, table->nbr_philos);
  table->finish_sem = sem_open("/end_sem", O_CREAT, 0644, 1);
	if (table->forks_sem == SEM_FAILED || table->monitor_sem == SEM_FAILED ||
    table->print_msg_sem == SEM_FAILED || table->finish_sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}
}

// static void  init_forks(t_table *table)
// {
//   int i;

//   i = 0;
//   table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
//   if (!table->forks)
//     error_exit("Malloc failed");
//   while (i < table->nbr_philos)
//   {
//     pthread_mutex_init(&table->forks[i].fork, NULL);
//     table->forks[i].fork_id = i + 1;
//     i++;
//   }
// }

static void  init_philos(t_table *table)
{
  int i;

  table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
  if (!table->philos)
  {
    clean_all(table);
    error_exit("Malloc failed");
  }
  i = 0;
  while (i < table->nbr_philos)
  {
    table->philos[i].id = i + 1;
    table->philos[i].meals_eaten = 0;
    table->philos[i].last_meal_time = table->start_simulation;
    table->philos[i].table = table;
    // table->philos[i].first_fork = &table->forks[i];
    // table->philos[i].second_fork = &table->forks[(i + 1) % table->nbr_philos];
    // if (table->philos[i].id % 2 == 0)
    // {
    //   table->philos[i].first_fork = &table->forks[(i + 1) % table->nbr_philos];
    //   table->philos[i].second_fork = &table->forks[i];
    // }
    i++;
  }
}

void  init_structs(t_table *table, int argc, char **argv)
{
  init_table(table, argc, argv);
  // init_forks(table);
  init_philos(table);
}
