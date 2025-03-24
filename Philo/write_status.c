#include "philo.h"

static void  write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
  {
    if(TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d has taken the FIRST fork -> %s%d%s\n", WHITE_B, elapsed, RESET, philo->id);
    else  if(TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d has taken the SECOND fork\n", WHITE_B, elapsed, RESET, philo->id);
    else if(EATING == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d is eating%s\n", WHITE_B, elapsed, YELLOW_B, philo->id, RESET);
    else if(SLEEPING == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d is sleeping\n", WHITE_B, elapsed, RESET, philo->id);
    else if(THINKING == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d is thinking\n", WHITE_B, elapsed, RESET, philo->id);
    else if(DIED == status)
      printf("%s%-6ld %d died%s\n", RED_B, elapsed,philo->id, RESET);
  }
}

void  write_status(t_philo_status status, t_philo *philo, bool debug)
{
  long  elapsed;

  elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
  if (philo->full)
    return ;
  safe_mutex_handle(&philo->table->write_lock, LOCK);
  if (debug)
    write_status_debug(status, philo, elapsed);
  else
  {
    if((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
      && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d has taken a fork\n", WHITE_B, elapsed, RESET, philo->id);
    else if(EATING == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d is eating%s\n", WHITE_B, elapsed, YELLOW_B, philo->id, RESET);
    else if(SLEEPING == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d is sleeping\n", WHITE_B, elapsed, RESET, philo->id);
    else if(THINKING == status && !simulation_finished(philo->table))
      printf("%s%-6ld%s %d is thinking\n", WHITE_B, elapsed, RESET, philo->id);
    else if(DIED == status)
      printf("%s%-6ld %d died%s\n", RED_B, elapsed,philo->id, RESET);
  }
  safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
