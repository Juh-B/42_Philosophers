#include "philo.h"

void  error_exit(char *str)
{
  printf("%sError%s\n%s\n", RED_B, RESET, str);
  exit(EXIT_FAILURE);
}

void cleanup(t_table *table)
{
  int i;

  i = 0;
  if (table->forks)
  {
    while (i < table->nbr_philos)
    {
      pthread_mutex_destroy(&table->forks[i].fork);
      i++;
    }
    free(table->forks);
  }
  if (table->philos)
  {
    i = 0;
    while (i < table->nbr_philos)
    {
      pthread_mutex_destroy(&table->philos[i].life_control);
      i++;
    }
    free(table->philos);
  }
  pthread_mutex_destroy(&table->print_msg_mtx);
  pthread_mutex_destroy(&table->table_mtx);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) > 0)
	{
		number = (number * 10) + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}

void  precise_sleep(long time, t_table *table)
{
  long  start;
  long  elapsed;
  long  remaining;

  start = current_time();
  while (current_time() - start < time)
  {
    if (simulation_finished(table))
      break ;
    elapsed = current_time() - start;
    if (elapsed >= time)
      break;
    remaining = time - elapsed;
    if (remaining > 5)
      usleep(remaining * 500);
    else
      usleep(100);
  }
}
