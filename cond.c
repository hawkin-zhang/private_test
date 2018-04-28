#include <pthread.h>
#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct tg_work{
    pthread_mutex_t masterlock;
    pthread_mutex_t slavelock;
    pthread_cond_t slave;
    pthread_cond_t master;
}work;

work mywork;
int finished = 0;

/* Initialize a buffer */  
void init(work *prod)  
{  
    pthread_mutex_init(&prod->masterlock,NULL);     // 初始化互斥锁 
    pthread_mutex_init(&prod->slavelock,NULL);     // 初始化互斥锁 
    pthread_cond_init(&prod->slave,NULL);  // 初始化条件变量 
    pthread_cond_init(&prod->master,NULL);  // 初始化条件变量  
} 

static void *thread_main(work *args)
{
    int count=0;

    while(1)
    {
        
        if(count %20 == 0)
        {
            finished = 0;
          printf("thread_main: [%d] \n",count);
          pthread_mutex_lock(&mywork.slavelock);        // 锁定互斥锁
          printf("master:notice slave \n");
          pthread_cond_signal(&mywork.slave);   // 发送有数据信号
          pthread_mutex_unlock(&mywork.slavelock);      // 解锁

          while(finished==0);

          //count=0;
        }

        count++;
        count = count&0xffff;
    }
    return 0;
}

static void *thread_slave(work *args)
{
    int count;
    while(1)
    {
        pthread_mutex_lock(&mywork.slavelock);
        printf("slave:wait master notice \n");
        pthread_cond_wait(&mywork.slave, &mywork.slavelock);
        printf("slave:get master notice \n");
        for(count=0; count< 5;count++)
        {
            printf("slave thread work %d \n",count);
        }
        pthread_mutex_unlock(&mywork.slavelock);
        finished = 1;
        
          
    }

    
    return 0;
}

int main(void)
{
    pthread_t tid_m,tid_s;
    
    init(&mywork);
    
    //子线程会一直等待资源，类似生产者和消费者，但是这里的消费者可以是多个消费者，而
    //不仅仅支持普通的单个消费者，这个模型虽然简单，但是很强大
    pthread_create(&tid_m, NULL, thread_main, NULL);
    pthread_create(&tid_s, NULL, thread_slave, NULL);
    
    pthread_join(tid_m, NULL);
    pthread_join(tid_s, NULL);
    printf("All done -- exiting\n");
    return 0;
}
