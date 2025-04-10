#include "philo_bonus.h"

void  print_msg(t_philo *philo, t_philo_status status)
{
  long  elapsed;

  elapsed = current_time() - philo->table->start_simulation;
  sem_wait(philo->table->print_msg_sem);
  // if (FIRST_FORK == status && !simulation_finished(philo->table))
  //   printf("%-6ld %s%d%s has taken the FIRST fork\n", elapsed, WHITE_B, philo->id, RESET);
  // else if (SECOND_FORK == status && !simulation_finished(philo->table))
  //   printf("%-6ld %s%d%s has taken the SECOND fork\n", elapsed, WHITE_B, philo->id, RESET);
  if ((FIRST_FORK == status || SECOND_FORK == status))// && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s has taken a fork\n", elapsed, WHITE_B, philo->id, RESET);
  else if (EATING == status)// && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s is eating%s\n", elapsed, WHITE_B, philo->id, GREEN_B, RESET);
    // printf("%-6ld %s%d%s is eating%s - %d Meal\n", elapsed, WHITE_B, philo->id, GREEN_B, RESET, philo->meals_eaten);
  else if (SLEEPING == status)// && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s is sleeping%s\n", elapsed, WHITE_B, philo->id, CYAN_B, RESET);
  else if (THINKING == status)// && !(philo->table->end_simulation))
    printf("%-6ld %s%d%s is thinking%s\n", elapsed, WHITE_B, philo->id, YELLOW_B, RESET);
  else // (DIED == status)
    printf("%-6ld %s%d died%s\n", elapsed, RED_B, philo->id, RESET);

  sem_post(philo->table->print_msg_sem);
}
