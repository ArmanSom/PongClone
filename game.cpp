//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries


#include <vector>
#include <sstream>

#include "ball.h"
#include "playerpaddle.h"
#include "computerpaddle.h"
#include "game.h"
#include "globals.h"
#include "texture.h"


/******* GAME CLASS DEFS *******/

//constructor starts game loop at title screen
Game::Game()
{
    level = TITLE;
}

//determines what level of game to run
void Game::level_control()
{
    //create white outline for window
    SDL_Rect outline = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    
    //determine level to run
    while ( level != END )
    {
        //if queued level is title screen
        if ( level == TITLE )
            //initiate title screen loop
            title_screen(outline);
        
        //if queued level is computer battle
        else if ( level == COMPUTER_BATTLE )
            //initiate computer battle game loop
            computer_battle(outline);
        
        //if queued level is player battle
        else if ( level == PLAYER_BATTLE )
            //initiate player battle game loop
            player_battle(outline);
        
        else if (level == INSTRUCTIONS )
            //initiate instructions loop
            instructions(outline);
    }
}


//title screen loop
void Game::title_screen( SDL_Rect window_outline )
{
    //light pink color for larger text
    SDL_Color color = { 219, 112, 147 };
    
    //create and load title text texture
    Texture title;
    title.load_text(big_font, color, "PONG");
    
    //create and load first button text texture
    Texture button1;
    button1.load_text(medium_font, color, "1 PLAYER");
    
    //create and load second button text texture
    Texture button2;
    button2.load_text(medium_font, color, "2 PLAYER");
    
    //create and load third button text texture
    Texture button3;
    button3.load_text(medium_font, color, "INSTRUCTIONS");
    
    //create and load credits text texture
    Texture credit;
    credit.load_text(smallest_font, color, "PONG IS ORIGINALLY CREATED BY ATARI INC.");
    
    //create button1 outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - button1.get_width()/2 - 7, (WINDOW_HEIGHT*4)/10 - button1.get_height()/2 - 10, button1.get_width() + 14, button1.get_height() + 14 };
    //create button select (determines which button is outlined)
    int button_select = 0;
    
    //title screen loop terminator
    bool terminated = false;
    
    //create object that reads in events
    SDL_Event event;
    
    //title screen loop
    while (terminated == false)
    {
        //take in events
        while ( SDL_PollEvent(&event) )
        {
            //if there's a quit event
            if ( event.type == SDL_QUIT )
            {
                //stop title screen loop
                terminated = true;
                //tell level control to end game
                level = END;
            }
            
            //if there's a non-repeat keypress event
            if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
            {
                //if down key was pressed
                if ( event.key.keysym.sym == SDLK_DOWN )
                {
                    //if first button is selected
                    if (button_select == 0)
                    {
                        //move outline to second button
                        ++button_select;
                        button_outline.y += (WINDOW_HEIGHT*1)/10;
                    }
                    
                    //if second button is selected
                    else if (button_select == 1)
                    {
                        //move outline to third button
                        ++button_select;
                        button_outline.y += (WINDOW_HEIGHT*1)/10;
                        button_outline.x -= 55;
                        button_outline.w += 110;
                    }
                    
                    //if third button is selected
                    else if (button_select == 2)
                    {
                        //move outline to first button
                        button_select = 0;
                        button_outline.y -= (WINDOW_HEIGHT*2)/10;
                        button_outline.x += 55;
                        button_outline.w -= 110;
                    }
                }
                
                //if up key is pressed
                if ( event.key.keysym.sym == SDLK_UP )
                {
                    //if first button is selected
                    if (button_select == 0)
                    {
                        //move outline to third button
                        button_select = 2;
                        button_outline.y += (WINDOW_HEIGHT*2)/10;
                        button_outline.x -= 55;
                        button_outline.w += 110;
                    }
                    
                    //if second button is selected
                    else if (button_select == 1)
                    {
                        //move outline to first button
                        --button_select;
                        button_outline.y -= (WINDOW_HEIGHT*1)/10;
                    }
                    
                    //if third button is selected
                    else if (button_select == 2)
                    {
                        //move outline to second button
                        --button_select;
                        button_outline.y -= (WINDOW_HEIGHT*1)/10;
                        button_outline.x += 55;
                        button_outline.w -= 110;
                    }
                    
                }
                
                //if enter key is pressed
                else if ( event.key.keysym.sym == SDLK_RETURN )
                {
                    //if first button is selected
                    if (button_select == 0)
                    {
                        //end title screen loop
                        terminated = true;
                        //change level to computer battle
                        level = COMPUTER_BATTLE;
                    }
                    
                    //if second button is selected
                    else if (button_select == 1)
                    {
                        //end title screen loop
                        terminated = true;
                        //change level to player battle
                        level = PLAYER_BATTLE;
                    }
                    
                    //if third button is selected
                    else if (button_select == 2)
                    {
                        //end title screen loop
                        terminated = true;
                        //change level to instructions
                        level = INSTRUCTIONS;
                    }
                }
            }
        }
        
        //clear window black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear(renderer);
        
        //set renderer color to white
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        
        //render window outline
        SDL_RenderDrawRect( renderer, &window_outline );
        //render button outline
        SDL_RenderDrawRect( renderer, &button_outline );
        
        //render title text
        title.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*2)/10);
        //render button texts
        button1.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*4)/10);
        button2.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*5)/10);
        button3.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*6)/10);
        //render credit text
        credit.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*9)/10);
        
        //update window with new renders
        SDL_RenderPresent( renderer );
    }
}





