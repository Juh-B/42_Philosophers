#include "philo.h"

int main(int argc, char **argv)
{
  t_table table;

  if (argc == 5 || argc == 6)
  {
    parse_input(&table, argv);
    data_init(&table);
    dinner_start(&table);
    clean(&table);
  }
  else
  {
    error_exit("Wrong input:\nExpected: "EXP_INPUT EXEMP_INPUT);
  }

  return (0);
}
