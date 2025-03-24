#include "philo.h"

// Numericos e Int
// timestamp > 60ms

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int	ft_atoi(const char *nptr)
// {
// 	int	i;
// 	int	sign;
// 	int	number;

// 	i = 0;
// 	sign = 1;
// 	number = 0;
// 	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
// 		i++;
// 	if (nptr[i] == '+' || nptr[i] == '-')
// 	{
// 		if (nptr[i] == '-')
// 			sign *= -1;
// 		i++;
// 	}
// 	while (ft_isdigit(nptr[i]) > 0)
// 	{
// 		number = (number * 10) + (nptr[i] - '0');
// 		i++;
// 	}
// 	return (number * sign);
// }

// static int *verif_input(const char *str)
// {
//   int		i;
// 	long	number;

// 	i = 0;
// 	number = 0;
//   while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '+')
//     i++;
//   else if (str[i] == '-')
//     error_exit(2);
// 	while (ft_isdigit(str[i]))
// 	{
// 		number = (number * 10) + (str[i] - '0');
// 		i++;
// 	}
// 	if (str[i] == '\0' && (number > 0 && number <= 2147483647))
// 		return (1);
// 	else if (!ft_isdigit(str[i]))
//     error_exit(3);
//   else if (number == 0  || number > 2147483647)
//     error_exit(4);
//   else
// 		return (0);
// }

// static long value_tol(const char *str)
// {
//   long nbr;

//   nbr = 0;
//   if (valid_input(str))
//     nbr = ft_atoi(str);
//   return (nbr);
// }


static long verif_input(const char *str)
{
  int		i;
	long	number;

	i = 0;
	number = 0;
  while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
    i++;
  else if (str[i] == '-')
    error_exit("Wrong input values!\nPlease, use only positive numbers.");
	while (ft_isdigit(str[i]))
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] == '\0' && (number > 0 && number <= 2147483647))
		return (number);
	else if (!ft_isdigit(str[i]))
    error_exit("The input isn't a correct digit.\nUse only positive numbers.");
  else if (number == 0  || number > 2147483647)
    error_exit("The value is huge.\nINT_MAX (2147483647) is the limit.");
  else
		return (0);
}

void  parse_input(t_table *table, char **argv)
{
  table->philo_nbr = verif_input(argv[1]);
  table->time_to_die = verif_input(argv[2]) * 1e3;
  table->time_to_eat = verif_input(argv[3]) * 1e3;
  table->time_to_sleep = verif_input(argv[4]) * 1e3;
  if (table->time_to_die < 6e4
      || table->time_to_eat < 6e4
      || table->time_to_sleep < 6e4)
      error_exit("Use timestamps greater than 60ms.");
  if (argv[5])
    table->nbr_limit_meals = verif_input(argv[5]);
  else
    table->nbr_limit_meals = -1;
}
