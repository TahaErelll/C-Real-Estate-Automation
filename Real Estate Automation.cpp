// -Taha Erel- This my Computer engineering 1st year project assignment.
//The texts to be projected on the screen were later translated from Turkish to English so the variables are in Turkish.
#include <iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
using namespace std;

class para
{
 public:
	char ucret[10];
};

class musteri
{ 
 public:
	char tel[11];
	char isim[20];
};        

class bina:public musteri, para
{  
    char binaid[6];
    char adres[50];

public:
    void VeriYaz()
    {

         cout<<"\nNew Data Entry...\n";
          cin.getline(binaid,6);
        cout<<"\nEnter the building id ";
          cin.getline(binaid,6);
        cout<<"\nEnter adress ";
          cin.getline(adres,50);
        cout<<"\nEnter Customer Name ";
          cin.getline(isim,20);
        cout<<"\nEnter Customer Telephone ";
          cin.getline(tel,11);
        cout<<"\nEnter Building Fee ";
          cin.getline(ucret,10);
   
        cout<<"\n\nData record has been created."<<endl;
    }

    void VeriListele()
    {
        cout<<"\nBuilding id : "<<binaid;
        cout<<"\nBuilding adress : ";
         puts(adres);
        cout<<"\nCustomer Name : ";
         puts(isim);
        cout<<"\nCustomer Telephone : "<<tel;
        cout<<"\nBuilding Fee : "<<ucret<<endl;
    }

    void VeriGuncelle()
    {
        cout<<"\nBuilding id : ";cin>>binaid;
        cout<<"\nBuilding adress : ";fflush(stdin);
         gets(adres);fflush(stdin);
        cout<<"\nCustomer Name : "; cin.getline(isim,20);
        cout<<"\nCustomer Telephone : ";cin>>tel;
        cout<<"\nBuilding Fee : ";cin>>ucret;
    }

    char* iddondur()
    {
        return binaid;
    }

   

    void rapor()
    {cout<<"\t"<<"ID: "<<binaid<<" "<<"ADRESS: "<<adres<<" "<<"CUSTOMER NAME: "<<isim<<" "<<"CUSTOMER TELEPHONE: "<<tel<<" "<<"FEE :"<<ucret<<endl;}

};        




fstream fp;
bina st;

void Dosyayayaz()
{
    fp.open("Kayitlar.txt",ios::out|ios::app);

        st.VeriYaz();
        fp.write((char*)&st,sizeof(bina));
    
    fp.close();
}




void VeriAra(char n[])
{
    cout<<"\nData Details\n";
    int kontrol=0;
    fp.open("Kayitlar.txt",ios::in);
    while(fp.read((char*)&st,sizeof(bina)))
    {
        if((strcmpi(st.iddondur(),n)==0))
        {
            st.VeriListele();
            kontrol=1;
        }
    }

    fp.close();
    if(kontrol==0)
            cout<<"\n\nThere is no such record";
   
}




void VeriGuncelle()
{
    char n[6];
    int kontrol=0;

    cout<<"\n\n\tData Update... ";
    cout<<"\n\n\tEnter the id of the building you want to update";
    cin>>n;
    fp.open("Kayitlar.txt",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(bina)) && kontrol==0)
    {
        if(strcmpi(st.iddondur(),n)==0)
        {
            st.VeriListele();
            cout<<"\nEnter new informations"<<endl;
            st.VeriGuncelle();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(bina));
            cout<<"\n\n\t Registration Updated";
            kontrol=1;
        }
    }

    fp.close();
    if(kontrol==0)
        cout<<"\n\n No Records Found. ";
}


void VeriSil()
{
    char n[6];
    int kontrol=0;

        cout<<"\n\n\nDelete Data...";
        cout<<"\n\nEnter the building id you want to delete : ";
        cin>>n;
        fp.open("Kayitlar.txt",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.txt",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(bina)))
    {
        if(strcmpi(st.iddondur(),n)!=0)
                 fp2.write((char*)&st,sizeof(bina));
        else
               kontrol=1;
    }

    fp2.close();
        fp.close();
        remove("Kayitlar.txt");
        rename("Temp.txt","Kayitlar.txt");
        if(kontrol==1)
             cout<<"\n\n\tRecords deleted...";
        else
             cout<<"\n\nNo Records Found."<<endl;
     
}




void Goster()
{

         fp.open("Kayitlar.txt",ios::in);
         if(!fp)
         {
               cout<<"The file could not be opened !";
               getch();
               return;
         }

    cout<<"\n\n\t\tData List\n\n";
    int sira=1; 
    while(fp.read((char*)&st,sizeof(bina)))
    { 
       cout<<sira;
        st.rapor();
       sira++;
    
    }

    fp.close();
  
}


int main()
{
	char devam;
	do{
	
int secim;
    cout<<"\n\n\n\tTaha Erel - Duzce University - Real Estate Agent Automation";
    cout<<"\n\n\t1.Add Data";
    cout<<"\n\n\t2.View All Data";
    cout<<"\n\n\t3.Search Data";
    cout<<"\n\n\t4.Data Update";
    cout<<"\n\n\t5.Delete Data";
    cout<<"\n\n\t6.Exit";
    cout<<"\n\n\tSelect the action you want to do ";
    cin>>secim;
    switch(secim)
    {
            case 1:
                Dosyayayaz();break;
            case 2: Goster();break;
            case 3:
                   char num[6];

                   cout<<"\n\n\tAramak istediginiz binanin id sini giriniz ";
                   cin>>num;
                   VeriAra(num);
                   break;
              case 4: VeriGuncelle();break;
              case 5: VeriSil();break;
              case 6: return 0 ;
              default:cout<<"You made the wrong choice."<<endl;
       }
       cout <<"Do you want to continue? Y / N"<<endl;
		cin>>devam;
	}while(devam=='Y'|| devam=='y');
	
	system("pause");
	return 0;
       
}


