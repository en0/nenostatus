# nenostatus

**nenostatus** is a status line application designed for DWM (Dynamic Window Manager) and similar
window managers. It aims to provide a minimalistic and user-customizable interface for monitoring
system metrics. The application allows users to easily add new metric collectors or customize
existing ones, following the principles of simplicity and extensibility.

## Quick Start Guide

To get started with nenostatus, follow these steps to clone the repository, build, and install the application:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/en0/nenostatus.git
   cd nenostatus
   ```

2. **Build the application:**
   ```bash
   make
   ```

3. **Install the application:**
   ```bash
   sudo make install
   ```

### Prerequisites

Before building nenostatus, ensure you have the following dependencies installed:

- **git**
- **make**
- **gcc**
- **libX11**
- **libm**
- **libasound**

## Features

- **Monitors system for basic metrics:** Collects and displays various system metrics such as CPU load, memory usage, battery status, and more.
- **Built-in notifications:** Alerts users for low battery and high temperature conditions.
- **Easy to extend and modify:** Users can easily add new metric collectors or customize existing ones to fit their needs.

## Application Architecture

The nenostatus application is structured around the following key components:

- **MetricCollector:** A base structure that defines how metrics are collected. Each collector has an update function to gather data.
- **OutputStrategy:** Defines how the collected metrics are displayed, allowing for flexibility in output methods (e.g., console output or integration with window managers).
- **MetricManager:** Orchestrates the collection of metrics from multiple collectors and manages their output to the specified output strategy.

## Changing the Layout of the Bar

To customize the layout of the status bar, you can modify the `src/main.c` file. This file contains
the configuration for the metric collectors that will be displayed. You can add, remove, or
rearrange the collectors in the `collectors` array to change what is shown on the status bar.

Example:
```c
MetricCollector *collectors[] = {
    (MetricCollector *)&space,
    (MetricCollector *)&avol,
    (MetricCollector *)&sep,
    // Add or remove collectors as needed
};
```

## Adding a New Collector

To add a new metric collector, follow these steps:

1. **Create a new collector header file:** Define a new structure that extends `MetricCollector` and implement the necessary update function.
2. **Implement the collector logic:** In the corresponding `.c` file, implement the logic to gather the desired metric and update the `status` field.
3. **Instantiate the collector:** In `src/main.c`, create an instance of your new collector and add it to the `collectors` array.

Example of a new collector:
```c
CustomCollector custom_collector = new_custom_collector("Some Parameter");
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.
