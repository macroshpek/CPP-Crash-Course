#include <cstdio>
struct Logger {
	virtual ~Logger() = default;
	virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger {
	void log_transfer(long from, long to, double amount) override {
		printf("[cons] %ld -> %ld: %f\n", from, to, amount);
	}
};

struct FileLogger : Logger {
	void log_transfer(long from, long to, double amount) override {
		printf("[file] %ld -> %ld: %f\n", from, to, amount);
	}
};

struct AccountDatabase {
	virtual void extract(long int id, long double amount) = 0;
	virtual void set_sum(long int id, long double amount) = 0;
};

struct InMemoryAccountDatabase : AccountDatabase {
	void extract(long int id, long double amount) {
		printf("[extracted] %ld: %lf\n", id, amount);
	}
	void set_sum(long int id, long double amount) {
		printf("[setted] %ld: %lf\n", id, amount);
	}
};

/*struct Bank {                                             //example from book
	Bank(Logger& logger) : logger{ logger } { }
	void make_transfer(long from, long to, double amount) {
		logger.log_transfer(from, to, amount);
	}
private:
	Logger& logger;
};
int main() {
	ConsoleLogger logger;
	Bank bank{ logger }; 
	bank.make_transfer(1000, 2000, 49.95);
	bank.make_transfer(2000, 4000, 20.00);
}*/

struct Bank {
	Bank(Logger* logger, InMemoryAccountDatabase* database) : logger{ logger }, database(database) { }
	void make_transfer(long from, long to, double amount) {
		logger->log_transfer(from, to, amount);
	}
	void set_logger(Logger* new_logger) {
		logger = new_logger;
	}
	void extract_amount(long int id, long double amount) {
		database->extract(id, amount);
	}
	void set_sum(long int id, long double amount) {
		database->set_sum(id, amount);
	}
private:
	Logger* logger;
	InMemoryAccountDatabase* database;
};

int main() {
	ConsoleLogger console_logger;
	FileLogger file_logger;
	InMemoryAccountDatabase database;
	Bank bank(&console_logger, &database);
	bank.set_logger(&console_logger); 
	bank.make_transfer(1000, 2000, 49.95);
	bank.set_logger(&file_logger);
	bank.make_transfer(2000, 4000, 20.00);
	bank.extract_amount(111111, 100);
	bank.set_sum(1, 11);
}