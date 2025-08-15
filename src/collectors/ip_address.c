#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "collectors/ip_address.h"
#include "core.h"

static void update(MetricCollector *self) {

    IPAddressCollector *s = (IPAddressCollector *)self;

    struct ifaddrs *ifaddr, *ifa;
    char ip_buffer[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) {
        snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "COLLECTOR ERROR");
        return;
    }

    // Initialize status to indicate no IP found
    snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "󰲜 Offline");

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL || strcmp(ifa->ifa_name, s->interface_name) != 0)
            continue; // Skip if no address or not the desired interface

        // Check if the address is an IPv4 address
        if (ifa->ifa_addr->sa_family == AF_INET) {
            if (inet_ntop(AF_INET, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, ip_buffer, sizeof(ip_buffer)) != NULL) {
                snprintf(self->status, MAX_COLLECTOR_STATUS_SIZE, "󰲝 %s", ip_buffer);
                break; // Exit loop after finding the first IP
            }
        }
    }

    freeifaddrs(ifaddr);
}

IPAddressCollector new_ip_address_collector(const char *interface_name) {
    IPAddressCollector ret = {.interface_name = interface_name};
    initialize_collector_base(&ret.base, "IP Address Collector", 60, update);
    return ret;
}
