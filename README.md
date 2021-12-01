# RENESAS + RT-Thread 传感器网关 DEMO

## 简介

这是一个基于 RA6M4-CPK 开发板 + RT-Thread 实现的传感器网关 DEMO。

本文将介绍如何一步步从零搭建一个传感器网关。

下图是整体的设计框图，板载 ISL29035 光敏传感器使用 IIC 通信接口接入主控芯片，RW007 用于网络通信。在主控芯片中添加所需要的软件包、组件等中间件来快速搭建起一个传感器网关。

![image-20211209181946189](image/image-20211130182936820.png)


## 实际运行效果
1、在 msh 中输入`linkkit_demo` 命令创建并启动 demo 线程

![image-20211130111948709](image/image-20211130111948709.png)

2、在云平台的设备调试页面查看实时刷新的数据。

![image-20211130111052259](image/image-20211130111052259.png)

## 准备工作

- [RT-Thread studio v2.1.4](https://download-sh-cmcc.rt-thread.org:9151/www/studio/download/RT-Thread%20Studio-v2.1.4-setup-x86_64_20211215-1700.exe)
- Renesas 开发板支持包
  ![image-20211216225122952](image\sdk-bsp.png)
- JLINK v7.50
  ![image-20211217104550311](image\jlink下载.png)
- GNU_Tools_for_ARM_Embedded_Processors v6.3.1 或 v10.2.1，默认配置为 v10.2.1
  ![image-20211223152205419](image/gcc.png)
- [RASC](https://github.com/renesas/fsp/releases)（可选）：版本 fsp v3.1.0、rasc v2021-04
  ![image-20211217012025247](image\rasc下载.png)
- 阿里云：[生活物联网平台](https://living.aliyun.com/)
- [RA6M4-CPK 开发板](https://www2.renesas.cn/cn/zh/products/microcontrollers-microprocessors/ra-cortex-m-mcus/cpk-ra6m4-evaluation-board)
- USB-TTL：连接 UART7 （TX:P613; RX:P614）**波特率 115200**
- 板载传感器：[ISL29035](https://www2.renesas.cn/cn/zh/products/sensor-products/light-proximity-sensors/ambient-light-sensors/ambient-light-digital-sensors/isl29035-integrated-digital-light-sensor-interrupt)
- WiFi 网络模块：[RW007](https://gitee.com/RT-Thread-Mirror/rw007)

## 实现过程

1. 下载必备的开发工具，[参考文档](https://gitee.com/rtthread/rt-thread/tree/master/bsp/ra6m4-cpk) 搭建好软件开发环境。

2. 将传感器模块和网络模块连接开发板。

|       模块        | 模块引脚 | 开发板引脚 | MCU引脚编号 |
| :---------------: | :------: | :--------: | :---------: |
|     **RW007**     |    \     |     \      |      \      |
|                   |   GND    |    GND     |     --      |
|                   |   SCK    |    P412    |   0x040C    |
|                   |   MISO   |    P410    |   0x040A    |
|                   |   MOSI   |    P411    |   0x040B    |
|                   |    CS    |    P413    |   0x040D    |
|                   | D9(INT)  |    P506    |   0x0506    |
|                   | D8(RST)  |    P415    |   0x040F    |
|                   |   3V3    |    VCC     |     --      |
| **板载 ISL29035** |    \     |     \      |      \      |
|                   |   SCL    |    P512    |   0x050C    |
|                   |   SDA    |    P511    |   0x050B    |

- 开发板示意图
  ![cpk-ra6m4.png](image/cpk-ra6m4.png)

- 实物连接图
  ![image-20211130205400622](image/image-20211130205400622.png)
  
- 连接 UART7 （TX:P613; RX:P614）,**波特率 115200**。

  ![image-20211217110528698](image\uart7.png)

3. 打开 RT-Thread studio，创建开发板示例工程

    ![image-20211216141944291](image\新建工程1.png)

    ![image-20211216142019209](image\新建工程2.png)

    ![image-20211216141818046](image\新建工程.png)


4. GCC 版本建议使用 v10.2.1，可以在 studio 的包管理器中下载并配置工具链路径

![image-20211223154338231](image/gcc-下载.png)

 > studio 中的路径：
 > \repo\Extract\ToolChain_Support_Packages\ARM\GNU_Tools_for_ARM_Embedded_Processors\10.2.1\bin

![image-20211215194633235](image/工具链配置.png)

5. 配置 JLINK 路径

![image-20211215225748084](image/jlink_config.png)

![image-20211215225559811](image/dbg_config.png)

6. 编译、下载，验证运行结果
  - 查看系统运行情况
  >输入命令 `help`、`ps`、`free`、`list_device` 等命令查看系统运行状态

  - 验证传感器功能
  > 输入命令 `sensor_polling li_isl29` 验证是否获取到传感器的光线强度数据。

  - 验证 WiFi 功能
  > 输入 `wifi` 查看系统支持的 wifi 命令
  > 输入 `wifi scan` 扫描当前环境中的 WiFi 热点信号及信息
  > 输入 `wifi join [ssid] [passwor]` 连接热点


7. 连云配置

  - 在[云平台](https://living.aliyun.com/)创建项目，创建完成后点击项目进入配置
    ![image-20211201110843504](image/image-20211201110843504.png)

  - 在新建的项目中创建产品
      ![image-20211201111106434](image/image-20211201111106434.png)

  - 进入设备调试页面选择将页面拉到最下方选择 “未认证模组”
    ![image-20211201112028255](image/image-20211201112028255.png)

  - 新增测试设备 “renesas_test”
    ![image-20211201112419422](image/image-20211201112419422.png)

  - 查看设备三元组信息
    ![image-20211201112857831](image/image-20211201112857831.png)

  - 在 menuconfig 中开启 ali-iotkit 软件包，将新创建的产品三元组信息填入配置项中。保存配置信息，编译、下载工程。

  > 注意：三元组信息是一机一密，所以不能有两个以上的设备使用同一组三元组信息。
  > ![image-20211201110539948](image/image-20211201110539948.png)

  - 修改代码中连接热点的 SSID 和 password，启动 demo 程序可自动连接。**注意：SSID 需要使用全小写**
    ![image-20211217120001220](image\修改ssid.png)

8. 编译、下载，验证传感器网关数据上报功能。
  >注意：暂不支持在 Studio 上 DEBUG，请直接下载程序验证。(12-27)
  >
  >命令行输入 `linkkit_demo` 命令，启动网关 demo 程序。在设备详情页查看实时上报信息
  >![image-20211130111052259](image/image-20211130111052259.png)


## 扩展内容
### 使用 RASC 配置工程

- 配置 RASC 路径

![image-20211216143948414](image\rasc-1.png)

![image-20211216144014033](image\rasc-2.png)

- 使用 RASC 结合 setting 配置工程，开启其他外设功能，可参考文档：[使用瑞萨FSP配置工具](https://gitee.com/rtthread/rt-thread/blob/master/bsp/ra6m4-cpk/docs)

### 如何从零开始配置传感器网关
1. 配置所需要的软件包、组件、外设驱动

- 创建 CPK-RA6M4 模板工程
- 添加 [RW007](http://packages.rt-thread.org/detail.html?package=rw007) 软件包，配置说明：[使用瑞萨FSP配置工具](https://gitee.com/rtthread/rt-thread/blob/master/bsp/ra6m4-cpk/docs) RW007 部分。
- 添加 [ali-iotkit](http://packages.rt-thread.org/detail.html?package=ali-iotkit) 软件包
- 修改 cJSON 软件包配置：版本号为 v1.7.14 。
- 添加 ISL29035 传感器软件包

2. 云平台创建产品，将设备的三元组信息配置到工程中
3. 编译、下载，验证执行结果

## 开源代码

整个 demo 的代码开源到 Github：[跳转链接](https://github.com/ShermanShao/renesas_sensor_gateway_demo)

## 更多资料

- [开发板官网主页](https://www2.renesas.cn/cn/zh/products/microcontrollers-microprocessors/ra-cortex-m-mcus/cpk-ra6m4-evaluation-board)
- [开发板用户手册](https://www2.renesas.cn/cn/zh/document/mah/1527156?language=zh&r=1527191)
- [瑞萨RA MCU 基础知识](https://www2.renesas.cn/cn/zh/document/gde/1520091)
- [RA6 MCU 快速设计指南](https://www2.renesas.cn/cn/zh/document/apn/ra6-quick-design-guide)
- [RA6M4_datasheet](https://www2.renesas.cn/cn/zh/document/dst/ra6m4-group-datasheet)
- [RA6M4 Group User’s Manual: Hardware](https://www2.renesas.cn/cn/zh/document/man/ra6m4-group-user-s-manual-hardware)
