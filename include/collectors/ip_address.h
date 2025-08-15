#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#include "core.h"

/**
 * IPAddressCollector Structure
 *
 * This structure represents a metric collector that retrieves and displays
 * the current IP address of a specified network interface. It extends the
 * base functionality of the MetricCollector to provide specific behavior
 * for IP address collection.
 *
 * Members:
 *
 * - MetricCollector base:
 *   The base structure that provides common functionality for all metric collectors,
 *   including the update mechanism and status management.
 *
 * - const char *interface_name:
 *   A string representing the name of the network interface for which the IP address
 *   will be collected. This allows the collector to target a specific interface
 *   when retrieving the IP address.
 */
typedef struct {
    MetricCollector base;
    const char *interface_name;
} IPAddressCollector;

/**
 * Function to create a new IPAddressCollector.
 *
 * This function creates and initializes a new instance of a IPAddressCollector,
 * which is responsible for collecting and displays the current IP address of a
 * specified network interface.
 *
 * Parameters:
 *
 * - const char *interface_name:
 *   A string representing the name of the network interface to monitor.
 *
 * Returns:
 *
 * - A IPAddressCollector instance that is initialized with the provided interface
 *   name. The caller is responsible for managing the lifecycle of the returned
 *   collector.
 */
IPAddressCollector new_ip_address_collector(const char *interface_name);

#endif // IP_ADDRESS_H
