#ifndef option_h
#define option_h

template <typename T>
class Option {
private:
    inline static Option none_;
    inline static bool is_none_set_ = false;
    T value_;
    bool has_value_;

public:
    static const Option<T>& getNone() {
        if (!is_none_set_) {
            Option::none_ = Option();
            Option::is_none_set_ = true;
        }

        return Option::none_;
    }

    Option();
    Option(T data);
    Option(const Option& item);

    bool getHasValue() const;
    T get() const;
};



template<typename T>
Option<T>::Option() {
    has_value_ = false;
}

template<typename T>
Option<T>::Option(T data) {
    value_ = data;
    has_value_ = true;
}

template<typename T>
Option<T>::Option(const Option &item) {
    if (item.has_value_) {
        value_ = item.value_;
        has_value_ = true;
    } else
        has_value_ = false;
}

template<typename T>
bool Option<T>::getHasValue() const {
    return has_value_;
}

template<typename T>
T Option<T>::get() const {
    if (!has_value_)
        throw std::out_of_range("The value is not set\n");

    return value_;
}

#endif