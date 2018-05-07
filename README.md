# SmartUPS
Let a computer with a simple UPS also have a smart sleep function when power is cut off.    
让使用简单的UPS的计算机也拥有聪明的休眠功能，在停电的时候。


交流电源供电检测程序   作者:rankaiyx  QQ:858075120  日期:20180421

原理说明: 路由器接交流电源，计算机由简单UPS供电，通过判断 Ping 路由器 的通断，确定交流电是否停电。
Ping通 则表示交流电供电正常，否则为异常并启动休眠。

IDE:VC6.0 Language:C

