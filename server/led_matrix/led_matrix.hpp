#ifndef LED_MATRIX_H
#define LED_MATRIX_H

class LedMatrix {
    private:
        int m_pin_clk;
        int m_pin_cs;
        int m_pin_din;
        void Init_MAX7219(void);
        void Write(unsigned char address, unsigned char dat);
        void Write_byte(unsigned char DATA);

    public:
        LedMatrix(int pin_clk, int pin_cs, int pin_din);
        void init(void);
        void turn_light_on(int color); // color 1 red : 2 green
        void turn_light_on_arrow_style(int color); // color 1 red : 2 green
        void turn_light_off(void);
};

#endif
