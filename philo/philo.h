/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:19:16 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/10 13:09:12 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <limits.h> //INT_MAX
# include <pthread.h> // mutex: init, destroy, lock, unlock
					 // threads: create, join, detach

# define RESET  "\001\033[0m\002"
# define RED_B  "\001\033[1;31m\002"
# define GREEN  "\001\033[0;32m\002"
# define GREEN_B  "\001\033[1;32m\002"
# define YELLOW  "\001\033[0;33m\002"
# define YELLOW_B  "\001\033[1;33m\002"
# define CYAN_B  "\001\033[1;36m\002"
# define WHITE_B  "\001\033[1;37m\002"

# define EXP_INPUT "./philo <nbr_of_philos> <time_to_die> <time_to_eat> \
<time_to_sleep> [<nbr_times_must_eat>]\n"
# define EXEMP_INPUT "Ex: ./philo 5 800 200 200 5"
# define VALID_NBR "The value must be a positive integer between \
1 and 2147483647"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_status
{
	FIRST_FORK,
	SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_philo_status;

typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	pthread_t	thread_id;
}	t_philo;

typedef struct s_table
{
	int			nbr_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_meals;
	long		start_simulation;
	int			end_simulation;
	t_mtx		print_msg_mtx;
	t_mtx		table_mtx;
	t_mtx		monitor_mtx;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
}	t_table;

// error_clean.c
void	error_exit(char *str);
void	clean_all(t_table *table);

// init.c
void	init_structs(t_table *table, int argc, char **argv);

// message.c
void	print_msg(t_philo *philo, t_philo_status status);

// simulation.c
void	simulation(t_table *table);

// utils.c
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
long	current_time(void);
void	precise_sleep(long time, t_table *table);

// verif_input.c
void	verif_input(int argc, char **argv);
long	convert_arg(char *str);

#endif
