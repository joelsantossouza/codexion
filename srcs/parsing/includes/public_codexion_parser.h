/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public_codexion_parser.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/18 19:56:47 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_PARSER_H
# define CODEXION_PARSER_H

# include <stdint.h>

typedef struct s_coder t_coder;
typedef struct s_monitor_config t_monitor_config;
typedef int	(*t_scheduler)(t_coder coders[], const t_monitor_config *config, uint32_t *available_dongles, t_coder **priority_coder);

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

int	codexion_parser(t_codexion *codexion, int argc, char **argv);

#endif
