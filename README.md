# HighSpeedAcquisitionSystemBasedOn4G
基于4G的高速采集系统

采用RaspberryPi树莓派3b驱动ADS1256模块 24位高精度ADC模块
硬件ADC驱动方式 BCM2835驱动方式
没有使用WringPi库  性能太低 SPI速度远低于采样率
通讯采用TCP/IP JSon格式解析

上位机采用QTchart OpenGL作图 
八通道同时采集画面测试流畅
