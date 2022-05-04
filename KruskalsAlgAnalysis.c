#include<stdio.h>
#include <time.h>

int main()
{
	printf("\n********************************WELCOME********************************\n");
	printf("\n*Test option is for bigger matrixes, so you can make a better analysis*\n");
	printf("\n*During the test option, your matrixes will be randomly filled        *\n");
	printf("\n*If you enter inputs as an matrix it must be as cost adjacency matrix *\n");
	printf("\n***********************************************************************\n");
	int i,j,a,hold,b,u,v,edges,ne=1,flag=0,xi=0;
	int min,mincost=0,cost[500][500],parent[500]={0};
	srand(0);
	clock_t t;
    t = clock();
    int decision,decision2;
	int k,y,x,c,test,counter[10];
	double time_taken[10];
	
	for(i=0; i<10;i++)//counter for process costs
		counter[i]=0;
		

	do{
		for(i=0; i<500;i++)//zeroing the cost matrix
			parent[i]=0;
			
		for(i=0; i<500;i++)//zeroing the cost matrix
			for(j=0; j<500;j++)
				cost[i][j]=0;
			
		printf("1.Type 1 to give inputs\n2.Type 2 for testing\n3.Exit\n");
		scanf("%d",&decision);
		if(decision==1){
			mincost=0;
			printf("1.To enter inputs as a matrix type 1\n2.To enter inputs as source-destination-cost, type 2\n");
			scanf("%d",&decision2);
			if(decision2==1){
				printf("\nEnter the number of edges:");
				scanf("%d",&edges);
				printf("\nEnter the cost adjacency matrix:\n");
				for(i=1;i<=edges;i++)//taking input as matrix
				{
					for(j=1;j<=edges;j++)
					{
						printf("Matrix[%d][%d]=",i,j );
						scanf("%d",&cost[i][j]);
					}
				}
				
				for(i=1;i<=edges;i++)
					for(j=1;j<=edges;j++)
						if(cost[i][j]==0)
								cost[i][j]=999;
				
			}
			else{
				printf("\nEnter the number of edges :   ");
				scanf("%d",&edges);
		
				printf("\nEnter your inputs as in order of source-destination-cost:\n    ");
				for(i=1;i<=edges;i++){//taking input in one line
					scanf("%d %d %d", &x,&c,&j);
					cost[x][c]=j;
				}
				
				
				for(i=1;i<=edges;i++)//if any value equals to 0, making them 999, this will serve as INFINITE value
					for(j=1;j<=edges;j++)
						if(cost[i][j]==0)
								cost[i][j]=999;		
			}
		
			ne=1;
			while(ne < edges){
				min=999;
				for(i=1;i<=edges;i++)//finding the smallest value
				{
					for(j=1;j <= edges;j++)
					{
						if(cost[i][j] < min)
						{
							min=cost[i][j];
							a=i;
							u=i;
							b=j;
							v=j;	
						}
						counter[xi]++;//counting the process cost
					}
				}
				if(parent[u]!=0){
					u=parent[u];
				}
				if(parent[v]!=0){
					v=parent[v];
				}
				flag=0;
				if(v!=u)//if there is a cycle v will be equal to u
				{
					parent[v]=u;
					flag=1;
				}
				if(flag==1)//this parts checks if there is any cycle(loop)
				{
					printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
					mincost +=min;
				}
				cost[a][b]=999;//making post values equal to INFINITE
				cost[b][a]=999;
			}
			xi++;
			printf("\nMinimum cost = %d\n\n",mincost);
			
		}
		else if(decision==2){
			hold=decision;
			printf("Please enter how many matrix you want to test with\n");
			scanf("%d", &test);// taking test number
			for(k=0; k<test; k++){
					
				printf("\nEnter the number of edges: ");
				printf("\n(You can enter a value up to 500, give high numbers for an accurate test.)\n ");
				scanf("%d",&edges);
				for (i = 1; i <= edges; i++) {//filling the matrix with random values
					for(j=1; j<=edges;j++){
						cost[i][j] = rand()%900;
					}
			    }
				ne=1;
				for(i=1;i<=edges;i++)//zeroing the parent matrix
					parent[i]=0;
					
				t = clock();
					
				for(y=0; y<10; y++){//each test will be repeated 10 times, afterwards values calculated here will be
									//divided to 10, so we will have average values
					
					while(ne < edges){
				
						for(i=1,min=999;i<=edges;i++){//same process as before, applying Kruskal's algorithm
							for(j=1;j <= edges;j++)
							{
								if(cost[i][j] < min)
								{
									min=cost[i][j];
									a=i;
									u=i;
									b=j;
									v=j;
									
								}
								counter[k]++;
							}
						}
						if(parent[u]!=0){
							u=parent[u];
						}
						
						if(parent[v]!=0){
							v=parent[v];
						}
						flag=0;
						if(v!=u){
							parent[v]=u;
							flag=1;
						}
						
						if(flag==1)	{
						//	printf("%d edge (%d,%d) =%d\n",ne,a,b,min); 
							ne++;
							mincost +=min;
						}
						
						cost[a][b]=999;
						cost[b][a]=999;
					}
					
				}
				t = clock() - t;
	    		time_taken[k]= ((double)t)/CLOCKS_PER_SEC;
	    		
	    		time_taken[k]= time_taken[k]/10;//taking average of values
				mincost=mincost/10;
				counter[k]=counter[k]/10;
				
				//printf("\n%d. Matrix : Minimum cost = %d\n",k+1,mincost);
				
			}
			
			
		}
		if((decision==3 && hold!=2) || decision==2){
		
			if(decision==3){
				k=xi;
			}
				
				
			do{
				printf("1.View process cost graph\n2.View process costs as number values\n3.View process time\n4.Exit\n");
				scanf("%d", &decision2);
						
					if(decision2==1){
						if(decision==2){
							printf("Attention: every '*' symbol equals to 1000.\n");//printing graph for test
							for(i=0;i<k;i++){
								printf("%d. Matrix: " , i+1);
								printf("|");
									for(j=0; j<counter[i]/1000; j++){
										printf("*");
									}
									printf("|\n");
								}
							}
						else{
							printf("Attention: every '*' symbol equals to 5.\n");
							for(i=0;i<k;i++){//printing graph of given inputs
								printf("%d. Matrix: " , i+1);
								printf("|");
									for(j=0; j<counter[i]/5; j++){
										printf("*");
									}
									printf("|\n");
								}
							}
					}
					else if(decision2==2){
						for(i=0;i<k;i++){
							printf("%d. Matrix counter: %d" , i+1, counter[i]);
							printf("\n");
						}
					}
					else if(decision2==3){
						for(i=0;i<k;i++){
						printf("%d. Matrix time: %f" , i+1, time_taken[i]);
						printf("\n");
					}
				}
			}while(decision2!=4);
	}
			
	
	}while(decision!=3);
	
	
	
return 0;	
}

