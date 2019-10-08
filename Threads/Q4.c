#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define INTERVAL 200 
void *RUN(void *par);
int circle_points = 0, square_points = 0; 
double pi;
int main(int argc, char *argv[])
{
	pthread_t tid[INTERVAL * INTERVAL];
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	srand(time(NULL)); 
	for (int i = 0; i < INTERVAL*INTERVAL; ++i)
	{
		pthread_create(&tid[i],&attr,RUN,NULL);
	}
	for (int i = 0; i < INTERVAL*INTERVAL; ++i)
	{
		pthread_join(tid[i],NULL);
	}
  
  	pi = (double)(4 * circle_points) / square_points; 
  	printf("%f\n",pi );
	return 0;
}

void *RUN(void *par)
{	 
    double rand_x, rand_y, origin_dist; 
  
    rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
    rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL; 
 
    origin_dist = rand_x * rand_x + rand_y * rand_y;

    if (origin_dist <= 1) 
        circle_points++; 

    square_points++; 

    pthread_exit(0);
}