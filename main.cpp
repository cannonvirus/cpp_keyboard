#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <thread>

using namespace std;

#define Up_Age 72
#define Down_Age 80
#define Up_bias 77
#define Down_bias 75
#define Init 76


void INThandler(){
  exit(0);
}

int main()
{
    

    // signal(SIGINT, INThandler);

    int age = 0;
    float bias = 0.0;
    int count = 33;

    thread keyboard_th([&age, &bias, &count] {

        char devname[] = "/dev/input/by-id/usb-SINO_WEALTH_USB_KEYBOARD-event-kbd";
        int device = open(devname, O_RDONLY);
        struct input_event ev;

        while(1)
        {
            read(device,&ev, sizeof(ev));
            if(ev.type == 1 && ev.value == 1){
                // printf("Key: %i State: %i\n",ev.code,ev.value);

                if (ev.code == Up_Age)
                    age +=3;
                else if (ev.code == Down_Age)
                    age -=3;
                else if (ev.code == Up_bias)
                    bias += 0.5;
                else if (ev.code == Down_bias)
                    bias -= 0.5;
                else if (ev.code == Init)
                    //  count 초기화
                    count = 0;

                // cout << "[After] age : " << age << " | bias : " << bias << endl;
            }
            
        }
    });

    keyboard_th.detach();

    while(1)
    {
        cout << "[After] age : " << age << " | bias : " << bias << " | count : " << count << endl;
        sleep(1);
    }
}