/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:19:29 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/17 19:31:01 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdbool.h>
# include <ctype.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct			s_philo
{
	unsigned int		number;
	unsigned int		left_fork;
	unsigned int		right_fork;
}						t_philo;


typedef struct			s_philo_info
{
	unsigned int		philo_amount;
	unsigned int		t_die;
	unsigned int		t_eat;
	unsigned int		t_sleep;
	bool				must_eat;
	unsigned int		nb_must_eat;
	t_philo				philo;
	pthread_mutex_t*	forks;
	bool				philo_died;
	pthread_mutex_t		m_philo_died;
	unsigned long		time;
	unsigned long		time_last_eat;
}						t_philo_info;


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
int error_malloc_failed();
int error_mutex_failed();

#endif
