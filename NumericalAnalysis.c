#include <stdio.h>
float fonk(int mtr[][2], int , int ,float);
void printfunc(int mtr[][2], int size, int N);
void invertmtr(float mtr[][50], int size, int N);
int getfunc(int N, int func[][2], int size);


int main(){
	
	int decision,decision2,decision3,N,func[100][2],i,j;
	float matrix[50][50],maxerror,x,a,b;
	int satirxsutun,iterasyon,itr=0;
	
	printf("\n*************Hosgeldiniz!*************\n\n");
	
	do{
		
	printf("Lutfen yapmak istediginiz islemi seciniz: \n");
	printf("1.Iterasyon yontemleri \n");
	printf("2.Matris islemleri \n");
	printf("3.Sayisal turev/integral \n");
	printf("4.Enterpolasyon \n"); 
	printf("5.Cikis \n"); 
	scanf(" %d", &decision);
	
	if(decision==1){
		printf("Lutfen kullanmak istediginiz yontemi seciniz: \n");
		printf("1.Bisection yontemi\n2.Regula-Falsi yontemi\n3.Newton-Raphson yontemi\n ");
		scanf(" %d", &decision2);
		if(decision2==1){
			
			N=getfunc(N,func,100);
			
			printf("\nGirdiginiz fonksiyon: \n");
			printfunc(func, 100, N);
			
			do{
				printf("\nUc degerleri giriniz(koklerin Y'deki goruntusunun isaretleri farkli olmali.): \n");
				printf("Alt deger: "); scanf("%f", &a); printf("f(x)=%f\n",fonk(func,100,N,a));
				printf("Ust deger: "); scanf("%f", &b); printf("f(x)=%f\n",fonk(func,100,N,b));
			}while(fonk(func,100,N,a)*fonk(func,100,N,b) >= 0);
			
			//	printf("%f",fonk(func,100,N,a)*fonk(func,100,N,b) );
			
			printf("\nEn fazla kac iterasyon yapilsin? : "); scanf("%d", &iterasyon);	
			printf("\nHata payi ne kadar olsun? : "); scanf("%f", &maxerror); 
			
				while(itr<iterasyon && (fonk(func,100,N,(a+b)/2)>maxerror||-fonk(func,100,N,(a+b)/2)>maxerror) && fonk(func,100,N,(a+b)/2)!=0){
				if(fonk(func,100,N,a)*fonk(func,100,N,(a+b)/2)<0){
					b = (a+b)/2;
				}
			
				else{
					a = (a+b)/2; 
				}			
				itr++;
				printf("%d. iterasyon sonuc: %f koku icin:  %f\n",itr,(a+b)/2,fonk(func,100,N,(a+b)/2)  );
			}
			
			if(fonk(func,100,N,(a+b)/2)==0){
				printf("%f gercek koktur", (a+b)/2);
			}	
			
			
		}
		else if(decision2==2){
			
			N=getfunc(N,func,100);
			
			printf("\nGirdiginiz fonksiyon: \n");
			printfunc(func, 100, N);
		
			do{
				printf("\nUc degerleri giriniz(koklerin Y'deki goruntusunun isaretleri farkli olmali.): \n");
				printf("Alt deger: "); scanf("%f", &a); printf("f(x)=%f\n",fonk(func,100,N,a));
				printf("Ust deger: "); scanf("%f", &b); printf("f(x)=%f\n",fonk(func,100,N,b));
			}while(fonk(func,100,N,a)*fonk(func,100,N,b) >= 0);
			
			//printf("%f",fonk(func,100,N,a)*fonk(func,100,N,b) );
			
			printf("\nEn fazla kac iterasyon yapilsin? : "); scanf("%d", &iterasyon);	
			printf("\nHata payi ne kadar olsun? : "); scanf("%f", &maxerror); 
				
			x = ( a*fonk(func,100,N,b) - b*fonk(func,100,N,a) ) / (fonk(func,100,N,b)-fonk(func,100,N,a) );
			itr=0;
			while(itr<iterasyon && (fonk(func,100,N,x)>maxerror || -fonk(func,100,N,x)>maxerror && fonk(func,100,N,x)!=0)){	
				x = ( a*fonk(func,100,N,b) - b*fonk(func,100,N,a) ) / (fonk(func,100,N,b)-fonk(func,100,N,a) );
				if(fonk(func,100,N,x)<0){
					a=x;
				}
				else{
					b=x;
				}	
				itr++;
				printf("%d. iterasyon sonuc: %f koku icin:  %f\n",itr,x,fonk(func,100,N,x)  );
			}
			
			if(fonk(func,100,N,x)==0){
				printf("%f gercek koktur", (a+b)/2);
			}	
					
		}
		else if(decision2==3){
			
			int derfunc[100][2];
			N=getfunc(N, func, 100);
			
			printf("\nGirdiginiz fonksiyon: \n");
			printfunc(func, 100, N);
			
			printf("\nLutfen girdiginiz fonksiyonun turevini giriniz: \n");
			int i;
			for(i=N-1; i>=0; i--){
				derfunc[i][0]=i;
				printf("%d. terimin katsayisi: ", N-i);
				scanf("%d", &derfunc[i][1]);
			}
			
			printf("\nGirdiginiz turev: \n");
			printfunc(derfunc, 100, N-1);
			
			printf("\nEn fazla kac iterasyon yapilsin? : "); scanf("%d", &iterasyon);	
			printf("\nHata payi ne kadar olsun? : "); scanf("%f", &maxerror); 
			
			printf("\nBir baslangic degeri giriniz: \n");
			scanf("%f", &x);
			
			x=x-fonk(func,100,N,x)/fonk(derfunc,100,N,x); 
			itr=0;
			while(itr<iterasyon && (fonk(func,100,N,x)>maxerror || -fonk(func,100,N,x)>maxerror )){	
				x=x-fonk(func,100,N,x)/fonk(derfunc,100,N,x); 
				itr++;
				printf("%d. iterasyon sonuc: %f koku icin:  %f\n",itr,x,fonk(func,100,N,x)  );
			}
		}
		
	}
	else if(decision==2){
		printf("Lutfen yapmak istediginiz islemi seciniz: \n");
		printf("1.Matrisin tersi\n2.Gauss Eliminasyon\n3.Gauss-Seidal\n ");
		scanf(" %d", &decision2);
		if(decision2==1){
		
			printf("Kare matrisin satir ve sutun sayisini giriniz.\n");
			scanf("%d",&satirxsutun);
			
			getmtr(satirxsutun,matrix,50);
			
			printf("Girdiginiz matrix:\n");
			printmtr(satirxsutun,matrix,50);

			invertmtr(matrix,50,satirxsutun); printf("\n\n");
			
		}
		else if(decision2==2){
			
			int denklemsayisi;
			float fmatrix[50][50];
			printf("Denklem sayisini giriniz \n");
			scanf("%d",&denklemsayisi);
			
			printf("Denklemleri matrix olarak giriniz: \n");
			for(i=0; i<denklemsayisi; i++){
				for(j=0; j<=denklemsayisi; j++){
					printf("Matrix[%d][%d]: ", i+1, j+1);
					scanf("%f", &fmatrix[i][j]);
				}
			}
			
			printf("Girdiginiz denklemler: \n");
			printmtrgauss(denklemsayisi,fmatrix,50); 
			
			int a;
			float temp;
			
			for(j=denklemsayisi-1; j>=0; j--){
		        for(i=denklemsayisi-1; i>=0; i--){
		            if(i<j){
		            	temp= fmatrix[i][j]/fmatrix[j][j];
		            	for(a=denklemsayisi; a>=0; a--){
		            		fmatrix[i][a] = fmatrix[i][a]- (temp*fmatrix[j][a]);	
						}		
		            }
		        }
		    }
		    
		    printf("Matris duzenleniyor... \n");
			printmtrgauss(denklemsayisi,fmatrix,50); 
			
			float elements[50] = {0};
			printf("sonuc: \n");
			
			elements[0]=(elements[0] + fmatrix[0][denklemsayisi])/fmatrix[0][0];
			
			for(i=1; i<denklemsayisi;i++){
				for(j=i-1; j>=0;j--){
					elements[i]=elements[i]-elements[j]*fmatrix[i][j];
				}
				elements[i]= (elements[i] + fmatrix[i][denklemsayisi])/fmatrix[i][i];
			}
			for(i=0; i<denklemsayisi;i++){
				printf("%c = %.3f  ", 97+i,elements[i]);
			}
			
		}
		else if(decision2==3){
			
			float roots[50]={0};
			printf("Denklem sayisini giriniz \n");
			scanf("%d",&satirxsutun);
			
			printf("Denklemleri matrix olarak giriniz: \n");
			for(i=0; i<satirxsutun; i++){
				for(j=0; j<=satirxsutun; j++){
					printf("Matrix[%d][%d]: ", i+1, j+1);
					scanf("%f", &matrix[i][j]);
				}
			}
			printmtrgaussseidel(satirxsutun,matrix,50);
			
			gaussseidel(satirxsutun,matrix,50,roots,50);
		}
	
	}
	else if(decision==3){
		printf("Lutfen yapmak istediginiz islemi seciniz: \n");
		printf("1.Sayisal Turev\n2.Simpson yontemi\n3.Trapez yontemi\n");
		scanf(" %d", &decision2);
		if(decision2==1){	
		
			N=getfunc(N, func, 100);
			
			printf("\nGirdiginiz fonksiyon: \n");
			printfunc(func, 100, N);
			
			printf("\nkullanmak istediginiz yontem?\n");
			printf("1.geri fark\n2.ileri fark\n3.merkezi fark\n");
			scanf(" %d", &decision3);
			
			float nokta;
			printf("Hangi noktada turev alinsin?\n");
			scanf("%f", &nokta);
			
			float h;
			printf("h degeri ne olsun?\n");
			scanf("%f", &h);
			float turev;
			
			if(decision3==1){
				turev=(fonk(func,100,N,nokta)-fonk(func,100,N,nokta-h))/h;
			}
			else if(decision3==2){
				turev=(fonk(func,100,N,nokta+h)-fonk(func,100,N,nokta))/h;
			}
			else{
				turev=(fonk(func,100,N,nokta+h)-fonk(func,100,N,nokta-h))/(2*h);
			}
			printf("%0.3f noktasindaki turev = %f\n",nokta,turev);
			
		}
		else if(decision2==2){
			
			N=getfunc(N, func, 100);
			
			printf("\nGirdiginiz fonksiyon: \n");
			printfunc(func, 100, N);
			
			float alt,ust;
			printf("\nAlt deger?  \n");scanf("%f", &alt);
			printf("Ust deger?  \n");scanf("%f", &ust);
			
			int split;
			float result=0;
			printf("Fonksiyon kac parcaya ayrilacak?\n");
			scanf("%d", &split);
			
			float h = (ust-alt)/split;
			ust=alt+h;
			printf("Hangi simpson yontemini kullanmak istersiniz?\n");
			printf("1.1/3\n2.3/8\n");
			scanf("%d", &decision3);
			
			if(decision3==1){
				for(i=0; i<split; i++){
					result += (ust-alt)*(fonk(func,100,N,ust)+fonk(func,100,N,alt)+4*fonk(func,100,N,((alt+ust)/2)))/6;
					alt+=h;
					ust=alt+h;	
				}
			}
			else{
				for(i=0; i<split; i++){
					result += (ust-alt)*(fonk(func,100,N,ust)+fonk(func,100,N,alt)+3*fonk(func,100,N,((2*alt+ust)/3))+3*fonk(func,100,N,((alt+2*ust)/3)))/8;
					alt+=h;
					ust=alt+h;	
				}
			}
				
			printf("alan= %f", result);		
		}
		else if(decision2==3){
			
			N=getfunc(N, func, 100);
			
			printf("\nGirdiginiz fonksiyon: \n");
			printfunc(func, 100, N);
			
			float alt,ust;
			printf("\nAlt deger?  \n");scanf("%f", &alt);
			printf("Ust deger?  \n");scanf("%f", &ust);
		
			int split;
			float result=0;
			printf("Fonksiyon kac parcaya ayrilacak?\n");
			scanf("%d", &split);
			
			float h = (ust-alt)/split;
			ust=alt+h;
			
			for(i=0; i<split; i++){
				result += (ust-alt)*(fonk(func,100,N,ust)+fonk(func,100,N,alt))/2;
				alt+=h;
				ust=alt+h;	
			}
			printf("alan= %f", result);	
		}
	}
	else if(decision==4){
		printf("1.Gregory Newton Enterpolasyonu\n");
		scanf("%d", &decision2);
		if(decision2==1){
			
			float x,data[100][100];
			int count;
			
			printf("Veri sayisini giriniz\n");
			scanf("%d", &N);
			
			printf("Lutfen x degerlerini giriniz\n");
			for(i=0; i<N; i++){
				printf("%d. x Verisi: ",i+1); scanf("%f", &data[i][0]);
			}
			printf("Lutfen y degerlerini giriniz\n");
			for(i=0; i<N; i++){
				printf("%d. y Verisi: ",i+1); scanf("%f", &data[i][1]);
			}
			
			printf("Hesaplamak istediginiz degeri giriniz\n");
			scanf("%f", &x);
			
			count=N;
			int j=2;
		
			while(count>=1){
				for(i=0; i<count-1; i++){
					data[i][j]=data[i+1][j-1]-data[i][j-1];
				}
				j++;
				count--;	
			}
			
			for(i=0; i<N; i++){//for debugging
				for(j=0; j<N+1-i; j++){
					printf("  %0.2f  ", data[i][j]);
				}printf("\n");
			}
			
			float h=data[1][0]-data[0][0];
			float k=(x-data[0][0])/h;//printf("k: %f\n", k);
			float total=0,temp,fact;
		
			for(i=0; i<N+1; i++){
				temp=1; fact=1; 
				for(j=i; j>0; j--){
					fact=fact*j;
					temp*=(k-j+1);
				}
				//printf("%d. adým : %f\n", i+1,(data[0][i+1]*temp)/fact );
				total+=(data[0][i+1]*temp)/fact;	
			}
		
			printf("\n%f koku icin enterpolasyon sonucu = %f\n", x, total);
		}
		
		
	}
	
	printf("\n\n ******************************* \n\n");	
	}while(decision!=5);
	
	
	
	return 0;
}

