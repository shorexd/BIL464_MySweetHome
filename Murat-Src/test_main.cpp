#include <iostream>
#include "../Murat-Devices/Device.h"
#include "../Murat-Devices/DeviceFactory.h"
#include "../Murat-Devices/SamsungFactory.h"
#include "../Murat-Devices/LGFactory.h"

int main() {
    std::cout << "---- Murat Device Factory Test ----" << std::endl;

    SamsungFactory samsungFactory;
    LGFactory lgFactory;

    Device* tv1 = samsungFactory.createTV();
    Device* tv2 = lgFactory.createTV();

    std::cout << "\n[Test] SamsungTV turnOn:" << std::endl;
    tv1->turnOn();

    std::cout << "\n[Test] SamsungTV turnOff:" << std::endl;
    tv1->turnOff();

    std::cout << "\n[Test] LGTV turnOn:" << std::endl;
    tv2->turnOn();

    std::cout << "\n[Test] LGTV turnOff:" << std::endl;
    tv2->turnOff();

    delete tv1;
    delete tv2;

    std::cout << "\n---- Test Completed Successfully ----" << std::endl;

    return 0;
}
