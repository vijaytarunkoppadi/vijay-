#include<lpc21xx.h>
#include"header.h"
#include<stdio.h>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart0_init(unsigned int baud){
int a[]={15,60,30,0,15};
unsigned int pclk=a[VPBDIV]*1000000;
unsigned int result=0;
result=pclk/(16*baud);
PINSEL0|=0x5;
U0LCR=0x83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0x03;
}
void uart0_tx(unsigned char data){
U0THR=data;
while(THRE==0);
}
void uart0_tx_string(s8 *ptr){
	while(*ptr){
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}
}
u8 uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}
void uart0_rx_string(s8 *ptr,s32 max_bytes){
s32 i;
for(i=0;i<max_bytes;i++){
	while(RDR==0);
	ptr[i]=U0RBR;
	if(ptr[i]=='\r')
		break;
}
ptr[i]='\0';
}

//void uart0_tx_integer(int n){
//s32 num,j;
//if(n==0){
//uart0_tx('0');
//return;
//}
//if(n<0){
//	uart0_tx('-');
//	n=-n;
//}
//for(j=1,num=n;num;num/=10,j*=10);
//for(j/=10,num=n;j>0;num%=j,j/=10){
//uart0_tx((num/j)+48);	
//}
//}

//void uart0_tx_float(float n){
//s32 num,j;
//float k;
//if(n==0){
//uart0_tx('0');
//return;
//}
//if(n<0){
//	uart0_tx('-');
//	n=-n;
//}
//for(j=1,num=n;num;num/=10,j*=10);
//for(j/=10,num=n;j>0 ;num%=j,j/=10){
//uart0_tx((num/j)+48);	
//}
//uart0_tx('-');
//k=n-(int)n;
//k=k*10;
//while((int)k!=0){
//uart0_tx((int)k+48);
//k=k-(int)k;
//k=k*10;
//}
//}

void uart0_tx_integer(s32 num){
	s8 buf[10];
	sprintf(buf,"%d",num);
	uart0_tx_string(buf);
}
void uart0_tx_float(float num){
	s8 buf[10];
	sprintf(buf,"%.1f",num);
	uart0_tx_string(buf);
}

int uart0_rx_integer(s8 *p){
	int l,i,s;
	for(l=0;p[l];l++);
	for(i=0,s=0;i<l;i++){
		s=s*10+(p[i]-48);
	}
	return s;
}
void uart0_tx_hex(int num){
	int k,i;
	for(i=7;i>=0;i--){
		k=((num>>(4*i))&0xf);
		if(k<10)
			uart0_tx(k+48);
		if(k==10)
			uart0_tx('A');
		if(k==11)
			uart0_tx('B');
		if(k==12)
			uart0_tx('C');
		if(k==13)
			uart0_tx('D');
		if(k==14)
			uart0_tx('E');
		if(k==15)
			uart0_tx('F');
	}
}
























