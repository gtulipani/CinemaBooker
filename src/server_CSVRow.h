#ifndef __CSV_ROW_H__
#define __CSV_ROW_H__

#include <string>
#include <vector>

class CSVRow {
private:
	std::vector <std::string> m_data;
public:
	std::string const &operator[](std::size_t index) const;

	std::size_t size() const;

	void readNextRow(std::istream &str);
};


#endif //__CSV_ROW_H__
