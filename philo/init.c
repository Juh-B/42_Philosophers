#include "philo.h"

long current_time(void)
{
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    error_exit("Gettimeofday failed");
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


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
  table->start_simulation = current_time();
  table->end_simulation = 0;
  table->full_philos = 0;
  pthread_mutex_init(&table->print_msg_mtx, NULL);
  pthread_mutex_init(&table->table_mtx, NULL);
}

static void  init_forks(t_table *table)
{
  int i;

  i = 0;
  table->forks = malloc(sizeof(t_fork) * table->nbr_philos);
  if (!table->forks)
    error_exit("Malloc failed");
  while (i < table->nbr_philos)
  {
    pthread_mutex_init(&table->forks[i].fork, NULL);
    table->forks[i].fork_id = i;
    i++;
  }
}

static void  init_philos(t_table *table)
{
  int i;

  table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
  if (!table->philos)
  {
    cleanup(table);
    error_exit("Malloc failed");
  }
  i = 0;
  while (i < table->nbr_philos)
  {
    table->philos[i].id = i + 1;
    table->philos[i].meals_eaten = 0;
    table->philos[i].last_meal_time = table->start_simulation;
    // table->philos[i].ate_all_meals = 0;
    table->philos[i].first_fork = &table->forks[i];
    table->philos[i].second_fork = &table->forks[(i + 1) % table->nbr_philos];
    pthread_mutex_init(&table->philos[i].life_control, NULL);
    table->philos[i].table = table;
    if (table->philos[i].id % 2 == 0)
    {
      table->philos[i].first_fork = &table->forks[(i + 1) % table->nbr_philos];
      table->philos[i].second_fork = &table->forks[i];
    }
    i++;
  }
}

void  init_structs(t_table *table, int argc, char **argv)
{
  init_table(table, argc, argv);
  init_forks(table);
  init_philos(table);
}
