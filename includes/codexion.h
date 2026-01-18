/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:41:04 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 01:33:31 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdint.h>
# include <sys/types.h>
# include "queue.h"

// UTILS
# define TRUE				1
# define FALSE				0

// CODER STATES
# define GIVE_ONE_DONGLE	0x01
# define TWO_DONGLES		0x02
# define DONGLES_RELEASED	0x04
# define WAITING_TO_COMPILE	0x08

typedef struct s_coder
{
	uint32_t		id;
	pthread_t		thread;
	pthread_mutex_t	local_mutex;
	pthread_mutex_t	*global_mutex;
	uint8_t			state;
	uint32_t		compilations_done;
	t_queue			last_compilation_time;
}	t_coder;

typedef uint32_t	(*t_scheduler)(uint32_t *available_dongles, uint32_t size, t_coder coders[size], uint32_t dongle_cooldown);

typedef struct s_codexion
{
	uint32_t	number_of_coders;
	uint32_t	time_to_burnout;
	uint32_t	time_to_compile;
	uint32_t	time_to_debug;
	uint32_t	time_to_refactor;
	uint32_t	number_of_compiles_required;
	uint32_t	dongle_cooldown;
	t_scheduler	scheduler;
}	t_codexion;

typedef void	*(*t_routine)(void *);

// ERRORS
const char	*get_error_str(uint32_t error_code);

// PARSER
int			codexion_parser(t_codexion *codexion, int argc, char **argv);

// GET RULES
int			get_coder_rules(uint32_t *burnout, uint32_t *compile, uint32_t *debug, uint32_t *refactor);
int			get_monitor_rules(uint32_t *ncoders, uint32_t *cooldown, uint32_t *ncompiles_required, t_scheduler *scheduler_func);

// TIME MANIPULATION
uint64_t	millis(void);
void		spend_time(uint32_t time, uint32_t *time_left);
uint64_t	time_elapsed(uint64_t *new_start);

// CODER ROUTINE
void		*start_working(t_coder *coder);

// MONITOR ROUTINE
uint32_t	fifo_scheduler(uint32_t *available_dongles, uint32_t size, t_coder coders[size], uint32_t dongle_cooldown);
void		*start_monitoring(t_coder coders[]);

#endif
