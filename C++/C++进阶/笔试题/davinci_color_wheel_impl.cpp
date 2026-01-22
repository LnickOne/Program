#include <iostream>
#include <cmath>
#include <algorithm>

#ifdef _WIN32
#include "davinci_color_wheel.h"

// 构造函数
DaVinciColorWheel::DaVinciColorWheel() {
    davinciWindow = nullptr;
    automation = nullptr;
    colorWheelElement = nullptr;
    memset(&colorWheelInfo, 0, sizeof(ColorWheelInfo));
    
    // 初始化UI自动化
    InitializeAutomation();
}

// 析构函数
DaVinciColorWheel::~DaVinciColorWheel() {
    CleanupAutomation();
}

// 初始化UI自动化
bool DaVinciColorWheel::InitializeAutomation() {
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    
    HRESULT hr = CoCreateInstance(
        __uuidof(CUIAutomation),
        NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(IUIAutomation),
        (void**)&automation
    );
    
    if (FAILED(hr)) {
        std::cerr << "Failed to create CUIAutomation instance." << std::endl;
        return false;
    }
    
    return true;
}

// 清理UI自动化
void DaVinciColorWheel::CleanupAutomation() {
    if (colorWheelElement) {
        colorWheelElement->Release();
        colorWheelElement = nullptr;
    }
    
    if (automation) {
        automation->Release();
        automation = nullptr;
    }
    
    CoUninitialize();
}

// 检查DaVinci Resolve是否运行
bool DaVinciColorWheel::IsDaVinciRunning() {
    return FindDaVinciWindow();
}

// 查找DaVinci Resolve窗口
bool DaVinciColorWheel::FindDaVinciWindow() {
    // 查找标题包含"DaVinci Resolve"的窗口
    davinciWindow = FindWindowA(NULL, "DaVinci Resolve");
    if (davinciWindow == nullptr) {
        davinciWindow = FindWindowA(NULL, "Resolve");  // 可能的替代标题
    }
    
    return davinciWindow != nullptr;
}

// 查找色轮组件
bool DaVinciColorWheel::FindColorWheel() {
    if (!automation || !davinciWindow) {
        return false;
    }
    
    // 从主窗口开始查找色轮组件
    IUIAutomationElement* rootElement = nullptr;
    HRESULT hr = automation->ElementFromHandle(davinciWindow, &rootElement);
    
    if (FAILED(hr) || !rootElement) {
        return false;
    }
    
    // 使用属性条件查找色轮组件
    // 这里使用"ColorWheel"作为控件类型示例，实际需要根据DaVinci的UI结构调整
    IUIAutomationPropertyCondition* condition = nullptr;
    IUIAutomationIdentifier* controlTypeProperty = nullptr;
    automation->get_ControlTypeProperty(&controlTypeProperty);
    
    if (controlTypeProperty) {
        automation->CreatePropertyCondition(controlTypeProperty, UIA_PaneControlTypeId, &condition);
        controlTypeProperty->Release();
    }
    
    if (!condition) {
        rootElement->Release();
        return false;
    }
    
    // 查找所有符合条件的元素
    IUIAutomationElementArray* elements = nullptr;
    hr = rootElement->FindAll(TreeScope_Descendants, condition, &elements);
    
    condition->Release();
    rootElement->Release();
    
    if (FAILED(hr) || !elements) {
        return false;
    }
    
    // 遍历元素，寻找色轮（这里需要更精确的识别条件）
    int count = 0;
    elements->get_Length(&count);
    
    for (int i = 0; i < count; i++) {
        IUIAutomationElement* element = nullptr;
        hr = elements->GetElement(i, &element);
        
        if (SUCCEEDED(hr) && element) {
            // 这里可以添加更精确的条件，比如名称、位置等
            // 暂时选择第一个找到的面板作为色轮组件
            colorWheelElement = element;
            break;
        }
        
        if (element) {
            element->Release();
        }
    }
    
    elements->Release();
    
    if (!colorWheelElement) {
        return false;
    }
    
    // 获取色轮组件的边界矩形
    UiaRect boundingRect;
    hr = colorWheelElement->get_CurrentBoundingRectangle(&boundingRect);
    
    if (FAILED(hr)) {
        colorWheelElement->Release();
        colorWheelElement = nullptr;
        return false;
    }
    
    // 填充色轮信息
    colorWheelInfo.boundingRect.left = static_cast<LONG>(boundingRect.left);
    colorWheelInfo.boundingRect.top = static_cast<LONG>(boundingRect.top);
    colorWheelInfo.boundingRect.right = static_cast<LONG>(boundingRect.right);
    colorWheelInfo.boundingRect.bottom = static_cast<LONG>(boundingRect.bottom);
    
    // 计算中心和半径
    colorWheelInfo.center.x = (colorWheelInfo.boundingRect.left + colorWheelInfo.boundingRect.right) / 2;
    colorWheelInfo.center.y = (colorWheelInfo.boundingRect.top + colorWheelInfo.boundingRect.bottom) / 2;
    colorWheelInfo.radius = std::min(
        colorWheelInfo.boundingRect.right - colorWheelInfo.boundingRect.left,
        colorWheelInfo.boundingRect.bottom - colorWheelInfo.boundingRect.top
    ) / 2;
    
    // 初始白点位置在中心
    colorWheelInfo.whitePoint = colorWheelInfo.center;
    colorWheelInfo.distance = 0;
    colorWheelInfo.angle = 0;
    
    return true;
}

