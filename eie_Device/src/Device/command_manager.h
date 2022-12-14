#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include <cjson/cJSON.h>
#include "device.h"

/** Sensor manager configuration structure */
struct DeviceManagerConfig {
    /** Name of the JSON file with the sensors config */
    const char *cfg_filename;
};

/**
 * Creates a sensor manager
 *
 * The sensor manager is in charge of dealing with the lifecycle
 * of the sensor devices. It creates the sensors from a JSON
 * config file and stores them in a hash table for name-based access.
 *
 * @param cfg Sensor manager configuration structure.
 *
 * @return Pointer to a sensor manager structure.
 */
struct DeviceManager *sensor_manager_create(struct DeviceManagerConfig *cfg);

/**
 * Gets a sensor from its name
 *
 * @param smgr Pointer to a sensor manager structure.
 * @param name Name of the sensor to get.
 *
 * @return Pointer to a sensor structure.
 */
struct Device *sensor_manager_sensor_get(struct DeviceManager *smgr,
                                         const char *name);

/**
 * Creates a sensor read command from a sensor name.
 * It should be destroyed using the command_destroy API.
 *
 * @param smgr Pointer to a sensor manager structure.
 * @param name Name of the sensor.
 *
 * @return Pointer to a sensor structure.
 */
struct Command *sensor_manager_read_cmd_create(
    struct DeviceManager *smgr,
    const char *name);

/**
 * Destroys a sensor manager
 *
 * Cleans up all the internal resources in the sensor manager,
 * including the sensor instances.
 *
 * @param smgr Pointer to a sensor manager structure.
 */
void sensor_manager_destroy(struct DeviceManager *smgr);

#endif // MANAGER_H_