#include <iostream>
#include <SDL.h>
#include "suzanne_vertices.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define PIXEL_SCALE 100;


struct point2d {
    float x;
    float y;
};


point2d perspectiveDivision(vertice v)
{
    point2d p;

    // Nos aseguramos de aplicar el pixel_scale por si z fuese cero.
    p.x = v.x * PIXEL_SCALE;
    p.y = v.y * PIXEL_SCALE;

    if (v.z != 0) {
        p.x = (v.x / v.z) * PIXEL_SCALE;
        p.y = (v.y / v.z) * PIXEL_SCALE;
    }

    // Centramos el punto en pantalla
    p.x+= WINDOW_WIDTH/2;
    p.y+= WINDOW_HEIGHT/2;

    return p;
}

vertice mueveVertice(vertice v, float x, float y, float z)
{
    vertice vt;
    vt.x = v.x + x;
    vt.y = v.y + y;
    vt.z = v.z + z;

    return vt;
}

int main() {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    // Limpiamos la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    loadVertices(); // suzanne_vertices.h

    // Seleccionamos color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Dibujamos cada vértice en el render
    for (int i = 0; i<=1448; i++) {
        v[i] = mueveVertice(v[i], 2, 2, 3);
        point2d p = perspectiveDivision(v[i]);
        SDL_RenderDrawPoint(renderer, p.x, p.y);
    }

    // Actualizamos pantalla
    SDL_RenderPresent(renderer);

    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
