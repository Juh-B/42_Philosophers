#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep, fork
#include <pthread.h> // threads: create, join, detach
#include <semaphore.h> // semaphore: open, wair, post, close, unlink
#include <fcntl.h> // O_CREAT - sem_open
#include <sys/time.h> // gettimeofday
#include <limits.h> //INT_MAX

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define GREEN_B  "\033[1;32m"
# define YELLOW  "\033[0;33m"
# define YELLOW_B  "\033[1;33m"
# define CYAN_B  "\033[1;36m"
# define WHITE_B  "\033[1;37m"

# define EXP_INPUT "./philo <nbr_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [<nbr_times_must_eat>]\n"
# define EXEMP_INPUT "Ex: ./philo 5 800 200 200 5"

// typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef enum  e_status
{
  FIRST_FORK,
  SECOND_FORK,
  EATING,
  SLEEPING,
  THINKING,
  DIED,
} t_philo_status;

// typedef struct s_fork
// {
//   int   fork_id;
//   t_mtx fork;
// } t_fork;

typedef struct s_philo
{
    int       id;
    int       meals_eaten;
    long      last_meal_time;
    t_table   *table;
    // t_fork    *first_fork;
    // t_fork    *second_fork;
    // pthread_t thread_id;
}   t_philo;

typedef struct s_table
{
    int       nbr_philos;
    int       time_to_die;
    int       time_to_eat;
    int       time_to_sleep;
    int       nbr_meals;

    int       nbr_forks;

    long      start_simulation;
    int       end_simulation;

    sem_t     *forks_sem;
    sem_t     *print_msg_sem;
    sem_t     *monitor_sem;
    sem_t     *finish_sem;

    t_philo   *philos;
    pthread_t monitor;
}   t_table;

// error_clean.c
void  error_exit(char *str);
void  clean_all(t_table *table);

// init.c
void  init_structs(t_table *table, int argc, char **argv);

// mensagem.c
void  print_msg(t_philo *philo, t_philo_status status);

// simulation.c
void  simulation(t_table *table);

// utils.c
int   ft_isdigit(int c);
int	  ft_atoi(const char *nptr);
long  current_time(void);
void  precise_sleep(long time, t_table *table);

// verif_input.c
long  convert_arg(char *str);
void  verif_input(int argc, char **argv);

#endif
