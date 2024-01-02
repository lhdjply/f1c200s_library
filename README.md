该项目是基于全志**F1C100S**或者**F1C200S**芯片

# 操作系统

windows（linux平台未测试，请自行测试）

# 编辑环境

推荐使用**VSCode**

# 编译器

arm-none-eabi-gcc

# 文件夹介绍


| 文件夹      | 简介                                                          |
| ----------- | ------------------------------------------------------------- |
| .gitee      | gitee平台issue和pr模板                                        |
| .github     | github平台issue和pr模板，以及ci检查                           |
| .vscode     | vscode配置文件                                                |
| bootloader  | bootloader文件                                                |
| dsp         | dsp库（例如`arm_mean_f32`)                                    |
| f1cx00s_lib | 模仿**stm32**风格写的库函数                                   |
| hardware    | 外设初始化                                                    |
| myresoure   | 屏幕界面程序（使用lvgl)                                       |
| pcb         | 使用嘉立创EDA专业版进行绘制，项目例子都基于改线路板进行编写。 |
| system      | 任务文件，以及延迟等等                                        |
| third_party | 第三方库，包含`cherryusb`、`fatfs`、`lvgl`、`rt-thread`       |
| tools       | 下载程序工具，code-format工具（需要安装astyle)                |
| user        | main函数，链接脚本                                            |

## myresoure文件夹

界面左边为lvgl官方例子，界面右边为库函数测试例子。
其中库函数例子外设初始化以及功能函数已在`hardware`，界面例子包括`gpio`、`i2c`、`pwm`、`sdio`、`spi`、`uart`、`usb`。
