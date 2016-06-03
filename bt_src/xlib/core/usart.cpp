
#include "sys.h"
#include "common.h"
#include "usart.h"


volatile uint8_t Uart2_pos=0;

Usart::Usart()
{
}

void Usart::InitBuffers(uint8_t rx_size, uint8_t tx_size)
{
	Uart2_RcvCnt = 0;
	Uart2_pos = 0;
	//init buffers
//	if ((this->rx_buffer_size = rx_size) && this->rx_buffer == NULL)
//		this->rx_buffer = new uint8_t[this->rx_buffer_size];
//	if ((this->tx_buffer_size = tx_size) && this->tx_buffer == NULL)
//		this->tx_buffer = new uint8_t[this->tx_buffer_size];
}


Usart::~Usart()
{
//	//free buffers
//	if (this->rx_buffer_size)
//		delete[] this->rx_buffer;
//	if (this->tx_buffer_size)
//		delete[] this->tx_buffer;
}

///**
// * Initialize usart
// *
// * \param usart Usart structure
// * \param port Port structure
// * \param tx Number of tx pin
// * \param n Object index for ISR handling
// * \param baud Baudrate
// *
// * \note There are predefined usart modules like usart0, usart1 which contains usart and port structure, tx pin number and module index
// */
void Usart::Init(uint8_t usart,uint32_t baud)
{
//	//TODO:why is 1M not working?
//	uint32_t new_baud;
//
//	uint16_t bsel; //12 bit
//	int8_t bscale; //-7 - 7
//
//	uint16_t bsel_best = 0;
//	int8_t bscale_best = 0;
//	float error = 1;
//
//	uint8_t mul = 16;
//
//	uint8_t i;
//
//	//reset events
//	for (i=0;i<xlib_core_usart_events_count;i++)
//		this->events[i] = NULL;
//
//	if (baud > freq_cpu/16)
//		mul = 8;
//
//	for (bscale = 7; bscale>=-7; bscale--)
//	{
//		if (bscale >= 0)
//		{
//			bsel = (uint16_t)((float)freq_cpu / (xlib_core_usart_pow(bscale)*mul*(float)baud) - 1);
//			new_baud = (uint32_t)((uint32_t)freq_cpu/(xlib_core_usart_pow(bscale)*mul*((uint16_t)bsel + 1)));
//		}
//		else
//		{
//			bsel = (uint16_t)((float)(1 / xlib_core_usart_pow(bscale)) * (float)(freq_cpu / (mul*(float)baud) - 1));
//			new_baud = (uint32_t)((uint32_t)freq_cpu/(mul*(xlib_core_usart_pow(bscale)*((uint16_t)bsel) + 1)));
//		}
//
//		if ((error > abs(1 - (float)((float)new_baud / (float)baud))) && (bsel < 1024))
//		{
//			bsel_best = bsel;
//			bscale_best = bscale;
//			error = abs(1 - (float)((float)new_baud / (float)baud));
//		}
//	}
//
//	GpioSetDirection(port, tx, OUTPUT);
//	GpioWrite(port, tx, HIGH);
//
//	this->dbg = false;
//
//	this->spi_mode = false;
//	this->sck_port = port;
//	this->sck_pin = tx - 2;
//
//	this->usart = usart;

	//set baudrate
//	this->usart->BAUDCTRLA = bsel_best;
//	this->usart->BAUDCTRLB = (bscale_best << 4) | (0x0F & (bsel_best >> 8));

	//reset CTRL
//	this->usart->CTRLB = 0;
//	this->usart->CTRLA = 0;

	//set doublespeed operation
//	if (mul == 8)
//		this->usart->CTRLB |= USART_CLK2X_bm;
//
//	//reset counters
//	this->write_index = 0;
//	this->read_index = 0;
//	this->rx_index = 0;
//	this->rx_len = 0;
//	this->tx_index = 0;
//	this->tx_len = 0;
//
//	//set format
//	this->usart->CTRLC = USART_CHSIZE_8BIT_gc;
//
//	//clear interrupts
//	this->usart->STATUS = 0b11000000;
//
//	//enable RX & int
//	if (this->rx_buffer_size)
//	{
//		this->usart->CTRLB |= USART_RXEN_bm;
//	}
//	//enable RX & int
//	if (this->tx_buffer_size)
//	{
//		this->usart->CTRLB |= USART_TXEN_bm;
//	}
//
//	//disable RTS CTS
//	this->cts_port = NULL;
//	this->rts_port = NULL;
//
//	//this has to be before IRQ settings so the hander can find the objects
//	usarts[n] = this;
//
//	this->irq_priority = LOW;
//	this->SetInterruptPriority(LOW);
//
//	this->rx_ovf = false;
}

