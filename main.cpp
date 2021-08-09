#include "SDL_utils.h"
#include "board.h"
#include "ttf.h"
#include "render.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

#define N 9
#define REC_SIZE 60

const int SCREEN_WIDTH = REC_SIZE * N + 2;
const int SCREEN_HEIGHT = REC_SIZE * N + 2;

const SDL_Color BLACK = {0, 0, 0};
const SDL_Color PURPLE = {128, 0, 128};

void renderNums(SDL_Renderer* renderer, tile board[][N]);

void drawMatrix(SDL_Renderer* &renderer, tile board[][N]);

void drawLine(SDL_Renderer* &renderer);

void loadNums(tile board[][N], string filename);

void drawSelect(SDL_Renderer* &renderer, tile board[][N], int y, int x);

void redMatrix(SDL_Renderer* &renderer, tile board[][N]);

bool isSafe(tile board[][N], int row, int col, int num);

bool solveSudoku(tile board[][N], int row, int col);

void checkIsError(SDL_Renderer* &renderer, tile board[][N]);

void redCell(SDL_Renderer* &renderer, tile board[][N], int y, int x);

void clearActiveStates(tile board[][N]);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "SUDOKU");

    SDL_RenderClear(renderer);

    tile board[N][N];
    loadNums(board, "newboard.txt");

    drawMatrix(renderer, board);
    drawLine(renderer);

    initTTF(renderer);

    renderNums(renderer, board);

    SDL_RenderPresent(renderer);

    SDL_Event e;

    bool isRunning = true;

//    bool tileActive = false;
    if (solveSudoku(board, 0, 0))
    {
        cout << "\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << board[i][j].result << " ";
            }
            cout << endl;
        }
    }

    int x = -1, y = -1;

    while (isRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                isRunning = false;
                quitSDL(window, renderer);
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int X;
                int Y;
                SDL_GetMouseState(&X, &Y);
                if (X < 0 || X > SCREEN_WIDTH || Y < 0 || Y > SCREEN_HEIGHT)
                {
                    continue;
                }

                x = Y / REC_SIZE; // if have time, fix it here ( - backGround)
                y = X / REC_SIZE;
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    //row, col rectange choose
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
                    SDL_RenderClear(renderer);
                    drawMatrix(renderer, board);
                    drawSelect(renderer, board, x, y);
                    redCell(renderer, board, x, y);
                    drawLine(renderer);
                    renderNums(renderer, board);
                    SDL_RenderPresent(renderer);
                }
            }

            if (e.type == SDL_KEYDOWN && board[x][y].changed)
            {
                for (int i = 0; i < N + 1; i++)
                {
                    if ((e.key.keysym.sym == SDLK_0 + i))
                    {
                        cout << "Keybroad" << i << " ";
                        board[x][y].value = i;
                        if (board[x][y].value != 0 && board[x][y].value != board[x][y].result)
                        {
                            board[x][y].isError = true;
                            cout << board[x][y].isError << " ";
                        }
                        else
                        {
                            board[x][y].isError = false;
                        }

                        SDL_RenderClear(renderer);

                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
                        drawMatrix(renderer, board);

                        drawSelect(renderer, board, x, y);
                        redCell(renderer, board, x, y);
                        drawLine(renderer);
                        renderNums(renderer, board);
                        SDL_RenderPresent(renderer);
                    }
                }
            }
        }
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

// read file and assign value into board
void loadNums(tile board[][N], string filename)
{
    fstream file("newboard.txt");
    if (!file)
    {
        cout << "File not found" << endl;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file >> board[i][j].value;
            cout << board[i][j].value << " ";
            if (board[i][j].value == 0)
            {
                board[i][j].changed = true;
            }
            else
            {
                board[i][j].changed = false;
            }
            board[i][j].isError = false;
            board[i][j].result = board[i][j].value;
        }
        cout << endl;
    }

    cout << endl << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j].result << " ";
        }
        cout << endl;
    }
    file.close();
}

// render number
void renderNums(SDL_Renderer* renderer, tile board[][N])
{
    TTF_Font* font = NULL;
    font = TTF_OpenFont("OpenSans-Regular.ttf", 45);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            string c = to_string(board[i][j].value);
            if (c != "0" && board[i][j].changed == false)
                rendererTTF(renderer, font, c, 20 + j * REC_SIZE, i * REC_SIZE, BLACK);
            if (c != "0" && board[i][j].changed == true)
            {
                rendererTTF(renderer, font, c, 20 + j * REC_SIZE, i * REC_SIZE, PURPLE);
            }
        }
    }
}

