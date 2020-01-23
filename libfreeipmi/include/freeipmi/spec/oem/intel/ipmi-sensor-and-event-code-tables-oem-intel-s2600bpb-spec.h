/*
 * Copyright (C) 2003-2015 FreeIPMI Core Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_INTEL_S2600BPB_SPEC_H
#define IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_INTEL_S2600BPB_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/spec/oem/intel/ipmi-sensor-and-event-code-tables-oem-intel-common-spec.h>

/*
 * S2600BPB
 */

/* Event Reading Type Code = IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NVME_CRITICAL_WARNING_SENSOR
 * Sensor Type = IPMI_SENSOR_TYPE_DISK_DRIVE
 */
#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA1_DISK_DRIVE_BITMASK 0x04
#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA1_DISK_DRIVE_SHIFT   0

#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA2_DISK_DRIVE_SPARE_SPACE_BELOW_THRESHOLD          0x01
#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA2_DISK_DRIVE_TEMPERATURE_ABOVE_OR_BELOW_THRESHOLD 0x02
#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA2_DISK_DRIVE_NVM_RELIABILITY_DEGRADED             0x04
#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA2_DISK_DRIVE_IN_READ_ONLY_MODE                    0x08
#define IPMI_OEM_INTEL_NVME_CRITICAL_WARNING_EVENT_DATA2_DISK_DRIVE_VOLATILE_BACKUP_SERVICE_FAILED       0x10

/* Sensor Type = IPMI_SENSOR_TYPE_SYSTEM_EVENT */
/* achu: this is not documented in IPMI spec, so assuming Intel OEM
 * extension?  Or possibly extension not yet released by Intel? */
#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_IMAGE_IS_UPLOADED 0x07
#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_IMAGE_IS_LOST     0x08

#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_EVENT_DATA2_BIOS_CONFIGURATION_TABLE  0x00
#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_EVENT_DATA2_BIOS_CONFIGURATION_CHANGE 0x01
#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_EVENT_DATA2_BIOS_IMAGE                0x02
#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_EVENT_DATA2_ME_IMAGE                  0x03
#define IPMI_OEM_INTEL_SENSOR_TYPE_SYSTEM_EVENT_EVENT_DATA2_FD_IMAGE                  0x04

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_INTEL_S2600BPB_SPEC_H */
