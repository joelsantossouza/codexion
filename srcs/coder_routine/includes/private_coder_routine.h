/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_coder_routine.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:57:36 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/20 10:07:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_CODER_ROUTINE_H
# define PRIVATE_CODER_ROUTINE_H

# include <stdio.h>
# include "public_coder_routine.h"
# include "time_manipulation.h"

// CODER ACTIVITY LOGS
# define TAKEN_DONGLE_MSG	"Has taken 1 dongle"
# define COMPILING_MSG		"Compiling"
# define DEBUGGING_MSG		"Debugging"
# define REFACTORING_MSG	"Refactoring"
# define BURNOUT_MSG		"had a burnout"

// CODER TASKS
enum
{
	COMPILE,
	DEBUG,
	REFACTOR,
	NUMBER_OF_TASKS
};

// CODER SIGNALS
enum
{
	CONTINUE_EXECUTION,
	STOP_EXECUTION
};

typedef struct s_coder_config
{
	uint32_t	tasks[NUMBER_OF_TASKS];
	uint32_t	burnout;
}	t_coder_config;

const t_coder_config	*coder_config(const uint32_t *compile, const uint32_t *debug, const uint32_t *refactor, const uint32_t *burnout);

static inline
void	log_coder_activity(const t_coder *coder, const char *log)
{
	pthread_mutex_lock(coder->global_mutex);
	printf("%lu %d %s\n", timestamp(NULL), coder->id, log);
	pthread_mutex_unlock(coder->global_mutex);
}

#endif
