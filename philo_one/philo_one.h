/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:19:29 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/13 14:25:46 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdbool.h>
# include <ctype.h>

typedef struct		s_philo
{
	unsigned int	nb_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	bool			must_eat;
	unsigned int	nb_must_eat;
}					t_philo;


/*
** utils
*/

int				ft_isdigit(char c);
unsigned int    ft_atoui(char *str);
int             ft_isnumber(char* str);

/*
** error messages
*/

int error_argument_amount();
int error_argument_numbers(int index, char* arg);
int error_philo_amount();
int error_time_to_low(char* time);
int error_amount_to_eat_zero();

#endif
