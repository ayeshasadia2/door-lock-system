# Password Protected Door Lock System Using ATmega328P

## Abstract
This project presents the design and implementation of a microcontroller-based password-protected door lock system using the ATmega328P. The system ensures secure access control by validating user-entered credentials through a keypad interface and actuating a locking mechanism accordingly. Real-time feedback is provided via an LCD display and LED indicators.

## Introduction
This project demonstrates a standalone embedded system designed to restrict unauthorized access using password authentication. It provides a low-cost and efficient alternative to traditional locking systems by integrating hardware and software components.

## Objectives
- Design a secure password-based access system  
- Interface keypad for user input  
- Display system feedback via LCD  
- Control locking mechanism using servo motor  
- Provide status indication using LEDs  

## System Architecture
Input: 4x3 Matrix Keypad  
Processing: ATmega328P Microcontroller  
Output: 16x2 I2C LCD, Servo Motor, Red and Green LEDs  

## Components Used
- ATmega328P Microcontroller  
- 4x3 Matrix Keypad  
- 16x2 LCD with I2C Module  
- Servo Motor  
- Red and Green LEDs  
- 16 MHz Crystal Oscillator  
- 22pF Capacitors  
- 5V Power Supply  

## Working Principle
On startup, the LCD prompts the user to enter a password. The servo remains in a locked position and LEDs are off. The user inputs a 4-digit password through the keypad, which is masked on the LCD. The system compares the entered password with a predefined password.

If the password is correct, the system displays "Access Granted", activates the green LED, and rotates the servo motor to unlock the door temporarily before returning to the locked state. If the password is incorrect, the system displays "Access Denied" and activates the red LED. Pressing '*' resets the system.

## Circuit Description
The system is built around the ATmega328P microcontroller. The keypad is connected to digital input pins, while the LCD communicates via I2C protocol. The servo motor is controlled using PWM signals. LEDs are connected with current-limiting resistors, and a crystal oscillator ensures stable clock operation.

## Software Features
- Password masking  
- Fixed-length password validation  
- Real-time LCD updates  
- Servo motor control using PWM  
- LED status indicators  

## Default Password
1234

## Simulation
The project is simulated in Proteus to verify system functionality. The simulation includes keypad input, LCD output, servo movement, and LED indications.

## Hardware Implementation
The system can be implemented using ATmega328P. Arduino Uno may be used for power supply and programming.


## How to Use
1. Assemble the circuit  
2. Upload the code to the microcontroller  
3. Power the system  
4. Enter password using keypad  

## Results
Correct password unlocks the system temporarily. Incorrect password triggers access denial with LED indication.

## Applications
- Home security systems  
- Office access control  
- Locker security  
- Embedded authentication systems  

## Future Improvements
- EEPROM-based password storage  
- Multiple user support  
- RFID or biometric integration  
- Alarm/buzzer addition  
- IoT-based remote access  

## Conclusion
This project demonstrates an effective embedded security system using ATmega328P, integrating hardware and software to achieve reliable password-based access control.
