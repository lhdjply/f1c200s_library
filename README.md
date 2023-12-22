该项目是基于全志**F1C100S**或者**F1C200S**芯片

# 操作系统

windows（linux平台未测试，请自行测试）

# 编辑环境

推荐使用**VSCode**

# 编译器

arm-none-eabi-gcc

# 文件夹

* .gitee：gitee平台issue和pr模板
* .github：github平台issue和pr模板，以及ci检查
* pcb：pcb文件待更新
* program：所有程序在改文件夹中
* tools：下载程序工具，code-format工具（需要安装astyle)

## program文件夹


| 文件夹      | 简介                                                    |
| ----------- | ------------------------------------------------------- |
| bootloader  | bootloader文件                                          |
| f1cx00s_lib | 模仿**stm32**风格写的库函数                             |
| hardware    | 外设初始化                                              |
| myresoure   | 屏幕界面程序（使用lvgl)                                 |
| system      | 任务文件，以及延迟等等                                  |
| third_party | 第三方库，包含`cherryusb`、`fatfs`、`lvgl`、`rt-thread` |
| user        | main函数                                                |

### myresoure文件夹

界面左边为lvgl官方例子，界面右边为库函数测试例子

其中库函数例子外设初始化以及功能函数已在`hardware`，界面例子目前只写了`gpio`，其他待更新