//computer battle loop
void Game::computer_battle( SDL_Rect window_outline)
{
    //create score counts
    int player1_score = 0;
    int player2_score = 0;
    
    //light pink color
    SDL_Color color = { 219, 112, 147 };
    
    //load score text textures (0 - 3)
    std::vector<Texture> scores(4);
    std::stringstream score_count;
    for (int i = 0; i < scores.size(); ++i)
    {
        score_count.str("");
        score_count << i;
        scores[i].load_text(big_font, color, score_count.str().c_str());
    }
    
    //white color
    color = { 255, 255, 255 };
    
    //load winning text texture
    Texture you_win;
    you_win.load_text(medium_font, color, "YOU WIN!");
    
    //load losing text texture
    Texture you_lose;
    you_lose.load_text(medium_font, color, "YOU LOSE!");
    
    //load try again text texture
    Texture try_again;
    try_again.load_text(medium_font, color, "TRY AGAIN?");
    
    //load yes or no text texture
    Texture yes_or_no;
    yes_or_no.load_text(medium_font, color, "YES   NO");
    
    //create yes or no button outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - yes_or_no.get_width()/2 - 14, (WINDOW_HEIGHT*7)/10 - yes_or_no.get_height()/2 - 10, yes_or_no.get_width()/2, yes_or_no.get_height() + 14 };
    //create yes or no button select
    bool button_select = true;
    
    //create ball
    Ball* ball = new Ball;
    //create right paddle (player)
    PlayerPaddle* paddle1 = new PlayerPaddle;
    //create left paddle (computer) and set pointers
    ComputerPaddle* paddle2 = new ComputerPaddle;
    paddle2->set_opponent(paddle1);
    paddle2->set_ball(ball);
    
    //create polymorphic vector of colliders for ball collisions
    std::vector<Collider*> paddles;
    paddles.push_back(paddle1);
    paddles.push_back(paddle2);
    
    //computer battle terminator
    bool terminated = false;
    
    //create object that reads events
    SDL_Event event;
    
    //player battle loop
    while (terminated == false)
    {
        //event loop
        while ( SDL_PollEvent(&event) )
        {
            //if there's a quit event, stop game loop and allow level control to end game
            if ( event.type == SDL_QUIT )
            {
                terminated = true;
                level = END;
            }
            
            //check events for velocity change
            paddle1->handle(event);
            //if there is no winner
            if ( player1_score != 3 && player2_score != 3)
                //check events for ball (to start movement if spawned)
                ball->handle(event);
            
            //if a player won
            if (player1_score == 3 || player2_score == 3)
            {
                //if there's a non-repeat keypress event
                if ( event.type == SDL_KEYDOWN && event.key.repeat == 0)
                {
                    //if left or right key was pressed
                    if ( event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
                    {
                        //if button outline is over YES
                        if (button_select == true)
                            //move button outline right
                            button_outline.x += 150;
                        //if button outline is over NO
                        else if (button_select == false)
                            //move button outline left
                            button_outline.x -= 150;
                        
                        //switch to other button
                        button_select = !button_select;
                    }
                    
                    //if enter key was pressed
                    if ( event.key.keysym.sym == SDLK_RETURN)
                    {
                        if (button_select == true)
                            //allow computer battle to end so it can restart
                            terminated = true;
                        else if (button_select == false)
                        {
                            //change level to title
                            level = TITLE;
                            //allow computer battle to end
                            terminated = true;
                        }
                    }
                }
            }
        }
        
        //set new coordinates based on velocity and modify score counts
        ball->move(paddles, player1_score, player2_score);
        //set new coordinates based on velocity
        paddle1->move();
        //set new coordinates based on opponent position and ball
        paddle2->move();
        
        //clear window black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear(renderer);
        
        //set renderer color to light pink
        SDL_SetRenderDrawColor( renderer, 219, 112, 147, 255 );
        
        //render (2-pixel width) dotted line in center
        for (int i = 0; i <= 1; ++i)
            for (int j = 0; j <= WINDOW_HEIGHT; ++j)
            {
                SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2 + i, j);
                if (j % 20 == 0)
                    j += 10;
            }
        
        //render player1 score
        if (player1_score == 0) scores[0].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player1_score == 1) scores[1].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player1_score == 2) scores[2].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player1_score == 3) scores[3].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        
        //render player2 score
        if (player2_score == 0) scores[0].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player2_score == 1) scores[1].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player2_score == 2) scores[2].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player2_score == 3) scores[3].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        
        //render paddles
        paddle1->render();
        paddle2->render();
        
        //set renderer color to white
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        
        //if a player won
        if (player1_score == 3 || player2_score == 3 )
        {
            //if player1 won, render you lose text
            if (player1_score == 3)
                you_lose.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10);
            
            //if player2 won, render you win text
            else if (player2_score == 3)
                you_win.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10);
            
            //render try again text
            try_again.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*6)/10);
            
            //render yes or no text
            yes_or_no.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*7)/10);
            
            //render yes or no button outline
            SDL_RenderDrawRect( renderer, &button_outline );
        }
        
        //render ball
        ball->render();
        
        //render window outline
        SDL_RenderDrawRect( renderer, &window_outline );
        
        //update window with new renders
        SDL_RenderPresent( renderer );
    }
    
    //cleanup
    delete paddle1;
    delete paddle2;
    delete ball;
    
}


