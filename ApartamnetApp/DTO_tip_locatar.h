#pragma once
#include <string> 
using std::string;

class DTO_tip_locatar
{

private:
	string type;
	int cnt; 

public:
	DTO_tip_locatar() = default;
	DTO_tip_locatar(string type) :type{ type }{
		cnt = 1;
	}

	string get_type() const  {
		return type;
	}

	int get_cnt() const noexcept {
		return cnt;
	}

	void increase_cnt() noexcept {
		cnt++;
	}

};

