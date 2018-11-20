
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include<string.h>
#include <iostream>

int main( void )
{
	int panduan_data = 0;

	while(1)
	{
	struct _stat buf;
	int result;
	char timebuf[26];   //1013752
	char huancun[26];  //缓存数据
	char* filename = "C:Users\\zhulifu\\Desktop\\Paded.csv";
	errno_t err;
	result = _stat( filename, &buf );

	if( result != 0 )
	{
		perror( "Problem getting information" );
		switch (errno)
		{
		case ENOENT:
			printf("File %s not found.\n", filename);
			break;
		case EINVAL:
			printf("Invalid parameter to _stat.\n");
			break;
		default:
			printf("Unexpected error in _stat.\n");
		}
	}
	else
	{ 
		panduan_data = panduan_data +1;
		//	printf( "Drive         : %c:\n", buf.st_dev + 'A' );//printf( "File size     : %ld\n", buf.st_size );
		err = ctime_s(timebuf, 26, &buf.st_mtime);    ////st_mtime 44:03  	// Output some of the statistics: 
		printf( "Time modified : %s", timebuf);
	
		if (panduan_data ==1)
		{
			 memcpy(huancun,timebuf,strlen(huancun));
			 printf("huancun:%s\n",huancun);
		}
	}
			 if (strcmp(huancun,timebuf)==0)
			 {
				 printf("is good!\n");
			 }
			 else
			 {
				 printf("fa song wen jian !");
				 panduan_data =0;
			 }
	_sleep(2000);
	}
}
