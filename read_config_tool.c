//this code is a simple practice for using link-list to save smbus path.
//first it will read a config file which follow special format, and build the link-list data to store the smbus path information.
//config file should be named as "config.cfg" and follow this format:
//slot1:[0x35-ch1][0xAF-ch2][0x2A-ch3]
//slot2:[0x35-ch2][0xAF-ch2]
//slot3:[0x35-ch1][0xAE-ch2]
//slot4:[0x36-ch1][0xAF-ch4]
//slot5:[0x35-ch3][0xAF-ch2]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LENGTH	1000

struct SMBUS_PATH{
	int switch_addr;
	int switch_ch;
	struct SMBUS_PATH *next;	
};
char *config_file;
char *config_file_temp;
char config_buff[MAX_STR_LENGTH];
char slot_path_info[MAX_STR_LENGTH];
//string parsing 
int str_parsing(char *config_str_buff,char *select_str)
{
	char *str_temp,*str_temp2;
	str_temp2 = &slot_path_info[0];
	str_temp = strstr(config_str_buff,select_str);
	printf("-->%s",str_temp);
	printf("---------------------------\n");
	while('\n' != (*str_temp))
	{	
		*str_temp2=*str_temp;
		printf("%c",*str_temp);
		str_temp++;
		str_temp2++;
	} 
return 0;

}
int main()
{
FILE *fd;
char ch_buff;
char *slot_sel="slot3";
	fd=fopen("config.cfg","r");
	if(fd==NULL)
	{printf("open fail\n");}
	else
	{printf("open success\n");}

config_file = &config_buff[0];
config_file_temp= config_file;
	while((ch_buff=fgetc(fd))!=EOF)
	{
		
		*config_file_temp = ch_buff;
		config_file_temp++;
		printf("%c",ch_buff);
	}
str_parsing(config_file,slot_sel);
printf("===============================\n");
printf("%s",slot_path_info);
fclose(fd);
return 0;
}
