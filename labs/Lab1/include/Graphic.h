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
        Graphic(SDL_Surface *sf, int (*func)(int), float a, float b);
        Graphic(SDL_Surface *sf, double (*func)(double), float a, float b);
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
        bool isIntFunctPassed;//флаг, указывающий на то, какого типа функция хранится в UniversalFunction
        //Указатель на функцию, график которой следует построить
        union UniversalFunction{
            int (*integer)(int);
            double (*real)(double);
        } func;
        /* Раскомментить на средний уровень
         * stack <point> pointsOfFracture;
        */
        //пересчитывает координаты от левого верхнего угла на левый нижний
        Point * convertCoords(Point *pt);
};

#endif // GRAPHIC_H
