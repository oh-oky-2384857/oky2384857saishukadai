#include"errorCode.h"
#include <fstream>

//�G���[�R�[�h�o�͗p;
std::ostream& operator<< (std::ostream& os, const errorCode code) {
	os << "errorCode { " << (int)code << "}\n";
	return os;
}

//�G���[�\�[�X�o�͗p;
std::ostream& operator<< (std::ostream& os, const errorSource source) {
	os << "errorCode { " << (int)source << "}\n";
	return os;
}


//�G���[�f�[�^�o�͗p;
std::ostream& operator<< (std::ostream& os, const errorData data) {
	os << data.code << data.source;
	os << "note {" << data.note << "}";
	return os;
}