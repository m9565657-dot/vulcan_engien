#include <iostream>
#include "windows_layer/windows_manager.h"


int main(){
    Window myWindow(680, 840, "HELLOW_WORLD");

    while(!myWindow.ShouldClose()){
        myWindow.PollEvents();
    }
    return 0;
}