// 显示色轮信息
void DaVinciColorWheel::DisplayColorWheelInfo() {
    std::cout << "Color Wheel Information:" << std::endl;
    std::cout << "Bounding Rect: " 
              << colorWheelInfo.boundingRect.left << ", " 
              << colorWheelInfo.boundingRect.top << " - " 
              << colorWheelInfo.boundingRect.right << ", " 
              << colorWheelInfo.boundingRect.bottom << std::endl;
    std::cout << "Center: " << colorWheelInfo.center.x << ", " << colorWheelInfo.center.y << std::endl;
    std::cout << "Radius: " << colorWheelInfo.radius << std::endl;
    std::cout << "White Point: " << colorWheelInfo.whitePoint.x << ", " << colorWheelInfo.whitePoint.y << std::endl;
    std::cout << "Distance: " << colorWheelInfo.distance << std::endl;
    std::cout << "Angle: " << colorWheelInfo.angle << " degrees" << std::endl;
}

// 捕获屏幕
bool DaVinciColorWheel::CaptureScreen() {
    HDC hdcScreen = GetDC(NULL);
    if (!hdcScreen) {
        return false;
    }
    
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    if (!hdcMem) {
        ReleaseDC(NULL, hdcScreen);
        return false;
    }
    
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    if (!hBitmap) {
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdcScreen);
        return false;
    }
    
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);
    
    // 将HBITMAP转换为cv::Mat
    BITMAPINFOHEADER bi;
    memset(&bi, 0, sizeof(BITMAPINFOHEADER));
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // 负高度表示自上而下的位图
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    
    screenCapture = cv::Mat(height, width, CV_8UC3);
    GetDIBits(hdcMem, hBitmap, 0, height, screenCapture.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    
    // 释放资源
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
    
    return true;
}

// 检查点是否在色轮内
bool DaVinciColorWheel::IsPointInWheel(POINT point) {
    int dx = point.x - colorWheelInfo.center.x;
    int dy = point.y - colorWheelInfo.center.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    
    return distance <= colorWheelInfo.radius;
}

