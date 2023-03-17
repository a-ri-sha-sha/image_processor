#include "cow_string.h"

CowString::MyString::MyString(const std::string &str) {
    count_ = 1;
    str_ = str;
}
int64_t CowString::MyString::GetCount() {
    return count_;
}
void CowString::MyString::AddCount(int x) {
    count_ += x;
}
char *CowString::MyString::GetData() {
    return str_.data();
}
size_t CowString::MyString::GetSize() {
    return str_.size();
}
char CowString::MyString::GetChar(size_t i) {
    return str_.at(i);
}
void CowString::MyString::SetStr(std::string str) {
    str_ = str;
}
std::string CowString::MyString::GetStr() {
    return str_;
}
CowString::MyString::operator std::string_view() {
    return static_cast<std::string_view>(str_);
}
CowString::MyChar::MyChar(size_t index, CowString *str) {
    index_ = index;
    str_ = str;
}
CowString::MyChar &CowString::MyChar::operator=(char val) {
    if (str_->my_string_->GetChar(index_) == val) {
        return *this;
    }
    if (str_->my_string_->GetCount() == 1) {
        std::string ans = str_->my_string_->GetStr();
        ans[index_] = val;
        str_->my_string_->SetStr(ans);
        return *this;
    }
    str_->my_string_->AddCount(-1);
    std::string ans = str_->my_string_->GetStr();
    ans[index_] = val;
    str_->my_string_ = new MyString(str_->my_string_->GetStr());
    str_->my_string_->SetStr(ans);
    return *this;
}
CowString::MyChar::operator char() const {
    return str_->my_string_->GetChar(index_);
}
CowString::Iterator::Iterator(size_t index, CowString *str) {
    index_ = index;
    str_ = str;
}
CowString::Iterator &CowString::Iterator::operator++() {
    ++index_;
    return *this;
}
CowString::Iterator &CowString::Iterator::operator--() {
    --index_;
    return *this;
}
CowString::MyChar CowString::Iterator::operator*() const {
    return MyChar(index_, str_);
}
bool CowString::Iterator::operator==(const CowString::Iterator &val) const {
    return (index_ == val.index_ && str_ == val.str_);
}
bool CowString::Iterator::operator!=(const CowString::Iterator &val) const {
    return !(index_ == val.index_ && str_ == val.str_);
}
CowString::ConstIterator::ConstIterator(size_t index, const CowString *str) {
    index_ = index;
    str_ = str;
}
CowString::ConstIterator &CowString::ConstIterator::operator++() {
    ++index_;
    return *this;
}
CowString::ConstIterator &CowString::ConstIterator::operator--() {
    --index_;
    return *this;
}
char CowString::ConstIterator::operator*() const {
    return str_->At(index_);
}
bool CowString::ConstIterator::operator==(const CowString::ConstIterator &val) const {
    return (index_ == val.index_ && str_ == val.str_);
}
bool CowString::ConstIterator::operator!=(const CowString::ConstIterator &val) const {
    return !(index_ == val.index_ && str_ == val.str_);
}
CowString::CowString(std::string str) {
    my_string_ = new MyString(str);
}
CowString::CowString(const CowString &str) {
    my_string_ = str.my_string_;
    my_string_->AddCount(1);
}
CowString::CowString(CowString &&str) {
    my_string_ = str.my_string_;
    str.my_string_ = nullptr;
}

CowString::~CowString() {
    if (my_string_->GetCount() == 1) {
        delete my_string_;
    } else {
        my_string_->AddCount(-1);
    }
}
char *CowString::GetData() const {
    return my_string_->GetData();
}
CowString::ConstIterator CowString::begin() const {
    return CowString::ConstIterator(0, this);
}
CowString::ConstIterator CowString::end() const {
    return CowString::ConstIterator(my_string_->GetSize(), this);
}
CowString::Iterator CowString::begin() {
    return CowString::Iterator(0, this);
}
CowString::Iterator CowString::end() {
    return CowString::Iterator(my_string_->GetSize(), this);
}
char CowString::At(size_t i) const {
    return my_string_->GetChar(i);
}
CowString::MyChar CowString::operator[](size_t i) {
    return CowString::MyChar(i, this);
}
CowString &CowString::operator+=(const CowString &val) {
    if (my_string_->GetCount() == 1) {
        my_string_->SetStr(my_string_->GetStr() + val.my_string_->GetStr());
    } else {
        my_string_->AddCount(-1);
        my_string_ = new MyString(my_string_->GetStr() + val.my_string_->GetStr());
    }
    return *this;
}
CowString &CowString::operator+=(std::string_view val) {
    if (my_string_->GetCount() == 1) {
        my_string_->SetStr(my_string_->GetStr() + static_cast<std::string>(val));
    } else {
        my_string_->AddCount(-1);
        my_string_ = new MyString(my_string_->GetStr() + static_cast<std::string>(val));
    }
    return *this;
}
CowString CowString::operator+(CowString &val) const {
    return CowString(my_string_->GetStr() + val.my_string_->GetStr());
}
CowString CowString::operator+(std::string_view val) const {
    return CowString(my_string_->GetStr() + static_cast<std::string>(val));
}
bool CowString::operator==(CowString &val) const {
    return my_string_->GetStr() == val.my_string_->GetStr();
}
bool CowString::operator==(std::string_view val) const {
    return my_string_->GetStr() == static_cast<std::string>(val);
}
bool CowString::operator!=(CowString &val) const {
    return !(my_string_->GetStr() == val.my_string_->GetStr());
}
bool CowString::operator!=(std::string_view val) const {
    return !(my_string_->GetStr() == static_cast<std::string>(val));
}
CowString::operator std::string_view() const {
    return *my_string_;
}
bool operator==(const char *ch, const CowString &cow_str) {
    return cow_str.my_string_->GetStr() == ch;
}
CowString &CowString::operator=(const CowString &val) {
    if (my_string_->GetCount() == 1) {
        delete my_string_;
    } else {
        my_string_->AddCount(-1);
    }
    val.my_string_->AddCount(1);
    my_string_ = val.my_string_;
    return *this;
}
