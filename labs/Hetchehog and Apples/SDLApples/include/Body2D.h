#ifndef BODY2D_H
#define BODY2D_H
#ifndef <SDL/SDL.h>
#include <SDL/SDL.h>

class Body2D
{
    public:
        /** Default constructor */
        Body2D();
        /** Default destructor */
        virtual ~Body2D();

        /** Возвращает вес тела
         * \return вес тела
         */
        unsigned int Getweight() { return m_weight; }

        /** Задает вес тела, но не менее 0
         * \param val новый вес тела
         */
        void Setweight(unsigned int val) { m_weight = val; }

        /** Возвращает скорость тела
         * \return скорость тела
         */
        float Getvelocity() { return m_velocity; }

        /** Задает скорость тела
         * \param val скорость тела
         */
        void Setvelocity(float val) { m_velocity = val; }

        /** Возвращает указатель на прямоугольник размеров тела
         * \return указатель на размеры тела
         */
        SDL_Rect Getbounds() { return m_bounds; }

        /** Позволяет задать размеры тела
         * \param val новые размеры тела
         */
        void Setbounds(SDL_Rect val) { m_bounds = val; }
        /** Access m_image
         * \return The current value of m_image
         */
        SDL_Surface Getimage() { return m_image; }
        /** Set m_image
         * \param val New value to set
         */
        void Setimage(SDL_Surface val) { m_image = val; }

    protected:

    private:
        unsigned int m_weight; //!< Member variable "m_weight"
        float m_velocity; //!< Member variable "m_velocity"
        SDL_Rect m_bounds; //!< Member variable "m_bounds"
        SDL_Surface m_image; //!< Member variable "m_image"
};

#endif // BODY2D_H
