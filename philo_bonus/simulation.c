#include "philo_bonus.h"

// static int  philo_died(t_table *table, int *count)
// {
//   int     i;

//   i = 0;
//   while (i < table->nbr_philos)
//   {
//     // sem_wait(table->finish_sem);
//     if ((current_time() - table->philos[i].last_meal_time) > table->time_to_die)
//     {
//       print_msg(table->philos[i], DIED);
//       table->end_simulation = 1;
//       sem_post(table->finish_sem);
//       return (1);
//     }
//     if (table->nbr_meals > 0 &&	table->philos[i].meals_eaten >= table->nbr_meals)
//       (*count)++;
//       sem_post(table->finish_sem);
//     i++;
//   }
//   return (0);
// }

// static void  *monitor_dinner(void *arg)
// {
//   // AJUSTAR PARA PARAR OS PROCESSOS
//   t_table *table;
// 	int			nbr_philos_full;

//   table = (t_table *)arg;
//   sem_wait(&table->finish_sem);
// 	while (!table->end_simulation)
// 	{
//     nbr_philos_full = 0;
//     if (philo_died(table, &nbr_philos_full))
//       return (NULL);
// 		if (table->nbr_meals > 0 && nbr_philos_full == table->nbr_philos)
// 		{
// 			table->end_simulation = 1;
// 			return (NULL);
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

static void *philo_rotine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
      // if (philo->table->nbr_philos == 1)
      // {
      //   print_msg(philo, FIRST_FORK);
      //   break ;
      // }
      printf("4. HEREEEE - %d\n", sem_wait(philo->table->forks_sem));
      sem_wait(philo->table->forks_sem);
      print_msg(philo, FIRST_FORK);
      sem_wait(philo->table->forks_sem);
      print_msg(philo, SECOND_FORK);
      philo->last_meal_time = current_time();
      philo->meals_eaten++;
      print_msg(philo, EATING);
      precise_sleep(philo->table->time_to_eat, philo->table);
      sem_post(philo->table->forks_sem);
      sem_post(philo->table->forks_sem);

      print_msg(philo, SLEEPING);
      precise_sleep(philo->table->time_to_sleep, philo->table);
      print_msg(philo, THINKING);
    }
    return (NULL);
}

void  simulation(t_table *table)
{
  // int   i;
  printf("1. HEREEEE\n");
  pid_t pid = fork();
  // pid_t pid2;

  if (pid == 0)
  {
    fork();
  }


  // i = 0;

  if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
  if (pid == 0)// || pid2 == 0)
  {
    printf("2..HEREEEE\n");
    sem_wait(table->monitor_sem);
    philo_rotine(&table->philos);
    usleep(100000);
    sem_post(table->monitor_sem);

  }
  if (pid > 0)
  {
    printf("3..HEREEEE\n");
    // pthread_create(&table->monitor, NULL, monitor_dinner, table);
    // pthread_join(table->monitor, NULL);
  }




  // int i;

  // i = 0;
  // while (i < table->nbr_philos)
  // {
  //   pthread_create(&table->philos[i].thread_id, NULL, philo_rotine, &table->philos[i]);
  //   i++;
  // }

  // i = 0;
  // while (i < table->nbr_philos)
  // {
  //   pthread_join(table->philos[i].thread_id, NULL);
  //   i++;
  // }
  // return (table->end_simulation);
}


// ------------------------------------
// pid_t pid = fork();
// if (pid == 0)
// {
//     // filho -> filósofo
//     philo_routine(...);
//     exit(0);
// }
// else
// {
//     // pai -> talvez roda monitor aqui
//     waitpid(pid, NULL, 0);
// }


// -------------------------------

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>    // Para O_CREAT
// #include <sys/wait.h> // Para wait
// #include <semaphore.h>

// int	main(void)
// {
// 	sem_t *sem;

// 	// Criar/abrir semáforo com valor inicial 1 (como um mutex)
// 	sem = sem_open("/print_sem", O_CREAT, 0644, 1);
// 	if (sem == SEM_FAILED)
// 	{
// 		perror("sem_open");
// 		exit(1);
// 	}

// 	pid_t pid = fork();

// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		exit(1);
// 	}
// 	else if (pid == 0)
// 	{
// 		// Processo filho
// 		for (int i = 0; i < 5; i++)
// 		{
// 			sem_wait(sem); // trava o semáforo
// 			printf("Filho: linha %d\n", i + 1);
// 			usleep(100000); // só pra simular trabalho
// 			sem_post(sem); // libera o semáforo
// 		}
// 		exit(0);
// 	}
// 	else
// 	{
// 		// Processo pai
// 		for (int i = 0; i < 5; i++)
// 		{
// 			sem_wait(sem);
// 			printf("Pai: linha %d\n", i + 1);
// 			usleep(100000);
// 			sem_post(sem);
// 		}
// 		wait(NULL); // espera o filho terminar

// 		// Limpeza final
// 		sem_close(sem);
// 		sem_unlink("/print_sem");
// 		printf("Finalizado!\n");
// 	}
// 	return (0);
// }