// draw matrix
void drawMatrix(SDL_Renderer* &renderer, tile board[][N])
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            SDL_Rect rect;
            rect.x = j * REC_SIZE;
            rect.y = i * REC_SIZE;
            rect.w = REC_SIZE;
            rect.h = REC_SIZE;
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

//draw line
void drawLine(SDL_Renderer* &renderer)
{
    //matrix 9x9
    SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
    for (int i = 0; i <= N; i++)
    {
        SDL_RenderDrawLine(renderer, i * REC_SIZE, 0, i * REC_SIZE, REC_SIZE * N);

        SDL_RenderDrawLine(renderer, 0, i * REC_SIZE, REC_SIZE * N, i * REC_SIZE);
    }

    //draw matrix 3x3 bold
    SDL_SetRenderDrawColor(renderer, 51, 0, 0, 255);
    for (int i = 0; i <= N / 3; i++)
    {
        SDL_RenderDrawLine(renderer, 3 * i * REC_SIZE, 0, 3 * i * REC_SIZE, REC_SIZE * N);

        SDL_RenderDrawLine(renderer, 0, 3 * i * REC_SIZE, REC_SIZE * N, 3 * i * REC_SIZE);
    }
}

void drawSelect(SDL_Renderer* &renderer, tile board[][N], int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 220, 242, 244, 0); // green
    for (int i = 0; i < N; i++)
    {
        SDL_Rect c;
        c.x = y * REC_SIZE;
        c.y = i * REC_SIZE;
        c.w = REC_SIZE;
        c.h = REC_SIZE;
        SDL_RenderFillRect(renderer, &c);

        SDL_Rect r;
        r.x = i * REC_SIZE;
        r.y = x * REC_SIZE;
        r.w = REC_SIZE;
        r.h = REC_SIZE;
        SDL_RenderFillRect(renderer, &r);
    }

    SDL_SetRenderDrawColor(renderer, 175, 239, 245, 1); // green: selected cell
    SDL_Rect cell;
    cell.x = y * REC_SIZE;
    cell.y = x * REC_SIZE;
    cell.w = REC_SIZE;
    cell.h = REC_SIZE;
    SDL_RenderFillRect(renderer, &cell);

    redMatrix(renderer, board);
}

void redCell(SDL_Renderer* &renderer, tile board[][N], int x, int y)
{
    if (board[x][y].isError == true) // board[x][y].value != 0 && board[x][y].value != board[x][y].result
    {
        SDL_SetRenderDrawColor(renderer, 243, 162, 162, 255); // red
        SDL_Rect r;
        r.x = y * REC_SIZE;
        r.y = x * REC_SIZE;
        r.w = REC_SIZE;
        r.h = REC_SIZE;
        SDL_RenderFillRect(renderer, &r);
    }
}

void redMatrix(SDL_Renderer* &renderer, tile board[][N])
{
    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j].isError == true)
            {
                SDL_SetRenderDrawColor(renderer, 243, 162, 162, 255); // red
                SDL_Rect r;
                r.x = j * REC_SIZE;
                r.y = i * REC_SIZE;
                r.w = REC_SIZE;
                r.h = REC_SIZE;
                SDL_RenderFillRect(renderer, &r);
            }

        }
    }
}

void checkIsError(SDL_Renderer* &renderer, tile board[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j].value != 0 && board[i][j].value != board[i][j].result)
            {
                board[i][j].isError = true;
            }
            else
            {
                board[i][j].isError = false;
            }
        }
    }
}

bool isSafe(tile board[][N], int row, int col, int num)
{
    // checlk if we find the samw num in the similar row, return false
    for (int i = 0; i < N; i++)
    {
        if (board[row][i].result == num)
        {
            return false;
        }
    }

    // check if we find the same num in the similar col, return false
    for (int i = 0; i < N; i++)
    {
        if (board[i][col].result == num)
        {
            return false;
        }
    }

    // check if we find the same num in the particular 3*3 matrix, return false
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i + startRow][j + startCol].result == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(tile board[][N], int row, int col)
{
    if (row == N - 1 && col == N)
    {
        return true;
    }

    if (col == N)
    {
        row++;
        col = 0;
    }

    if (board[row][col].result > 0)
    {
        return solveSudoku(board, row, col + 1);
    }

    for (int num = 1; num <= N; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col].result = num;
            if (solveSudoku(board, row, col + 1))
            {
                return true;
            }
        }
        board[row][col].result = 0;
    }
    return false;
}

// check mouse click
void clearActiveStates(tile board[][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++){
			board[i][j].isActive = false;
		}
	}
}
