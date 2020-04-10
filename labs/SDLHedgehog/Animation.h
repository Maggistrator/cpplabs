#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL/SDL.h>
#include <SDL_image.h>

class Animation
{

    private:
        int num = 0;            //number of frames
        int cf = 0;             //current frame
        //TODO: int framerate = 30;
        //TODO: bool cycled = false;
        SDL_Surface ** frames;  //array of frames pointers
        SDL_Rect image_size;    //common images size of this animation

        long prev_frm;

        void recalcVisibleRect(SDL_Surface * frame)
        {
            image_size.w = frame->w > image_size.w ? frame->w : image_size.w;
            image_size.h = frame->h > image_size.h ? frame->h : image_size.h;
        }

    public:
        Animation(){
            frames = (SDL_Surface**)malloc(sizeof(SDL_Surface*));
            image_size.x = 0;
            image_size.y = 0;
            image_size.w = 0;
            image_size.h = 0;
        }

        Animation(int num, SDL_Surface ** frames)
        {
            this->num = num > 0 ? num : 0;
            this->frames = frames;
            if(num > 0) {
                image_size.x = 0;
                image_size.y = 0;
                image_size.w = (*frames)->w;
                image_size.h = (*frames)->h;
            }
            prev_frm = SDL_GetTicks();
        }

        void render(SDL_Surface * target, SDL_Rect * position)
        {
            SDL_BlitSurface(*(frames+cf), NULL, target, position);

            if((SDL_GetTicks() - prev_frm) > 1000/(num * 2) )
            {
                prev_frm = SDL_GetTicks();
                cf++;
            }

            if(cf % num == 0) cf = 0;
        }

        SDL_Surface * loadFrame(const char* path)
        {
            SDL_Surface *image;
            image=IMG_Load(path);
            if(!image) {
                printf("error: %s\n", IMG_GetError());
                return NULL;
            } else{
                num++;
                frames = (SDL_Surface**)realloc(frames, sizeof(SDL_Surface*)*num);
                *(frames+num-1) = image;
                recalcVisibleRect(image);
                return image;
            }
        }

        //TODO: loadFramesRecursievly(FILE* directory){}

        void addFrame(SDL_Surface * frame)
        {
            num++;
            //TODO: добавить защиту от переполнения памяти, если вернется нулевой указатель
            frames = (SDL_Surface**)realloc(frames, sizeof(SDL_Surface*)*num);
            *(frames+num-1) = frame;
            recalcVisibleRect(frame);
        }

        void removeFrame(SDL_Surface * frame)
        {
            int i, j;
            for(i = 0, j = 0; i < num; i++){
                if(*(frames+i) != frame) j++;
                *(frames+j) = *(frames+i);
            }
            if(i > j){
                num = num - (i - j);
                frames = (SDL_Surface**)realloc(frames, sizeof(SDL_Surface*)*num);
            }
        }

        void removeFrame(int n)
        {
            if(n > num - 1 ||  n < 0) return;

            for(int i = 0, j = 0; i < num; i++){
                if(i != n) j++;
                *(frames+j) = *(frames+i);
            }
            num--;
            frames = (SDL_Surface**)realloc(frames, sizeof(SDL_Surface*)*num);
        }

        virtual ~Animation(){
            for(int i = 0; i < num; i++){
                SDL_FreeSurface(*(frames+i));
            }
            free(frames);
        }
};

#endif // ANIMATION_H
