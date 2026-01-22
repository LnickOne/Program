#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <WinUser.h>
#include <UIAutomation.h>
#include <opencv2/opencv.hpp>
#endif

#include <string>
#include <vector>

#ifdef _WIN32
// 色轮组件信息结构体
typedef struct {
    RECT boundingRect;  // 色轮组件的边界矩形
    POINT center;       // 色轮中心坐标
    int radius;         // 色轮半径
    POINT whitePoint;   // 白点当前位置
    double distance;    // 白点与圆心的距离
    double angle;       // 白点与圆心的角度（度）
} ColorWheelInfo;

// DaVinci Resolve色轮自动化类
class DaVinciColorWheel {
private:
    HWND davinciWindow;                 // DaVinci Resolve主窗口句柄
    IUIAutomation* automation;          // UI自动化接口
    IUIAutomationElement* colorWheelElement;  // 色轮组件元素
    ColorWheelInfo colorWheelInfo;      // 色轮信息
    cv::Mat screenCapture;              // 屏幕截图
    
    // 私有辅助方法
    bool CaptureScreen();
    bool IsPointInWheel(POINT point);
    void CalculateDistanceAndAngle();
    
public:
    // 构造函数和析构函数
    DaVinciColorWheel();
    ~DaVinciColorWheel();
    
    // 初始化和清理
    bool InitializeAutomation();
    void CleanupAutomation();
    
    // DaVinci Resolve相关检查
    bool IsDaVinciRunning();
    bool FindDaVinciWindow();
    
    // 色轮组件操作
    bool FindColorWheel();
    void DisplayColorWheelInfo();
    
    // 参数调整
    bool AdjustDistance(int delta);
    bool AdjustAngle(int deltaDegrees);
    
    // 视觉反馈
    void DrawWhiteFrame();
    
    // 获取色轮信息
    ColorWheelInfo GetColorWheelInfo() const;
};

#endif  // _WIN32