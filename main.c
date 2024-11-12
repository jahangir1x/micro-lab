// DARMSTM.DLL
//-pSTM32F103C8
#define MMIO32(addr) (*(volatile unsigned int *)(addr))

#define RCC            0x40021000
#define PORTC          0x40011000
#define TIM2           0x40000000

#define RCC_APB2ENR    MMIO32(RCC + 0x18)
#define RCC_APB1ENR    MMIO32(RCC + 0x1C)

#define GPIOC_CRH      MMIO32(PORTC + 0x04)
#define GPIOC_BSRR     MMIO32(PORTC + 0x10)

#define TIM2_PSC       MMIO32(TIM2 + 0x28)
#define TIM2_ARR       MMIO32(TIM2 + 0x2C)
#define TIM2_SR        MMIO32(TIM2 + 0x10)
#define TIM2_CR1      MMIO32(TIM2 + 0x00)

void delay(int count) {
    TIM2_PSC = 8000 - 1;
    TIM2_ARR = count - 1;
    TIM2_SR &= ~(1);

    TIM2_CR1 |= 1;
    while (!(TIM2_SR & 1)){
        // wait
    }
    TIM2_CR1 &= ~(1);
}

int main() {
    // clock enable
    RCC_APB2ENR |= (1 << 4);
    RCC_APB1ENR |= 1;

    // mode setup
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |= (1 << 20);

    while (1) {
        GPIOC_BSRR |= (1 << 13);
        delay(1000);

        GPIOC_BSRR |= (1 << (13 + 16));
        delay(1000);
    }

	return 0;
}






