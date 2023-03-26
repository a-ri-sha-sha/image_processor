//
// Created by Arina Shaydeman on 09.03.2023.
// Шаблонная версия matrix
// Когда мы делаем шаблонную заготовку, пишем все в h файле

#ifndef UNTITLED1_TMATRIX_H
#define UNTITLED1_TMATRIX_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class TMatrix {
public:
    // ожидаемые (стандартные) для типов данных производнных от T
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = value_type&;

    class Row {
        friend class TMatrix<T>;

    public:
        T& operator[](size_t colnum) const {
            return matrix_->operator()(rownum_, colnum);
        }

        size_t Size() const {
            return matrix_->GetCollsNum();  //
        }

    protected:
        Row(TMatrix<T>* m, size_t rownum) : rownum_(rownum), matrix_(m) {
        }

    protected:
        size_t rownum_;
        TMatrix<T>* matrix_;
    };

    class ConstRow {
        friend class TMatrix<T>;

    public:
        /*const int&*/ T operator[](size_t colnum) const {
            return matrix_->operator()(rownum_, colnum);
        }

        size_t Size() const {
            return matrix_->cols_num_;
        }

    protected:
        ConstRow(const TMatrix<T>* m, size_t rownum) : rownum_(rownum), matrix_(m) {
        }

    protected:
        size_t rownum_;
        const TMatrix<T>* matrix_;
    };

    class Col {
        friend class Matrix;

    public:
        T& operator[](size_t rownum) const {
            return matrix_->operator()(rownum, colnum_);
        }

        size_t Size() const {
            return matrix_->rows_num_;
        }

    protected:
        Col(TMatrix<T>* m, size_t colnum) : colnum_(colnum), matrix_(m) {
        }

    protected:
        size_t colnum_;
        TMatrix<T>* matrix_;
    };

    class ConstCol {
        friend class TMatrix<T>;

    public:
        /*const int&*/ T operator[](size_t rownum) const {
            return matrix_->operator()(rownum, colnum_);
        }

        size_t Size() const {
            return matrix_->rows_num_;
        }

    protected:
        ConstCol(const TMatrix<T>* m, size_t colnum) : colnum_(colnum), matrix_(m) {
        }

    protected:
        size_t colnum_;
        const TMatrix<T>* matrix_;
    };

public:
    // Если мы явным образом не создали никаких конструкторов, то будет создан конструктор по умолчанию,
    // который делает ничего.

    // Matrix() = delete;
    // Такая запись позволяет удалить дефолтные, создаваемые компилятором, члены класса.

    TMatrix(const TMatrix<T>& other) {
        rows_num_ = other.rows_num_;
        cols_num_ = other.cols_num_;
        table_ = AllocateMatrix(rows_num_, cols_num_);
        for (size_t i = 0; i < rows_num_; ++i) {
            for (size_t j = 0; j < cols_num_; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
    }

    // Конструктор создаёт матрицу размера m x n и задаёт значение элементов по умолчанию
    // Если один из параметров не равен 0, то другой тоже. Иначе кидаем исключительную ситуацию
    TMatrix(size_t rows_num = 0, size_t cols_num = 0, T def = T{}) {
        if (rows_num == 0 && cols_num == 0) {
            rows_num_ = 0;
            cols_num_ = 0;
            table_ = nullptr;
            return;
        }

        if (rows_num == 0 || cols_num == 0) {
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }
        rows_num_ = rows_num;
        cols_num_ = cols_num;
        table_ = AllocateMatrix(rows_num_, cols_num_);

        // Нежизненно:
        for (size_t i = 0; i < rows_num; ++i) {
            for (size_t j = 0; j < cols_num; ++j) {
                this->operator()(i, j) = def;
            }
        }
    }

    ~TMatrix() {
        Clear();
    }

    // Возвращает i,j -й элемент матрицы
    T operator()(size_t i, size_t j) const {
        //        return table_[i * cols_num_ + j];
        return GetIJEl(table_, i, j, cols_num_);
    }

    T& operator()(size_t i, size_t j) {
        return GetIJEl(table_, i, j, cols_num_);
    }

    // Возвращает i-ю строку, обёрнутую в абстракцию
    Row operator[](size_t i) {
        /*typename*/ TMatrix<T>::Row ri(this, i);
        return ri;
    }

    ConstRow operator[](size_t i) const {
        return ConstRow(this, i);
    };

    T At(size_t i, size_t j) const {
        if (i < rows_num_ && j < cols_num_) {
            return this->operator()(i, j);
        }
        throw std::out_of_range("IOJ (matrix).");
    }

    reference At(size_t i, size_t j) {
        if (i < rows_num_ && j < cols_num_) {
            return this->operator()(i, j);
        }
        throw std::out_of_range("IOJ (matrix).");
    }

public:
    void Resize(size_t newColNum, size_t newRowNum, T def = T{}) {
        if (newColNum == 0 && newRowNum == 0) {
            Clear();
            return;
        }
        if (newRowNum == 0 || newColNum == 0) {
            throw std::invalid_argument("Can't make matrix with 0 rows or columns");
        }

        T* new_table = AllocateMatrix(newRowNum, newColNum);
        for (size_t i = 0; i < newRowNum; ++i) {
            for (size_t j = 0; j < newColNum; ++j) {
                if (i < rows_num_ && j < cols_num_) {
                    GetIJEl(new_table, i, j, newColNum) = GetIJEl(table_, i, j, cols_num_);
                } else {
                    GetIJEl(new_table, i, j, newColNum) = def;
                }
            }
        }
        delete[] table_;
        table_ = new_table;
        rows_num_ = newRowNum;
        cols_num_ = newColNum;
    }

    void Clear() {
        if (!table_) {
            return;
        }
        delete[] table_;
        table_ = nullptr;
        rows_num_ = 0;
        cols_num_ = 0;
    }
    void Swap(TMatrix<T>& rhv, TMatrix<T>& lhv) {
        std::swap(rhv.cols_num_, lhv.cols_num_);
        std::swap(rhv.rows_num_, lhv.rows_num_);
        std::swap(rhv.table_, lhv.table_);
    }
    TMatrix& operator=(const TMatrix<T>& lhv) {
        TMatrix<T> other(lhv);
        Swap(*this, other);
        return *this;
    }
    size_t GetRowsNum() const {
        return rows_num_;
    }

    size_t GetCollsNum() const {
        return cols_num_;
    }

    T* GetPtr() {
        return table_;
    }
    const T* GetPtr() const {
        return table_;
    }
    static reference GetIJEl(T* arr, size_t i, size_t j, size_t cols_num) {
        return arr[i * cols_num + j];
    }

protected:
    // Метод аллоцирует память в кучу для заданных параметров n и m
    // Методу от this ничего не надо, поэтому он статический
    static T* AllocateMatrix(size_t rows_n, size_t cols_m) {
        T* ans = new T[rows_n * cols_m];
        return ans;
    }

protected:
    pointer table_;  // читается тяжелее чем T*, но так написано в стандарте
    size_t rows_num_;
    size_t cols_num_;
};

#endif  // UNTITLED1_TMATRIX_H
