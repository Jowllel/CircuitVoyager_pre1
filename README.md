# CircuitVoyager_pre1
In this Project, my goal is to develop a DMM prototype, that can measure voltage, current and power. The Project can be divided into 3 parts. First the Hardware: I made a PCB whose files are stored in the "5\Hardware" folder and can be opened with Altium Designer (Viewer). This PCB gives the DevBoard the skill to measure voltage, current, beep and light up in color. In extent there's a Firmware which runs on the DevBoard, that automatically measures voltage and current, manages Overloads and range switching and send the measured values over the ST-Links UART to a PC. This Firmware is in the folder "6_Software/CV_FW" and can be opened and flashed using STM32CubeIDE. And last there's a Software running on a PC, which is stored in "6_Software\slash CV_UI", where the exe file can be opened directly or the python script can be run with PySerial installed. This Software connects to the DMM and displays the voltage current and power values. Later this Software should also be able to log the measured results.

My most important results were, that I learned a lot about developing measurement hardware and I was able to connect a microcontroller to an actual Windows app. I've also learned a lot about LaTeX. I'd rather say this was the most valuable experience gathered in this project.

[**Documentation HERE**](2_Documentation/1_Main/Documentation_CircuitVoyager_Pre1/main.pdf)

![HW Conecpt](2_Documentation/2_Project_Planning/HW_Concept/Hardware_Concept_CircuitVoyager_pre1.drawio.svg)
