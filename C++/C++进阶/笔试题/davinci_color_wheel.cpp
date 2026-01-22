// DaVinci Resolve Color Wheel Automation Tool

#include <iostream>

#ifdef _WIN32
#include "davinci_color_wheel.h"
#include <chrono>
#include <thread>
#include <windows.h>

int main() {
    std::cout << "DaVinci Resolve Color Wheel Automation Tool" << std::endl;
    std::cout << "Press 'W' to adjust distance, 'D' to adjust angle, 'ESC' to exit." << std::endl;
    
    // 初始化DaVinciColorWheel实例
    DaVinciColorWheel colorWheel;
    
    // 检查是否有DaVinci Resolve进程运行
    if (!colorWheel.IsDaVinciRunning()) {
        std::cerr << "Error: DaVinci Resolve is not running!" << std::endl;
        return 1;
    }
    
    // 查找色轮组件
    if (!colorWheel.FindColorWheel()) {
        std::cerr << "Error: Color wheel component not found!" << std::endl;
        return 1;
    }
    
    // 显示色轮信息
    colorWheel.DisplayColorWheelInfo();
    
    // 主循环
    bool running = true;
    while (running) {
        // 检查键盘输入
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            running = false;
        }
        
        // 调整距离（W键）
        if (GetAsyncKeyState(0x57) & 0x8000) {  // 0x57 is 'W'
            colorWheel.AdjustDistance(1);  // 增加距离
            std::this_thread::sleep_for(std::chrono::milliseconds(50));  // 控制速度
        }
        
        // 调整角度（D键）
        if (GetAsyncKeyState(0x44) & 0x8000) {  // 0x44 is 'D'
            colorWheel.AdjustAngle(5);  // 增加角度（度）
            std::this_thread::sleep_for(std::chrono::milliseconds(50));  // 控制速度
        }
        
        // 绘制白色线框
        colorWheel.DrawWhiteFrame();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 降低CPU使用率
    }
    
    std::cout << "Program exited." << std::endl;
    return 0;
}
#else
int main() {
    std::cerr << "This program only runs on Windows platform!" << std::endl;
    return 1;
}
#endif