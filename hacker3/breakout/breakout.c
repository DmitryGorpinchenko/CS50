//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// width and height of paddle
#define PADDLE_H 10
#define PADDLE_W 70

// gap
#define GAP 5

//scale for velocity increase
#define SCALE 10.0

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void centerLabelLocation(GWindow window, GLabel label);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void gameOver(int lives, int bricks, GWindow window, GLabel label);

int main(int argc, char* argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    double v_x = drand48()*2 + 1;
    double v_y = drand48()*2 + 1;
    
    bool isGod = false;
    
    if(argc == 2 && strcmp(argv[1], "GOD") == 0)
    {
        isGod = true;
    }   
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (!isGod && event != NULL)
        {            
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
        else if (event != NULL)
        {
            isGod = false;
        }
        else if (isGod)
        {   
            setLocation(paddle, getX(ball) + RADIUS - PADDLE_W/2.0, getY(paddle));
        }   
        
        move(ball, v_x, v_y);
        
        if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
        {
            v_x = -v_x;
        }
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            v_y = -v_y;
            lives--;
        }
        if (getY(ball) <= 0)
        {
            v_y = -v_y;
        }
        
        GObject object = detectCollision(window, ball);
           
        if (object != NULL && strcmp(getType(object), "GRect") == 0)
        {
            v_y = -v_y;
            if (object != paddle)
            {
                removeGWindow(window, object);
                points++;
                bricks--;
                v_x = v_x + SCALE / (ROWS*COLS);
                v_y = v_y + SCALE / (ROWS*COLS);
                updateScoreboard(window, label, points);
            }
        }
        
        pause(10);
    }
    
    gameOver(lives, bricks, window, label);

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

// finish game
void gameOver(int lives, int bricks, GWindow window, GLabel label)
{
    if (lives == 0)
    {
        setColor(label, "RED");
        setLabel(label, "You lose!");
        centerLabelLocation(window, label);
    }
    else if (bricks == 0)
    {
        setColor(label, "GREEN");
        setLabel(label, "You win!");
        centerLabelLocation(window, label);
    }
}   

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            double x = j * (WIDTH + 0.0) / COLS + GAP / 2.0;
            double y = i * PADDLE_H + GAP;
            GRect brick = newGRect(x, y, (WIDTH + 0.0) / COLS - GAP, PADDLE_H - GAP / 2.0);
            setColor(brick, "BLACK");
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = WIDTH / 2.0 - RADIUS;
    double y = HEIGHT / 2.0;
    GOval ball = newGOval(x, y, 2 * RADIUS, 2 * RADIUS);
    setColor(ball, "GRAY");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double x = (WIDTH - PADDLE_W) / 2.0;
    double y = HEIGHT - 5 * PADDLE_H;
    GRect paddle = newGRect(x, y, PADDLE_W, PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    setColor(label, "PINK");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}

// centering of the label's location
void centerLabelLocation(GWindow window, GLabel label)
{
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    centerLabelLocation(window, label);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
