#pragma once
#include <vector>
#include <string>

class Pack 
{
    public:
        Pack();
        Pack(int _first, int _second, int _third); 
        Pack(int _first, bool _first_negated, int _second, bool _second_negated, int _third, bool _third_negated); 
        ~Pack();

        bool is_staisfied_by(const std::vector<bool>* genome);

        int getFirst();
        int getSecond();
        int getThird();

        bool first_getIsNegated();
        bool second_getIsNegated();
        bool third_getIsNegated();

        void setFirst(int _first);
        void setSecond(int _second);
        void setThird(int _third);

        void first_setIsNegated(bool _first);
        void second_setIsNegated(bool _first);
        void third_setIsNegated(bool _first);

        std::string toString();
    private:
        int first;
        int second;
        int third;
        bool first_isNegated;
        bool second_isNegated;
        bool third_isNegated;

};
