/*******************************************************
 usb buzzer control

depend: libusb  libudev

sudo ./hidtest

********************************************************/

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

// Headers needed for sleeping.
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char* argv[])
{
    int res;
    unsigned char buf[256];
#define MAX_STR 255
    wchar_t wstr[MAX_STR];
    hid_device* handle;
    int i;

#ifdef WIN32
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);
#endif

#define VID 0X5131
#define PID 0X2019

    struct hid_device_info* devs, * cur_dev;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    char hidpath[128] = { 0 };
    while (cur_dev)
    {

        printf("VID:%x PID:%x Interface:%d\n", cur_dev->vendor_id, cur_dev->product_id, cur_dev->interface_number);
        if (cur_dev->vendor_id == VID && cur_dev->product_id == PID)
        {

            if (cur_dev->interface_number == 3)
            {
                strcpy(hidpath, cur_dev->path);
                printf("found device,devpath:%s\n", cur_dev->path);


                break;
            }

        }
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);



    handle = hid_open_path(hidpath);
    if (!handle)
    {
        printf("usb open fail!\n");
        exit(-1);
    }
    printf("usb open success!\n");

    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);

    // Try to read from the device. There shoud be no
    // data here, but execution should not block.
    //res = hid_read(handle, buf, 17);

	/*
    buf[0] = 0;
    buf[1] = 0xa0;  //read devid
    buf[2] = 0;
    buf[3] = 0;
    buf[4] = 0xa0;

    res = hid_write(handle, buf, 65);
    if (res < 0)
    {
        printf("Unable to write()\n");
        printf("Error: %ls\n", hid_error(handle));
    }
	*/
    memset(buf, 0, sizeof(buf));

    while (1)
    {

		static long c = 0;


	
		//BLE-->USB
		printf("hidread...\n");
        res = hid_read(handle, buf, 64);
        if (res > 0)
        {
			//如果USB不一定性上传64字节 系统底层驱动可能不会收到数据，所以不管收到多少字节都上传64字节，请自定义协议比如第一字节表示数据长度
            printf("Data read:\n   ");
            for (i = 0; i < res; i++)
                printf("%02hhx ", buf[i]);
            printf("\n");


			switch (buf[0])
			{
			case 0xa0:
			{
				UINT32 devid;
				UINT8* pid = (UINT8*)&devid;
				pid[0] = (unsigned char)buf[4];
				pid[1] = (unsigned char)buf[5];
				pid[2] = (unsigned char)buf[6];
				pid[3] = (unsigned char)buf[7];

				printf("设备ID:%u\n", devid);
			}
			break;
			}
          
        }
        if (res < 0)
            printf("Unable to read()\n");



	
		{
			buf[0] = 0; //MUST BE 0
			buf[1] = 'H';   
			buf[2] = 'I';
			buf[3] = 'D';
			buf[4] = '2';
			buf[5] = 'B';
			buf[6] = 'L';
			buf[7] = 'E';
			buf[8] = '\0';
			//USB--> BLE
			printf("Data write USB--> BLE\n");
			res = hid_write(handle, buf, 65);//MUST  BE 65
			Sleep(500);
		}




#ifdef WIN32
        Sleep(500);
#else
        usleep(500 * 1000);
#endif
    }




    hid_close(handle);

    /* Free static HIDAPI objects. */
    hid_exit();

#ifdef WIN32
    system("pause");
#endif

    return 0;
}
