#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //win头文件

int execmd(char* cmd,char* result) 
{
	char buffer[128];                         //定义缓冲区                        
	FILE* pipe = _popen(cmd, "r");            //打开管道，并执行命令 
	if (!pipe)
		return 0;                             //返回0表示运行失败 
	while(!feof(pipe)) 
	{
		if(fgets(buffer, 128, pipe))
		{                                     //将管道输出到result中 
			strcat(result,buffer);
		}
	}
	_pclose(pipe);                            //关闭管道 
	return 1;                                 //返回1表示运行成功 
}

int main()
{
	char result[1024*4]="";                   //定义存放结果的字符串数组 
	int i;
	int Ping_OK;

	printf("交流电源供电检测程序 V1.0  \n作者:rankaiyx  QQ:858075120  日期:20180421\n\n");
	printf("说明:\n即将开始 Ping 路由器\n目标设备IP: 192.168.0.1\n");
	printf("Ping通 则表示交流电供电正常，否则为异常并启动休眠\n\n");
	
	for(i=10;i>0;i--)
	{
		printf("还有 %d 秒开始测试\n",i);
		Sleep(1000); //延时 1000 ms
	}
	printf("\n开始测试\n",i);

	while(1)
	{
		memset(result,0,1024);                //清空字符串
		execmd("ping 192.168.0.1",result);    //执行 Ping 命令
		//printf("%s", result);  

		Ping_OK = 0;
		for(i=0;i<1024;i++)
		{
			if(result[i]=='T' && result[i+1]=='T' && result[i+2]=='L')  //检查平 Ping 结果中是否包含 "TTL",如果包含则表示 Ping 通
			{
				Ping_OK = 1;
			}
		}
		if(Ping_OK == 1)
		{
			printf("\n");
			printf("#################  交流电源 供电正常！ #################\n");
			printf("\n");
		}
		else
		{
			for(i=5;i>0;i--)
			{
				printf("交流电源 供电异常！ 还有 %d 秒进行验证！\n",i);
				Sleep(1000); //延时 1000 ms
			}

			printf("\n开始验证\n\n",i);

			memset(result,0,1024);
			execmd("ping 192.168.0.1",result);

			for(i=0;i<1024;i++)
			{
				if(result[i]=='T' && result[i+1]=='T' && result[i+2]=='L')
				{
					Ping_OK = 1;
				}
			}
			if(Ping_OK == 0)
			{
				printf("\n#############  供电异常 启动休眠！ ##############\n\n\n");
				system("shutdown /h");                          //开始休眠  (该命令的休眠参数 只存在 Windows Vista 以上系统中)
				break;
			}
		}

		for(i=20;i>0;i--)
		{
			printf("还有 %d 秒开始重测\n",i);
			Sleep(1000); //延时 1000 ms
		}
		printf("开始重测\n\n",i);
	}
	
	system("pause");                          //暂停以查看结果 
} 
