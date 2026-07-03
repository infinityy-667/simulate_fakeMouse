// this is simulating an auto mouse cliker 

#include <stdio.h>
#include <unistd.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <time.h>


int main(){
//create a fake mouse
struct libevdev *dev = libevdev_new();
struct libevdev_uinput *uidev = NULL;

libevdev_set_name(dev, "fake fyf_mouse");
libevdev_enable_event_type(dev, EV_REL);
libevdev_enable_event_code(dev, EV_REL, REL_X, NULL);
libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);
libevdev_enable_event_type(dev, EV_KEY);
libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, NULL);
libevdev_enable_event_code(dev, EV_KEY, BTN_MIDDLE, NULL);
libevdev_enable_event_code(dev, EV_KEY, BTN_RIGHT, NULL);

libevdev_enable_event_type(dev, EV_SYN);
libevdev_enable_event_code(dev, EV_SYN, SYN_REPORT, NULL);

int code = libevdev_uinput_create_from_device(dev,  LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);

if(code !=0){

    perror("ERROR!:");
    return -1;
}
printf("mouse will start cliking in 5s");
usleep(5000000);

while (1){
    libevdev_uinput_write_event(uidev,EV_KEY, BTN_LEFT, 1);
    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
    usleep(50000);

    libevdev_uinput_write_event(uidev, EV_KEY, BTN_LEFT, 0);

    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);

    usleep(500000);
}


    return 0;
}