// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"
#include "afxsock.h"
#include "iostream"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		/*
		// Khoi tao Thu vien
		if( AfxSocketInit() == FALSE)
		{ 
			cout<<"Khong the khoi tao Socket Libraray";
			return FALSE; 
		}

		// Tao socket dau tien
		CSocket ClientSocket;
		ClientSocket.Create();*/

		CSocket ClientSocket;
		char sAdd[1000];
		unsigned int port = 1234; //Cung port voi server
		AfxSocketInit(NULL);

		//1. Tao socket
		ClientSocket.Create();

		// Nhap dia chi IP cua server
		printf("\n Nhap dia chi IP cua server: ");
		gets_s(sAdd);

		// Ket noi den Server
		if (ClientSocket.Connect(CA2W(sAdd), port))
		{
			printf("\n Client da ket noi toi server\n");
			

			char ClientMsg[5];		
			int MsgSize;
			char *temp;

			

			// Nhan thong diep tu Server
				ClientSocket.Receive((char*)&MsgSize,sizeof(int),0); // Neu nhan loi thi tra ve la SOCKET_ERROR.			
				temp = new char[MsgSize +1];
				ClientSocket.Receive((char*)temp,MsgSize,0);

			// In thong diep ra
				temp[MsgSize] ='\0';
				cout<<"Server:\n "<<temp<<endl;
				delete temp;
			//Cho nguoi dung chon hanh trinh
				int hanhtrinh;
 
				cout <<"Client:";
				cin >> hanhtrinh;
			// Gui di lua chon cua client
				ClientSocket.Send((char*)&hanhtrinh,sizeof(int),0);
				
				
			// Nhan thong diep tu Server
				ClientSocket.Receive((char*)&MsgSize, sizeof(int), 0); // Neu nhan loi thi tra ve la SOCKET_ERROR.			
				temp = new char[MsgSize + 1];
				ClientSocket.Receive((char*)temp, MsgSize, 0);

			// In thong diep ra
				temp[MsgSize] = '\0';
				cout << "Server:\n " << temp << endl;
				delete temp;
			//Cho nguoi dung chon chi tiet ve
				char loaive;
				cout << "Loai ve: ";
				cin >> loaive;
			  // Gui di lua chon cua client
				ClientSocket.Send((char*)&loaive, sizeof(char), 0);
				
				int sl;
				cout << "So luong: ";
				cin >> sl;
				// Gui di lua chon cua client
				ClientSocket.Send((char*)&sl, sizeof(int), 0);
				
				int maloi;
				ClientSocket.Receive((char*)&maloi, sizeof(int), 0);

				if( maloi ==0){
				
				//nhan bao gia
				int gia;

				ClientSocket.Receive((char*)&gia, sizeof(int), 0);
				cout<<"So tien phai tra la: "<< gia;
				}
				else if(maloi==1)  {
					cout << "\nXin loi quy khach. So luong ve quy khach dat mua da vuot qua so luong hien co trong kho";
					cout << "\nSo luong hien co la ";
					int soveco;
					ClientSocket.Receive((char*)&soveco, sizeof(int), 0);
					cout << soveco;
				}
		
				
				
				
		
				
			
			
			
		}
		else
		{
			cout<<"Khong the ket noi den Server !!!"<<endl;
		}

		// Dong ket noi
		ClientSocket.Close();
	}

	return nRetCode;
}
