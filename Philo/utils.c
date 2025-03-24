#include "philo.h"

void  error_exit(char *str)
{
  printf("%sError%s\n%s\n", RED_B, RESET, str);
  exit(EXIT_FAILURE);
}

long  get_time(t_time_code time_code)
{
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    error_exit("Gettimeofdai failed.");
  if (SECOND == time_code)
    return (tv.tv_sec + (tv.tv_usec / 1e3));
  else if (MILLISECOND == time_code)
    return ((tv.tv_sec + 1e3) + (tv.tv_usec / 1e3));
  else  if (MICROSECOND == time_code)
    return ((tv.tv_sec + 1e6) + tv.tv_usec);
  else
    error_exit("Wrong input to get_time.");
  return (1500);
}

void  precise_usleep(long usec, t_table *table)
{
  long  start;
  long  elapse;
  long  remain;

  start = get_time(MICROSECOND);
  while (get_time(MICROSECOND) - start < usec)
  {
    if (simulation_finished(table))
      break ;
    elapse = get_time(MICROSECOND) - start;
    remain = usec - elapse;
    if (remain > 1e3)
      usleep(remain / 2);
    else
    {
      while (get_time(MICROSECOND) - start < usec)
        ;
    }
  }
}
