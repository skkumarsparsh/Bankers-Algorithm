#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void main()
{   
    
    int n,m,available[10],max[10][10],allocation[10][10],need[10][10],total[10],i,j,count=0,ans[10],k=0,p[10],sum,req[10],proc,t=1,ta[10];
    char ch;

    printf("\n\n");
    printf("Enter the number of processes\n");
    scanf("%d",&n);

    printf("\n\n");
    printf("Enter the number of resources\n");
    scanf("%d",&m);
    
    printf("\n\n");
    printf("Enter the allocation table\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }

    printf("\n\n");
    printf("Enter the max table\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }

    printf("\n\n");
    printf("Enter the total no instances of reach resource type\n");
    for(i=0;i<m;i++)
    {
        printf("Resource %d : ", i);
        scanf("%d",&total[i]);
    }

    for(j=0;j<m;j++)
    {   
        sum=0;
        for(i=0;i<n;i++)
        {
            sum+=allocation[i][j];
        }
        available[j]=total[j]-sum;
        ta[j]=available[j];
    }

    printf("\n\n");
    printf("The available is : ");
    for(i=0;i<m;i++)
    {
        printf("%d ",available[i]);
    }
    printf("\n");

    //the need matrix
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }

    printf("\n\n");
    printf("The need matrix is : \n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<n;i++)
        p[i]=0;
    
    A:
    for(i=0;i<n;i++)
    {   
        if(p[i]==0)
        {
            count=0;
            for(j=0;j<m;j++)
            {
                if(need[i][j]<=available[j])
                {
                    count++;
                }
            }
            if(count==m)
            {
                ans[k++]=i;
                p[i]=1;
                for(j=0;j<m;j++)
                {
                    available[j]+=allocation[i][j];
                }
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(p[i]==0)
        {  
            goto A;
        }
    }
    
    printf("\n\n");
    printf("The safe sequence is \n");
    printf("< ");
    for(i=0;i<k;i++)
    {
        printf("p[%d] ",ans[i]);
    }
    printf(">\n");

    count=0;
    for(i=0;i<m;i++)
    {
        if(total[i]==available[i])
        {
            count++;
        }
    }
    if(count==m)
    {
        printf("\n\nSystem is in a safe state\n");
    }
    else
    {
        printf("\n\nSystem is in an unsafe state\n");
    }

    for(i=0;i<m;i++)
    {
        available[i]=ta[i];
    }


    printf("\n\n");
    while ((getchar()) != '\n');
    printf("Do you need to grant a process an extra resource(Y/N)\n");
    scanf("%c",&ch);
    if(ch=='Y')
    {   
        printf("\n\n");
        printf("Enter the process number\n");
        scanf("%d",&proc);

        printf("\n\n");
        printf("Enter the requested resources\n");
        for(i=0;i<m;i++)
        {
            scanf("%d",&req[i]);
        }

        count=0;
        for(i=0;i<m;i++)
        {
            if(req[i]<=need[proc][i])
            {
                count++;
            }
        }
        if(count==m)
        {
            count=0;
            for(i=0;i<m;i++)
            {
                if(req[i]<=available[i])
                {
                    count++;
                }
            }
            if(count==m)
            {
                for(i=0;i<m;i++)
                {
                    available[i]-=req[i];
                    allocation[proc][i]+=req[i];
                    need[proc][i]-=req[i];
                }

                printf("\n\n");
                printf("The allocation matrix now is \n");
                for(i=0;i<n;i++)
                {
                    for(j=0;j<m;j++)
                    {
                        printf("%d ",allocation[i][j]);
                    }
                    printf("\n");
                }

                printf("\n\n");
                printf("The need matrix now is \n");
                for(i=0;i<n;i++)
                {
                    for(j=0;j<m;j++)
                    {
                        printf("%d ",need[i][j]);
                    }
                    printf("\n");
                }

                printf("\n\n");
                printf("The available now is \n");
                for(i=0;i<m;i++)
                {
                    printf("%d ",available[i]);
                }
                printf("\n");

                for(i=0;i<n;i++)
                    p[i]=0;

                k=0;

                B:
                for(i=0;i<n;i++)
                {   
                    if(p[i]==0)
                    {
                        count=0;
                        for(j=0;j<m;j++)
                        {
                            if(need[i][j]<=available[j])
                            {
                                count++;
                            }
                        }
                        if(count==m)
                        {
                            ans[k++]=i;
                            p[i]=1;
                            for(j=0;j<m;j++)
                            {
                                available[j]+=allocation[i][j];
                            }
                        }
                    }
                }
                for(i=0;i<n;i++)
                {
                    if(p[i]==0)
                    {  
                        goto B;
                    }
                }
                
                printf("\n\n");
                printf("The safe sequence is \n");
                printf("< ");
                for(i=0;i<k;i++)
                {
                    printf("p[%d] ",ans[i]);
                }
                printf(">\n");

                count=0;
                for(i=0;i<m;i++)
                {
                    if(total[i]==available[i])
                    {
                        count++;
                    }
                }
                if(count==m)
                {
                    printf("\n\nSystem is in a safe state\nThe resources can be granted\n");
                    t=0;
                }
                else
                {
                    printf("\n\nSystem is in an unsafe state\nThe resources can't be granted\n");
                    t=0;
                }
            }
        }
        if(t==1)
            printf("\n\nThe system is in an unsafe state\n");
    }
    printf("\n\nTHANK YOU!\n");
}