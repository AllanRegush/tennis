#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct Window {
  SDL_Window *window;
  SDL_Surface *surface;
  SDL_Renderer *renderer;
} Window;

typedef struct Vec2D {
  int x;
  int y;
} Vec2D;

typedef struct Ball {
  Vec2D vec;
  Vec2D deltaVec;
} Ball;

typedef struct Paddle {
  Vec2D vec;
  Vec2D dVec;
} Paddle;


static Ball ball;
static Paddle paddle1;
static bool quit;

Window window;

bool init() {
  bool success = true;
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    success = false;
    SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    window.window = SDL_CreateWindow("Tennis",
				     SDL_WINDOWPOS_UNDEFINED,
				     SDL_WINDOWPOS_UNDEFINED,
				     SCREEN_WIDTH,
				     SCREEN_HEIGHT,
				     SDL_WINDOW_SHOWN);

    if(!window.window) {
      success = false;
      SDL_Log("Window could not be created SDL_Error %s\n", SDL_GetError());
    } else {
      window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);
    }
    ball.deltaVec.x = 2;
    ball.deltaVec.y = 1;
    paddle1.vec.x = 10;
    paddle1.vec.y = 10;
  }
  return success;
}

void update() {
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0) {
    if(e.type == SDL_QUIT) {
      quit = true;
    }
  }
  if(ball.vec.x < 0 || ball.vec.x+10 > SCREEN_WIDTH) {
    ball.deltaVec.x *= -1;
  }
  if(ball.vec.y < 0 || ball.vec.y+10 > SCREEN_HEIGHT) {
    ball.deltaVec.y *= -1;
  }

  ball.vec.x += ball.deltaVec.x;
  ball.vec.y += ball.deltaVec.y;
}

void drawPaddle() {
  SDL_Rect rect;
  rect.x = paddle1.vec.x;
  rect.y = paddle1.vec.y;
  rect.w = 10;
  rect.h = 40;
  SDL_SetRenderDrawColor(window.renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(window.renderer, &rect);
}

void drawBall() {
  SDL_Rect rect;
  rect.x = ball.vec.x;
  rect.y = ball.vec.y;
  rect.w = 10;
  rect.h = 10;
  SDL_SetRenderDrawColor(window.renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(window.renderer, &rect);
}

void render() {
  SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(window.renderer);
  drawBall();
  drawPaddle();
  SDL_RenderPresent(window.renderer);
}
  

int main(int argc, char* argv[]) {
  init();
  quit = false;
  while(!quit) {
    update();
    render();
    SDL_Delay(30);
  }
  
  return 0;
}
