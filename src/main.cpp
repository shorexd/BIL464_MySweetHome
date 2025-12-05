/* * File: src/main.cpp
 * SystemController entegre edildi.
 */

#include <iostream>
// Makefile "-Iinclude" dedigi icin basina "include/" yazmana gerek yok:
#include "SystemController.h" 

int main() {
    // 1. Sistemin Tek Örneğini (Singleton) Al
    SystemController* sys = SystemController::getInstance();

    // 2. Sistemi Başlat (Loglar, Ayarlar, Sensörler)
    sys->init();

    // 3. Ana Döngüyü Çalıştır (Menü burada dönecek)
    sys->run();

    // 4. Program Bitince Temizlik (Opsiyonel, OS zaten yapar ama iyidir)
    // SystemController destructor'ı shutdown'ı çağırır.
    // Ancak pointer olduğu için manuel delete diyebiliriz veya shutdown'ı elle çağırabiliriz.
    // Singleton olduğu için genelde program bitişine bırakılır ama temizlik şudur:
    
    // delete sys; // (Destructor public ise)
    
    return 0;
}