#include "jsonParser.h"
#include<stdio.h>
#include<string.h>

using namespace std;

int JsonParser :: parse_config_file(struct pair *p,char *str)
{
	FILE *fp;
	fp=fopen(str,"r");
	if(fp==NULL)
	{
		printf("\n file can not be opened");
		return 0;
	}
	char ch;
	int i,j=0,flag=-1,flag1=0;
	while((ch=fgetc(fp))!=EOF)
	{
		//		printf("%c",ch);
		if(ch==' ' || ch=='\n')
			continue;
		//can add comments handling logic here in extended version
		else if(flag && ch=='{')
		{
			flag=0;
		}
		else if(!flag)
		{
			if(ch==',')
				continue;
			else if(ch=='}')
			{
				flag=1;
				break;
			}
			else if(ch==':')
			{
			//	printf("\n here");
				flag1=1;
			}
			else
			{

				if(!flag1)
				{
					if(ch=='"')
					{
						i=0;
						while((ch=fgetc(fp))!='"')
						{
							p[j].key[i]=ch;
					//		printf("k=%c",p[j].key[i]);
							i++;
						}
					//	ch=fgetc(fp);
					//	printf("ch=%c",ch);
					}
				}
				else if(flag1)
				{
					if(ch=='"')
					{
						i=0;
						while((ch=fgetc(fp))!='"')
						{
							p[j].value[i]=ch;
			//				printf("v=%c",p[j].value[i]);						
							i++;
						}
					//	ch=fgetc(fp);
					//	printf("ch=%c",ch);			
						flag1=0;
						j++;
					}
				}
			}
		}
	}
	
	return j;
}
