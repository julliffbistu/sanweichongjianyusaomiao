#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


int main()
{
	int data = 1;
	//��ʼ�� DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
while(1)
	{
		data = data +1;
	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("192.168.1.10");  //�����IP��ַ
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬
	listen(servSock, 20);

	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	//��ͻ��˷�������
	char str[2000];
	sprintf(str, "%d",data);
	//char *str = "Hello World !";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	printf("fa song\n");
	//_sleep(100);
	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);
	}
	//��ֹ DLL ��ʹ��
	WSACleanup();
	return 0;
}
