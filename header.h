typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int ms);

extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *ptr);
extern void rtol(char *,int pos);
extern void ltor(char *,int pos);
extern void cgram_init(void);

extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(s8 *ptr);
extern u8 uart0_rx(void);
extern void uart0_rx_string(s8 *ptr,s32 max_bytes);
extern void uart0_tx_integer(int n);
extern void uart0_tx_float(float n);
extern int uart0_rx_integer(s8 *p);
extern void uart0_tx_hex(int num);

extern void adc_init(void);
extern u32 adc_read(u32 ch_num);

extern void config_VIC(void);
extern void en_uart0_intr(void);
extern void UART0_Handler(void)__irq;


