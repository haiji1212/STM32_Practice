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