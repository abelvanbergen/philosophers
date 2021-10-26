/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 09:47:10 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 14:18:13 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	are_all_numbers(char **numbers, int amount)
{
	int	i;

	i = 1;
	while (i < amount)
	{
		if (ft_isnumber(numbers[i]) == 0)
			error_argument_numbers(i, numbers[i]);
		if (ft_strlen(numbers[i]) == 0)
			error_argument_empty_string(i);
		i++;
	}
	return (0);
}

static void	parse_times(char **av, t_parse *time)
{
	time->t_die = ft_atoui(av[2]);
	if (time->t_die < 60)
		error_time_to_low("Time to die");
	time->t_eat = ft_atoui(av[3]);
	if (time->t_eat < 60)
		error_time_to_low("Time to eat");
	time->t_sleep = ft_atoui(av[4]);
	if (time->t_sleep < 60)
		error_time_to_low("Time to sleep");
}

int	parse_input(int ac, char **av, t_parse *parse)
{
	are_all_numbers(av, ac);
	parse->philo_amount = ft_atoui(av[1]);
	if (parse->philo_amount == 0 || parse->philo_amount > 200)
		error_philo_amount(parse->philo_amount);
	parse_times(av, parse);
	if (ac == 6)
	{
		parse->must_eat = true;
		parse->nb_must_eat = ft_atoui(av[5]);
		if (parse->nb_must_eat == 0)
			error_amount_to_eat_zero();
	}
	else
		parse->must_eat = false;
	return (0);
}
