/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/12 18:19:29 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/05/12 22:54:07 by abelfrancis   ########   odam.nl         */
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

#endif
