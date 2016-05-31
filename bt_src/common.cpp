#include "common.h"
#include "drivers/uart.h"
#include <string.h>


uint8_t hw_revision;

char *strcpy_P( char *, unsigned char *)
{
	return 0;
}

void GetID_str(char * id)
{
	
}

uint32_t task_get_ms_tick()
{
	return 00000000l;
}

//----------------------------------------------------------

DataBuffer::DataBuffer(uint16_t size)
{
	this->size = size;
	this->length = 0;
	this->write_index = 0;
	this->read_index = 0;

	this->data = new uint8_t[size];
	if (this->data == NULL)
	{
		this->size = 0;
	}
}

DataBuffer::~DataBuffer()
{

}


uint16_t DataBuffer::Read(uint16_t len, uint8_t * * data)
{
	(*data) = this->data + this->read_index;

	if (len > this->length)
		len = this->length;

	if (this->read_index + len > this->size)
		len = this->size - this->read_index;

	this->read_index = (this->read_index + len) % this->size;
	this->length -= len;

	return len;
}

bool DataBuffer::Write(uint16_t len, uint8_t * data)
{
	if (this->size - this->length < len)
		return false;

	if (this->write_index + len > this->size)
	{
		uint16_t first_len = this->size - this->write_index;
		memcpy(this->data + this->write_index, data, first_len);
		memcpy(this->data, data + first_len, len - first_len);
	}
	else
	{
		memcpy(this->data + this->write_index, data, len);
	}

	this->write_index = (this->write_index + len) % this->size;
	this->length += len;

	return true;
}

uint16_t DataBuffer::Length()
{
	return this->length;
}

void DataBuffer::Clear()
{
	this->length = 0;
	this->write_index = 0;
	this->read_index = 0;
}

//*****************



//***************************************************


volatile struct cfg_t config;


struct cfg_t config_ee;
