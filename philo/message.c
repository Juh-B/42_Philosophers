#include "philo.h"

void  print_msg(t_philo *philo, t_philo_status status)
{
  long  elapsed;

  elapsed = current_time() - philo->table->start_simulation;
  pthread_mutex_lock(&philo->table->print_msg_mtx);
  if ((FIRST_FORK == status || SECOND_FORK == status) && \
      !(philo->table->end_simulation))
    printf("%-6ld %s%d%s has taken a fork\n", elapsed, WHITE_B, \
            philo->id, RESET);
  else if (EATING == status && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s is eating%s\n", elapsed, WHITE_B, philo->id, \
            GREEN_B, RESET);
  else if (SLEEPING == status && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s is sleeping%s\n", elapsed, WHITE_B, philo->id, \
            CYAN_B, RESET);
  else if (THINKING == status && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s is thinking%s\n", elapsed, WHITE_B, philo->id, \
            YELLOW_B, RESET);
  else if (DIED == status)
    printf("%-6ld %s%d died%s\n", elapsed, RED_B, philo->id, RESET);
  pthread_mutex_unlock(&philo->table->print_msg_mtx);
}
