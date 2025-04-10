#include "philo_bonus.h"

void  error_exit(char *str)
{
  printf("%sError%s\n%s\n", RED_B, RESET, str);
  exit(EXIT_FAILURE);
}

void clean_all(t_table *table)
{
  // int i;

  // i = 0;
  // if (table->forks)
  // {
  //   while (i < table->nbr_philos)
  //   {
  //     pthread_mutex_destroy(&table->forks[i].fork);
  //     i++;
  //   }
  //   free(table->forks);
  // }
  if (table->philos)
    free(table->philos);
  sem_close(table->forks_sem);
  sem_close(table->monitor_sem);
  sem_close(table->print_msg_sem);
  sem_close(table->finish_sem);
  sem_unlink("/fork_sem");
  sem_unlink("/msg_sem");
  sem_unlink("/monit_sem");
  sem_unlink("/end_sem");
  // pthread_mutex_destroy(&table->print_msg_mtx);
  // pthread_mutex_destroy(&table->table_mtx);
  // pthread_mutex_destroy(&table->monitor_mtx);
}