float fonk(int mtr[][2], int size, int N,float root){//bir denklemin sonucunu hesaplamak için fonksiyon
	
	float total=0,result;
	int j,exp;

	for(j=N; j>0; j--){
		result=1;
		exp=mtr[j][0];
		
		if(exp<0){
			exp = -exp;	
		}				
		while(exp>0){
			result = result*root; 
			exp--;
		}
		result*= mtr[j][1];
    	total+=result;
	}
	total+= mtr[0][1];

	return total;
}

void printfunc(int mtr[][2], int size, int N){//denklemi yazdýrmak için fonksiyon
	
	int j;
	
	for(j=N; j>0; j--){	
		if(mtr[j][1] != 0){	
			if(mtr[j][1] >0)
				printf("+");		
			printf("%dx^%d ",mtr[j][1], j);
		}
	}
	if(mtr[0][1]>0)
		printf("+");			
	printf("%d",mtr[0][1]);
}

int getfunc(int N, int func[][2], int size){
	
	printf("Denklemdeki derecesi en buyuk terimin, derecesini yaziniz.(Ornek=x^3 icin 3)\n");
	scanf(" %d", &N);	

	printf("Lutfen terimlerin katsayilarini giriniz: \n");
	
	int i;
	for(i=N; i>=0; i--){
		func[i][0]=i;
		printf("%d. terimin katsayisi: ", N-i+1);
		scanf("%d", &func[i][1]);
	}
	
	return N;
}

