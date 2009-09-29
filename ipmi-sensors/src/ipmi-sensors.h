/*
  Copyright (C) 2003-2009 FreeIPMI Core Team

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
*/

#ifndef _IPMI_SENSORS_H
#define _IPMI_SENSORS_H

#include <freeipmi/freeipmi.h>

#include "tool-cmdline-common.h"
#include "tool-sdr-cache-common.h"
#include "tool-sensor-common.h"
#include "pstdout.h"

enum ipmi_sensors_argp_option_keys
  {
    VERBOSE_KEY = 'v',
    SDR_INFO_KEY = 'i',
    QUIET_READINGS_KEY = 'q',
    SENSORS_KEY = 's',          /* legacy */
    RECORD_IDS_KEY = 'r',
    EXCLUDE_RECORD_IDS_KEY = 'R',
    GROUP_KEY = 160,              /* legacy */
    GROUPS_KEY = 'g',             /* legacy */
    EXCLUDE_GROUPS_KEY = 161,   /* legacy */
    LIST_GROUPS_KEY = 162,      /* legacy */
    SENSOR_TYPE_KEY = 163,
    SENSOR_TYPES_KEY = 't',
    EXCLUDE_SENSOR_TYPES_KEY = 'T',
    LIST_SENSOR_TYPES_KEY = 'L',
    BRIDGE_SENSORS_KEY = 'b',
    SHARED_SENSORS_KEY = 164,
    INTERPRET_OEM_DATA_KEY = 165,
    IGNORE_NOT_AVAILABLE_SENSORS_KEY = 166,
    ENTITY_SENSOR_NAMES_KEY = 167,
    COMMA_SEPARATED_OUTPUT_KEY = 168,
    NON_ABBREVIATED_UNITS_KEY = 169,
    NO_SENSOR_TYPE_KEY = 170,
    LEGACY_OUTPUT_KEY = 171,
  };

struct ipmi_sensors_arguments
{
  struct common_cmd_args common;
  struct sdr_cmd_args sdr;
  struct hostrange_cmd_args hostrange;
  int verbose_count;
  int sdr_info;
  int quiet_readings;
  unsigned int record_ids[MAX_SENSOR_RECORD_IDS];
  unsigned int record_ids_length;
  unsigned int exclude_record_ids[MAX_SENSOR_RECORD_IDS];
  unsigned int exclude_record_ids_length;
  char sensor_types[MAX_SENSOR_TYPES][MAX_SENSOR_TYPES_STRING_LENGTH+1];
  unsigned int sensor_types_length;
  char exclude_sensor_types[MAX_SENSOR_TYPES][MAX_SENSOR_TYPES_STRING_LENGTH+1];
  unsigned int exclude_sensor_types_length;
  int list_sensor_types;
  int bridge_sensors;
  int shared_sensors;
  int interpret_oem_data;
  int ignore_not_available_sensors;
  int entity_sensor_names;
  int comma_separated_output;
  int non_abbreviated_units;
  int no_sensor_type;
  int legacy_output;
};

typedef struct ipmi_sensors_prog_data
{
  char *progname;
  struct ipmi_sensors_arguments *args;
} ipmi_sensors_prog_data_t;

typedef struct ipmi_sensors_state_data
{
  ipmi_sensors_prog_data_t *prog_data;
  ipmi_ctx_t ipmi_ctx;
  pstdout_state_t pstate;
  char *hostname;
  ipmi_sdr_cache_ctx_t sdr_cache_ctx;
  ipmi_sdr_parse_ctx_t sdr_parse_ctx;
  ipmi_sensor_read_ctx_t sensor_read_ctx;
  int output_headers;
  struct sensor_entity_id_counts entity_id_counts;
  struct sensor_column_width column_width;
  uint32_t manufacturer_id;
  uint16_t product_id;
} ipmi_sensors_state_data_t;

#endif
