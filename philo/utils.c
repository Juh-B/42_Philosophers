#include "philo.h"

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

long current_time(void)
{
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    error_exit("Gettimeofday failed");
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void precise_sleep(long time, t_table *table)
{
	long  start;
  long  elapsed;
  long  remaining;

  start = current_time();
	while (1)
	{
		pthread_mutex_lock(&table->monitor_mtx);
		if (table->end_simulation)
		{
			pthread_mutex_unlock(&table->monitor_mtx);
			break;
		}
		pthread_mutex_unlock(&table->monitor_mtx);
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
