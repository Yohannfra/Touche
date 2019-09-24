int pinCLK = 25;
int pinCS = 26;
int pinDIN = 27;

void setup()
{
	pinMode(pinCLK,OUTPUT);
	pinMode(pinCS,OUTPUT);
	pinMode(pinDIN,OUTPUT);
	delay(50);
	Init_MAX7219();
}

void Init_MAX7219(void)
{
	Write(0x09, 0x00);       //decoding ：BCD
	Write(0x0a, 0x01);       //brightness (de 0x01 a 0x0f)
	Write(0x0b, 0x07);       //scanlimit；8 LEDs
	Write(0x0c, 0x01);       //power-down mode：0，normal mode：1
	Write(0x0f, 0x00);       //test display：1；EOT，display：0
}

//Ecriture sur une rangee
void Write(unsigned char address,unsigned char dat)
{
        digitalWrite(pinCS,LOW);
        Write_byte(address);           //address，code of LED
        Write_byte(dat);               //data，figure on LED
        digitalWrite(pinCS,HIGH);
}

// Ecriture sur un 8x8
void Write_byte(unsigned char DATA)
{
            unsigned char i;
       digitalWrite(pinCS,LOW);
       for(i=8;i>=1;i--)
          {
             digitalWrite(pinCLK,LOW);
             digitalWrite(pinDIN,DATA&0x80);// Extracting a bit data
             DATA = DATA<<1;
             digitalWrite(pinCLK,HIGH);
           }
}

void turn_light_on(int color) // color 1 red : 2 green
{
	if (color == 1) {
	 	Write(1, B11111111);
	 	Write(2, B11111111);
		Write(3, B11111111);
	 	Write(4, B11111111);
	 	Write(5, B00000000);
	 	Write(6, B00000000);
	 	Write(7, B00000000);
	 	Write(8, B00000000);

	} else if (color == 2) {
		Write(1, B00000000);
	 	Write(2, B00000000);
		Write(3, B00000000);
	 	Write(4, B00000000);
	 	Write(5, B11111111);
	 	Write(6, B11111111);
	 	Write(7, B11111111);
	 	Write(8, B11111111);
	}
}

void turn_light_on_arrow_style(int color) // color 1 red : 2 green
{
	if (color == 1) {
	 	Write(1, B00000000);
	 	Write(2, B00001000);
		Write(3, B00000100);
	 	Write(4, B00000011);
	 	Write(5, B11111111);
	 	Write(6, B00000011);
	 	Write(7, B00000100);
	 	Write(8, B00001000);

	} else if (color == 2) {
		Write(1, B00000000);
	 	Write(2, B00010000);
		Write(3, B00100000);
	 	Write(4, B11000000);
	 	Write(5, B11111111);
	 	Write(6, B11000000);
	 	Write(7, B00100000);
	 	Write(8, B00010000);
	}
}


void turn_light_off(void)
{
 	Write(1, B00000000);
 	Write(2, B00000000);
	Write(3, B00000000);
 	Write(4, B00000000);
 	Write(5, B00000000);
 	Write(6, B00000000);
 	Write(7, B00000000);
 	Write(8, B00000000);
}

void loop()
{
	turn_light_on_arrow_style(1);
	delay(1500);
	turn_light_on_arrow_style(2);
	delay(1500);
}