//player versus player battle loop
void Game::player_battle( SDL_Rect window_outline )
{
    //create score counts
    int player1_score = 0;
    int player2_score = 0;
    
    //load score textures
    std::vector<Texture> scores(4);
    std::stringstream score_count;
    //light pink color
    SDL_Color color = { 219, 112, 147 };
    for (int i = 0; i < scores.size(); ++i)
    {
        score_count.str("");
        score_count << i;
        scores[i].load_text(big_font, color, score_count.str().c_str());
    }
    
    //white color
    color = { 255, 255, 255 };
    //load player1 wins text texture
    Texture player1_wins;
    player1_wins.load_text(medium_font, color, "PLAYER 1 WINS!");
    
    //load player2 wins text texture
    Texture player2_wins;
    player2_wins.load_text(medium_font, color, "PLAYER 2 WINS!");
    
    //load try again text texture
    Texture try_again;
    try_again.load_text(medium_font, color, "TRY AGAIN?");
    
    //yes or no text texture
    Texture yes_or_no;
    yes_or_no.load_text(medium_font, color, "YES   NO");
    
    //create yes or no button outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - yes_or_no.get_width()/2 - 14, (WINDOW_HEIGHT*7)/10 - yes_or_no.get_height()/2 - 10, yes_or_no.get_width()/2, yes_or_no.get_height() + 14 };
    //yes or no button select
    bool button_select = true;
    
    //create ball
    Ball* ball = new Ball;
    //create right paddle (player)
    PlayerPaddle* paddle1 = new PlayerPaddle;
    //create left paddle (computer)
    PlayerPaddle* paddle2 = new PlayerPaddle(PLAYER_BATTLE);
    
    //create a polymorphic vector of colliders for ball collisions
    std::vector<Collider*> paddles;
    paddles.push_back(paddle1);
    paddles.push_back(paddle2);
    
    //create player battle loop terminator
    bool terminated = false;
    //create object that reads in events
    SDL_Event event;
    
    //game loop
    while (terminated == false)
    {
        //event loop
        while ( SDL_PollEvent(&event) )
        {
            //if there's a quit event
            if ( event.type == SDL_QUIT )
            {
                terminated = true;
                level = END;
            }
            
            //check events for velocity change
            paddle1->handle(event);
            paddle2->handle(event);
            
            //if no one has won yet
            if ( player1_score != 3 && player2_score != 3)
                //check events for ball (to start movement if spawned)
                ball->handle(event);
            
            //if a player won
            if (player1_score == 3 || player2_score == 3)
            {
                //if there's a non-repeat keypress event
                if ( event.type == SDL_KEYDOWN && event.key.repeat == 0)
                {
                    //if left or right key was pressed
                    if ( event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
                    {
                        //if button outline is over YES
                        if (button_select == true)
                            //move button outline right
                            button_outline.x += 150;
                        //if button outline is over NO
                        else if (button_select == false)
                            //move button outline left
                            button_outline.x -= 150;
                        
                        //switch to other button
                        button_select = !button_select;
                    }
                    
                    //if enter key was pressed
                    if ( event.key.keysym.sym == SDLK_RETURN)
                    {
                        //if YES button is selected
                        if (button_select == true)
                            //allow player battle to end so it can restart
                            terminated = true;
                        //if NO button is selected
                        else if (button_select == false)
                        {
                            //change level to title
                            level = TITLE;
                            //allow player battle to end
                            terminated = true;
                        }
                    }
                }
            }
        }
        
        //move objects and modify score counts
        ball->move(paddles, player1_score, player2_score);
        paddle1->move();
        paddle2->move();
        
        //clear window black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear(renderer);
        
        //set renderer color to light pink
        SDL_SetRenderDrawColor( renderer, 219, 112, 147, 255 );
        
        //render (2-pixel width) dotted line in center
        for (int i = 0; i <= 1; ++i)
            for (int j = 0; j <= WINDOW_HEIGHT; ++j)
            {
                SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2 + i, j);
                if (j % 20 == 0)
                    j += 10;
            }
        
        //render player1 score
        if (player1_score == 0) scores[0].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player1_score == 1) scores[1].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player1_score == 2) scores[2].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player1_score == 3) scores[3].render( (WINDOW_WIDTH*4)/10, (WINDOW_HEIGHT*3)/20 );
        
        //render player2 score
        if (player2_score == 0) scores[0].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player2_score == 1) scores[1].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player2_score == 2) scores[2].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        else if (player2_score == 3) scores[3].render( (WINDOW_WIDTH*6)/10, (WINDOW_HEIGHT*3)/20 );
        
        //render paddles
        paddle1->render();
        paddle2->render();
        
        //set renderer color to white
        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        
        //if a player won
        if (player1_score == 3 || player2_score == 3 )
        {
            //if player1 wins, render player1 wins text
            if (player1_score == 3)
                player1_wins.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10);
            
            //if player2 wins, render player2 wins text
            else if (player2_score == 3)
                player2_wins.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10);
            
            //render try again text
            try_again.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*6)/10);
            
            //render yes or no text
            yes_or_no.render(WINDOW_WIDTH/2, (WINDOW_HEIGHT*7)/10);
            
            //render yes or no button outline
            SDL_RenderDrawRect( renderer, &button_outline );
        }
        
        //render ball
        ball->render();
        
        //render window outline
        SDL_RenderDrawRect( renderer, &window_outline );
        
        //update window with new renders
        SDL_RenderPresent( renderer );
    }
    
    //cleanup
    delete paddle1;
    delete paddle2;
    delete ball;
}