void invertmtr(float mtr[][50], int size, int N){
	
	int i,j,a;
	float temp;
	
	for(i=0; i<N; i++){
		for(j=N;j<2*N;j++){
			mtr[i][j]=0;
		}
		mtr[i][N+i]=1;
	}

	for(j=N-1; j>=0; j--){
        for(i=N-1; i>=0; i--){
            if(i<j){
            	temp= mtr[i][j]/mtr[j][j];
            	for(a=2*N; a>=0; a--){
            		mtr[i][a] = mtr[i][a]- (temp*mtr[j][a]);	
				}		
            }
            if(i>j){
            	temp= mtr[i][j]/mtr[j][j];
            	for(a=0; a<N*2; a++){
            		mtr[i][a] = mtr[i][a]- (temp*mtr[j][a]);	
				}		
            }
        }
    }
 
    for(i=0; i<N;i++){
    	temp=mtr[i][i];
    	for(j=0;j<2*N;j++){
    		mtr[i][j]=mtr[i][j]/temp;
		}
	}

	printf("ters matrix: \n");
	for(i=0; i<N; i++){
		for(j=N; j<2*N; j++){
			printf("%0.2f  ", mtr[i][j]);
		}
		printf("\n");
	}	
}


void getmtr(int satirxsutun, float mtr[][50], int size){
	int i,j;
	for(i=0; i<satirxsutun; i++){
		for(j=0; j<satirxsutun; j++){
			printf("Matrix[%d][%d]: ", i+1, j+1);
			scanf("%f", &mtr[i][j]);
		}
	}
}

