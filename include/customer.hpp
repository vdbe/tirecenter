#pragma once
#include <string>

class Customer {
	private:
		std::string name;
		std::string address;
		char type;

	public:
		std::string getName(void);
		void setName(std::string);

		std::string getAddress(void);
		void setAddress(std::string);

		char getType(void);
		void setType(char);
};
