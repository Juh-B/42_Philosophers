#include "philo.h"

int simulation_finished(t_table *table)
{
   return (table->end_simulation);
}

void  *monitor_dinner(void *arg)
{
  t_table *table;
  int     i;
  long		now;
	int			full_count;

  table = (t_table *)arg;
	while (!table->end_simulation)
	{
		i = 0;
		full_count = 0;
		while (i < table->nbr_philos)
		{
			pthread_mutex_lock(&table->table_mtx);
			now = current_time();
			if ((now - table->philos[i].last_meal_time) > table->time_to_die)
			{
				print_msg(&table->philos[i], DIED);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->table_mtx);
				return (NULL);
			}
			if (table->nbr_meals > 0 &&	table->philos[i].meals_eaten >= table->nbr_meals)
				full_count++;
			pthread_mutex_unlock(&table->table_mtx);
			i++;
		}
		if (table->nbr_meals > 0 && full_count == table->nbr_philos)
		{
			table->end_simulation = 1;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void *philo_rotine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

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
      if (philo->table->nbr_meals > 0
        && philo->meals_eaten == philo->table->nbr_meals)
      {
        philo->table->full_philos++;
        // printf("PHILO %d is FULL\n", philo->id);
      }
      pthread_mutex_unlock(&philo->second_fork->fork);
      pthread_mutex_unlock(&philo->first_fork->fork);
      print_msg(philo, SLEEPING);
      precise_sleep(philo->table->time_to_sleep, philo->table);
      print_msg(philo, THINKING);
    }
    return (NULL);
}

int  simulation(t_table *table)
{
  int i;
  pthread_t monitor;

  // pthread_create(&table->monitor, NULL, monitor_dinner, &table->monitor);
  pthread_create(&monitor, NULL, monitor_dinner, table);
  i = 0;
  while (i < table->nbr_philos)
  {
    pthread_create(&table->philos[i].thread_id, NULL, philo_rotine, &table->philos[i]);
    i++;
  }

  pthread_join(monitor, NULL);
  // pthread_join(table->monitor, NULL);
  i = 0;
  while (i < table->nbr_philos)
  {
    pthread_join(table->philos[i].thread_id, NULL);
    i++;
  }
  // printf("End = %d\n", table->end_simulation);
  return (table->end_simulation);
}
