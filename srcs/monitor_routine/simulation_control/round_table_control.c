/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_table_control.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:42:40 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/03 15:41:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion_parser.h"
#include "simulation_control.h"

static
void	destroy_round_table(uint32_t size, t_signal round_table[size])
{
	uint32_t	i;

	i = -1;
	while (++i < size)
	{
		pthread_mutex_destroy(&round_table[i].mutex);
		pthread_cond_destroy(&round_table[i].cond);
	}
}

static
int	init_round_table(uint32_t size, t_signal round_table[size])
{
	uint32_t	i;
	int			exit_status;

	i = -1;
	while (++i < size)
	{
		exit_status = pthread_mutex_init(&round_table[i].mutex, NULL);
		if (exit_status != 0)
		{
			destroy_round_table(i, round_table);
			return (exit_status);
		}
		exit_status = pthread_cond_init(&round_table[i].cond, NULL);
		if (exit_status != 0)
		{
			pthread_mutex_destroy(&round_table[i].mutex);
			destroy_round_table(i, round_table);
			return (exit_status);
		}
	}
	return (0);
}

t_signal	*round_table_control(uint32_t id, enum e_table_actions action)
{
	static t_signal	round_table[MAX_CODERS];

	if (action == TABLE_INIT)
	{
		if (init_round_table(MAX_CODERS, round_table) != 0)
			return (NULL);
	}
	else if (action == TABLE_DESTROY)
	{
		destroy_round_table(MAX_CODERS, round_table);
		return (NULL);
	}
	return (&round_table[id]);
}