//instructions loop
void Game::instructions( SDL_Rect window_outline )
{
    //light pink color for instructions text
    SDL_Color color = { 219, 112, 147 };
    
    //load first instruction texture
    Texture instruction1;
    instruction1.load_text(small_font, color, "GET THE BALL BEHIND YOUR OPPONENT");
    
    //load second instruction texture
    Texture instruction2;
    instruction2.load_text(small_font, color, "USE THE UP/DOWN OR W/D KEYS TO MOVE");
    
    //load third instruction texture
    Texture instruction3;
    instruction3.load_text(small_font, color, "PRESS SPACE TO LAUNCH BALL FROM CENTER");
    
    //load fourth instruction texture
    Texture instruction4;
    instruction4.load_text(small_font, color, "SCORE 3 POINTS TO WIN");
    
    //load back button texture
    Texture back;
    back.load_text(small_font, color, "BACK TO MENU");
    
    //create button outline
    SDL_Rect button_outline = { WINDOW_WIDTH/2 - back.get_width()/2 - 7, (WINDOW_HEIGHT*7)/10 - back.get_height()/2 - 10, back.get_width() + 14, back.get_height() + 14 };
    
    //instructions loop terminator
    bool terminated = false;
    
    //create event reader
    SDL_Event event;
    
    //instructions loop
    while (terminated == false)
    {
        //event loop (while there are events in queue)
        while ( SDL_PollEvent(&event) != 0 )
        {
            //if quit event
            if (event.type == SDL_QUIT)
            {
                //end instructions loop
                terminated = true;
                //end main loop
                level = END;
            }
            
            //if non-repeat key press event
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                //if enter key
                if ( event.key.keysym.sym == SDLK_RETURN)
                {
                    //end instructions loop
                    terminated = true;
                    //change level to title screen
                    level = TITLE;
                }
        }
        
        //clear window black
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear(renderer);
        
        //set renderer color to light pink
        SDL_SetRenderDrawColor( renderer, 219, 112, 147, 255 );
        
        //render instructions
        instruction1.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*2)/10);
        instruction2.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*3)/10);
        instruction3.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*4)/10);
        instruction4.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*5)/10);
        //render back button
        back.render( WINDOW_WIDTH/2, (WINDOW_HEIGHT*7)/10);
        
        //set renderer color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        //render back button outline
        SDL_RenderDrawRect(renderer, &button_outline);
        //render window outline
        SDL_RenderDrawRect(renderer, &window_outline);
        
        //update window with new renders
        SDL_RenderPresent( renderer );
    }
}
