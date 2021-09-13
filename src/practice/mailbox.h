#ifndef MAILBOX_H_
#define MAILBOX_H_
#include <string>
#include <list>

typedef std::string _str;


namespace vsnc
{
	namespace bot
	{
		class MailBox
		{
		public:
			typedef struct User
			{
				_str			name;
				_str			tripcode;

				User operator=(const User& b)
				{
					User temp;
					this->name = b.name;
					this->tripcode = b.tripcode;
					return temp;
				};

				bool operator==(const User& b)
				{
					return (this->name == b.name && this->tripcode == b.tripcode) ? true : false;
				};
			}User;

			typedef struct Data
			{
				User			to_User;
				User			from_User;
				bool			secret = false;
				int				timestamp = -1;
				_str			message;
			}Data;

			typedef struct To
			{
				User			to_User;
				std::list<Data>	dataList;
			}To;

			typedef struct From
			{
				User			from_User;
				int				times;
			}From;
			MailBox() {};
			~MailBox() {};
			bool Send(Data data);
			void Read(User user,int num = 1);

		private:
			const int maxSize = 5;
			int check_full();
			std::list<To>	toLists;
			std::list<From> fromLists;



		};


	}
}



#endif // !MAILBOX
