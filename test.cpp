#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;
class signal
{
	private:
	int length;
	float maximum_value,average_value;
	float *signal_data;
	int average()
	{
		average_value=signal_data[0];
		for(int i=1;i<length;i++)
		{
			average_value=average_value+signal_data[i];
		}
		average_value=average_value/(float)length;
	}
	int maximum()
	{
		maximum_value=signal_data[0];
		for(int i=1;i<length;i++)
		{
			if(maximum_value<signal_data[i])
				maximum_value=signal_data[i];
		}
	}
	public:
	int sig_info()
	{
		//display sig_info
		maximum();
		average();
		cout<<endl<<endl<<"length\t\t:\t"<<length<<endl<<"maximum value\t:\t"<<maximum_value<<endl<<"average value\t:\t"<<average_value;
	}
	int save_file()
	{
		//save code
		char save_file_name[20];
		cout<<"enter file name to save without extension";
		cin>>save_file_name;
		strcat(save_file_name,".txt");
		maximum();
		fstream file;
		file.open(save_file_name,ios::out);
		file<<length<<" "<<maximum_value;
		for(int i=0;i<length;i++)
		{
			file<<endl<<signal_data[i];
		}
		file.close();
	}
	signal()
	{
		char default_file_name[20]="default.txt";
		file_read(default_file_name);
	}
	signal(int number)
	{
		char file_name[20]="Raw_data_";
		if(number&&number<10)
		{
			strcat(file_name,"0");
		}
		char file_number[5];
		sprintf(file_number,"%d",number);
		strcat(file_name,file_number);
		strcat(file_name,".txt");
		file_read(file_name);
	}
	signal(char* file_name)
	{
		file_read(file_name);
	}
	int file_read(char* file_name)
	{
		int unnecessary;
		fstream file;
		file.open(file_name,ios::in);
		file>>length>>unnecessary;
		signal_data=new float[length];
		for(int i=0;i<length;i++)
		{
			file>>signal_data[i];
			//cout<<signal_data[i]<<endl;
		}
		return 0;
	}
	~signal()
	{
		//destructor
	}
	int offset(float offset_value)
	{
		//offset code
		for(int i=0;i<length;i++)
		{
			signal_data[i]=signal_data[i]+offset_value;
			cout<<signal_data[i]<<endl;
		}		
	}
	int scale(float scale_factor)
	{
		//scale code
		for(int i=0;i<length;i++)
		{
			signal_data[i]=signal_data[i]*scale_factor;
			cout<<signal_data[i]<<endl;
		}
	}
	int center()
	{
		//center code
		average();
		for(int i=0;i<length;i++)
		{
			signal_data[i]=signal_data[i]-average_value;
			cout<<signal_data[i]<<endl;
		}
	}
	int normalize()
	{
		//normal code
		maximum();
		for(int i=0;i<length;i++)
		{
			signal_data[i]=signal_data[i]/(float)maximum_value;
			cout<<signal_data[i]<<endl;
		}
	}
	int statistics()
	{
		//statistics code
		maximum();
		average();
	}
	int menu()
	{
		menu:
		cout<<endl<<endl<<"----------MENU----------"<<endl<<"1.Offset"<<endl<<"2.Scale"<<endl<<"3.Center"<<endl<<"4.Normalize"<<endl<<"5.Statistics"<<endl<<"6.Signal Information"<<endl<<"7.Save file"<<endl<<"8.Exit"<<endl<<endl<<"Enter your option  ";
		int choice=0;
		cin>>choice;
		switch(choice)
		{
			case 1 :
			float offset_value;
			cout<<"enter offset value ";
			cin>>offset_value;
			offset(offset_value);
			break;
			case 2 :
			float scale_factor;
			cout<<"enter scale factor ";
			cin>>scale_factor;
			scale(scale_factor);
			break;
			case 3 :
			center();
			break;
			case 4:
			normalize();
			break;
			case 5:
			statistics();
			break;
			case 6:
			sig_info();
			break;
			case 7:
			save_file();
			break;
			case 8:
			//code exit
			goto end;
			default:
			cout<<"entered wrong choice try again";
			goto menu;
		}
		goto menu;
		end:	
		return 0;
	}
};
int main(int argc,char* argv[])
{
	if(argc==1)
	{
		signal obj;
		obj.statistics();
		obj.menu();
	}
	else
	{
		if(argv[1][1]=='n')
		{
			signal obj(atoi(argv[2]));
			obj.statistics();
			obj.menu();
		}
		else if(argv[1][1]=='f')
		{
			signal obj(argv[2]);
			obj.statistics();
			obj.menu();
		}
		else
		{
			//input invalid 
			cout<<"entered command line argument is wrong. please try again.";
		}
	}
	return 0;
}