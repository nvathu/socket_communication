// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "afxsock.h"



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

		// Khoi tao thu vien Socket
		CSocket ServerSocket;
		unsigned int port = 1234;
		int i;
		AfxSocketInit(NULL);

		ServerSocket.Create(port);
		ServerSocket.Listen(5);
		int n;
		cout << "Nhap so luong client:";
		cin >> n;

		//luu thong tin ve
		typedef struct Thongtinve {
			char loaive;
			int sl;
			int gia;



		}Thongtinve;
		//thong tin ve hcm-hn
		Thongtinve hcmhn[3];
		hcmhn[0].loaive = 'a';
		hcmhn[0].sl = 50;
		hcmhn[0].gia = 60;

		hcmhn[1].loaive = 'b';
		hcmhn[1].sl = 80;
		hcmhn[1].gia = 80;

		hcmhn[2].loaive = 'c';
		hcmhn[2].sl = 40;
		hcmhn[2].gia = 60;

		//thong tin ve hcm-hue
		Thongtinve hcmhue[3];
		hcmhue[0].loaive = 'a';
		hcmhue[0].sl = 35;
		hcmhue[0].gia = 60;

		hcmhue[1].loaive = 'b';
		hcmhue[1].sl = 54;
		hcmhue[1].gia = 50;

		hcmhue[2].loaive = 'c';
		hcmhue[2].sl = 48;
		hcmhue[2].gia = 40;


		//thong tin ve hn-dl
		Thongtinve hndl[3];
		hndl[0].loaive = 'a';
		hndl[0].sl = 70;
		hndl[0].gia = 120;

		hndl[1].loaive = 'b';
		hndl[1].sl = 50;
		hndl[1].gia = 90;

		hndl[2].loaive = 'c';
		hndl[2].sl = 30;
		hndl[2].gia = 70;
		for (int i = 0; i < n; i++){
		CSocket Connector;
		
		// Khoi tao mot socket de duy tri viec ket noi va trao doi du lieu
		if (ServerSocket.Accept(Connector))
		{
			cout <<"Da co Client ket Noi !!!"<<endl<<endl;
			

			char ServerMsg[100]= "Hay chon hanh trinh cua ban (nhap 1,2 hay 3)\n1.TPHCM-HaNoi\n2.TPHCM-Hue\n3.HaNoi-Dalat";
			int MsgSize;
			

			
			
			MsgSize = strlen(ServerMsg);
			// Gui di do dai thong diep de server biet duoc do dai nay
			Connector.Send(&MsgSize,sizeof(MsgSize),0);

			// Gui di thong diep voi do dai la MsgSize
			Connector.Send(ServerMsg,MsgSize,0);

			//Nhan thong diep tu Client
			int hanhtrinh;

			Connector.Receive((char*)&hanhtrinh,sizeof(int),0); 
			printf("Khach lua chon hanh trinh %d",hanhtrinh);
			
			
			if (hanhtrinh == 1) 
			{
				
				char thongtin1[210]= "\t\tThong tin chuyen Ho Chi Minh-Ha Noi:\nLoai ve: a\tSo luong hien co: 50\t Gia: 100USD/ve\nLoai ve: b\tSo luong hien co: 80\t Gia: 80USD/ve\nLoai ve: c\tSo luong hien co: 40\t Gia: 60USD/ve\n\nVui long chon chi tiet ve";
				int kichthuoc;
				kichthuoc = strlen(thongtin1);
				// Gui di do dai thong diep de server biet duoc do dai nay
				Connector.Send(&kichthuoc, sizeof(kichthuoc), 0);
				// Gui di thong diep voi do dai la MsgSize
				Connector.Send(thongtin1, kichthuoc, 0);



				char loai,soluong ;
				Connector.Receive(&loai, sizeof(char),0);
				printf("\nDa nhan loai ve %c tu client.", loai);
				Connector.Receive(&soluong, sizeof(int), 0);
				printf("\nDa nhan so luong ve %d tu client.", soluong);
				int gia=0;
				int maloi;
				//Loc du lieu
				if (loai == 'a' && soluong <= hcmhn[0].sl || loai == 'b' && soluong <= hcmhn[1].sl || loai == 'c' && soluong <= hcmhn[2].sl) 
				{    
					int maloi = 0;
					Connector.Send((char*)&maloi, sizeof(int), 0);

					if (loai == 'a' && soluong <= hcmhn[0].sl) {

						hcmhn[0].sl -= soluong;
						cout << "\nCon " << hcmhn[0].sl << " ve";
						gia = hcmhn[0].gia * soluong;
						//in gia tren server
						cout << "\nGia tien: " << gia;

						Connector.Send((char*)&gia, sizeof(int), 0);

					}
					else if (loai == 'b' && soluong <= hcmhn[1].sl) {
						hcmhn[1].sl -= soluong;
						cout << "\nCon " << hcmhn[1].sl << " ve";
						gia = hcmhn[1].gia * soluong;

						cout << "\nGia tien: " << gia;



					}
					else if (loai == 'c' && soluong <= hcmhn[2].sl) 
					{
						hcmhn[2].sl -= soluong;
						cout << "\nCon " << hcmhn[2].sl << " ve";
						gia = hcmhn[2].gia * soluong;

						cout << "\nGia tien: " << gia;

					}
				}
				else {
					maloi = 1;
					Connector.Send((char*)&maloi, sizeof(int), 0);
					cout << "\nSo luong ve vuot qua so luong hien co";
					if(loai == 'a'){
						Connector.Send((char*)&hcmhn[0].sl, sizeof(int), 0);
					}
					if (loai == 'b') {
						Connector.Send((char*)&hcmhn[1].sl, sizeof(int), 0);
					}
					if (loai == 'c') {
						Connector.Send((char*)&hcmhn[2].sl, sizeof(int), 0);
					}
					
				}


				
			}
			else if(hanhtrinh==2){
				char thongtin2[255] = "\t\tThong tin chuyen Ho Chi Minh-Hue:\nLoai ve: a\tSo luong hien co: 35\t Gia: 60USD/ve\nLoai ve: b\tSo luong hien co: 54\t Gia: 50USD/ve\nLoai ve: c\tSo luong hien co: 48\t Gia: 40USD/ve\n\nVui long chon chi tiet ve";
				int kichthuoc;
				kichthuoc = strlen(thongtin2);
				// Gui di do dai thong diep de server biet duoc do dai nay
				Connector.Send(&kichthuoc, sizeof(kichthuoc), 0);

				// Gui di thong diep voi do dai la MsgSize
				Connector.Send(thongtin2, kichthuoc, 0);

				char loai, soluong;
				Connector.Receive(&loai, sizeof(char), 0);
				printf("\nDa nhan loai ve %c tu client.", loai);
				Connector.Receive(&soluong, sizeof(int), 0);
				printf("\nDa nhan so luong ve %d tu client.", soluong);
				int gia = 0;
				int maloi;
				//Loc du lieu
				if (loai == 'a' && soluong <= hcmhue[0].sl || loai == 'b' && soluong <= hcmhue[1].sl || loai == 'c' && soluong <= hcmhue[2].sl)
				{
					int maloi = 0;
					Connector.Send((char*)&maloi, sizeof(int), 0);
					if (loai == 'a' && soluong <= hcmhue[0].sl) {
						hcmhue[0].sl -= soluong;
						cout << "\nCon " << hcmhue[0].sl << " ve";
						gia = hcmhue[0].gia * soluong;
						//in gia tren server
						cout << "\nGia tien: " << gia;
						Connector.Send((char*)&gia, sizeof(int), 0);

					}
					else if (loai == 'b' && soluong <= hcmhue[1].sl) {
						hcmhue[1].sl -= soluong;
						cout << "\nCon " << hcmhue[1].sl << " ve";
						gia = hcmhue[1].gia * soluong;

						cout << "\nGia tien: " << gia;



					}
					else if (loai == 'c' && soluong <= hcmhue[2].sl) {
						hcmhue[2].sl -= soluong;
						cout << "\nCon " << hcmhue[2].sl << " ve";
						gia = hcmhue[2].gia * soluong;

						cout << "\nGia tien: " << gia;

					}
				}
				else {
					maloi = 1;
					Connector.Send((char*)&maloi, sizeof(int), 0);
					cout << "\nSo luong ve vuot qua so luong hien co";
					//gui so luong
					if (loai == 'a') {
						Connector.Send((char*)&hcmhue[0].sl, sizeof(int), 0);
					}
					if (loai == 'b') {
						Connector.Send((char*)&hcmhue[1].sl, sizeof(int), 0);
					}
					if (loai == 'c') {
						Connector.Send((char*)&hcmhue[2].sl, sizeof(int), 0);
					}
					
					
				}

				

			}
			else if(hanhtrinh==3){
				char thongtin3[255] = "\t\tThong tin chuyen Ha Noi-Da Lat:\nLoai ve: a\tSo luong hien co: 70\t Gia: 120USD/ve\nLoai ve: b\tSo luong hien co: 50\t Gia: 90USD/ve\nLoai ve: c\tSo luong hien co: 30\t Gia: 70USD/ve\n Vui long chon chi tiet ve";
				int kichthuoc;
				kichthuoc = strlen(thongtin3);
				// Gui di do dai thong diep de server biet duoc do dai nay
				Connector.Send(&kichthuoc, sizeof(kichthuoc), 0);

				// Gui di thong diep voi do dai la MsgSize
				Connector.Send(thongtin3, kichthuoc, 0);

				char loai, soluong;
				Connector.Receive(&loai, sizeof(char), 0);
				printf("\nDa nhan loai ve %c tu client.", loai);
				Connector.Receive(&soluong, sizeof(int), 0);
				printf("\nDa nhan so luong ve %d tu client.", soluong);
				int gia = 0;
				int maloi;
				//Loc du lieu
				if (loai == 'a' && soluong <= hndl[0].sl || loai == 'b' && soluong <= hndl[1].sl || loai == 'c' && soluong <= hndl[2].sl)
				{
					int maloi = 0;
					Connector.Send((char*)&maloi, sizeof(int), 0);
					//Loc du lieu
					if (loai == 'a' && soluong <= hndl[0].sl) {
						hndl[0].sl -= soluong;
						cout << "\nCon " << hndl[0].sl << " ve";
						gia = hndl[0].gia * soluong;
						//in gia tren server
						cout << "\nGia tien: " << gia;


						Connector.Send((char*)&gia, sizeof(int), 0);

					}
					else if (loai == 'b' && soluong <= hndl[1].sl) {
						hndl[1].sl -= soluong;
						cout << "\nCon " << hndl[1].sl << " ve";
						gia = hndl[1].gia * soluong;

						cout << "\nGia tien: " << gia;



					}
					else if (loai == 'c' && soluong <= hndl[2].sl) {
						hndl[2].sl -= soluong;
						cout << "\nCon " << hndl[2].sl << " ve";
						gia = hndl[2].gia * soluong;

						cout << "\nGia tien: " << gia;

					}
				}
				else {
					maloi = 1;
					Connector.Send((char*)&maloi, sizeof(int), 0);
					cout << "\nSo luong ve vuot qua so luong hien co";
					//gui so luong
					if (loai == 'a') {
						Connector.Send((char*)&hndl[0].sl, sizeof(int), 0);
					}
					if (loai == 'b') {
						Connector.Send((char*)&hndl[1].sl, sizeof(int), 0);
					}
					if (loai == 'c') {
						Connector.Send((char*)&hndl[2].sl, sizeof(int), 0);
					}
				}

				

			}
			
			

				
				
			
			
		}
		Connector.Close();
		}
		ServerSocket.Close();
	}

	return nRetCode;
}
