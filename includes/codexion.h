/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:41:04 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/09 12:33:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdint.h>
# include <sys/types.h>

# define TRUE	1
# define FALSE	0

typedef struct s_codexion
{
	uint32_t	number_of_coders;
	uint32_t	time_to_burnout;
	uint32_t	time_to_compile;
	uint32_t	time_to_debug;
	uint32_t	time_to_refactor;
	uint32_t	number_of_compiles_required;
	uint32_t	dongle_cooldown;
	const char	*scheduler;
}	t_codexion;

typedef struct s_coder
{
	uint32_t		id;
	pthread_mutex_t	local_mutex;
	pthread_mutex_t	*global_mutex;
	uint8_t			is_ready_to_compile;
	uint32_t		compilations_done;
	uint64_t		last_compilation_time;
}	t_coder;

// ERRORS
const char	*get_error_str(uint32_t error_code);

// PARSER
int			codexion_parser(t_codexion *codexion, int argc, char **argv);

// GET RULES
int	get_coder_rules(uint32_t *burnout, uint32_t *compile, uint32_t *debug, uint32_t *refactor);
int	get_monitor_rules(uint32_t *ncoders, uint32_t *cooldown, uint32_t *ncompiles_required);

// TIME MANIPULATION
size_t	millis(void);
void	spend_time(uint32_t time, uint32_t *time_left);
int		timed_wait(uint8_t *is_ready_flag, pthread_mutex_t *mutex, uint32_t *time_left);

// THREAD ROUTINES


#endif
