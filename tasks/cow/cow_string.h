#pragma once

#include <string>

class CowString {
public:
    class MyString {
    public:
        explicit MyString(const std::string& str);
        int64_t GetCount();
        char* GetData();
        void AddCount(int x);
        size_t GetSize();
        char GetChar(size_t i);
        void SetStr(std::string str);
        std::string GetStr();
        operator std::string_view();

    private:
        int64_t count_;
        std::string str_;
    };
    class MyChar {
    public:
        MyChar(size_t index, CowString* str);
        MyChar& operator=(char val);
        operator char() const;

    private:
        size_t index_;
        CowString* str_;
    };

    class Iterator {
    public:
        Iterator(size_t index, CowString* str);
        Iterator& operator++();
        Iterator& operator--();
        MyChar operator*() const;
        bool operator==(const Iterator& val) const;
        bool operator!=(const Iterator& val) const;

    private:
        size_t index_;
        CowString* str_;
    };

    class ConstIterator {
    public:
        ConstIterator(size_t index, const CowString* str);
        ConstIterator& operator++();
        ConstIterator& operator--();
        char operator*() const;
        bool operator==(const ConstIterator& val) const;
        bool operator!=(const ConstIterator& val) const;

    private:
        size_t index_;
        const CowString* str_;
    };

public:
    explicit CowString(std::string str);
    CowString(const CowString& str);
    CowString(CowString&& str);

public:
    char* GetData() const;
    ConstIterator begin() const;
    ConstIterator end() const;
    Iterator begin();
    Iterator end();
    char At(size_t i) const;
    MyChar operator[](size_t i);
    CowString& operator=(const CowString& val);
    CowString& operator+=(const CowString& val);
    CowString& operator+=(std::string_view val);
    CowString operator+(CowString& val) const;
    CowString operator+(std::string_view val) const;
    bool operator==(CowString& val) const;
    bool operator==(std::string_view val) const;
    bool operator!=(CowString& val) const;
    bool operator!=(std::string_view val) const;
    operator std::string_view() const;
    friend bool operator==(const char* ch, const CowString& cow_str);

private:
    MyString* my_string_;
};
