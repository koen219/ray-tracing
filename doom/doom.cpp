#include "doom.h"


double Doom::getLengthToWall(double rot) {
    double length = 0;
    bool collision = false;
    float x = Player->Position.x + 8;
    float y = Player->Position.y + 8;
    while (length < 500 and not collision) {
        length += 3;
        float nx = x + length * cos((rot) * 3.1415 / 180.0);
        float ny = y + length * sin((rot) * 3.1415 / 180.0);
        int ix = (int)((float)(nx) / tileSize);
        int iy = (int)((float)(ny) / tileSize);
        if (ix >= 0 and iy >= 0 and ix < Height and iy < Width and bord[iy][ix] == 'w')
            collision = true;

    }
    return length;
}

void Doom::drawFOV() {
    std::vector<double> lengths;
    for (int i = 0; i < FOV; i+=1) {

        sf::RectangleShape line;
        double length = getLengthToWall(Player->Rotation + i);
        lengths.push_back(length);

        /*
        line.setSize(sf::Vector2f(length, 1));
        line.setFillColor(sf::Color::Black);
        line.setPosition(Player->Position.x + 8, Player->Position.y + 8);
        line.setRotation(i+Player->Rotation);
        window->draw(line);*/
    }
    for (int j = ScreenWidth/2; j < ScreenWidth; j++) {
        int x = j - ScreenWidth / 2;
        int f =  x * FOV / (double)(ScreenWidth/2);
        double h = 0;
        if (lengths[f]> 0.001)
            h = ScreenHeight / 2 * (lengths[f]/100) / (sqrt(lengths[f]*lengths[f]/10000+1));
        walls3D[f].setSize(sf::Vector2f(1, ScreenHeight - 2 * h));
        air3D[f].setSize(sf::Vector2f(1, h));
        ground3D[f].setSize(sf::Vector2f(1, h));
        air3D[f].setPosition(j, 0);
        air3D[f].setFillColor(sf::Color::Cyan);
        walls3D[f].setPosition(j, h);
        walls3D[f].setFillColor(sf::Color::Red);
        ground3D[f].setPosition(j, ScreenHeight - h);
        ground3D[f].setFillColor(sf::Color(77, 25, 25));
        window->draw(air3D[f]);
        window->draw(walls3D[f]);
        window->draw(ground3D[f]);
    }
}

void Doom::draw()
{
    /*
    sf::Image image;
    image.create(ScreenWidth, ScreenHeight, sf::Color::Red);
    for (int j = 0; j < ScreenWidth; j++) {
        double theta = j * 45 / ScreenWidth + Player->Rotation;
        double distanceToWall = -1.0;
        for (int R = 5; R < 32*8; R++) {
            double r = R / 1.0;
            vector2D newPos = Player->Position + vector2D(std::cos(theta * 3.1415 / 180.0), std::sin(theta * 3.1415 / 180.0)) * r;
            if (bord[(int)(newPos.x/tileSize)][(int)(newPos.y/tileSize)] == 'w') {
                distanceToWall = (newPos + Player->Position*(-1)).magnitude();
                R = 100;
            }
        }
        double factor = 2;
        std::cout << distanceToWall << std::endl;
        for (int i = 0; i < ScreenHeight; i++) {
            if (distanceToWall < 0) {
                image.setPixel(j, i, sf::Color::Magenta);
            }
            else {
                if (i < distanceToWall * factor) {
                    image.setPixel(i, j, sf::Color::Blue);
                }
                else {
                    if (i > ScreenHeight - distanceToWall * factor) {
                        image.setPixel(i, j, sf::Color::Yellow);
                    }
                    else {
                        image.setPixel(i, j, sf::Color::Red);
                    }
                }
            }
        }
    }
    sf::Texture tex;
    tex.loadFromImage(image);
    sf::Sprite spr;
    spr.setTexture(tex);
    */
    window->clear();

    

    sf::RectangleShape back(sf::Vector2f(ScreenHeight, ScreenWidth / 2));
    back.setFillColor(sf::Color::White);
    window->draw(back);
    for (sf::RectangleShape wall : walls) {
        window->draw(wall);
    }

    sf::Vector2i mPos = sf::Mouse::getPosition(*window);
    int x = (int)((float)(mPos.x) / tileSize);
    int y = (int)((float)(mPos.y) / tileSize);
    if (x >= 0 and x < 16 and y >= 0 and y <= 16) {
        sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
        rect.setPosition(tileSize*x,tileSize* y);
        if (bord[y][x] == 'w')
            rect.setFillColor(sf::Color::Cyan);
        else
            rect.setFillColor(sf::Color::Magenta);
        window->draw(rect);
    }

    drawFOV();
    for (moveable* x : drawAbles) {
        x->draw(window);
    }
    //window->draw(spr);

    window->display();
    gameOver = not window->isOpen();
}

void Doom::handleEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        
    }
}
void Doom::playerMove() {
    double speed = 1;
    double rotationSpeed = 0.5;
    double dx = 0;
    double dy = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dx = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dx = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        dy = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        dy = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        Player->Rotation -= rotationSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        Player->Rotation += rotationSpeed;
    }
    Player->Position = Player->Position + vector2D(dx, dy);
}

void Doom::gameLoop() {
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (not gameOver)
    {
        handleEvents();
        playerMove();
        draw();
    }
    std::cout << "End of game loop" << std::endl;
}