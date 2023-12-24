#include<lpc21xx.h>  //header file lpc21xx 
#include"header.h"   // the header contain uart funtion declartions
void array_shift(int *p,int l){    // shifting of array operends
	int k;
	for(k=l+1;p[k];k++){
		p[k]=p[k+1];
	}
	p[k-1]=0;
}	
void char_shift(char *p,int l){   // shifting of operator 
	int k;
	for(k=l;p[k];k++){
		p[k]=p[k+1];
	}
	p[k-1]=0;
}
int main(){
int arr[10]={0},i,l,m,n;
char n1,ch[10]={0};
uart0_init(9600);

while(1){
for(i=0;i<10;i++){
	int s=0;
	while(1){
		n1=uart0_rx();
		if(n1=='+'||n1=='-'||n1=='*'||n1=='/'||n1=='%'||n1=='='){
		uart0_tx(n1);
		ch[i]=n1;
			break;
		}
		uart0_tx(n1);
		s=s*10+(n1-48);
	}
	arr[i]=s;
	if(ch[i]=='=')
		break;
}
for(m=0;ch[m];m++){
for(l=0;ch[l];l++)
{
	if(ch[l]=='*'||ch[l]=='/'||ch[l]=='%'){
		if(ch[l]=='*'){
		arr[l]=arr[l]*arr[l+1];
			array_shift(arr,l);
			char_shift(ch,l);
		}
		else if(ch[l]=='/'){
			if(arr[l+1]==0){
				uart0_tx_string("error");
				break;
			}
			arr[l]=arr[l]/arr[l+1];
			array_shift(arr,l);
			char_shift(ch,l);
		}
		else if(ch[l]=='%'){
  		arr[l]=arr[l]%arr[l+1];
			array_shift(arr,l);
			char_shift(ch,l);
		}
	}
}
}
for(n=0;ch[n];n++){
for(l=0;ch[l];l++){
		if(ch[l]=='-'){
		  arr[l]=arr[l]-arr[l+1];
			array_shift(arr,l);
			char_shift(ch,l);
		}	
}
}
for(n=0;ch[n];n++){
for(l=0;ch[l];l++){
		if(ch[l]=='+'){
		  arr[l]=arr[l]+arr[l+1];
			array_shift(arr,l);
			char_shift(ch,l);
		}	
}
}
uart0_tx_integer(arr[0]);
uart0_tx('\r');
uart0_tx('\n');
}
}

