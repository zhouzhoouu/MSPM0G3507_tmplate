# MSPM0G3507 工程模板（基于 CMake + GCC）

这是一个基于 [Texas Instruments MSPM0G3507](https://www.ti.com/product/MSPM0G3507) 微控制器的工程模板，使用 CMake 管理构建流程，可使用 PyOCD 烧录调试。

---

## 文件结构说明

```bash
MSPM0G3507_tmplate/
│
├── cmake/                    # 工具链配置
│   └── gcc-arm-none-eabi.cmake      # GCC Toolchain 文件
│
├── CMSIS/                    # CMSIS 头文件，可选
│   ├── Core/
│   └── DSP/
│
├── Lib/                      # 链接的静态库
│   ├── arm_cortexM0l_math.a        # CMSIS DSP 数学库
│   └── driverlib.a                 # TI 提供的 DriverLib 库（预编译）
│
├── Startup/                  # 启动文件与链接脚本
│   ├── mspm0g3507.lds              # Linker script，设置内存布局
│   └── startup_mspm0g350x_gcc.c    # 启动代码，含中断向量表
│
├── Sysconfig/                # SysConfig 工具生成的外设配置代码
│   ├── sys.syscfg                  # SysConfig 配置源文件
│   ├── ti_msp_dl_config.c          # 外设初始化代码
│   └── ti_msp_dl_config.h          # 外设初始化头文件
│
├── ti/                       # TI SDK 源文件（当前未启用）
│   └── devices/
│       └── driverlib/              # TI DriverLib 源码（可选编译使用）
│
├── User/                     # 用户代码
│   ├── Inc/                        # 自定义头文件
│   └── Src/                        # 自定义源文件（如 main.c）
│
├── CMakeLists.txt            # CMake 主配置文件
├── .gitignore                # Git 忽略规则
└── README.md                 # 项目说明文档（本文件）
```

## 构建方法
- #### 准备工作
    - 安装工具链：
        - [GCC ARM Embedded](https://developer.arm.com/downloads/-/gnu-rm)
        - [CMake](https://cmake.org/)
        - [Ninja](https://ninja-build.org/)（推荐）
    - 可选：安装 [TI SysConfig](https://www.ti.com/tool/SYSCONFIG) 进行外设配置
- #### 编译命令
    ```bash
    cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
    cmake --build build
    ```
    driverlib.a 和 startup.c 会自动链接，输出 MSPM0G3507_Blink.elf

## 烧录与调试
- #### 使用 PyOCD 烧录
    ```bash
    pyocd flash build/MSPM0G3507_Blink.elf
    ```
- #### 启动 GDB 调试服务器
    ```bash
    pyocd gdbserver
    ```
    CLion 中可配置 GDB Debug，路径选择 arm-none-eabi-gdb，并连接到 3333 端口。

## 示例功能
- 本模板已实现基本 LED 闪烁功能，代码位于：

    ```c
    // User/Src/main.c

    int main(void) {
        SYSCFG_DL_init();                // 调用 SysConfig 生成的初始化代码
        while (1) {
            DL_GPIO_togglePins(GPIOB, DL_GPIO_PIN_22);
            delay_loop();                // 简易延时函数
        }
    }
    ```
## 常见问题
- #### 无法命中断点：确认 -g 选项已启用并烧录了最新 .elf 文件。
    PyOCD 无法识别器件：
    确认已安装 CMSIS-Pack
    ```bash
    pyocd pack install TexasInstruments.MSPM0G_DFP
    ```
## 参考资源
- [MSPM0G3507 Datasheet](https://www.ti.com/lit/ds/symlink/mspm0g3507.pdf)
- [MSPM0 SDK](https://www.ti.com/tool/MSPM0-SDK)
- [TI SysConfig 工具](https://www.ti.com/tool/SYSCONFIG)
- [PyOCD 文档](https://pyocd.io/)