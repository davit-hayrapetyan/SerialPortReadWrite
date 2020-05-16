//Some small test

#include <string>
#include <iostream>

#include "SerialPort.hpp"

int main()
{
	std::string device0Name_ = "/dev/ttyS10";
	std::string device1Name_ = "/dev/ttyS11";
	LinuxSerial::SerialPort serialPort0(device0Name_, LinuxSerial::BaudRate::B_57600);
	serialPort0.Open();

	LinuxSerial::SerialPort serialPort1(device1Name_, LinuxSerial::BaudRate::B_57600);
	serialPort1.Open();

	serialPort0.Write("Hello");

	std::string readData;
	serialPort1.Read(readData);

	std::cout << "Written Hello, read " << readData;
	return 0;
}
