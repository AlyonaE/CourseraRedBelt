#include<iostream>
#include <string>
#include <map>
#include <queue>

struct HotelStatus {
	int rooms_count = 0;
	int clients_count = 0;
	std::map<int, int> clients_repeated;
};

struct BookingRecord {
	long long time;
	std::string hotel_name;
	int client_id;
	int room_count;
};

class BookingSystem {
public:
	BookingSystem() {};
	void Book(const long long time, const std::string& hotel_name, const int client_id, const int room_count) {
		DeleteOldRecords(time);
		//to hotel info
		if (_hotel_info.find(hotel_name) == _hotel_info.end()) {
			std::map<int, int> loc;
			loc[client_id] = 1;
			_hotel_info[hotel_name] = { room_count, 1, loc};
		}
		else {
			HotelStatus& loc = _hotel_info[hotel_name];
			loc.rooms_count += room_count;
			if (loc.clients_repeated.find(client_id) == loc.clients_repeated.end()) {
				loc.clients_count++;
			}
			loc.clients_repeated[client_id] += 1;
		}
		//to time line
		_time_line.push({ time, hotel_name, client_id, room_count });
	}
	int GetClientsCount(const std::string& hotel_name) {
		if (_hotel_info.find(hotel_name) == _hotel_info.end()) {
			return 0;
		}
		return _hotel_info[hotel_name].clients_count;
	}
	int GetBookedRoomsCount(const std::string& hotel_name) {
		if (_hotel_info.find(hotel_name) == _hotel_info.end()) {
			return 0;
		}
		return _hotel_info[hotel_name].rooms_count;
	}
private:
	std::map<std::string, HotelStatus> _hotel_info;
	std::queue<BookingRecord> _time_line;

	void DeleteOldRecords(const long long time) {
		int i = 0;
		int time_size = _time_line.size();
		while (i < time_size) {
			BookingRecord cur_record = _time_line.front();
			if (cur_record.time <= time - 86400) {
				//actualize hotel_info;
				HotelStatus& loc = _hotel_info[cur_record.hotel_name];
				loc.rooms_count -= cur_record.room_count;
				if (loc.clients_repeated[cur_record.client_id] == 1) {
					loc.clients_count--;
					loc.clients_repeated.erase(cur_record.client_id);
				}
				else {
					loc.clients_repeated[cur_record.client_id]--;
				}
				_time_line.pop();
			}
			else {
				return;
			}
			i++;
		}
	}
};


int main() {
	BookingSystem booking;
	int query_count;
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
	std::cin >> query_count;
	for (int i = 0; i < query_count; i++) {
		std::string query_type;
		std::cin >> query_type;
		if (query_type == "BOOK") {
			long long time;
			std::string hotel_name;
			int client_id;
			int room_count;
			std::cin >> time >> hotel_name >> client_id >> room_count;
			booking.Book(time, hotel_name, client_id, room_count);
		}
		else if (query_type == "CLIENTS") {
			std::string hotel_name;
			std::cin >> hotel_name;
			std::cout << booking.GetClientsCount(hotel_name) << "\n";
		}
		else if (query_type == "ROOMS"){
			std::string hotel_name;
			std::cin >> hotel_name;
			std::cout << booking.GetBookedRoomsCount(hotel_name) << "\n";
		}
	}

	return 0;
}