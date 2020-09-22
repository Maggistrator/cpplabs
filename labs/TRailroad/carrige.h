#ifndef CARRIAGE_H_INCLUDED
#define CARRIAGE_H_INCLUDED

///Вагон
class carrige
{
    public:
    static const int CARGO = 0, PASSENGER = 1;

    int id;
    int type;

    carrige(int t, int id){
        type = t;
        this->id = id;
    }
};

#endif // CARRIAGE_H_INCLUDED
