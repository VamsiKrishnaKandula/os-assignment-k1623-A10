#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
struct pro
{

	char processname[20];
    int  bursttime,arrivaltime,processid,processclass,turna_t,wait_t,comple_t;
};

int global_time;

int main(){
	char buffer [100];
	int x;
	write(1,"Number of processes : ",50);
	scanf("%d",&x);
	struct pro pro[x];
	struct pro queue1[x];
	struct pro queue2[x];
	int count=0;
	
	while(count < x)
	{
		write(1,"\nEnter process name    : ",44);
		read(0,pro[count].processname,15);
		write(1,"Enter arival time      : ",42);
		scanf("%d",&pro[count].arrivaltime);

    	write(1,"Enter burst  time     : ",42);
		scanf("%d",&pro[count].bursttime);
	
		write(1,"Enter process type (sys/user-0/1)       : ",42);
		scanf("%d",&pro[count].processclass);
	
		pro[count].processid=count;
		count++;
	
	} 

	printf("\nPROCESSING ");
	int q1_count=0;
	int q2_count=0;
	int i;
	for(i=0;i<x;i++){
		if(pro[i].processclass == 0){
				queue1[q1_count]=pro[i];
				q1_count++;
			}
		else if(pro[i].processclass == 1){
				queue2[q2_count]=pro[i];
				q2_count++;
			}
	}
	
	
	write(1,"\nEnter start time  :  ",26);
	scanf("%d",&global_time);
	fflush(stdin);
	
	int time_quantum=2,bz=0,rt[x],flag,k=0,j,z,comp= 0, t = 0,minm=queue1[0].bursttime,shortest = 0, finish_time,flag1 = 0;
	struct pro_temp;

	while(1){
		
		for (i = 0; i < q1_count;i++)
		{
			rt[i] = queue1[i].bursttime;
		}
       				
       	while(comp != q1_count)
		   {
	       		for (j = 0; j < q1_count; j++)
				    {
	            	if ((queue1[j].arrivaltime <= global_time) && (rt[j] <= minm) && rt[j] > 0) 
					{
	                	minm = rt[j];
	                	shortest = j;
	                	flag1=1;
					}
	       		}
	       		
	       			
	 		if(flag1==0)
			  {
	            global_time++;
	            continue;
	        }
	        rt[shortest]--;
	        minm = rt[shortest];
	        if(minm == 0)
	             minm = INT_MAX;
			 
			if (rt[shortest] == 0) 
			{
	            comp++;
	            queue1[shortest].comple_t = global_time;
	            finish_time = global_time + 1;
	 			queue1[shortest].comple_t = global_time+1;
			}
				
	           
	        global_time ++ ;		
		}
		
		int a;
		for(a=0; a< q1_count ; a++)
		{
			printf("\nCompletion time. %s = %d ",queue1[a].processname,queue1[a].comple_t);
		}
		
		        for(j=0;bz != q2_count;){
					if(queue2[j].bursttime <= time_quantum && queue2[j].bursttime >0 ){
						global_time+=queue2[j].bursttime;
      					queue2[j].bursttime=0;
     					flag=1; 
					}
					else if(queue2[j].bursttime>0)
    				{ 
     					queue2[j].bursttime-=time_quantum;
      					global_time+=time_quantum; 
   					}
					   
					if(queue2[j].bursttime==0 && flag==1)
				    { 
				    	bz++; 
					  	queue2[j].comple_t = global_time+1; 
				      	flag=0; 
				    }  
					if(j==q2_count -1) 
      					j=0; 
					else if(queue2[j+1].arrivaltime<=global_time)
      					j++; 
					else 
      					j=0; 

			}
	        printf("\n\nQueue2 executed");
			for(a=0; a< q2_count ; a++)
				{
					printf("\nCompletion time. %s = %d ",queue2[a].processname,queue2[a].comple_t);
				}
 
			break;
	}
	int avg_tat1=0;
	int avg_tat2=0;
	int avg_wt1=0;
	int avg_wt2=0;

	for(i=0;i<q1_count;i++){
		queue1[i].turna_t=queue1[i].comple_t - queue1[i].arrivaltime;
	
	}
	
	for(i=0;i<q2_count;i++){
		queue2[i].turna_t=queue2[i].comple_t - queue2[i].arrivaltime;
	
	}
	
	for(i=0;i<q2_count;i++){
		queue2[i].wait_t=queue2[i].turna_t - queue2[i].bursttime;
	
	}
	
	for(i=0;i<q1_count;i++){
		queue1[i].wait_t=queue1[i].turna_t - queue1[i].bursttime;
	
	}
	
	printf("\n\nPROCESS NAME |\t TURN AROUND TIME |\t WAITING TIME \n");
	for(i=0;i<q1_count;i++){
	printf(" %s             |\t\t%d         |\t\t%d \n",queue1[i].processname,queue1[i].turna_t,queue1[i].wait_t);
	}
		for(j=0;j<q2_count;j++){
	printf(" %s             |\t\t%d         |\t\t%d \n ",queue2[j].processname,queue2[j].turna_t,queue2[j].wait_t);
	}
	
	printf("\n\t\tAVERAGE turnaroundtime & AVERAGE Waitingtime");
	
	for(i=0;i<q1_count;i++){
	
		avg_tat1=avg_tat1+queue1[i].turna_t;
	}
	avg_tat1= (avg_tat1 / q1_count);
	for(i=0;i<q2_count;i++){
	
		avg_tat2=avg_tat2+queue2[i].turna_t;
	}
	avg_tat2= (avg_tat2 / q2_count);
	for(i=0;i<q2_count;i++){
	
		avg_wt2=avg_wt2+queue2[i].wait_t;
	}
	avg_wt2= (avg_wt2 / q2_count);
	for(i=0;i<q1_count;i++){
	
		avg_wt1=avg_wt1+queue1[i].wait_t;
	}
	avg_wt1= (avg_wt1 / q1_count);
	
	printf("\n\nPROCESS NAME |\t AVERAGE TURN AROUND TIME |\t AVERAGE WAITING TIME \n");
	printf(" %s             |\t\t%d         |\t\t%d \n",queue1[i].processname,avg_tat1,avg_wt1);
	printf(" %s             |\t\t%d         |\t\t%d \n",queue1[i].processname,avg_tat2,avg_wt2);
	
	}
