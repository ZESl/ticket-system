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
		if (m_pTicket[num-1]==1) {
			flag = false;
			// remove num from array
			m_pTicket[num - 1] = 0;
			m_nSoldNum++;
			m_nBalanceNum--;
			break;
		}
	}
	return num;
}

int CTicketBiz::GetBalanceNum()
{
	return m_nBalanceNum;
}
