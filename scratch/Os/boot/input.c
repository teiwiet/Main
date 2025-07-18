#define pic1_command 			0x20 
#define pic1_data 				0x21 
#define pic2_command 			0xa0 
#define pic2_data 				0xa1 
#define icw1_def 				0x10 
#define icw1_icw4 				0x01 
#define icw4_x86 				0x01 

#define y_overflow 				0b10000000
#define x_overflow 				0b01000000 
#define y_negative 				0b00100000
#define x_negative 				0b00010000
#define always_set 				0b00001000
#define middle_click 			0b00000100
#define right_click 			0b00000010
#define left_click 				0b00000001

#define unused_a				0b10000000
#define unused_b				0b01000000

void InitialiseIDT();
extern void LoadIDT();
void HandleISR1();
void HandleISR12();
void RemapPIC();

struct IDTElement {
	unsigned short lower;
	unsigned short selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short higher;
};

struct IDTElement _idt[256];
extern unsigned int isr1,isr12;
unsigned int base,base12;

unsigned char inportb(unsigned short port){
	unsigned char value;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (value) : "dN" (port));
};

void outportb(unsigned short port,unsigned char data){
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port),"a" (data));
}

void InitialiseIDT(){
	_idt[1].lower = (base & 0xffff);
	_idt[1].higher = (base >> 16) & 0xffff;
	_idt[1].selector = 0x08;
	_idt[1].zero = 0;
	_idt[1].flags = 0x8e;

	_idt[12].lower = (base12 & 0xffff);
	_idt[12].higher = (base12 >> 16) & 0xffff;
	_idt[12].selector = 0x08;
	_idt[12].zero = 0;
	_idt[12].flags = 0x8e;

	RemapPIC();
	outportb(0x21,0b11111001);
	outportb(0xa1,0xff);
	
	LoadIDT();
}

void RemapPIC(){
	unsigned char a,b;
	a = inportb(pic1_data);
	b = inportb(pic2_data);
}
