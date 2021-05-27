/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 09:26:57 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/27 14:06:23 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdbool.h>

typedef struct s_philo_info
{
	unsigned int	philo_amount;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	bool			must_eat;
	unsigned int	nb_must_eat;
	sem_t			*forks;
	bool			philo_died;
	sem_t			*s_philo_died;
	sem_t			*print;
	unsigned long	time;
}					t_philo_info;

typedef struct s_philo
{
	unsigned int	number;
	unsigned long	time_last_eat;
	pthread_t		monitor;
	bool			done_eating;
	t_philo_info	*info;
}					t_philo;

/*
** error messages functions +--------------------------------------------------+
*/

void	error_argument_amount(void);
void	error_argument_numbers(int index, char *arg);
void	error_philo_amount(int amount);
void	error_time_to_low(char *time);
void	error_amount_to_eat_zero(void);

#endif
