#include "DeviceDriver.h"
#include <exception>
#include <windows.h>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int firstRead = (int)m_hardware->read(address);
    for (int i = 2; i <= MaxReadCount ;i++)
    {
        Sleep(200);
        int nextRead = (int)m_hardware->read(address);
        if (firstRead == nextRead)
	        continue;

        throw exception("Read is failed.");
    }

    return firstRead;
}

void DeviceDriver::write(long address, int data)
{
    int read = (int)m_hardware->read(address);
    if (read == Erased)
        throw exception("Write is failed.");

    m_hardware->write(address, (unsigned char)data);
}