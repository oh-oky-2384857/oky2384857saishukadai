#include"errorCode.h"
#include <fstream>

//エラーコード出力用;
std::ostream& operator<< (std::ostream& os, const errorCode code) {
	os << "errorCode { " << (int)code << "}\n";
	return os;
}

//エラーソース出力用;
std::ostream& operator<< (std::ostream& os, const errorSource source) {
	os << "errorCode { " << (int)source << "}\n";
	return os;
}


//エラーデータ出力用;
std::ostream& operator<< (std::ostream& os, const errorData data) {
	os << data.code << data.source;
	os << "note {" << data.note << "}";
	return os;
}