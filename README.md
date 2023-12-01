## 要求
1、系统设计合理、具有一定的实用价值
2、设计报告应符合学校有关对论文的要求，规范
3、实行分组合作，2-3人一题的形式（报告必须一人一份）
4、系统中所设计功能必须完善，代码量得上万行。
5、界面设计要求美观，大方
6、合理地实现系统的设计与开发
7、需要提交的报告内容要求涵盖：问题的分析、程序的设计、程序的实现及调试情况。
## 内容
### 必选模块
构图（裁剪）、 旋转、光感、亮度、曝光、对比度、曲线调整、直方图均衡化、饱和度调整，曲线调色、HSL，锐化，平滑、色温、色调、文字
### 三选一模块
- 去雾功能：完成图像去雾功能
- 水印功能：为修图后的图像添加可见水印，但不影响整体视觉只来给你
- 美颜滤镜：为人脸图片添加美颜功能。要求：(a)实现图片的人脸检测; (b)仅仅对人脸进行美颜滤镜，其他的地方不需要
## 具体实现
### 使用工具
- qt
- opencv
- cmake
- vscode
### 主要框架
```
|-- CMakeLists.txt
|-- README.md
|-- apps
|   |-- CMakeLists.txt
|   `-- mip.cpp
|-- build
|-- res
`-- src
    |-- CMakeLists.txt
    |-- MainInterface.cpp
    |-- MainInterface.h
    |-- MainInterface.ui
    |-- fun
    |   |-- ColorAdjust.cpp
    |   |-- ColorAdjust.h
    |   |-- ImageEdit.cpp
    |   |-- ImageEdit.h
    |   |-- Others.cpp
    |   |-- Others.h
    |   `-- Tool.hpp
    |-- interface
    |   |-- QComposition.cpp
    |   |-- QComposition.h
    |   `-- QComposition.ui
    `-- res.qrc
```
### 分类
#### 图像编辑：Image editing
- 构图（裁剪）Composition (cropping)
- 旋转 Spin
- 曝光 Exposure
- 亮度 Brightness
- 对比度 Contrast ratio
- 直方图均衡化 Histogram equalization
- 锐化 Sharpen
- 平滑 Smooth
- 色温 Color temperature
- 色调 Tone
#### 色彩调整功能：Color adjustment
- 光感 Light sense
- 曲线调整 Curve adjustment
- 饱和度调整 Saturation adjustment
- 曲线调色 Curve tone
- HSL（色相、饱和度、亮度）HSL (Hue, saturation, brightness)
#### 其他功能：Others
- 文字 Text
- 去雾 Clear the fog
- 水印 Watermark
- 美颜 Beauty
### 功能实现
#### 必选功能
- 构图（裁剪）：使用 `cv::Rect` 和 `cv::Mat` 的 `operator()` 运算符来切割图像

- 旋转：使用 `cv::getRotationMatrix2D` 函数获取旋转矩阵，再使用 `cv::warpAffine` 函数进行仿射变换

- 光感、亮度、曝光、对比度、曲线调整、直方图均衡化、饱和度调整、曲线调色：这些功能可以通过调整像素的数值来实现。你可以使用 `cv::Mat` 的 `operator()` 运算符和 `cv::addWeighted` 函数来调整图像的亮度、对比度和曝光，使用 `cv::LUT` 函数来应用曲线调整和直方图均衡化。

- HSL、色温、色调：这些功能可以通过转换图像的颜色空间来实现。你可以使用 `cv::cvtColor` 函数将图像从一个颜色空间转换为另一个颜色空间，例如从 RGB 转换到 HLS。

- 锐化：使用卷积操作和滤波器来实现图像的锐化。你可以使用 `cv::filter2D` 函数应用自定义的卷积核来增强图像的边缘和细节。

- 平滑：使用平滑滤波器（例如高斯滤波器或均值滤波器）来减少图像的噪声和细节。你可以使用 `cv::GaussianBlur` 或 `cv::blur` 函数来应用平滑滤波器。

- 色调：使用 `cv::addWeighted` 函数来调整图像的颜色和色调。

- 文字：使用 `cv::putText` 函数在图像上添加文字。你可以指定字体、位置、颜色和大小等参数。
#### 三选一功能
1. 去雾功能：
   - 去雾是一个比较复杂的任务，需要使用一些图像处理算法。你可以尝试使用 Dark Channel Prior（暗通道先验）算法或者 Retinex（多尺度图像增强）算法等去雾方法。
   - 首先，你需要对输入图像进行预处理，例如计算图像的暗通道或者多尺度图像。
   - 然后，使用计算得到的暗通道或者多尺度图像来估计场景中的大气光照和透射率。
   - 最后，使用估计得到的大气光照和透射率来恢复去雾后的图像。
2. 水印功能：
   - 为了给修图后的图像添加水印，你可以在图像上绘制文字或者图像作为水印。
   - 使用 OpenCV 的 `cv::putText` 函数可以在图像上添加文字水印。你可以指定字体、位置、颜色和大小等参数。
   - 如果你想要添加图像水印，你可以使用 OpenCV 的 `cv::addWeighted` 函数将图像水印叠加到修图后的图像上。
3. 美颜滤镜：
   - 美颜滤镜需要先进行人脸检测，你可以使用 OpenCV 的人脸检测器（例如 Haar 特征分类器或者深度学习模型）来检测人脸位置。
   - 一旦检测到人脸，你可以使用美颜滤镜算法来对人脸区域进行美颜处理。例如，你可以使用图像的模糊、均值迁移或者色彩校正等方法来实现美颜效果。
   - 请注意，美颜滤镜只应用于人脸区域，其他区域不需要进行处理。你可以使用人脸检测结果来选择应用美颜滤镜的区域。