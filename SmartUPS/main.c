#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //winͷ�ļ�


int execmd(char* cmd,char* result) 
{
    char buffer[128];                         //���建����                        
    FILE* pipe = _popen(cmd, "r");            //�򿪹ܵ�����ִ������ 
    if (!pipe)
          return 0;                      //����0��ʾ����ʧ�� 

    while(!feof(pipe)) 
	{
		if(fgets(buffer, 128, pipe))
		{             //���ܵ������result�� 
            strcat(result,buffer);
        }
    }
    _pclose(pipe);                            //�رչܵ� 
    return 1;                                 //����1��ʾ���гɹ� 
}

int main()
{
    char result[1024*4]="";                   //�����Ž�����ַ������� 
	int i;
	int Ping_OK;

	printf("������Դ��������� V1.0  \n����:rankaiyx  QQ:858075120  ����:20180421\n\n");
    printf("˵��:\n������ʼ Ping ·����\nĿ���豸IP: 192.168.0.1\n");
	printf("Pingͨ ���ʾ�����繩������������Ϊ�쳣����������\n\n");
	for(i=10;i>0;i--)
    {
        printf("���� %d �뿪ʼ����\n",i);
        Sleep(1000); //��ʱ1��
    }
	printf("\n��ʼ����\n",i);

	while(1)
	{
		memset(result,0,1024);                //����ַ���
		execmd("ping 192.168.0.1",result);    //ִ�� Ping ����
		//printf("%s", result);  

		Ping_OK = 0;
		for(i=0;i<1024;i++)
		{
			if(result[i]=='T' && result[i+1]=='T' && result[i+2]=='L')  //���ƽ Ping ������Ƿ���� "TTL",����������ʾ Ping ͨ
			{
				Ping_OK = 1;
			}
		}
		if(Ping_OK == 1)
		{
			printf("\n");
            printf("#################  ������Դ ���������� #################\n");
            printf("\n");
		}
		else
		{
			for(i=5;i>0;i--)
			{
				printf("������Դ �����쳣�� ���� %d �������֤��\n",i);
				Sleep(1000); //��ʱ1��
			}

			printf("\n��ʼ��֤\n\n",i);

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
				printf("\n#############  �����쳣 �������ߣ� ##############\n\n\n");
				system("shutdown /h");                          //��ʼ����  (����������߲��� ֻ���� Windows Vista ����ϵͳ��)
				break;
			}

		}

		for(i=20;i>0;i--)
        {
            printf("���� %d �뿪ʼ�ز�\n",i);
            Sleep(1000); //��ʱ1��
        }
		printf("��ʼ�ز�\n\n",i);
	}

    system("pause");                          //��ͣ�Բ鿴��� 

} 