#include "CTicketBiz.h"



CTicketBiz::CTicketBiz(int *pTicket, int nTotalNum)
{
	m_pTicket = pTicket;		//Point to the array that saves the ticket information
	m_nTotalNum = nTotalNum;		//Total ticket number
	m_nSoldNum = 0;		//Sold ticket number
	m_nBalanceNum = nTotalNum;		//Remaining ticket number
}


CTicketBiz::~CTicketBiz()
{
}

void CTicketBiz::GenerateTicket(int)
{
}

int CTicketBiz::GetRandTicket()
{
	return 0;
}

int CTicketBiz::GetBalanceNum()
{
	return 0;
}
