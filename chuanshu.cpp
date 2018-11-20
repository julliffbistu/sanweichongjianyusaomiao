
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>

int main( void )
{
	int panduan_data = 0;
	while(1)
	{
		panduan_data = panduan_data +1;
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
		// Output some of the statistics: 
		//printf( "File size     : %ld\n", buf.st_size );
	//	printf( "Drive         : %c:\n", buf.st_dev + 'A' );
		err = ctime_s(timebuf, 26, &buf.st_mtime);
		printf( "Time modified : %s", timebuf );
		if (panduan_data ==1)
		{
			huancun = timebuf;
		}

	}
	_sleep(2000);
	}
}
