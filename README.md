# Pes_Project_4

PES PROJECT 4 – Sensor and State Machines

Project By: Aaksha Jaywant and Rucha Borwankar
 
 
 
The project interfaces the TMP102 temperature sensor with the NXP Freedom KL25Z board using the I2C protocol. The project consists of two interconnected state machines where one is based on State Oriented State machine and other on Table Driven State Machine. The state machine starts with a Power on Self Test that checks if the temperature sensor is properly connected or not. On entering the state machine 1, it will then read the temperature from the sensor and calculate the average of the temperature reading when a complete event occurs. After waiting for a timeout of 15 secs in the Average state it will again go back to the Temperature Reading state. This process will repeat thrice until an alert event occurs or timeout 4 takes place. If an alert event has occurred i.e. in our case if a negative temperature value has been detected, it’ll readily transition to the Alert state and hence move to the Average state when a complete event occurs. The temperature will be read as normal. Whenever a disconnect event occurs such as when it tries to read a value from the temperature or configuration register value and it doesn’t get a reply. In such a situation, the disconnect event would occur and it would then transition to the Disconnected state. At fourth timeout, control goes to the second state machine i.e. the table driven state machine.

In this project we have used a polling approach for I2C communication with the sensor TMP102. We have also created a logger in which we have used an enum for tracing our code by function name. There are various log levels such as Test, Debug and Status which would be displayed on the UART when we configure the logger in a particular mode.  In Test mode, all messages will be printed on the UART whereas in Debug mode , only Debug and Status messages will be printed and in Status mode, only Status status messages will be printed.

Execution Notes: Change enum value in project.c, state_driven.c, table

Observations:
Implemented I2C protocol with TMP102 sensor. 

