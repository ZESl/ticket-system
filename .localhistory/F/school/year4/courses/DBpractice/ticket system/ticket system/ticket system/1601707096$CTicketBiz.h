// Ticket management class is used to save the movie ticket information.
class CTicketBiz
{
public:
	CTicketBiz();
	~CTicketBiz();

	void GenerateTicket(int);		//Generate the ticket.Initialize the movie ticket array.
	int GetRandTicket();		//Get a ticket randomly
	int GetBalanceNum();		//Get the remaining ticket number
};
