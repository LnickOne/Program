# DaVinci Resolve 色轮自动化程序

## 项目简介

本项目实现了一个用于DaVinci Resolve的色轮自动化工具，可以通过键盘控制色轮的白点位置，实现距离和角度的精确调整。

## 功能特点

- 自动检测DaVinci Resolve窗口和色轮组件
- 通过键盘W/D键调整白点距离和角度
- 实时显示色轮信息（中心、半径、白点位置等）
- 在色轮周围绘制白色线框提供视觉反馈
- 支持Windows平台的UI自动化

## 系统要求

- Windows操作系统
- DaVinci Resolve软件
- Visual Studio 2017或更高版本（用于编译）
- OpenCV库（用于屏幕捕获和图像处理）

## 依赖库

- UIAutomationCore - Windows UI自动化库
- OpenCV - 计算机视觉库
- ole32, oleaut32 - Windows COM组件库

## 编译步骤

1. 确保已安装Visual Studio和OpenCV
2. 打开命令提示符，进入项目目录
3. 运行以下命令编译程序：

```bash
make
```

或者使用Visual Studio的开发人员命令提示符，手动编译：

```bash
g++ -std=c++11 davinci_color_wheel.cpp davinci_color_wheel_impl.cpp -o davinci_color_wheel -lUIAutomationCore -lole32 -loleaut32 -lcv2 -lhighgui -limgproc -lopencv_core
```

## 使用方法

1. 确保DaVinci Resolve正在运行
2. 运行编译好的程序：

```bash
make run
```
或
```bash
./davinci_color_wheel
```

3. 程序会自动查找DaVinci Resolve窗口和色轮组件
4. 使用键盘控制：
   - W键：增加白点距离（向色轮边缘移动）
   - S键：减少白点距离（向色轮中心移动）
   - D键：增加角度（顺时针旋转）
   - A键：减少角度（逆时针旋转）
   - Q键：退出程序

5. 程序会实时显示色轮信息和白点位置

## 注意事项

1. 本程序仅在Windows平台上运行
2. 确保DaVinci Resolve正在运行且显示色轮组件
3. 程序可能需要以管理员权限运行
4. 色轮检测依赖于UI自动化，可能需要根据DaVinci Resolve的版本调整检测条件
5. 如需调整检测条件，请修改`davinci_color_wheel_impl.cpp`中的`FindColorWheel`函数

## 文件结构

```
├── davinci_color_wheel.h      # 头文件，定义类和结构
├── davinci_color_wheel.cpp    # 主程序文件，包含main函数
├── davinci_color_wheel_impl.cpp  # 实现文件，实现所有功能
├── Makefile                   # 编译脚本
└── README.md                  # 项目说明文档
```

## 技术说明

- 使用Windows UI Automation API自动检测和操作UI元素
- 使用OpenCV进行屏幕捕获和图像处理
- 使用GDI进行屏幕绘制，提供视觉反馈
- 采用面向对象设计，代码结构清晰，易于扩展

## 扩展建议

1. 添加更多快捷键支持
2. 实现自定义色彩预设
3. 添加颜色值显示和调整
4. 支持多色轮同步操作
5. 增加配置文件，支持自定义设置

## 许可证

本项目采用MIT许可证，可自由使用和修改。