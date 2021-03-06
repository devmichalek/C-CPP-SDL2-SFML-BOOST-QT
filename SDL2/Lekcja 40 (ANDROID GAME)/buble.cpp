#include "buble.h"

Buble::Buble()
{
    posX = 0;
    posY = 0;
    vel = 1.5;
    slow = 10;
    hit = 7 * slow;

    rect = NULL;
    rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    lifebar = new Lifebar;
    texture = new Texture( 13 );
    random = new Random;
}

Buble::~Buble()
{
    delete lifebar;
    lifebar = NULL;

    delete texture;
    texture = NULL;

    delete random;
    random = NULL;

    delete rect;
    rect = NULL;
}

void Buble::load( SDL_Renderer* &renderer, Uint16 w )
{
    texture->setTexture( renderer, "enemy/0.png" );
    texture->setSlow( slow );
    rect->w = texture->getWidth() * 2;
    rect->h = texture->getHeight() * 2;

    lifebar->setAlpha( 0xFF );
    lifebar->setColor( 0xFF, 0x00, 0x00 );
    lifebar->setSizes( 3, rect->w, 15 );
    lifebar->setXY( rect->x, rect->y - 10 );

    random->randomX( 1, ( w - rect->w ) );
    random->randomY( -50, -100 );
    posX = random->getX();
    posY = random->getY();
    rect->x = posX;
    rect->y = posY;
}

bool Buble::event( SDL_Event &e )
{
    bool success = false;
    x = -100;
    y = -100;

    if( e.type == SDL_MOUSEBUTTONDOWN ) // SDL_MOUSEBUTTONDOWN SDL_FINGERDOWN
    {
        // x = e.tfinger.x * w;
        // y = e.tfinger.y * h;
        SDL_GetMouseState( &x, &y );

        if( x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h )
        {
            success = true;
            if( lifebar->getLife() > 0 )                lifebar->subtraction( 1 );
            if( lifebar->isDead() && hit == 7 * slow )  hit = 0;
            else if( hit == 7 * slow )                  hit = 8 * slow;
        }
    }

    return success;
}

void Buble::motion( Uint16 w, Uint16 h )
{
    if( hit == 7 * slow ) // jesli nie bylo uderzenia to wyswietlaj dalej animacje
    {
        texture->runOffset( 0, 4 );
    }
    else if( hit > 7 * slow )
    {
        texture->setOffset( hit );
        hit ++;
        if( hit == 10 * slow )
            hit = 7 * slow;
    }
    else if( hit < 7 * slow )
    {
        texture->setOffset( hit + 8 * slow );
        hit ++;
    }

    if( rect->x < random->getX() )
    {
        posX += vel;
        texture->setFlip( SDL_FLIP_NONE );
    }
    else if( rect->x > random->getX() )
    {
        posX -= vel;
        texture->setFlip( SDL_FLIP_HORIZONTAL );
    }

    if( rect->x <= random->getX() + 5 && rect->x > random->getX() - 5 )
    {
        random->randomX( 1, ( w - rect->w ) );
    }

    posY += vel;
    rect->x = posX;
    rect->y = posY;
    if( rect->y > h || hit == 4 * slow )
    {
        hit = 20 * slow;
    }
}

void Buble::render( SDL_Renderer* &renderer )
{
    lifebar->setXY( rect->x, rect->y - 10 );
    lifebar->render( renderer );
    texture->render( renderer, rect );
}

bool Buble::isDead()
{
    if( hit == 20 * slow )  return 1;
    return 0;
}

void Buble::setVel( float v )
{
    vel = v;
}