// 计算距离和角度
void DaVinciColorWheel::CalculateDistanceAndAngle() {
    int dx = colorWheelInfo.whitePoint.x - colorWheelInfo.center.x;
    int dy = colorWheelInfo.whitePoint.y - colorWheelInfo.center.y;
    
    colorWheelInfo.distance = std::sqrt(dx * dx + dy * dy);
    colorWheelInfo.angle = std::atan2(dy, dx) * 180 / M_PI;
    if (colorWheelInfo.angle < 0) {
        colorWheelInfo.angle += 360;
    }
}

// 调整距离
bool DaVinciColorWheel::AdjustDistance(int delta) {
    // 计算新的距离
    double newDistance = colorWheelInfo.distance + delta;
    
    // 限制距离在0到半径之间
    newDistance = std::max(0.0, std::min(newDistance, static_cast<double>(colorWheelInfo.radius)));
    
    // 计算新的白点位置
    double radians = colorWheelInfo.angle * M_PI / 180;
    colorWheelInfo.whitePoint.x = static_cast<LONG>(colorWheelInfo.center.x + newDistance * std::cos(radians));
    colorWheelInfo.whitePoint.y = static_cast<LONG>(colorWheelInfo.center.y + newDistance * std::sin(radians));
    
    // 更新距离
    colorWheelInfo.distance = newDistance;
    
    // 模拟鼠标拖拽
    SetCursorPos(colorWheelInfo.whitePoint.x, colorWheelInfo.whitePoint.y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    
    return true;
}

// 调整角度
bool DaVinciColorWheel::AdjustAngle(int deltaDegrees) {
    // 计算新的角度
    double newAngle = colorWheelInfo.angle + deltaDegrees;
    
    // 确保角度在0-360度之间
    if (newAngle >= 360) {
        newAngle -= 360;
    } else if (newAngle < 0) {
        newAngle += 360;
    }
    
    // 计算新的白点位置
    double radians = newAngle * M_PI / 180;
    colorWheelInfo.whitePoint.x = static_cast<LONG>(colorWheelInfo.center.x + colorWheelInfo.distance * std::cos(radians));
    colorWheelInfo.whitePoint.y = static_cast<LONG>(colorWheelInfo.center.y + colorWheelInfo.distance * std::sin(radians));
    
    // 更新角度
    colorWheelInfo.angle = newAngle;
    
    // 模拟鼠标拖拽
    SetCursorPos(colorWheelInfo.whitePoint.x, colorWheelInfo.whitePoint.y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    
    return true;
}

// 绘制白色线框
void DaVinciColorWheel::DrawWhiteFrame() {
    // 捕获屏幕
    if (!CaptureScreen()) {
        return;
    }
    
    // 绘制白色线框
    cv::Rect rect(
        colorWheelInfo.boundingRect.left,
        colorWheelInfo.boundingRect.top,
        colorWheelInfo.boundingRect.right - colorWheelInfo.boundingRect.left,
        colorWheelInfo.boundingRect.bottom - colorWheelInfo.boundingRect.top
    );
    
    cv::rectangle(screenCapture, rect, cv::Scalar(255, 255, 255), 2);
    
    // 显示结果（可选）
    // cv::imshow("Color Wheel Frame", screenCapture);
    // cv::waitKey(1);
    
    // 或者直接在屏幕上绘制（使用GDI）
    HDC hdcScreen = GetDC(NULL);
    if (hdcScreen) {
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HPEN hOldPen = (HPEN)SelectObject(hdcScreen, hPen);
        
        Rectangle(
            hdcScreen,
            colorWheelInfo.boundingRect.left,
            colorWheelInfo.boundingRect.top,
            colorWheelInfo.boundingRect.right,
            colorWheelInfo.boundingRect.bottom
        );
        
        SelectObject(hdcScreen, hOldPen);
        DeleteObject(hPen);
        ReleaseDC(NULL, hdcScreen);
    }
}

// 获取色轮信息
ColorWheelInfo DaVinciColorWheel::GetColorWheelInfo() const {
    return colorWheelInfo;
}

#endif  // _WIN32