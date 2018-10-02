#include "serverCSVIterator.h"

std::istream &operator>>(std::istream &str, CSVRow &data) {
	data.readNextRow(str);
	return str;
}

CSVIterator::CSVIterator(std::istream &str) :
		m_str(str.good() ? &str : nullptr) {
	++(*this);
}

CSVIterator::CSVIterator() : m_str(nullptr) {}

CSVIterator &CSVIterator::operator++() {
	if (m_str) {
		if (!((*m_str) >> m_row)) {
			m_str = nullptr;
		}
	}
	return *this;
}

const CSVIterator CSVIterator::operator++(int) {
	CSVIterator tmp(*this);
	++(*this);
	return tmp;
}

CSVRow const &CSVIterator::operator*() const {
	return m_row;
}

CSVRow const *CSVIterator::operator->() const {
	return &m_row;
}

bool CSVIterator::operator==(CSVIterator const &rhs) {
	return ((this == &rhs) || ((this->m_str == nullptr) && (rhs.m_str ==
			nullptr)));
}

bool CSVIterator::operator!=(CSVIterator const &rhs) {
	return !((*this) == rhs);
}
