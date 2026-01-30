/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:42:30 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/30 19:42:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_INTERNAL_H
# define CODER_INTERNAL_H

# include "coder.h"
# include "errors.h"
# include "simulation_control.h"
# include "time_utils.h"

# define UINT64_MAXLEN				21
# define LOG_BUFFER_SIZE			64

# define MSG_TAKEN_DONGLE			"has taken a dongle"
# define MSG_TAKEN_DONGLE_STRLEN	18

# define MSG_COMPILING				"is compiling"
# define MSG_COMPILING_STRLEN		12

# define MSG_DEBUGGING				"is debugging"
# define MSG_DEBUGGING_STRLEN		12

# define MSG_REFACTORING			"is refactoring"
# define MSG_REFACTORING_STRLEN		14

# define MSG_BURNOUT				"burned out"
# define MSG_BURNOUT_STRLEN			10

enum e_event_id
{
	EVENT_TAKEN_DONGLE,
	EVENT_COMPILING,
	EVENT_DEBUGGING,
	EVENT_REFACTORING,
	EVENT_BURNOUT,
	MAX_EVENTS
};

void				init_coder_log(void);
enum e_exit_status	log_coder_event(const t_coder *coder, enum e_event_id event_id);

static inline
__attribute__((always_inline))
enum e_simulation_status	execute_task(const t_coder *coder, uint64_t task_duration_ms)
{
	return (monitored_wait_until(millis() + task_duration_ms, coder->deadline_ms));
}

static inline
__attribute__((always_inline))
void	reset_deadline(t_coder *coder, uint64_t time_to_burnout_ms)
{
	coder->deadline_ms = millis() + time_to_burnout_ms;
	set_abstime(&coder->deadline_ts, time_to_burnout_ms);
}

#endif
