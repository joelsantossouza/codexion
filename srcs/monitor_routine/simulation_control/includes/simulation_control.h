/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:13:34 by joesanto          #+#    #+#             */
/*   Updated: 2026/02/03 15:19:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_CONTROL_H
# define SIMULATION_CONTROL_H

# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>

enum e_simulation_status
{
	SIMULATION_RUNNING,
	SIMULATION_STOPPED,
};

enum e_table_actions
{
	TABLE_GET,
	TABLE_INIT,
	TABLE_DESTROY
};

typedef struct s_signal
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_signal;

enum e_simulation_status	monitored_wait_until(uint64_t wait_until_ms, uint64_t limit_ms);
bool						simulation_control(const bool *set_state);
void						stop_simulation(void);

t_signal					*round_table_control(uint32_t id, enum e_table_actions action);

static inline
bool	is_simulation_running(void)
{
	return (simulation_control(NULL));
}

static inline
t_signal	*table_init(void)
{
	return (round_table_control(0, TABLE_INIT));
}

static inline
void	table_destroy(void)
{
	round_table_control(0, TABLE_DESTROY);
}

static inline
t_signal	*table_get_signal(uint32_t id)
{
	return (round_table_control(id, TABLE_GET));
}

#endif
