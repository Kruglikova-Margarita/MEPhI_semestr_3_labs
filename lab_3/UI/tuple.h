#ifndef LAB_3SEM_3_TUPLE_H
#define LAB_3SEM_3_TUPLE_H

template<typename T1, typename T2, typename T3>
class Tuple {
private:
    T1 value_1_;
    T2 value_2_;
    T3 value_3_;

public:
    Tuple() = default;
    Tuple(T1 value1, T2 value2, T3 value3) noexcept : value_1_(value1), value_2_(value2), value_3_(value3) {}

    T1 getValue1() const noexcept {
        return value_1_;
    }

    T2 getValue2() const noexcept {
        return value_2_;
    }

    T3 getValue3() const noexcept {
        return value_3_;
    }

    bool operator !=(Tuple<T1, T2, T3>& tuple) const noexcept {
        if ((value_1_ == tuple.value_1_) && (value_2_ == tuple.value_2_) && (value_3_ == tuple.value_3_))
            return false;

        return true;
    }
};

#endif //LAB_3SEM_3_TUPLE_H
