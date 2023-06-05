#include "DeviceDriver.h"
#include <iostream>
using namespace std;

class Application
{
public:
	explicit Application(DeviceDriver* driver)
	{
		m_driver = driver;
	}

	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long addr = startAddr; addr <= endAddr; addr++) {
			cout << m_driver->read(addr) << endl;
		}
	}

	void WriteAll(int value)
	{
		for (int addr = 0x0; addr <= 0x4; addr++)
		{
			m_driver->write(addr, value);
		}
	}
private:
	DeviceDriver *m_driver;
};

