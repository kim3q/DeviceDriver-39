#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "..\Project17/DeviceDriver.cpp"
#include "..\Project17/App.cpp"

using namespace std;
using namespace testing;

class MockDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char), (override));
};

TEST(TESTCaseName, ReadSuccessTest1)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read).Times(5);

	DeviceDriver driver(&mock_device);
	driver.read(0xA);
}

TEST(TESTCaseName, ReadExceptionTest1)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x6))
		.WillOnce(Return(0x6))
		.WillOnce(Return(0x6))
		.WillOnce(Return(0x6))
		.WillOnce(Return(0x2));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.read(0x2), exception);
}

TEST(TestCaseName, WriteSuccessTest1)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, write(0x1, 0xAA));
	EXPECT_CALL(mock_device, read(0x1)).Times(6).WillRepeatedly(Return(0xAA));

	DeviceDriver driver(&mock_device);
	driver.write(0x1, 0xAA);
	EXPECT_THAT(driver.read(0x1), Eq(0xAA));
}

TEST(TestCaseName, WriteExceptionTest1)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0x2)).WillRepeatedly(Return(0xFF));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.write(0x2, 0xAA), exception);
}

TEST(TestCaseName, AppReadAndPrintSuccess1)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0x0)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, read(0x1)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, read(0x2)).WillRepeatedly(Return(0x1));
	DeviceDriver driver(&mock_device);
	Application apps(&driver);
	apps.ReadAndPrint(0x0, 0x2);
}

TEST(TestCaseName, AppWriteAllSuccess1)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0x0)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, write(0x0, 0x5));
	EXPECT_CALL(mock_device, read(0x1)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, write(0x1, 0x5));
	EXPECT_CALL(mock_device, read(0x2)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, write(0x2, 0x5));
	EXPECT_CALL(mock_device, read(0x3)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, write(0x3, 0x5));
	EXPECT_CALL(mock_device, read(0x4)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(mock_device, write(0x4, 0x5));
	DeviceDriver driver(&mock_device);
	Application apps(&driver);
	apps.WriteAll(0x5);
}