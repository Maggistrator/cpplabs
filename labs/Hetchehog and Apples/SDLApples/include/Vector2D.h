#ifndef VECTOR2D_H
#define VECTOR2D_H
struct Vector2D{
    float x;
    float y;

    const bool operator==(const Vector2D& another_vector) const {
        return (another_vector.x == x) && (another_vector.y == y);
    }

    const Vector2D& operator+(const Vector2D& another_vector) const {
        Vector2D temp = *this;
        temp.x = x + another_vector.x;
        temp.y = y + another_vector.y;
        return temp;
    }

    const Vector2D& operator-(const Vector2D& another_vector) const {
        Vector2D temp = *this;
        temp.x = x - another_vector.x;
        temp.y = y - another_vector.y;
        return temp;
    }
};
#endif // VECTOR2D_H
