// Ticket management class is used to save the movie ticket information.
class CTicketBiz
{
public:
	CTicketBiz(int *,int);
	~CTicketBiz();

	void GenerateTicket(int);		//Generate the ticket.Initialize the movie ticket array.
	int GetRandTicket();		//Get a ticket randomly
	int GetBalanceNum();		//Get the remaining ticket number

private:
	int* m_pTicket;		//Point to the array that saves the ticket information
	int	m_nTotalNum;		//Total ticket number
	int	m_nSoldNum;		//Sold ticket number
	int	m_nBalanceNum;		//Remaining ticket number
};