void printmtr(int satirxsutun, float mtr[][50], int size){
	int i,j;
	for(i=0; i<satirxsutun; i++){
		for(j=0; j<satirxsutun; j++){
			printf("%0.2f  ", mtr[i][j]);
		}
		printf("\n");
	}
}

void printmtrgauss(int denklemsayisi, float mtr[][50], int size){
	int i,j;
	for(i=0; i<denklemsayisi; i++){
		for(j=0; j<i+1; j++){
			printf("%.1f%c  ", mtr[i][j],97+j);
		}
		printf(" ="); printf("%2f\n", mtr[i][denklemsayisi]);
	}
}

void printmtrgaussseidel(int rowandcolumn, float mtr[][50], int size){
	int i,j;
	for(i=0; i<rowandcolumn; i++){
		for(j=0; j<rowandcolumn; j++){
			printf("%2.0f ", mtr[i][j]);
		}
		printf(" |"); printf("%2f\n", mtr[i][rowandcolumn]);
	}
}

void gaussseidel(int rowandcolumn, float mtr[][50], int size1, float roots[], int size2){
	
	int maxitr,i,j;
	float temp;
	printf("Max iteration?: "); scanf("%d", &maxitr);
	
	int itr=1;
	
	while(itr<=maxitr){
		
		for(i=0; i<rowandcolumn; i++){
			temp=0;
			for(j=0; j<rowandcolumn; j++){
				temp= temp + mtr[i][j]*roots[j];
			}
			temp=temp-mtr[i][i]*roots[i];
			roots[i]= (mtr[i][rowandcolumn]-temp) / mtr[i][i];
		}
		
		printf("Iteration == %d\n----------------\n", itr);
		for(i=0; i<rowandcolumn; i++){
			printf("%d. terim:  %f\n",i+1,roots[i]);
		}
		printf("----------------\n");
		itr++;
	}
	printf("-----sonuc:-----\n");
	for(i=0; i<rowandcolumn; i++){
		printf("%d. terim:  %f\n",i+1,roots[i]);
	}
}
