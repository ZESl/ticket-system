#include "CTicketBiz.h"
#include <stdlib.h>      

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
	bool flag = true;
	int num = rand() % m_nTotalNum + 1;

	while (flag) {
		num = rand() % m_nTotalNum + 1;
		// ���m_pTicket�Ʊ��Ϊnum��Ʊ�����ڣ�return num��flag��Ϊfalse������ѭ��
		for (int i = 0; i < m_pTicket; i++) {
			if (num ) {
				flag = false;
				// remove num from array
				break;
			}
		}
	}

	return num;
}

int CTicketBiz::GetBalanceNum()
{
	return 0;
}
