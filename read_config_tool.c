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
#include <ctype.h>
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
int ascii_to_hex(char ch) 
{ 
char ch_tmp; 
int hex_val = -1; 

	ch_tmp = tolower(ch); 

	if ((ch_tmp >= '0') && (ch_tmp <= '9')) { 
		hex_val = ch_tmp - '0'; 
	} 
	else if ((ch_tmp >= 'a') && (ch_tmp <= 'f')) { 
		hex_val = ch_tmp - 'a' + 10; 
	} 

	return hex_val; 
} 
/********/
int str_to_hex(char *hex_str) 
{
int i, len; 
int hex_tmp, hex_val; 
char *bptr;
	bptr = strstr(hex_str, "0x");
	if ( bptr != NULL ) bptr+=2;
	else 	bptr=hex_str;

	len = (int)strlen(bptr); 
	hex_val = 0; 
 	for (i=0; i<len;i++) { 
		hex_tmp = ascii_to_hex(bptr[i]); 
		if (hex_tmp == -1) 
		{ return -1; } 

		hex_val = (hex_val) * 16 + hex_tmp; 
	} 
	return hex_val; 
} 
//==========string parsing=============================== 
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
//=====================================================
//==============select switch channel  ================
//slot5:[0x35-ch3][0xAF-ch2]
int str2link(void)
{
int xi=0;
char addr[5]="0x00\0";
char ch[5]="0x00\0";

	
	while(slot_path_info[xi]!=0)
	{
		//printf("%c",slot_path_info[xi]);
		if(slot_path_info[xi] == '[')
		{
			//addr[0]=slot_path_info[xi+1];
			//addr[1]=slot_path_info[xi+2];
			addr[2]=slot_path_info[xi+3];
			addr[3]=slot_path_info[xi+4];
			printf("addr%s-- 0x%x\t",addr,str_to_hex(addr));
			
		}
		else if(slot_path_info[xi] == '-')
		{

			//ch[0]=slot_path_info[xi+1];
			//ch[1]=slot_path_info[xi+2];
			//ch[2]=slot_path_info[xi+3];
			ch[3]=slot_path_info[xi+3];
			printf("channel%s 0x%x\n",ch,str_to_hex(ch));
//int32_t _lmbsmb_switch_ch(str_to_hex(addr), str_to_hex(ch))

		}
		else if(slot_path_info[xi] == ']')
		{
			
		}
		else
		{}
		xi++;

	}
return 0;
}
/*
//==============string to link list ===================
//slot5:[0x35-ch3][0xAF-ch2]
int str2link(char *data_str)
{
	int xi=0;
	printf("--->\n");
	
	char *addr,*ch;
	char *addr_temp,*ch_temp;
	u_int8_t addr_flag,ch_flag;
	addr_flag=0;ch_flag=0;
	//printf("%ld---%ld\n",sizeof(data_str),sizeof(slot_path_info));
	//for(xi=0;xi<sizeof(data_str);xi++)
	//{
	//	printf("%c",*(data_str+xi));
	//}
	while(slot_path_info[xi]!=NULL)
	{
		printf("%c",slot_path_info[xi]);
		if(slot_path_info[xi] == '[')
		{
			addr_flag=1;
		}
		else if(slot_path_info[xi] == '-')
		{
			addr_flag=0;
			ch_flag=1;
		}
		else if(slot_path_info[xi] == ']')
		{
			ch_flag=0;
		}
		else
		{}

		xi++;

		if(addr_flag==1)
		{
			*addr=slot_path_info[xi];
			addr++;
		}
		if(ch_flag==1)
		{
			*ch=slot_path_info[xi];			
			ch++;
		}

	}
return 0;
}*/
//=====================================================
int main()
{
FILE *fd;
char ch_buff;
char *slot_sel="s";
char slot_sel2[6];
	fd=fopen("config.cfg","r");
	if(fd==NULL)
	{printf("open fail\n");}
	else
	{printf("open success\n");}
sprintf((slot_sel2),"slot%d",1);
printf(">>>%s\n",slot_sel2);
config_file = &config_buff[0];
config_file_temp= config_file;
	while((ch_buff=fgetc(fd))!=EOF)
	{
		
		*config_file_temp = ch_buff;
		config_file_temp++;
		printf("%c",ch_buff);
	}
str_parsing(config_file,slot_sel2);
printf("===============================\n");
printf("%s",slot_path_info);
printf("================================\n");
str2link();
fclose(fd);
return 0;
}
