# Industrial_Environmental_Monitoring_and_Timestamp-Based_Data_Logging_System_using_LPC2148
LPC2148 ARM7 \| Embedded C \| LM35 \| ADC \| RTC \| LCD \| UART \|
External Interrupt

An embedded project that monitors temperature using an LM35 sensor,
reads date and time from the LPC2148 Real-Time Clock (RTC), displays the
information on an LCD, and sends timestamped readings to a PC through
UART. The firmware also provides keypad-based RTC adjustment through an
external interrupt and activates a buzzer when the measured temperature
exceeds the configured threshold.


## Overview
Industrial and laboratory environments can benefit from monitoring
temperature and keeping a time-based record of measurements. This
project uses the LPC2148 ARM7 microcontroller to build a
temperature-monitoring and timestamped data-logging application.
The LM35 provides an analog temperature signal. The LPC2148 ADC converts
this signal into a digital value, and the firmware calculates the
temperature in degrees Celsius. The on-chip RTC supplies the current
date and time. The LCD displays the current date, time, and temperature,
while UART sends periodic records to a connected computer.
The project also includes: - A 4×4 keypad for entering RTC values. - A
push button configured to trigger an external interrupt for RTC
adjustment. - A buzzer output for a high-temperature alert. - PC-side
serial logging using a UART connection.


## Project Objectives
-   Measure ambient temperature using the LM35.
-   Convert the sensor output using the LPC2148 ADC.
-   Obtain date and time from the on-chip RTC.
-   Display temperature and timestamp information on an LCD.
-   Transmit periodic timestamped sensor readings to a PC.
-   Allow the user to update RTC values through a keypad.
-   Use an external interrupt to enter RTC configuration.
-   Provide an audible alert when temperature exceeds the firmware
    threshold.

  ## Implemented Functions
  -----------------------------------------------------------------------
  Function                            Description
  ----------------------------------- -----------------------------------
  Temperature acquisition             Reads the LM35 through the ADC

  RTC time/date read                  Reads the current RTC clock and
                                      calendar values

  LCD display                         Displays date, time, and integer
                                      temperature

  UART logging                        Sends date, time, and temperature
                                      records to the PC

  RTC setting menu                    Provides keypad-based time/date
                                      adjustment

  External interrupt                  Sets a flag to request RTC
                                      configuration

  Temperature alert                   Activates the buzzer when
                                      temperature is greater than the
                                      configured setpoint
  -----------------------------------------------------------------------
  
## Hardware Used
  Component                             Role
  ------------------------------------- --------------------------------
  LPC2148 ARM7 microcontroller          Main controller
  LM35 temperature sensor               Analog temperature measurement
  16×2 LCD                              Local display
  4×4 matrix keypad                     RTC configuration input
  Push-button switch                    External interrupt trigger
  Buzzer                                Temperature warning output
  MAX232                                UART serial-level interface
  USB-to-UART converter or DB-9 cable   PC serial connection

## How the System Works
1.  The firmware initializes the ADC, RTC, LCD, keypad, UART, external
    interrupt, and buzzer GPIO.
2.  The LM35 sensor voltage is sampled through the LPC2148 ADC.
3.  The ADC result is converted into a temperature value in Celsius.
4.  The firmware reads the current date and time from the RTC.
5.  The LCD is updated with the date, time, and temperature.
6.  At the configured logging time, the firmware sends a timestamped
    record over UART.
7.  The temperature is compared with the configured alert threshold.
8.  If the external interrupt flag is set, the RTC menu is entered and
    the user can update time/date using the keypad.
9.  The application continues monitoring after the RTC configuration
    routine completes.

 ## LCD and UART Output
The LCD is programmed to show the RTC date on the first line and the
time with a temperature value on the second line. The temperature is
displayed as an integer in the current main application code.

The UART startup message identifies the application as an industrial
environment monitoring and real-time data logger. Periodic records are
transmitted in a human-readable format containing:

-   Date
-   Time
-   Temperature in °C

The provided `log_file.TXT` contains example serial output captured from
the project. Example records include date/time readings and temperature
alert messages. These are retained as project output evidence; they
should not be interpreted as a guarantee that every run produces
identical values.

## Repository Contents
This repository includes: - Embedded C source and header files. -
Project specification document. - Block diagram and project images. -
LCD output image. - Recorded project demonstration video. - Sample UART
log file.

## Project Summary

This project demonstrates a practical embedded monitoring system built
around the LPC2148 ARM7 microcontroller. It combines LM35 temperature
sensing, ADC conversion, RTC timekeeping, LCD display, UART-based
timestamped logging, keypad-based RTC configuration, external interrupt
handling, and buzzer alert generation.

It provides hands-on experience with embedded C, microcontroller
peripherals, sensor interfacing, serial communication, and modular
firmware development.

