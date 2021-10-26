/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 12:14:44 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/09/17 13:19:10 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_parse
{
	unsigned int	philo_amount;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	bool			must_eat;
	unsigned int	nb_must_eat;
}					t_parse;

typedef struct s_philo
{
	t_parse			parse;
	sem_t			*forks;
	bool			philo_died;
	sem_t			*print;
	unsigned long	time;
	unsigned int	number;
	pthread_t		monitor;
	unsigned long	time_last_eat;
	bool			done_eating;
	pid_t			*children;
}					t_philo;

/*
** error messages functions +--------------------------------------------------+
*/

void			error_argument_amount(void);
void			error_argument_numbers(int index, char *arg);
void			error_philo_amount(unsigned int amount);
void			error_time_to_low(char *time);
void			error_amount_to_eat_zero(void);
void			error_argument_empty_string(int index);
int				error_threads_failed(void);
void			error_malloc_failed(void);
void			error_fork_failed(void);

/*
** parse functions +----------------------------------------------------+
*/
int				parse_input(int ac, char **av, t_parse *parse);

/*
** philosophers functions +----------------------------------------------------+
*/

void			philo_init(t_philo *info);
void			philo_being_philo(t_philo *info);

/*
** utils +---------------------------------------------------------------------+
*/
unsigned long	get_time_ms(void);
void			ft_sleep(unsigned int time_to_pass);
int				ft_isnumber(char *str);
unsigned int	ft_atoui(char *str);

#endif
