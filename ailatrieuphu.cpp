#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;
static int Quyentrogiup=3;
static int Quyentrogiupdachon[4]={
	0,0,0,0
};//khai bao mang 4 phan tu de dung pha tu 1,2,3 cho phu hop voi quyen tro giup 1,2,3
static int isdungcuocchoi=0;
static int dapngaunhiendungtrogiupthu3 =0;
struct Cauhoi{
	char Noidung[1000];
	int Dapan;	
};
void Indongchuvoitoadovamau(int x,int y, int mamau)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,mamau);
	COORD tinh = {x,y} ;
	SetConsoleCursorPosition(mau,tinh ) ;
}
int isdadungQuyentrogiup(int k)
{
	for(int i=1;i<4;i++)
	{
		if(Quyentrogiupdachon[k]==1)//kiem tra neu quyen tro giup do da dung
		return 1;
	}
	return 0;	
}
void Docfile(Cauhoi DScauhoi[], int &n)
{
	FILE *f=fopen("data.txt","r");
	FILE *ff=fopen("dataso.txt","r");
	fscanf(ff,"%d",&n);
	for(int i=0;i<n;i++)
    	fread(&DScauhoi[i],sizeof(Cauhoi),1,f);
    fclose(f);
    fclose(ff);
}

void Ghivaofile()
{
	int n;
	FILE *f=fopen("data.txt","a");
	FILE *ff=fopen("dataso.txt","r+");
	fscanf(ff,"%d",&n);
	printf("\nSo cau hoi file la: %d",n);
	fclose(ff);

	Cauhoi *add = new Cauhoi;
	while(true)
	{
		printf("\nNhap vao noi dung cau hoi: ");
		fflush(stdin);
		scanf("%[^#]",&add->Noidung);//ket thuc khi nhap #
		if(add->Noidung[0]=='*')//neu nhap ki tu * thi se  cham dut qua  trinh them cau hoi
			break;
		fflush(stdin);
		printf("\nNhap vao dap an: ");
		scanf("%d",&add->Dapan);
		fwrite(add,sizeof(Cauhoi),1,f);
		n++;
		
 	

	}
	ff=fopen("dataso.txt","w");
	fprintf(ff,"%d",n);	
	fclose(ff);
    fclose(f);
   
}
void Trogiup(Cauhoi qs)
{
	Quyentrogiup--;
	int k;
	printf("\nNhap vao quyen can tro giup");
	printf("\n1.Su tro  giup goi dien thoai cho nguoi than");
	printf("\n2.Su tro giup khan gia");
	printf("\n3.Su tro  giup 50/50\n");
	do{
		scanf("%d",&k);
		if(isdadungQuyentrogiup(k))
			printf("Ban da dung quyen tro giup do vui long chon quyen tro giup khac:\n");
		else
			break;
	}
	while(1);
	
	switch(k)
	{
		case 1:
			{
				Quyentrogiupdachon[1]=1;//moi quyen tro giup dung roi se dc gan la 1 trong mang
				if(Quyentrogiupdachon[3]==0)
				{
					int da=qs.Dapan,x;
					int ngaunhien;
					srand( time(NULL) );
					do
					{
						ngaunhien= 1 + rand()%4;
					}
					while(ngaunhien==da);
					x=rand()%4;
					dapngaunhiendungtrogiupthu3=ngaunhien;
					if(x!=0)//kha nang dung cua su  tro giup la 75%
					printf("\nNguoi than cua ban chon phuong an %d",da);
					else
					printf("\nNguoi than ban chon phuong an %d",ngaunhien);
				}
				else
				{
					int da=qs.Dapan,x;
					x=rand()%4;
					if(x!=0)//kha nang dung la 75%
					printf("\nNguoi than cua ban chon phuong an %d",da);
					else
					printf("\nNguoi than ban chon phuong an %d",dapngaunhiendungtrogiupthu3);
				}
				
				break;
			}
		case 2:
			{
				Quyentrogiupdachon[2]=1;
				if(Quyentrogiupdachon[3]==0)
				{		
				
					int a[5],sum=0;
					int da=qs.Dapan;
					srand( time(NULL) );
					for(int i=1;i<5;i++)
					{
						if(i!=da)
						{
							a[i]=rand()%25;
							sum+=a[i];
						}
					}
					a[da]=100-sum;
					for(int i=1;i<5;i++)
					{
						printf("\nDan an %d duoc khan gia binh chon %d%% ",i,a[i]);
					}
				}
				else
				{
					srand( time(NULL) );
					int ngaunhien= rand()%40;
					if(ngaunhien<3)//giam kha nang sai
						{
						printf("\nDan an %d duoc khan gia binh chon %d%% ",dapngaunhiendungtrogiupthu3,100-ngaunhien);
						printf("\nDan an %d duoc khan gia binh chon %d%% ",qs.Dapan,ngaunhien);
						}
					else
						{
						printf("\nDan an %d duoc khan gia binh chon %d%% ",qs.Dapan,100-ngaunhien);
						printf("\nDan an %d duoc khan gia binh chon %d%% ",dapngaunhiendungtrogiupthu3,ngaunhien);
						}	
				}
				break;
			}
		case 3:
			{
				Quyentrogiupdachon[3]=1;
				int da=qs.Dapan;
				int ngaunhien,x;
				srand( time(NULL) );
				do
				{
					ngaunhien= 1 + rand()%4;
				}
				while(ngaunhien==da);
				dapngaunhiendungtrogiupthu3=ngaunhien;
				printf("\nHai dap an con lai co kha nang dung la %d va %d",da,ngaunhien);
			
				break;
			}
		 default:
			 return;
	}
}
int Chay1cauhoi(Cauhoi x)
{
	int k,su;char kitu[3];
	printf("\n%s\n",x.Noidung);
	if(Quyentrogiup>0)
	{
		printf("\nBan co muon su dung quyen tro giup hay khong: \nNhap Yes neu co khong thi nhap ki tu bat ki \n");
		fflush(stdin);
		gets(kitu);
		if(stricmp(kitu,"yes")==0)
		{
			TROGIUP :
			Trogiup(x);
			if(Quyentrogiup>0)
			{
			printf("\nNeu khong chac chan ban co the su dung tiep \nThem 1 quyen tro giup bang cach nhap phim 1,neu khong thi nhap 0\n");
			scanf("%d",&su);
			if(su==1)
			goto TROGIUP;
			}
		}	
	
		
	}
	
	do{
	printf("\nDap an lua chon tuong ung la 1 2 3 4\nNeu muon dung cuoc choi chon phim 5\nDap an cua ban la:");
	fflush(stdin);
	scanf("%d",&k);
	if(k>5 || k<1)
		printf("Lua chon cua ban khong phu hop");
	}
	while(k>5 || k<1);
	
	if(k==x.Dapan)
		{
		system("cls");
		printf("\nChuc mung dap an %d la dap an dung",x.Dapan);
	 	Sleep( 1000 ); //dung man hinh 1s
	 	system("cls");
		return 1;
		}
	else if(k!=5)
		{
		system("cls");
		Indongchuvoitoadovamau(45,3,240);
		printf("That dang tiec ban da tra loi sai dap an dung la %d",x.Dapan);
		Sleep( 2000 ); //dung man hinh 2s
		system("cls");
		return 0;	
		}
	else if(k==5)
	{
		isdungcuocchoi =1;// cho  bien staic dung cuoc choi = 1
		return 5;
	}	
}
int isTrung(int mang[],int count, int k)
{
	for(int i=0;i<count;i++)
	{
		if(k==mang[i])
			return 1;
	}
	return 0;
}
void Layngaunhien15cauhoi(Cauhoi danhsach[], int n,Cauhoi dschay[])
{
	int k;
	int mang[15];
	srand( time(NULL) );
	for(int i=0;i<15;i++)
	{
		do{
			k=rand()%n;		
		}
		while(isTrung(mang,i,k)==1);
		mang[i]=k;
		dschay[i]=danhsach[k];
	}
	
}
int Chaytatcacauhoi(Cauhoi dschay[])
{
	int i;
	for(i=0;i<15;i++)
	{
		system("cls");
		printf("\nCau hoi so %d:",i+1);
		int x=Chay1cauhoi(dschay[i]);
		if(x==0 || x==5)
		{
		return i;
		}
	}
	return i;
}
double Tienthuong(int i, int isdungcuocchoi)
{
	int socau=i+1;
	if(isdungcuocchoi==0)//kiem tra khong dung cuoc choi
	{
		if(socau>=15)
			return 150;	
		else if(socau >=10)
			return 22;
		else if(socau >=5)
			return 2;
		else 
			return 0;
	}
	else // dung cuoc choi
	{
		switch(socau-1)
		{
			case 0:
				return 0;
			break;
			case 1:
			return 0.2;
				break;
			case 2:
			return 0.4;
				break;
			case 3:
			return 0.6;
				break;
			case 4:
			return 1;
				break;
			case 5:
			return 2;
				break;
			case 6:
			return 3;
				break;
			case 7:
			return 6;
				break;
			case 8:
			return 10;
				break;
			case 9:
			return 14;
				break;
			case 10:
			return 22;
				break;
			case 11:
			return 30;
				break;
			case 12:
			return 40;
				break;
			case 13:
			return 60;
				break;
			case 14:
			return 85;
				break;
			case 15:
			return 150;
				break;
		}
	}	
}
void timkiemcauhoi(Cauhoi danhsach[], int n)
{
	int dem=0;
	char chuoi[1000];
	printf("\nNhap vao noi dung cau hoi can tim: ");
	fflush(stdin);
	gets(chuoi);
	for(int i=0;i<n;i++)
	{
		if(strstr(danhsach[i].Noidung,chuoi)!=NULL)
			{
				printf("\n%s\n",danhsach[i].Noidung);
				printf("Dap an :%d\n--------------\n",danhsach[i].Dapan);
				dem++;
			}
	}
	if(dem==0)
		printf("\nKhong tim thay cau hoi nao co noi dung phu hop");
	printf("\nGo phim bat ki de quay ve Menu cai dat ");
	getchar();
	return;
	
}
void themcauhoi()
{
	printf("\nThem cau hoi vao chuong trinh: \n");
	printf("\nDe ket thuc qua trinh nhap cau hoi tai phan noi dung nhap ki tu *# roi Enter\n");
	printf("\nDe ket thuc sau khi nhap noi dung nhap ki tu # o cuoi chuoi roi Enter\n");
	printf("\nDe ket thuc phan dap an  nhap dan an roi Enter\n");
	Ghivaofile();	
	return;
}
void Capnhatcauhoi(Cauhoi danhsach[], int n)
{
	
	int dem=0,vitri=-1,vt=-1;
	char chuoi[1000];
	TIM :
	int k=0;
	printf("\nNhap vao 1 neu muon tim bang noi dung cau hoi nhap vao 0 neu muon tim bang vi tri trong danh sach  : \n");
	scanf("%d",&k);
	if(k==1)
	{
		printf("\nNhap vao noi dung cau hoi can tim: ");
		fflush(stdin);
		gets(chuoi);
		for(int i=0;i<n;i++)
		{
			if(strstr(danhsach[i].Noidung,chuoi)!=NULL)
				{
					printf("\nCau hoi duoc tim thay o vi tri thu %d trong danh sach",i);
					printf("\n%s\n",danhsach[i].Noidung);
					printf("Dap an :%d\n--------------\n",danhsach[i].Dapan);
					dem++;
					vitri=i;
				}
		}
	}
	if(k==0)
	{
		printf("\nNhap vao vi tri cua cau hoi: ");
		scanf("%d",&vt);
		for(int i=0;i<n;i++)
		{
			if(i==vt)
				{
					printf("\nCau hoi duoc tim thay o vi tri thu %d trong danh sach",i);
					printf("\n%s\n",danhsach[i].Noidung);
					printf("Dap an :%d\n--------------\n",danhsach[i].Dapan);
					dem++;
					vitri=i;
				}
		}
			
	}
	
	if(dem==0)
		{
		string chuoi ="\nKhong tim thay cau hoi nao co noi dung phu hop chuong trinh se quay ve Menu cai dat sau 3 giay nua\n";
		for(int i=0;i<chuoi.length();i++)
		{
			printf("%c",chuoi[i]);
			Sleep(50);
		}
		for(int i=3;i>0;i--)
		{
			printf("%d... ",i);
			Sleep(1000);
		}	
		return;
		}
	if (dem >1)
	{	
		printf("\nCo den %d ",dem);
		string chuoi = "cau hoi duoc tim thay vui long dung chuc nang tim kiem de xac dinh chinh xac cau hoi\nChuong trinh se quay ve menu cai dat sau 10 giay nua\n"; 
		for(int i=0;i<chuoi.length();i++)
		{
			printf("%c",chuoi[i]);
			Sleep(50);
		}
		for(int i=10;i>0;i--)
		{
			printf("%d... ",i);
			Sleep(1000);
		}	
		return;
	}
	if(dem==1)
	{
		printf("\nVi tri cau hoi tim thay trong danh sach la %d",vitri);
		string chuoi ="\nMot cau hoi duoc tim thay \nDe ket thuc sau khi nhap noi dung nhap ki tu # o cuoi chuoi roi Enter\n\nDe ket thuc phan dap an  nhap dan an roi Enter\nNhap vao noi dung moi cua cau hoi: ";
		for(int i=0;i<chuoi.length();i++)
		{
			printf("%c",chuoi[i]);
			Sleep(10);
		}
		fflush(stdin);
		scanf("%[^#]",&danhsach[vitri].Noidung);//ket thuc khi nhap # va enter
		fflush(stdin);
		printf("\nNhap vao dap an moi : ");
		scanf("%d",&danhsach[vitri].Dapan);
		FILE *f=fopen("data.txt","w");
		for(int i=0;i<n;i++)
		{
			fwrite(&danhsach[i],sizeof(Cauhoi),1,f);
		}
		fclose(f);	
	}
	return;
}
void caidat(Cauhoi danhsach[],int n)
{
	CAIDAT :
	system("cls");
	int k=0;
	Indongchuvoitoadovamau(45,3,240);
	printf("------------CAI DAT----------\n");
	Indongchuvoitoadovamau(45,7,240);
	printf("1.Tim kiem cau hoi           \n");
	Indongchuvoitoadovamau(45,9,240);
	printf("2.Cap nhat cau hoi           \n");
	Indongchuvoitoadovamau(45,11,240);
	printf("3.Them cau hoi   \n");
	Indongchuvoitoadovamau(45,13,240);
	printf("4.Tro ve Menu chinh");
	Indongchuvoitoadovamau(45,15,15);
	fflush(stdin);
	scanf("%d",&k);
	switch(k)
	{
		case 1:
			timkiemcauhoi(danhsach,n);
			goto CAIDAT;
			break;
		case 2:
			Capnhatcauhoi(danhsach,n);
			goto CAIDAT;
			break;
		case 3:
			themcauhoi();
			goto CAIDAT;
			break;
		default:
			return;
	}
}
int main()
{
	SetConsoleTitle("BAI TAP LON CTDL-GT");
	Cauhoi ds[100];// danh sach cau hoi lay tu file
	Cauhoi dschay[15];//danh sach cau hoi se chay trong chuong trinh
	BATDAU :
	int n=1;
	Docfile(ds,n);
	Layngaunhien15cauhoi(ds,n,dschay);
	system("cls");
	int k=0;
	Indongchuvoitoadovamau(45,3,240);
	printf("------------MENU----------\n");
	Indongchuvoitoadovamau(45,7,240);
	printf("1.Vao tro choi            \n");
	Indongchuvoitoadovamau(45,9,240);
	printf("2.Cai dat tro choi        \n");
	Indongchuvoitoadovamau(45,11,240);
	printf("3.Tac gia   \n");
	Indongchuvoitoadovamau(45,13,240);
	printf("4.Thoat chuong trinh      \n");
	Indongchuvoitoadovamau(45,15,15);
	scanf("%d",&k);
	switch(k)
	{
		case 1:
		{	
			Quyentrogiup=3;
			Quyentrogiupdachon[1]=0;
			Quyentrogiupdachon[2]=0;
			Quyentrogiupdachon[3]=0;
			isdungcuocchoi=0;
			dapngaunhiendungtrogiupthu3 =0;
			system("cls");
			string chuoi("\n\t\t\t\t\tBan se duoc bat dau voi 15 cau hoi va  3 quyen tro giup \n\t\t\t\t\tO moi cau hoi se deu co quyen dung tro giup cho den\n\t\t\t\t\tKhi het ca 3 quyen tro giup thi se khong tiep tuc hien nua\n\t\t\t\t\tNhap ENTER neu ban da san sang\n\t\t\t\t\t");
			for(int i=0;i<chuoi.length();i++)
			{
				printf("%c",chuoi[i]);
				Sleep(50);
			}
			fflush(stdin);
			scanf("%[^\n]");	
			int socau=Chaytatcacauhoi(dschay);
			double tienthuong=Tienthuong(socau,isdungcuocchoi);
			system("cls");
			Indongchuvoitoadovamau(45,3,15);
			if(tienthuong==150)
				printf("BAN DA CHIEN THANG ");
			Indongchuvoitoadovamau(45,5,15);
			printf("Tien thuong cua ban la: %1.lf dong",tienthuong*1000000);
			
			Sleep(3000);//ngung chuong trinh 3s
			goto BATDAU;
		}
			break;
		case 2:
			caidat(ds,n);
			goto BATDAU;
			break;
		case 3:
		{
			system("Cls");
		
			Indongchuvoitoadovamau(45,9,112);
			string chuoi1="Le Ke Hien          \n";
			for(int i=0;i<chuoi1.length();i++)
			{
				printf("%c",chuoi1[i]);
				Sleep(30);
			}
		
		
			Indongchuvoitoadovamau(45,17,12);
			printf("Nhap ENTER de  quay lai MENU chinh");
			fflush(stdin);
			scanf("%[^\n]");
			goto BATDAU;
			break;
		}
		default:
			return 0;
	}
	return 0;
}