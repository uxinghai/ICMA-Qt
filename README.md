# ICMA-Qt

This software uses the Qt framework, licensed under the GNU Lesser General Public License (LGPL) version 2.1 (or later).
You can obtain a copy of the LGPL license at https://www.gnu.org/licenses/lgpl.html.

2025届个人毕业设计



### 毕设每日完成情况（按时间顺序排列）

#### 2025/01/06

- 软件正式启动，构思结构。

#### 2025/01/08

- 应用实现了8种主题（深色浅色各4种），以及系统主题的切换（无需重启软件）。

#### 2025/01/09

- 应用启动时通过配置文件初始化UI（用户上次行为）。
- 退出应用时，提示用户并将界面状态保存至配置文件（保存当次行为）。
- 完成QT简介、ICMA简介及多语言版本的协议声明，使用本地Apifox进行记录与调用。

#### 2025/01/12

- 系统中文件写入ICMA数据库（目录部分完成），并在软件启动时通过多线程方式写入。

#### 2025/01/15

- 实现人脸检测模块的百度AIToken获取功能。
- 通过NetworkAccessManager后台静默获取Token。

#### 2025/01/17

- 图像处理中的人脸信息检测模块：使用多线程技术避免窗口堵塞。
    - 主线程负责UI实时刷新显示人脸。
    - 副线程实时处理人脸图像转为Base64，发出API请求获取人脸信息。
    - 实现了较为美观的界面及高效功能。

#### 2025/01/18

- 自定义GraphicsView并实现以下功能：
    1. 用户按住Ctrl + 滚轮实现缩放；
    2. 图像随用户改变窗口大小而改变；
    3. 用户可直接从外部拖拽支持的图像格式进入窗口；
    4. 实现了一个“最佳适应”右键菜单动作项。

#### 2025/01/20

1. 实现图像比例裁剪功能。
2. 自定义MyAutoStack类用于存放图像修改历史记录，便于用户撤回修改。
3. 每次撤回时从历史记录中撤回，并在每次切换模块时更新shouldBeProcessed指向的图像，该功能的核心在于图像指向的变化。

#### 2025/01/21

1. 自定义MyInformationBox类，实现类似浏览器风格的自上而下弹出的消息提示框，支持自动隐藏时长，并使用QT自带的动画类，使其自然美观。
2. 优化图像处理界面中的替换保存和另存功能，并结合自定义的消息提示框，向用户提供提示信息，提升用户体验。
3. 完成Resize功能实现。
4. 优化了Crop类和Resize类的代码，使其结构清晰减少了冗余。
5. 实现了自定义尺寸功能，并对输入进行了有效性的限制。
6. 优化了图像处理的所有信号槽连接代码，使其更简洁。



#### 2025/01/22

保存图像后使历史记录只保留最新保存的图像，即清空后放入栈顶保留图像



#### 2025/01/23

##### 图像亮度对比度饱和度反相度处理

##### 坑：原图必须使用imread读取，而非直接使用pixmapToMat转换！！！否则无法后续修改像素值

##### **（一种植物），convertTo崩溃就是因为没有使用imread读取,（不报错但崩溃）

利用processedMat来保留最新处理图像,processedMat在每次调整功能模块时更新

curMat用于实时更新图像



#### 2025/01/24

优化程序所有图像以cv::Mat格式保存，需要pixmap时转换即可

使用如下格式优化系统

```c++
QMap<cv::Mat,MatInfo> curMat;
```

MatInfo中包含:

```c++
struct AdjustValue {
  double brightness = -1;
  double contrast = -1;
  double saturation = -1;
  double contrary = -1;
};

struct Algorithm {
  int kernelValue = 0;
  QRadioButton* radioButton = {};
};

struct Crop {
  int cropValue = 0;
};

struct Resize {
  int resizeValue = 0;
};

struct MatInfo {
  AdjustValue adjustValue;
  Algorithm algorithm;
  Crop crop;
  Resize resize;
};
```

图像像素修改完成



#### 2025/01/26

1. 过滤算法模块（磨皮去杂边功能）完成。

2. 图像旋转变换模块完成。

3. 优化美化了ToolBox，提供更优的用户体验。

4. 优化PS模块的信号槽连接代码。

5. 修复Bug

   | BUG名称                    | 表现形式                             | 修复过程                                                     |
   	| -------------------------- | ------------------------------------ | ------------------------------------------------------------ |
   | 首次打卡图像无法被正常处理 | 直接拖拽滑块处理，会显示一张空白图像 | ![image-20250126010211633](../AppData/Roaming/Typora/typora-user-images/image-20250126010211633.png) |
   | Kernel 控制异常            | 滑块无法被拖动                       | ![image-20250126011346932](../AppData/Roaming/Typora/typora-user-images/image-20250126011346932.png) |

	