void Usart::Stop()
{
//	return (this->rx_len == 0);
}

void Usart::TxComplete()
{
	
}


/**
 * Test if RX buffer is empty (all received data read from RX buffer)
 *
 * \return true if RX buffer is empty
 */
bool Usart::isRxBufferEmpty()
{
	return !(Uart2_RcvCnt - Uart2_pos);
}


void Usart::ClearRxBuffer()
{
	Uart2_RcvCnt = 0;
	Uart2_pos = 0;
	//wait to send all data
//	this->rx_len = 0;
//	this->rx_index = 0;
}


/**
 * Set interrupt priority for this usart module
 *
 * \param p interrupt priority
 */
void Usart::SetInterruptPriority(uint8_t p)
{
//	switch (p)
//	{
//	case(HIGH):
//		this->irq_priority = 0b11;
//	break;
//	case(MEDIUM):
//		this->irq_priority = 0b10;
//	break;
//	case(LOW):
//		this->irq_priority = 0b01;
//	break;
//	case(NONE):
//		this->irq_priority = 0b00;
//	break;
//	}
//
//	this->usart->CTRLA &= 0b11001100;
//
//	if (this->rx_buffer_size)
//		this->usart->CTRLA |= this->irq_priority << 4;
//
//	if (this->tx_buffer_size)
//		this->usart->CTRLA |= this->irq_priority << 0;
}

/**
 * Write character to TX buffer
 *
 * \param c character to write
 */
void Usart::Write(uint8_t c)
{
	Uart2SendHex(c);
//	while (this->tx_len == this->tx_buffer_size);
//
//	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
//	{
//		if (this->tx_len || !(this->usart->STATUS & USART_DREIF_bm))
//		{
//			cli();
//			this->tx_len++;
//			this->tx_buffer[(this->write_index)++] = c;
//			sei();
//			if (this->write_index == this->tx_buffer_size)
//				this->write_index = 0;
//
//			//enable DRE interupts
//			this->usart->CTRLA |= this->irq_priority << 0;
//		}
//		else
//		{
//			this->usart->DATA = c;
//		}
//	}
}

/**
 * Read character from RX buffer
 *
 * \return character form RX buffer
 * \note this function will block if there is no character in RX buffer (use isRxBufferEmpty or Peek for non blocking behavior)
 */
uint8_t Usart::Read()
{
	uint8_t c;
	
	c = Uart2_Buff[Uart2_pos++];
	
	if(Uart2_RcvCnt == Uart2_pos){
		Uart2_RcvCnt = Uart2_pos = 0;
	}
	
//
////	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
//	{
//
//		while (this->rx_len == 0);
//
//		c = this->rx_buffer[(this->read_index)++];
//		if (this->read_index == this->rx_buffer_size)
//			this->read_index = 0;
//
//		(this->rx_len)--;
//
//		//Buffer freed -> CTS active
//		if (this->cts_port != NULL)
//		{
//			if (this->rx_len < this->cts_threshold)
//				GpioWrite(this->cts_port, this->cts_pin, this->cts_active);
//		}
//	}

	return c;

}

