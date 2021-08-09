//#include "render.h"
//
//
//void renderNums(SDL_Renderer* renderer, tile board[][N])
//{
//    TTF_Font* font = NULL;
//    font = TTF_OpenFont("OpenSans-Regular.ttf", 45);
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < N; j++)
//        {
//            string c = to_string(board[i][j].value);
//            if (c != "0")
//                rendererTTF(renderer, font, c, 20 + i * REC_SIZE, j * REC_SIZE, BLACK);
//        }
//    }
//}
//
//// draw matrix
//void drawMatrix(SDL_Renderer* &renderer)
//{
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
//    for (int i = 0; i <= N; i++)
//    {
//        for (int j = 0; j <= N; j++)
//        {
//            SDL_Rect rect;
//            rect.x = i * REC_SIZE;
//            rect.y = j * REC_SIZE;
//            rect.w = REC_SIZE;
//            rect.h = REC_SIZE;
//            SDL_RenderFillRect(renderer, &rect);
//        }
//    }
//}
//
////draw line
//void drawLine(SDL_Renderer* &renderer)
//{
//    //matrix 9x9
//    SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
//    for (int i = 0; i <= N; i++)
//    {
//        SDL_RenderDrawLine(renderer, i * REC_SIZE, 0, i * REC_SIZE, REC_SIZE * N);
//
//        SDL_RenderDrawLine(renderer, 0, i * REC_SIZE, REC_SIZE * N, i * REC_SIZE);
//    }
//
//    //draw matrix 3x3 bold
//    SDL_SetRenderDrawColor(renderer, 51, 0, 0, 255);
//    for (int i = 0; i <= N / 3; i++)
//    {
//        SDL_RenderDrawLine(renderer, 3 * i * REC_SIZE, 0, 3 * i * REC_SIZE, REC_SIZE * N);
//
//        SDL_RenderDrawLine(renderer, 0, 3 * i * REC_SIZE, REC_SIZE * N, 3 * i * REC_SIZE);
//    }
//}
//
//void drawSelect(SDL_Renderer* &renderer, tile board[][N], int x, int y)
//{
//    SDL_SetRenderDrawColor(renderer, 220, 242, 244, 0); // green
//    for (int i = 0; i < N; i++)
//    {
//        SDL_Rect c;
//        c.x = x * REC_SIZE;
//        c.y = i * REC_SIZE;
//        c.w = REC_SIZE;
//        c.h = REC_SIZE;
//        SDL_RenderFillRect(renderer, &c);
//
//        SDL_Rect r;
//        r.x = i * REC_SIZE;
//        r.y = y * REC_SIZE;
//        r.w = REC_SIZE;
//        r.h = REC_SIZE;
//        SDL_RenderFillRect(renderer, &r);
//    }
//
//    SDL_SetRenderDrawColor(renderer, 175, 239, 245, 1); // green: selected cell
//    SDL_Rect cell;
//    cell.x = x * REC_SIZE;
//    cell.y = y * REC_SIZE;
//    cell.w = REC_SIZE;
//    cell.h = REC_SIZE;
//    SDL_RenderFillRect(renderer, &cell);
//}
