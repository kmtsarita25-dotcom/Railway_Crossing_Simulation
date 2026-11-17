
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>

// ---------------- DRAW TREE ----------------
void drawTree(int x, int y)
{
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(x - 5, y, x + 5, y + 35);

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(x, y - 10, 22, 25);
}

// ---------------- DRAW CLOUD ----------------
void drawCloud(int x, int y)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);

    fillellipse(x, y, 20, 12);
    fillellipse(x + 18, y - 8, 20, 15);
    fillellipse(x + 38, y, 20, 12);
}

// ---------------- DRAW TRAIN ----------------
void drawTrain(int x)
{
    int i;

    // Engine body
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, RED);
    bar(x, 280, x + 120, 350);

    // Engine cabin
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(x + 15, 245, x + 85, 280);

    // Engine window
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(x + 25, 252, x + 65, 273);

    // Engine front
    setfillstyle(SOLID_FILL, YELLOW);
    bar(x + 100, 315, x + 120, 340);

    // Passenger coaches
    for(i = 0; i < 3; i++)
    {
        int cx = x + 130 + i * 115;

        setcolor(WHITE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(cx, 270, cx + 105, 350);

        // Coach windows
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        bar(cx + 10, 282, cx + 35, 305);
        bar(cx + 45, 282, cx + 70, 305);
        bar(cx + 78, 282, cx + 95, 305);
    }

    // Engine wheels
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);

    for(i = 0; i < 4; i++)
    {
        int wx = x + 15 + i * 30;
        fillellipse(wx, 355, 10, 10);
    }

    // Coach wheels
    for(i = 0; i < 3; i++)
    {
        int wx = x + 145 + i * 115;

        fillellipse(wx, 355, 10, 10);
        fillellipse(wx + 65, 355, 10, 10);
    }
}

// ---------------- DRAW RAILWAY TRACK ----------------
void drawTrack()
{
    int i;

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, 360, 640, 410);

    setcolor(WHITE);
    line(0, 370, 640, 370);
    line(0, 400, 640, 400);

    // Railway sleepers
    for(i = 0; i < 640; i += 30)
    {
        setfillstyle(SOLID_FILL, BROWN);
        bar(i, 360, i + 8, 410);
    }
}

// ---------------- DRAW VERTICAL ROAD ----------------
void drawRoad()
{
    // Road surface
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(290, 0, 350, 480);

    // Road boundaries
    setcolor(WHITE);
    line(290, 0, 290, 480);
    line(350, 0, 350, 480);

    // Centre marking
    setlinestyle(DASHED_LINE, 0, 1);
    line(320, 0, 320, 480);

    setlinestyle(SOLID_LINE, 0, 1);
}

// ---------------- DRAW BARRIER ----------------
void drawGate(int closed)
{
    int i;

    // Barrier support
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(275, 325, 290, 360);

    if(closed)
    {
        // Horizontal closed barrier
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, 6);
        line(282, 345, 358, 345);

        // Red stripes
        setcolor(RED);
        setlinestyle(SOLID_LINE, 0, 3);

        for(i = 292; i <= 348; i += 14)
        {
            line(i, 342, i, 348);
        }
    }
    else
    {
        // Raised open barrier
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, 6);
        line(282, 345, 320, 270);
    }

    setlinestyle(SOLID_LINE, 0, 1);
}

// ---------------- DRAW WARNING SIGNAL ----------------
void drawSignal(int warning)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(365, 290, 395, 345);

    if(warning)
        setfillstyle(SOLID_FILL, RED);
    else
        setfillstyle(SOLID_FILL, DARKGRAY);

    fillellipse(380, 307, 9, 9);

    setfillstyle(SOLID_FILL, DARKGRAY);
    fillellipse(380, 330, 9, 9);
}

// ---------------- DRAW MOVING CAR ----------------
void drawCar(int y)
{
    // Car body
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(298, y, 342, y + 55);

    // Front and rear windows
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(304, y + 7, 336, y + 23);
    bar(304, y + 32, 336, y + 45);

    // Wheels
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(298, y + 12, 4, 7);
    fillellipse(342, y + 12, 4, 7);
    fillellipse(298, y + 43, 4, 7);
    fillellipse(342, y + 43, 4, 7);
}

// ---------------- MAIN FUNCTION ----------------
int main()
{
    int gd = DETECT, gm;
    int x;
    int carY = -60;

    int trainAtCrossing;
    int warning;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    while(!kbhit())
    {
        for(x = -450; x < 700; x += 5)
        {
            cleardevice();

            // Background
            setbkcolor(LIGHTBLUE);

            // Green ground
            setfillstyle(SOLID_FILL, GREEN);
            bar(0, 410, 640, 480);

            // Vertical road
            drawRoad();

            // Clouds
            drawCloud(80, 70);
            drawCloud(430, 90);

            // Trees
            drawTree(80, 220);
            drawTree(570, 220);

            // Railway track
            drawTrack();

            // --------------------------------
            // TRAIN CROSSING DETECTION
            // --------------------------------

            if(x + 465 >= 250 && x <= 350)
            {
                trainAtCrossing = 1;
            }
            else
            {
                trainAtCrossing = 0;
            }

            // --------------------------------
            // CAR MOVEMENT CONTROL
            // --------------------------------

            if(trainAtCrossing)
            {
                // Car approaches and stops
                // before the closed barrier

                if(carY < 280)
                {
                    carY += 3;

                    if(carY > 280)
                        carY = 280;
                }
            }
            else
            {
                // Barrier open: car moves forward
                carY += 3;

                // Reset car after leaving screen
                if(carY > 480)
                {
                    carY = -60;
                }
            }

            // --------------------------------
            // WARNING SIGNAL
            // --------------------------------

            warning = ((x / 10) % 2 == 0);

            // Draw moving train
            drawTrain(x);

            // --------------------------------
            // BARRIER CONTROL
            // --------------------------------

            if(trainAtCrossing)
            {
                drawGate(1);
                drawSignal(warning);
            }
            else
            {
                drawGate(0);
                drawSignal(0);
            }

            // --------------------------------
            // DRAW MOVING CAR
            // --------------------------------

            drawCar(carY);

            // Project title
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

            outtextxy(115, 20,
                      "RAILWAY CROSSING SIMULATION");

            // Exit instruction
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            outtextxy(220, 450,
                      "Press any key to exit");

            delay(40);
        }
    }

    closegraph();
    return 0;
}
