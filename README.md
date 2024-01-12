# STM32_Practice
以下是文件夹的**文件说明**：

- .gitignore
  - 根据 keil 规则忽略部分文件
- keilkill
  - 自动删除脚本文件
- 2-1 STM32工程模板
  - 简单地实现点亮LED灯
    - User	//用户存放main函数和mcu应用配置函数
      - main	//功能实现
- 3-1 LED闪烁
  - 实现LED的亮灭交替闪烁
    - System
      - Delay	//延时函数模块
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 3-2 LED流水灯
  - 实现LED流水灯
    - System
      - Delay	//延时函数模块
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 3-3 蜂鸣器
  - 驱动蜂鸣器
    - System
      - Delay	//延时函数模块
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 3-4 按键控制LED
  - 用两个按键分别控制对应LED的亮灭切换
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 3-5 光敏传感器控制蜂鸣器
  - 光线强度未达到阈值时，蜂鸣器发声；光线达到阈值时，蜂鸣器不发声。
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - Buzzer   //Buzzer模块，包括蜂鸣器初始化、蜂鸣器响/不响、反转蜂鸣器状态的函数
      - LightSensor   //LightSensor模块，包括光敏传感器初始化、获取光敏传感器状态的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 4-1 OLED显示屏
  - 关于OLED显示屏的基本操作
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 5-1 对射式红外传感器
  - 利用外部中断对对射式红外传感器的触发次数进行计次
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 5-2 旋转编码器计次
  - 用两个引脚作为外部中断触发源，当发生中断时，通过引脚电平高低来判断正转还是反转
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-1 定时器定时中断
  - TIM2内部定时，实现OLED显示屏显示数字每秒加1
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-2 定时器外部时钟
  - TIM2外部引脚触发。实验中，外部引脚连接到对射式红外传感器，每次触发CNT加一，加到第10次则触发中断。
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-3 PWM驱动LED呼吸灯
  - 在该实验中，ARR = 100 - 1，PSC = 720 - 1，则每隔 10 us，CNT 加一；当 CNT 从 0 加到 99，触发中断（即每隔 1 ms 触发一次中断）。在输出比较中，初始化定义高电平输出有效，选择PWM1模式，即当 CNT < CCR 时，会输出高电平。因此当 CCR 由 0 依次递增到 100 时，LED（接至A0） 逐渐变亮；当 CCR 由 100 依次递减到 0 时，LED 逐渐变暗。
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - PWM  //PWM模块，包括PWM初始化、设置CCR的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-4 PWM驱动舵机
  - 实现按键控制舵机可以由 0° 旋转至 180°
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - PWM  //PWM模块，包括PWM初始化、设置CCR的函数
      - Servo  //Servo模块，包括舵机初始化、将角度线性转换设置CCR的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-5 PWM驱动直流电机
  - 实现按键控制直流电机正反转的速率
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - PWM  //PWM模块，包括PWM初始化、设置CCR的函数
      - Servo  //Servo模块，包括舵机初始化、将角度线性转换设置CCR的函数
      - Motor  //Motor模块，包括电机初始化、设置正/反转的速度的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-6 输入捕获模式测频率
  - 实现用输出比较的方式实现输出固定频率的PWM方波，用输入捕获获取该方波频率。
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - PWM  //PWM模块，包括PWM初始化、设置CCR的函数
      - IC  //IC模块，包括IC初始化、获取输入捕获频率的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-7 PWMI模式测频率占空比
  - 实现用输出比较的方式实现输出固定频率的PWM方波，用输入捕获和PWMI获取该方波频率和占空比。
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - PWM  //PWM模块，包括PWM初始化、设置CCR的函数
      - IC  //IC模块，包括IC初始化、获取输入捕获频率、获取输入捕获占空比的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 6-8 编码器接口测速
  - 实现编码器正反转计数
    - System
      - Delay	//延时函数模块
      - Timer   //定时器模块，包括Timer初始化、Timer中断的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - CountSensor  //CountSensor模块，包括相关IO和外部中断的初始化、计次、中断的函数
      - Encoder  //Encoder模块，包括Encoder初始化、获取编码器的增量值的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 7-1 AD单通道
  - 实时检测电位器电压
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - AD  //AD模块，包括AD初始化、获取AD转换数据的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 7-2 AD多通道
  - 实时检测电位器、对射式红外传感器、热敏传感器、光感传感器电压
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - AD  //AD模块，包括AD初始化、获取AD转换数据的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 8-1 DMA数据转运
  - 实现存储器到存储器的数据转运
    - System
      - Delay	//延时函数模块
      - MyDMA  //DMA模块，包括DMA初始化、DMA转运的函数
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 8-2 DMA+AD多通道
  - 实时检测电位器、对射式红外传感器、热敏传感器、光感传感器ADC电压采样数据，通过DMA转运数据
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - AD  //AD模块，包括AD初始化的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 9-1 串口发送
  - 实现主板作为发送端向上位机发送数据的功能
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - Serial  //Serial模块，包括Serial初始化、串口发送一个字节数据、串口发送数组、串口发送字符串、串口发送数字、串口打印字符串的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 9-2 串口发送+接收
  - 实现主板作为接收端接收上位机发送的数据的功能
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - Serial  //Serial模块，包括Serial初始化、串口发送一个字节数据、串口发送数组、串口发送字符串、串口发送数字、串口打印字符串、获取串口接收标志、获取串口接收数据、接收中断的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 9-3 串口收发HEX数据包
  - 实现主板对HEX数据包的收发
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - Serial  //Serial模块，包括Serial初始化、串口发送一个字节数据、串口发送数组、串口发送字符串、串口发送数字、串口打印字符串、获取串口接收标志、获取串口接收数据、接收中断、发送封装包头包尾的数据包的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现
- 9-4 串口收发文本数据包
  - 实现主板对文本数据包的接收，并解析数据包，如果解析结果符合要求则亮灯
    - System
      - Delay	//延时函数模块
    - Hardware
      - LED	//LED模块，包括LED初始化、点亮LED、熄灭LED、反转LED亮灭状态的函数
      - Key    //Key模块，包括Key初始化、获取Key状态的函数
      - OLED  //OLED模块，包括OLED初始化、OLED显示的函数
      - OLED_Font  //OLED字模库
      - Serial  //Serial模块，包括Serial初始化、串口发送一个字节数据、串口发送数组、串口发送字符串、串口发送数字、串口打印字符串、获取串口接收标志、获取串口接收数据、接收中断、发送封装包头包尾的数据包的函数
    - User   //用户存放main函数和mcu应用配置函数
      - main  //功能实现