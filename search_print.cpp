#include "ls.h"
#include "global_def.h"

void search_print()
{
	mode_bit=0;
	cout<<clear;	
	int x=searchs.size();
	cout<<"Search Results:: \n";
	cout<<"\n";
	int i=0;
	while(i<x)
	{
		cout<<searchs[i]<<"\n";
		++i;
	}
	status_user_mode();
	char buf[PATH_MAX + 1];
    struct stat mystat;
    // directory = opendir(s);	
	unsigned int cpos=2;
	char kstroke,uinput1,uinput2;
	struct termios initial_settings, new_settings;
	printf(ctop);
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	tcsetattr(0,TCSANOW,&new_settings);
	fflush(stdout);

	while(1)
	{
		kstroke=getchar();
		if((int)kstroke == ESC)
		{
			uinput1 = getchar();
			uinput2 = getchar();
			if(uinput1 == BRAC && uinput2 == A && cpos>2)
			{

				cpos--;
				cout<<KEY_UP;
			}
			else if ( uinput1 == BRAC && uinput2 == B && cpos<=x)
			{
				cpos++;
				cout<<KEY_DOWN;
			}
			
		}
		else if(kstroke == q || kstroke == Q)
		{
			 tcsetattr(0,TCSANOW,&initial_settings);
			 cout<<clear;
			// tcsetattr(0,&initial_settings);
			 initial_settings.c_lflag &= ICANON;
			 initial_settings.c_lflag &= ECHO;
			 initial_settings.c_lflag &= ISIG;
			break;
		}
		
		else if(kstroke == ENTER && cpos!=0)
		{

			stat(searchs[cpos-2].c_str(),&mystat);
			if(S_ISDIR(mystat.st_mode))
			{
				char *temp = realpath(searchs[cpos-2].c_str(),buf);
				searchs.erase(searchs.begin(),searchs.end());
				ls(buf);
				tcsetattr(0,TCSANOW,&initial_settings);
				cout<<clear;
				// tcsetattr(0,&initial_settings);
				initial_settings.c_lflag &= ICANON;
				initial_settings.c_lflag &= ECHO;
				initial_settings.c_lflag &= ISIG;
		 		break;
						
			}
		}
	}
}