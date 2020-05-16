#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <fstream>
#include <sstream>
#include <termios.h> // POSIX terminal control definitions (struct termios)
#include <vector>

namespace LinuxSerial 
{

	//Strongly-typed enumeration of baud rates for use with the SerialPort class
	enum class BaudRate 
	{
		B_9600,
		B_38400,
		B_57600,
		B_115200,
		CUSTOM
	};

	enum class State
	{
		CLOSED,
		OPEN
	};

	//SerialPort object is used to perform rx/tx serial communication.
	class SerialPort
	{

	public:
		SerialPort();

		SerialPort(const std::string &device, BaudRate baudRate);

		virtual ~SerialPort();

		//Sets the device to use for serial port communications.
		void SetDevice(const std::string &device);

		void SetBaudRate(BaudRate baudRate);

		//Sets the read timeout (in milliseconds)/blocking mode.
		// Only call when state != OPEN. This method manupulates VMIN and VTIME.
		void SetTimeout(int32_t timeout_ms);

		void SetEcho(bool value);

		void Open();

		void Close();
		
		void Write(const std::string& data);

		void Read(std::string& data);

	private:

		//Returns a populated termios structure for the passed in file descriptor.
		termios GetTermios();

		//Configures the tty device as a serial port.
		void ConfigureTermios();

		void SetTermios(termios myTermios);

		// Keeps track of the serial port's state.
		State state_;

		//The file path to the serial port device (e.g. "/dev/ttyUSB0").
		std::string device_;

		//The current baud rate.
		BaudRate baudRate_;

		//The file descriptor for the open file. This gets written to when Open() is called.
		int fileDesc_;

		bool echo_;

		int32_t timeout_ms_;

		std::vector<char> readBuffer_;
		unsigned char readBufferSize_B_;

		static constexpr BaudRate defaultBaudRate_ = BaudRate::B_57600;
		static constexpr int32_t defaultTimeout_ms_ = -1;
		static constexpr unsigned char defaultReadBufferSize_B_ = 255;


	};

} // namespace LinuxSerial

#endif // #ifndef SERIALPORT_H
