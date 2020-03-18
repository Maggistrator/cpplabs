#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <SDL/SDL.h>
#include <stack>

/**
* Класс графика функции от одного аргумента
*/
class Graphic
{
    public:
        Graphic(SDL_Surface *sf, float (*func)(float), float a, float b);
        /**Рисует график*/
        void draw();
        /**Возвращает установленный шаг аргумента*/
        float getdx();
        /**Задает шаг аргумента, если это не 0*/
        void setdx(float dx);
        /**Задает интервал, на котором строится график*/
        void setGraphicInterval(float a, float b);
        /**Возвращает левую границу интервала, на котором строится график*/
        float getA();
        /**Возвращает правую границу интервала, на котором строится график*/
        float getB();
        /**точка, с координатами (x,y)*/
        typedef struct point {
            int x, y;
        } Point;
        //void addPointsOfFracture(point p...);  работа с точками разрыва
        //void addIntervalOfFracture(point a, point b);
        virtual ~Graphic();

    protected:

    private:
        SDL_Surface *sf;//место отрисовки графика
        float scaleFactor;//коэффициент масштабирования графика, чтобы он занимал все окно
        float a, b;//границы интервала построения графика
        float dx = 1; //Приращение аргумента | Шаг построения графика
        //Указатель на функцию, график которой следует построить
        float (*func)(float);
        /* Раскомментить на средний уровень
         * stack <point> pointsOfFracture;
        */
        //пересчитывает координаты от левого верхнего угла на левый нижний
        void convertCoords(float*, float*);
};

#endif // GRAPHIC_H
