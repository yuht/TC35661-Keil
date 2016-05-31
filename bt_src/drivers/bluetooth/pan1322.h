/*
 * pan_lite.h
 *
 *  Created on: 25.9.2014
 *      Author: horinek
 */

#ifndef PAN1322_H_
#define PAN1322_H_
class pan1322
{
public:

//	Usart * usart;

	void Init(void * uart);
	void TxResume();

	void Step();
	void SendString(void * str);

};

#endif /* PAN_LITE_H_ */
