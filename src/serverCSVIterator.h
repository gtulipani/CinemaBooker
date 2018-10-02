#ifndef __CSV_ITERATOR_H__
#define __CSV_ITERATOR_H__

#include <istream>
#include "serverCSVRow.h"

class CSVIterator {
public:
	typedef std::input_iterator_tag     iterator_category;
	typedef CSVRow                      value_type;
	typedef std::size_t                 difference_type;
	typedef CSVRow*                     pointer;
	typedef CSVRow&                     reference;

	explicit CSVIterator(std::istream& str);
	CSVIterator();

	// Pre Increment
	CSVIterator& operator++();
	// Post increment
	const CSVIterator operator++(int);

	CSVRow const& operator*() const;
	CSVRow const* operator->() const;

	bool operator==(CSVIterator const& rhs);
	bool operator!=(CSVIterator const& rhs);

private:
	std::istream*       m_str;
	CSVRow              m_row;
};


#endif //__CSV_ITERATOR_H__
