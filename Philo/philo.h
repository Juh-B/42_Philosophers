
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, usleep
#include <pthread.h> // mutex: init, destroy, lock, unlock
                    // threads: create, join, detach
#include <sys/time.h> // gettimeofday
#include <limits.h> //INT_MAX
#include <stdbool.h>

# define RESET  "\033[0m"
# define RED_B  "\033[1;31m"
# define GREEN  "\033[0;32m"
# define GREEN_B  "\033[1;32m"
# define YELLOW  "\033[0;33m"
# define YELLOW_B  "\033[1;33m"
# define WHITE_B  "\033[1;37m"

# define EXP_INPUT "./philo <nbr_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [<nbr_times_must_eat>]\n"
# define EXEMP_INPUT "Ex. ./philo 5 800 200 200 [5]"

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

// Mutex and Theread
typedef enum  e_opcode
{
  LOCK,
  UNLOCK,
  INIT,
  DESTROY,
  CREATE,
  JOIN,
  DETACH,
} t_opcode;

// Get_time
typedef enum  e_time_code
{
  SECOND,
  MILLISECOND,
  MICROSECOND,
} t_time_code;

// Philo states
typedef enum  e_status
{
  EATING,
  SLEEPING,
  THINKING,
  TAKE_FIRST_FORK,
  TAKE_SECOND_FORK,
  DIED,
} t_philo_status;

// Fork struct
typedef struct s_fork
{
  t_mtx fork;
  int   fork_id;
} t_fork;

// Philo struct
typedef struct  s_philo
{
  int id;
  long  meals_counter;
  bool  full;
  long  last_meal_time;
  t_fork  *first_fork;
  t_fork  *second_fork;
  pthread_t thread_id;
  t_table *table;
} t_philo;

// Table struct
struct s_table
{
  long  philo_nbr;
  long  time_to_die;
  long  time_to_eat;
  long  time_to_sleep;
  long  nbr_limit_meals;
  long  start_simulation;
  bool  end_simulation;
  bool  all_threads_ready;
  t_mtx table_mutex;
  t_mtx write_lock;
  t_fork  *forks;
  t_philo *philos;
};

// utils.c
void  error_exit(char *str);
long  get_time(t_time_code time_code);
void  precise_usleep(long usec, t_table *table);

// parsing.c
void  parse_input(t_table *table, char **argv);

// safe_functions.c
void  safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
void  safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void  *safe_malloc(size_t bytes);

// data.init.c
void  data_init(t_table *table);

// getters_setters.c
void  set_bool(t_mtx *mutex, bool *dest, bool value);
void  set_long(t_mtx *mutex, long *dest, long value);
long  get_long(t_mtx *mutex, long *value);
bool  get_bool(t_mtx *mutex, bool *value);
bool  simulation_finished(t_table *table);

// synchro_utils.c
void  wait_all_threads(t_table *table);

// write_status.c
void  write_status(t_philo_status status, t_philo *philo, bool debug);
