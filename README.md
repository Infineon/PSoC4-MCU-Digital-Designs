## Table of Contents

* [Introduction](#introduction)
* [Navigating the Repository](#navigating-the-repository)
* [Required Tools](#required-tools)
* [Code Examples List](#code-examples-list)
* [References](#references)

# Introduction

This repository contains examples and demos for [PSoC 4 MCU](http://www.cypress.com/products/32-bit-arm-cortex-m0-psoc-4) family of devices, world's Most Flexible 32-bit ARM Cortex-M0 One-Chip Solution. Cypress provides a wealth of data at [www.cypress.com](http://www.cypress.com/) to help you select the right PSoC device and effectively integrate it into your design. Visit our [PSoC 4 MCU](http://www.cypress.com/products/32-bit-arm-cortex-m0-psoc-4) webpage to explore more about PSoC 4 MCU family of device.

Feel free to explore through the code example source files and Let us innovate together!

# Navigating the Repository

This repository provides examples that demonstrates how to develop PSoC 4 MCU based digital designs. PSoC 4 MCU provides wide digital resources like Serial Communication block (SCB) for UART, I2C, SPI based serial communication, TCPWM block for timer/counter/PWM based designs, UDBs for implementing digital functions like encoders, decoders, state machines etc. The examples listed out in this repository helps you understand how to use them and incorporate these features in your design.
If you are new to developing projects with PSoC 4 MCU, we recommend you to refer the [PSoC 4 Getting Started](https://github.com/cypresssemiconductorco/PSoC4-MCU-Getting-Started) GitHub page which can help you familiarize with device features and guides you to create a simple PSoC 4 design with PSoC Creator IDE. For other block specific designs please refer to the following GitHub repositories:

#### 1. [Analog Designs](https://github.com/cypresssemiconductorco/PSoC4-MCU-Analog-Designs)
#### 2. [Capacitive Touch Designs](https://github.com/cypresssemiconductorco/PSoC4-MCU-Capacitive-Touch-Designs)
#### 3. [BLE Connectivity Designs](https://github.com/cypresssemiconductorco/PSoC4-MCU-BLE-Connectivity-Designs)
#### 4. [USB Connectivity Designs](https://github.com/cypresssemiconductorco/PSoC4-MCU-USB-Connectivity-Designs)
#### 5. [Device Related Designs](https://github.com/cypresssemiconductorco/PSoC4-MCU-Device-Related-Designs)
#### 6. [PSoC 4 Pioneer Kit](https://github.com/cypresssemiconductorco/PSoC4-MCU-Pioneer-Kits)
#### 7. [System Designs](https://github.com/cypresssemiconductorco/PSoC4-MCU-System-Designs)

You can use these block level examples to guide you through the development of a system-level design. All the code examples in this repository comes with well documented design guidelines to help you understand the design and how to develop it. The code examples and their associated documentation are in the Code Example folder in the repository.

# Required Tools

## Software
### Integrated Development Environment (IDE)
To use the code examples in this repository, please download and install
[PSoC Creator](http://www.cypress.com/products/psoc-creator)

## Hardware
### PSoC 4 MCU Development Kits
* [CY8CKIT-042-BLE-A Bluetooth® Low Energy 4.2 Compliant Pioneer Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-042-ble-bluetooth-low-energy-42-compliant-pioneer-kit).

* [CY8CKIT-041-41XX PSoC 4100S CapSense Pioneer Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-041-41xx-psoc-4100s-capsense-pioneer-kit). 

* [CY8CKIT-046 PSoC 4 L-Series Pioneer Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-046-psoc-4-l-series-pioneer-kit)

* [CY8CKIT-044 PSoC 4 M-Series Pioneer Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-044-psoc-4-m-series-pioneer-kit)

* [CY8CKIT-049-4xxx PSoC 4 Prototyping Kit](http://www.cypress.com/documentation/development-kitsboards/psoc-4-cy8ckit-049-4xxx-prototyping-kits)

* [CY8CKIT-042 PSoC 4 Pioneer Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-042-psoc-4-pioneer-kit) 

**Note** Please refer to the code example documnetation for selecting the appropriate kit for testing the project

## Code Example List

### Encoders Decoders Counters Sequence generators
#### 1. CE95354 - Quadrature Decoder with PSoC 4
This data sheet code example demonstrates operation of the TCPWM (Quadrature Decoder Mode) component with the PSoC Creator Software.
#### 2. CE95294 - 7-bit Down Counter with PSoC 3/4/5LP
This code example demonstrates functionality of the Count7 component.
#### 3. CE95296 - Cyclic Redundancy Check with PSoC 3/4/5LP
This code example demonstrates operation of the CRC (Cyclic Redundancy Check) component with the PSoC Creator Software. The CRC-16 polynomial, 16 bit resolution and single cycle configuration is demonstrated.
#### 4. CE95349 - Pseudo Random Sequence (PRS) generator with PSoC 3/4/5LP
This datasheet code example demonstrates operation of the PRS (Pseudo Random Sequence) component with the PSoC Creator Software. The clocked and API Single Step run modes, 16 bit resolution and single cycles implementation configuration is demonstrated.

### LUTs
#### 1. CE95334 - Lookup table (LUT) with PSoC 3/4/5LP
The LUT Example design project contains an example for the use of the LUT component. This simple example sets the input and output to 2. Output is verified using a Character LCD.

### I2C
#### 1. CE95362 - Cypress EzI2C communication using a Serial Communication Block (SCB) with PSoC 4
This example project demonstrates the basic operation of the EZ I2C slave (SCB mode) component. The EZ I2C slave accepts the packet with a command from the I2C master to control the RGB LED color. The EZ I2C slave updates its buffer with a status packet in response to the accepted command.
#### 2. CE95363 - I2C Master using a Serial Communication Block (SCB) with PSoC 4
This code example demonstrates the basic operation of the I2C master (SCB mode) component. I2C master sends packet with command to I2C slave to control RGB LED color. The packet with status is read back.
#### 3. CE95364 - I2C Slave using a Serial Communication Block (SCB) with PSoC 4
This code example demonstrates the basic operation of the I2C slave (SCB mode) component. The I2C slave accepts packet with command from I2C master to control RGB LED color. The I2C slave updates its buffer with status packet in response to the accepted command.

### Signal Modulation
#### 1. CE95348 - Precise Illumination Signal Modulation (PrISM) with PSoC 3/4/5LP
This datasheet code example demonstrates operation of the PrISM component with the PSoC Creator Software. The LED blinking is demonstrated.

### SPI
#### 1. CE95365 - SPI Transmit and Receive using a Serial Communication Block (SCB) with PSoC 4
This datasheet code example demonstrates operation of the SCB component configured in SPI. The first instance of SCB is configured as SPI master and the second as SPI Slave mode. The SPI master communicates with slave (bit rate 1Mbps).

### TCPWM
#### 1. CE95351 - Fixed Function PWM with PSoC 4
This code example demonstrates operation of the TCPWM (PWM Mode) component with the PSoC Creator Software.
#### 2. CE95380 - TCPWM configuration with PSoC 4
This data sheet code example demonstrates operation of the TCPWM (Unconfigured TCPWM Mode) component with the PSoC Creator Software
#### 3. CE95385 - TCPWM Timer/Counter Operation with PSoC 4
This data sheet code example demonstrates operation of the TCPWM (Timer / Counter Mode) component with the PSoC Creator Software.

### UART
#### 1. CE95366 PSoC® 4 SCB UART
This example shows how to use the Serial Communication Block (SCB) Component as UART in PSoC® 4.This datasheet code example demonstrates operation of the SCB component configured in UART Tx+Rx mode. Data typed on the HyperTerminal is sent through serial port to the DVK and displayed on the LCD.After that this data is sent back and displayed on the HyperTerminal.
#### 2. CE95379 - Software based UART transmit with PSoC 3/4/5LP
This code example demonstrates basic functionality of Software Transmit UART component.
#### 3. CE95388 - UART Receive with PSoC 3/4/5LP
The UART Rx design project contains an example for the use of the UART component. This example demonstrates the UART Reception (Rx) mechanism. Data input via HyperTerminal is sent through the serial port and displayed on the LCD module.
#### 4. CE95389 - UART Transmit with PSoC 3/4/5LP
The UART TX design project contains an example for the use of the UART component. This example demonstrates the UART Transmission (TX) -mechanism. Data sent via the serial port is displayed on HyperTerminal and the LCD module.

## References
#### 1. PSoC 4 MCU
PSoC 4 is the world's Most Flexible 32-bit ARM Cortex-M0 One-Chip Solution. PSoC 4 has tackled some of the complex portions of embedded system design making it easier for you to get your product to market. Functions such as analog sensor integration, capacitive touch, and wireless connectivity have been integrated and optimized in PSoC 4 to “just work” so you don’t have to. To learn more on the device. Learn more: [PSoC 4 MCU](http://www.cypress.com/products/32-bit-arm-cortex-m0-psoc-4)

####  2. PSoC 4 MCU Learning resource list
##### 2.1 PSoC 4 MCU Datasheets
Device datasheets list the features and electrical specifications of PSoC 4 families of devices: [PSoC 4 MCU Datasheets](http://www.cypress.com/search/all?f%5b0%5d=meta_type%3Atechnical_documents&f%5b1%5d=field_related_products%3A1297&f%5b2%5d=resource_meta_type%3A575)
##### 2.2 PSoC 4 MCU Application Notes
Application notes are available on the Cypress website to assist you with designing your PSoC application: [A list of PSoC 4 MCU ANs](https://community.cypress.com/external-link.jspa?url=http%3A%2F%2Fwww.cypress.com%2Fsearch%2Fall%3Ff%255b0%255d%3Dmeta_type%253Atechnical_documents%26f%255b1%255d%3Dfield_related_products%253A1297%26f%255b2%255d%3Dresource_meta_type%253A574)
##### 2.3 PSoC 4 MCU Component Datasheets
PSoC Creator utilizes "components" as interfaces to functional Hardware (HW). Each component in PSoC Creator has an associated datasheet that describes the functionality, APIs, and electrical specifications for the HW. You can access component datasheets in PSoC Creator by right-clicking a component on the schematic page or by going through the component library listing. You can also access component datasheets from the Cypress website: [PSoC 4 Component Datasheets](https://community.cypress.com/external-link.jspa?url=http%3A%2F%2Fwww.cypress.com%2Fsearch%2Fall%3Ff%255b0%255d%3Dmeta_type%253Asoftware_tools%26f%255b1%255d%3Dfield_related_products%253A1297%26f%255b2%255d%3Dsoftware_tools_meta_type%253A532)
##### 2.4 PSoC 4 MCU Technical Reference Manuals (TRM)
The TRM provides detailed descriptions of the internal architecture of PSoC 4 devices:[PSoC 4 MCU TRMs](https://community.cypress.com/external-link.jspa?url=http%3A%2F%2Fwww.cypress.com%2Fsearch%2Fall%3Ff%255b0%255d%3Dmeta_type%253Atechnical_documents%26f%255b1%255d%3Dfield_related_products%253A1297%26f%255b2%255d%3Dresource_meta_type%253A583)

## FAQ

### Technical Support
Need support for your design and development questions? Check out the [Cypress Developer Community 3.0](https://community.cypress.com/welcome).  

Interact with technical experts in the embedded design community and receive answers verified by Cypress' very best applications engineers. You'll also have access to robust technical documentation, active conversation threads, and rich multimedia content.

You can also use the following support resources if you need quick assistance:

Self-help: [http://www.cypress.com/support](http://www.cypress.com/support)

Local Sales office locations: [http://www.cypress.com/about-us/sales-offices](http://www.cypress.com/about-us/sales-offices)

