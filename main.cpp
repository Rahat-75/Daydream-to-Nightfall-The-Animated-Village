#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

// Global variables for animation
float day = 1.0;
float sunMoonPos = -10.0;
float cloudPosX = 0.0;
float birdPosX = 0.0;
float boatPosX = 0.0;
float hillBoatPosX = 0.0;
float jetPosX = -120.0;
float jetPosY = 65.0;
float jetSpeed = 0.2;

// Draw an  circle using a triangle fan
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2 * PI * i / 100;
        glVertex2f(cx + rx * cosf(angle), cy + ry * sinf(angle));
    }
    glEnd();
}


void drawSky()
{
    glBegin(GL_POLYGON);
    if (day > 0)
    {
        glColor3f(1.0, 1.0, 1.0); // White
        glVertex2f(-100.0, 20.0);
        glVertex2f(100.0, 20.0);
        glColor3ub(0, 102, 204); // Blue
        glVertex2f(100.0, 100.0);
        glVertex2f(-100.0, 100.0);
    }
    else
    {
        glColor3f(0.0, 0.0, 0.0); // Black
        glVertex2f(-100.0, 20.0);
        glVertex2f(100.0, 20.0);
        glVertex2f(100.0, 100.0);
        glVertex2f(-100.0, 100.0);
    }
    glEnd();
}

void drawRiver()
{
    glBegin(GL_POLYGON);
    glColor3ub(0, 76, 153);
    glVertex2f(-100.0, 20.0);
    glVertex2f(100.0, 20.0);
    glColor3ub(102, 178, 255);
    glVertex2f(100.0, -40.0);
    glVertex2f(-100.0, -40.0);
    glEnd();
}


void drawGrass()
{
    glColor3f(0.2, 0.9, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-100.0, -100.0);
    glVertex2f(100.0, -100.0);
    glVertex2f(100.0, -40.0);
    glVertex2f(-100.0, -40.0);
    glEnd();
}


void drawSunMoon()
{
    if (day > 0)
    {
        glColor3ub(255, 180, 50); // Bright coral sun
        circle(8.0, 12.0, -65.0, sunMoonPos);
    }
    else
    {
        glColor3f(1.0, 1.0, 1.0); // White for moon
        circle(4.0, 8.0, -65.0, sunMoonPos);
    }
}


void drawBirds()
{
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_LINES);

    // Bird 1
    glVertex2f(birdPosX - 60.0, 70.0);
    glVertex2f(birdPosX - 58.0, 72.0);
    glVertex2f(birdPosX - 58.0, 72.0);
    glVertex2f(birdPosX - 56.0, 70.0);

    // Bird 2
    glVertex2f(birdPosX - 50.0, 75.0);
    glVertex2f(birdPosX - 48.0, 77.0);
    glVertex2f(birdPosX - 48.0, 77.0);
    glVertex2f(birdPosX - 46.0, 75.0);

    // Bird 3
    glVertex2f(birdPosX - 40.0, 72.0);
    glVertex2f(birdPosX - 38.0, 74.0);
    glVertex2f(birdPosX - 38.0, 74.0);
    glVertex2f(birdPosX - 36.0, 72.0);
    glEnd();
}


void drawClouds()
{
    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
    glDisable(GL_BLEND);
    glColor3ub(240, 245, 255); // Pale lavender clouds

    // Cloud 1
    circle(5.0, 5.0, cloudPosX - 80.0, 80.0);
    circle(5.5, 5.5, cloudPosX - 76.0, 83.0);
    circle(5.5, 5.5, cloudPosX - 72.0, 81.0);
    circle(5.0, 5.0, cloudPosX - 68.0, 78.0);
    circle(4.0, 4.0, cloudPosX - 84.0, 78.0);
    circle(5.5, 5.5, cloudPosX - 79.0, 77.0);
    circle(5.5, 5.5, cloudPosX - 73.0, 76.0);

    // Cloud 2
    circle(5.0, 5.0, cloudPosX + 20.0, 90.0);
    circle(5.5, 5.5, cloudPosX + 24.0, 93.0);
    circle(5.5, 5.5, cloudPosX + 28.0, 91.0);
    circle(5.0, 5.0, cloudPosX + 32.0, 88.0);
    circle(4.0, 4.0, cloudPosX + 16.0, 88.0);
    circle(5.5, 5.5, cloudPosX + 21.0, 87.0);
    circle(5.5, 5.5, cloudPosX + 27.0, 86.0);

    // Cloud 3
    circle(5.0, 5.0, cloudPosX + 120.0, 85.0);
    circle(5.5, 5.5, cloudPosX + 124.0, 88.0);
    circle(5.5, 5.5, cloudPosX + 128.0, 86.0);
    circle(5.0, 5.0, cloudPosX + 132.0, 83.0);
    circle(4.0, 4.0, cloudPosX + 116.0, 83.0);
    circle(5.5, 5.5, cloudPosX + 121.0, 82.0);
    circle(5.5, 5.5, cloudPosX + 127.0, 81.0);

    glPopAttrib();
}


void drawStars()
{
    glColor3ub(255, 255, 255); // White
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2f(-98.0, 43.0);
    glVertex2f(-92.0, 67.0);
    glVertex2f(-90.0, 91.0);
    glVertex2f(-84.0, 49.0);
    glVertex2f(-81.0, 76.0);
    glVertex2f(-78.0, 53.0);
    glVertex2f(-73.0, 89.0);
    glVertex2f(-69.0, 65.0);
    glVertex2f(-66.0, 46.0);
    glVertex2f(-61.0, 82.0);
    glVertex2f(-59.0, 60.0);
    glVertex2f(-54.0, 94.0);
    glVertex2f(-51.0, 70.0);
    glVertex2f(-48.0, 48.0);
    glVertex2f(-43.0, 86.0);
    glVertex2f(-40.0, 62.0);
    glVertex2f(-35.0, 52.0);
    glVertex2f(-32.0, 78.0);
    glVertex2f(-28.0, 97.0);
    glVertex2f(-25.0, 44.0);
    glVertex2f(-20.0, 70.0);
    glVertex2f(-17.0, 87.0);
    glVertex2f(-13.0, 56.0);
    glVertex2f(-10.0, 74.0);
    glVertex2f(-5.0, 49.0);
    glVertex2f(-2.0, 93.0);
    glVertex2f(2.0, 66.0);
    glVertex2f(7.0, 44.0);
    glVertex2f(10.0, 80.0);
    glVertex2f(15.0, 57.0);
    glVertex2f(18.0, 95.0);
    glVertex2f(23.0, 72.0);
    glVertex2f(26.0, 48.0);
    glVertex2f(30.0, 87.0);
    glVertex2f(35.0, 63.0);
    glVertex2f(38.0, 52.0);
    glVertex2f(43.0, 89.0);
    glVertex2f(47.0, 68.0);
    glVertex2f(52.0, 46.0);
    glVertex2f(55.0, 93.0);
    glVertex2f(59.0, 71.0);
    glVertex2f(64.0, 59.0);
    glVertex2f(68.0, 83.0);
    glVertex2f(73.0, 47.0);
    glVertex2f(77.0, 75.0);
    glVertex2f(82.0, 52.0);
    glVertex2f(85.0, 91.0);
    glVertex2f(89.0, 68.0);
    glVertex2f(94.0, 45.0);
    glVertex2f(97.0, 87.0);
    glVertex2f(-94.0, 60.0);
    glVertex2f(-88.0, 82.0);
    glVertex2f(-82.0, 41.0);
    glVertex2f(-77.0, 96.0);
    glVertex2f(-71.0, 56.0);
    glVertex2f(-67.0, 74.0);
    glVertex2f(-62.0, 50.0);
    glVertex2f(-57.0, 88.0);
    glVertex2f(-53.0, 66.0);
    glVertex2f(-48.0, 43.0);
    glVertex2f(-44.0, 80.0);
    glVertex2f(-39.0, 96.0);
    glVertex2f(-34.0, 55.0);
    glVertex2f(-30.0, 73.0);
    glVertex2f(-25.0, 47.0);
    glVertex2f(-21.0, 85.0);
    glVertex2f(-16.0, 61.0);
    glVertex2f(-12.0, 92.0);
    glVertex2f(-8.0, 69.0);
    glVertex2f(-3.0, 46.0);
    glVertex2f(1.0, 85.0);
    glEnd();
    glPointSize(1.0);
}

void drawHills()
{
    glColor3ub(155, 118, 83);
    glBegin(GL_TRIANGLES);

    // Volcano 1
    glVertex2f(-35.0, 20.0);
    glVertex2f(60.0, 20.0);
    glVertex2f(10.0, 65.0);

    // Volcano 2
    glVertex2f(50.0, 20.0);
    glVertex2f(130.0, 20.0);
    glVertex2f(90.0, 65.0);
    glEnd();

    // Fire glow
    glColor3ub(255, 102, 0);
    circle(4.0, 4.0, 10.0, 63.0);
    glColor3ub(255, 153, 51);
    circle(3.0, 3.0, 10.0, 63.0);
    glColor3ub(255, 204, 102);
    circle(2.0, 2.0, 10.0, 63.0);
    glColor3ub(255, 102, 0);
    circle(4.0, 4.0, 90.0, 63.0);
    glColor3ub(255, 153, 51);
    circle(3.0, 3.0, 90.0, 63.0);
    glColor3ub(255, 204, 102);
    circle(2.0, 2.0, 90.0, 63.0);
}

// Draw tree leaves at bottom of hills
void drawTreeLeaves()
{
    glColor3ub(0, 100, 0); // Dark green
    circle(9.0, 6.0, -30.0, 25.0);
    circle(7.0, 5.0, -35.0, 20.0);
    circle(7.0, 5.0, -25.0, 20.0);

    glBegin(GL_TRIANGLES);
    glVertex2f(-15.0, 30.0);
    glVertex2f(-20.0, 20.0);
    glVertex2f(-10.0, 20.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-20.0, 25.0);
    glVertex2f(-22.5, 18.0);
    glVertex2f(-17.5, 18.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-10.0, 25.0);
    glVertex2f(-12.5, 18.0);
    glVertex2f(-7.5, 18.0);
    glEnd();

    circle(8.0, 8.0, 0.0, 25.0);
    circle(6.0, 6.0, -5.0, 20.0);
    circle(6.0, 6.0, 5.0, 20.0);

    circle(6.0, 9.0, 15.0, 25.0);
    circle(5.0, 7.0, 10.0, 20.0);
    circle(5.0, 7.0, 20.0, 20.0);

    circle(9.0, 6.0, 30.0, 25.0);
    circle(7.0, 5.0, 25.0, 20.0);
    circle(7.0, 5.0, 35.0, 20.0);

    glBegin(GL_TRIANGLES);
    glVertex2f(45.0, 30.0);
    glVertex2f(40.0, 20.0);
    glVertex2f(50.0, 20.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(40.0, 25.0);
    glVertex2f(37.5, 18.0);
    glVertex2f(42.5, 18.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(50.0, 25.0);
    glVertex2f(47.5, 18.0);
    glVertex2f(52.5, 18.0);
    glEnd();


    circle(8.0, 8.0, 60.0, 25.0);
    circle(6.0, 6.0, 55.0, 20.0);
    circle(6.0, 6.0, 65.0, 20.0);

    circle(6.0, 9.0, 75.0, 25.0);
    circle(5.0, 7.0, 70.0, 20.0);
    circle(5.0, 7.0, 80.0, 20.0);

    circle(9.0, 6.0, 90.0, 25.0);
    circle(7.0, 5.0, 85.0, 20.0);
    circle(7.0, 5.0, 95.0, 20.0);
}



void drawJet()
{
    // Jet fuselage
    glColor3ub(255, 255, 0); // Bright yellow
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX - 20.0, jetPosY);
    glVertex2f(jetPosX + 20.0, jetPosY);
    glVertex2f(jetPosX + 20.0, jetPosY - 6.0);
    glVertex2f(jetPosX - 20.0, jetPosY - 6.0);
    glEnd();

    // Jet nose
    glColor3ub(128, 0, 128); // Purple
    glBegin(GL_TRIANGLES);
    glVertex2f(jetPosX + 20.0, jetPosY);
    glVertex2f(jetPosX + 28.0, jetPosY - 3.0);
    glVertex2f(jetPosX + 20.0, jetPosY - 6.0);
    glEnd();

    // Jet tail fin
    glColor3ub(128, 0, 128); // Purple
    glBegin(GL_TRIANGLES);
    glVertex2f(jetPosX - 20.0, jetPosY);
    glVertex2f(jetPosX - 25.0, jetPosY + 15.0);
    glVertex2f(jetPosX - 20.0, jetPosY - 6.0);
    glEnd();

    // Jet left wing
    glColor3ub(255, 0, 255); // Magenta
    glBegin(GL_TRIANGLES);
    glVertex2f(jetPosX - 0.0, jetPosY - 6.0);
    glVertex2f(jetPosX - 5.0, jetPosY - 12.0);
    glVertex2f(jetPosX + 10.0, jetPosY - 6.0);
    glEnd();

    // Jet right wing
    glBegin(GL_TRIANGLES);
    glVertex2f(jetPosX - 5.0, jetPosY - 6.0);
    glVertex2f(jetPosX - 10.0, jetPosY - 12.0);
    glVertex2f(jetPosX + 5.0, jetPosY - 6.0);
    glEnd();

    // Jet windows
    glColor3ub(135, 206, 250); // Light sky blue
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX - 15.0, jetPosY - 2.0);
    glVertex2f(jetPosX - 12.0, jetPosY - 2.0);
    glVertex2f(jetPosX - 12.0, jetPosY - 4.0);
    glVertex2f(jetPosX - 15.0, jetPosY - 4.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX - 7.0, jetPosY - 2.0);
    glVertex2f(jetPosX - 4.0, jetPosY - 2.0);
    glVertex2f(jetPosX - 4.0, jetPosY - 4.0);
    glVertex2f(jetPosX - 7.0, jetPosY - 4.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX + 1.0, jetPosY - 2.0);
    glVertex2f(jetPosX + 4.0, jetPosY - 2.0);
    glVertex2f(jetPosX + 4.0, jetPosY - 4.0);
    glVertex2f(jetPosX + 1.0, jetPosY - 4.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX + 9.0, jetPosY - 2.0);
    glVertex2f(jetPosX + 12.0, jetPosY - 2.0);
    glVertex2f(jetPosX + 12.0, jetPosY - 4.0);
    glVertex2f(jetPosX + 9.0, jetPosY - 4.0);
    glEnd();

    // Jet engines
    glColor3ub(255, 165, 0); // Orange
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX - 10.0, jetPosY - 6.0);
    glVertex2f(jetPosX - 5.0, jetPosY - 6.0);
    glVertex2f(jetPosX - 5.0, jetPosY - 9.0);
    glVertex2f(jetPosX - 10.0, jetPosY - 9.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(jetPosX + 2.0, jetPosY - 6.0);
    glVertex2f(jetPosX + 7.0, jetPosY - 6.0);
    glVertex2f(jetPosX + 7.0, jetPosY - 9.0);
    glVertex2f(jetPosX + 2.0, jetPosY - 9.0);
    glEnd();

}


void drawHillBoat()
{
    // Boat hull
    glColor3ub(60, 60, 180); // Darker vibrant indigo
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 90.0, -5.0);
    glVertex2f(hillBoatPosX - 20.0, -5.0);
    glVertex2f(hillBoatPosX - 15.0, 10.0);
    glVertex2f(hillBoatPosX - 95.0, 10.0);
    glEnd();

    glColor3ub(120, 120, 220); // Darker light purple
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 95.0, 10.0);
    glVertex2f(hillBoatPosX - 15.0, 10.0);
    glVertex2f(hillBoatPosX - 15.0, 15.0);
    glVertex2f(hillBoatPosX - 95.0, 15.0);
    glEnd();

    glColor3ub(220, 80, 80); // Darker neon red stripe
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 90.0, -5.0);
    glVertex2f(hillBoatPosX - 20.0, -5.0);
    glVertex2f(hillBoatPosX - 20.0, -2.0);
    glVertex2f(hillBoatPosX - 90.0, -2.0);
    glEnd();

    // Boat portholes
    glColor3ub(220, 170, 170); // Darker pale pink
    circle(2.0, 2.0, hillBoatPosX - 35.0, 2.5);
    circle(2.0, 2.0, hillBoatPosX - 75.0, 2.5);
    circle(2.0, 2.0, hillBoatPosX - 65.0, 2.5);
    circle(2.0, 2.0, hillBoatPosX - 55.0, 2.5);
    circle(2.0, 2.0, hillBoatPosX - 45.0, 2.5);

    // Cargo containers - Row 1
    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 15.0);
    glVertex2f(hillBoatPosX - 70.0, 15.0);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glVertex2f(hillBoatPosX - 80.0, 20.0);
    glEnd();
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 70.0, 15.0);
    glVertex2f(hillBoatPosX - 60.0, 15.0);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glEnd();
    glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 60.0, 15.0);
    glVertex2f(hillBoatPosX - 50.0, 15.0);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glEnd();
    glColor3ub(255, 165, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 50.0, 15.0);
    glVertex2f(hillBoatPosX - 40.0, 15.0);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glEnd();
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 40.0, 15.0);
    glVertex2f(hillBoatPosX - 30.0, 15.0);
    glVertex2f(hillBoatPosX - 30.0, 20.0);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glEnd();

    // Cargo containers - Row 2
    glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 20.0);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glVertex2f(hillBoatPosX - 80.0, 25.0);
    glEnd();
    glColor3ub(255, 165, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glEnd();
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glEnd();
    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glEnd();
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glVertex2f(hillBoatPosX - 30.0, 20.0);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glEnd();

    // Cargo containers - Row 3
    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 25.0);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glVertex2f(hillBoatPosX - 70.0, 30.0);
    glVertex2f(hillBoatPosX - 80.0, 30.0);
    glEnd();
    glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glVertex2f(hillBoatPosX - 60.0, 30.0);
    glVertex2f(hillBoatPosX - 70.0, 30.0);
    glEnd();
    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glVertex2f(hillBoatPosX - 50.0, 30.0);
    glVertex2f(hillBoatPosX - 60.0, 30.0);
    glEnd();
    glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glVertex2f(hillBoatPosX - 40.0, 30.0);
    glVertex2f(hillBoatPosX - 50.0, 30.0);
    glEnd();
    glColor3ub(255, 165, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 30.0);
    glVertex2f(hillBoatPosX - 40.0, 30.0);
    glEnd();

    // Boat mast
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 15.0);
    glVertex2f(hillBoatPosX - 31.0, 15.0);
    glVertex2f(hillBoatPosX - 31.0, 37.0);
    glVertex2f(hillBoatPosX - 30.0, 37.0);
    glEnd();

    // Boat green stripe
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 31.0);
    glVertex2f(hillBoatPosX - 15.0, 31.0);
    glVertex2f(hillBoatPosX - 15.0, 35.0);
    glVertex2f(hillBoatPosX - 30.0, 35.0);
    glEnd();

    // Boat white stripe
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 28.0);
    glVertex2f(hillBoatPosX - 15.0, 28.0);
    glVertex2f(hillBoatPosX - 15.0, 31.0);
    glVertex2f(hillBoatPosX - 30.0, 31.0);
    glEnd();

    // Boat red stripe
    glColor3ub(10, 153, 0);
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 15.0, 25.0);
    glVertex2f(hillBoatPosX - 15.0, 28.0);
    glVertex2f(hillBoatPosX - 30.0, 28.0);
    glEnd();

    // Boat flag
    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 35.0);
    glVertex2f(hillBoatPosX - 23.33, 30.0);
    glEnd();

    // Boat flag outline
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 35.0);
    glVertex2f(hillBoatPosX - 23.33, 30.0);
    glEnd();

    // Boat wake effect
    glColor3ub(102, 178, 255);
    glBegin(GL_TRIANGLES);
    glVertex2f(hillBoatPosX - 90.0, -5.0);
    glVertex2f(hillBoatPosX - 95.0, -7.0);
    glVertex2f(hillBoatPosX - 85.0, -7.0);
    glVertex2f(hillBoatPosX - 85.0, -5.0);
    glVertex2f(hillBoatPosX - 90.0, -7.0);
    glVertex2f(hillBoatPosX - 80.0, -7.0);
    glEnd();
}


void drawNewBoat()
{
    // Boat hull
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX - 24.0, -24.0);
    glVertex2f(boatPosX + 28.0, -24.0);
    glVertex2f(boatPosX + 40.0, -12.0);
    glVertex2f(boatPosX - 32.0, -12.0);
    glEnd();

    // Boat cabin
    glColor3ub(204, 77, 0);
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX - 24.0, -12.0);
    glVertex2f(boatPosX + 20.0, -12.0);
    glVertex2f(boatPosX + 20.0, 4.0);
    glVertex2f(boatPosX - 24.0, 4.0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(1.6);
    glBegin(GL_LINES);

    glVertex2f(boatPosX - 24.0, -4.0);
    glVertex2f(boatPosX + 20.0, -4.0);
    glVertex2f(boatPosX - 24.0, 0.0);
    glVertex2f(boatPosX + 20.0, 0.0);
    glVertex2f(boatPosX - 24.0, -8.0);
    glVertex2f(boatPosX + 20.0, -8.0);

    glVertex2f(boatPosX - 12.0, -12.0);
    glVertex2f(boatPosX - 12.0, 4.0);
    glVertex2f(boatPosX + 4.0, -12.0);
    glVertex2f(boatPosX + 4.0, 4.0);
    glEnd();
    glLineWidth(1.0);

    // Boat mast
    glColor3ub(0, 0, 175);
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX + 20.0, -12.0);
    glVertex2f(boatPosX + 21.0, -12.0);
    glVertex2f(boatPosX + 21.0, 20.0);
    glVertex2f(boatPosX + 20.0, 20.0);
    glEnd();

    // Green Rectangle
    glColor3ub(0, 155, 0);
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX + 21.0, 0.8);
    glVertex2f(boatPosX + 42.0, 0.8);
    glVertex2f(boatPosX + 42.0, 17.6);
    glVertex2f(boatPosX + 21.0, 17.6);
    glEnd();

    // Red Circle
    glColor3ub(255, 0, 0);
    circle(4.8, 6.4, boatPosX + 31.5, 9.6);

    // Boat wake effect
    glColor3ub(102, 248, 255);
    glBegin(GL_TRIANGLES);
    glVertex2f(boatPosX - 24.0, -24.0);
    glVertex2f(boatPosX - 28.0, -25.6);
    glVertex2f(boatPosX - 20.0, -25.6);
    glVertex2f(boatPosX - 20.0, -24.0);
    glVertex2f(boatPosX - 24.0, -25.6);
    glVertex2f(boatPosX - 16.0, -25.6);
    glEnd();
}


void drawSailBoat()
{
    // Boat hull
    glColor3ub(150, 75, 0); // Brownish
    glBegin(GL_POLYGON);
    glVertex2f(-18.0, -35.0);
    glVertex2f(2.0, -35.0);
    glVertex2f(0.0, -40.0);
    glVertex2f(-16.0, -40.0);
    glEnd();

    // Boat mast
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_LINES);
    glVertex2f(-8.0, -35.0);
    glVertex2f(-8.0, -20.0);
    glEnd();

    // Boat sail
    glColor3ub(255, 255, 255); // White
    glBegin(GL_TRIANGLES);
    glVertex2f(-8.0, -20.0);
    glVertex2f(-8.0, -25.0);
    glVertex2f(0.0, -25.0);
    glEnd();
}


void drawBigTree1()
{
    // Tree trunk
    glColor3ub(139, 69, 19); // Brown
    glBegin(GL_POLYGON);
    glVertex2f(-83.0, -80.0);
    glVertex2f(-77.0, -80.0);
    glVertex2f(-77.0, -30.0);
    glVertex2f(-83.0, -30.0);
    glEnd();

    // Tree leaves
    glColor3ub(0, 100, 0); // Dark green
    circle(12.0, 12.0, -80.0, -25.0);
    circle(10.0, 10.0, -87.0, -30.0);
    circle(10.0, 10.0, -73.0, -30.0);
}


void drawBigTree2()
{
    // Tree trunk
    glColor3ub(139, 69, 19); // Brown
    glBegin(GL_POLYGON);
    glVertex2f(-38.0, -80.0);
    glVertex2f(-32.0, -80.0);
    glVertex2f(-32.0, -30.0);
    glVertex2f(-38.0, -30.0);
    glEnd();

    // Tree leaves
    glColor3ub(0, 100, 0); // Dark green
    circle(12.0, 12.0, -35.0, -25.0);
    circle(10.0, 10.0, -42.0, -30.0);
    circle(10.0, 10.0, -28.0, -30.0);
}


void drawHouse()
{
    // House base
    glColor3ub(255, 204, 153);
    glBegin(GL_POLYGON);
    glVertex2f(-40.0, -80.0);
    glVertex2f(-10.0, -80.0);
    glVertex2f(-10.0, -56.0);
    glVertex2f(-40.0, -56.0);
    glEnd();

    // House roof
    glColor3ub(139, 69, 19);
    glBegin(GL_TRIANGLES);
    glVertex2f(-43.0, -56.0);
    glVertex2f(-7.0, -56.0);
    glVertex2f(-25.0, -40.0);
    glEnd();

    // House door
    glColor3ub(102, 51, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-28.0, -80.0);
    glVertex2f(-22.0, -80.0);
    glVertex2f(-22.0, -68.0);
    glVertex2f(-28.0, -68.0);
    glEnd();

    // House windows
    glColor3ub(0, 204, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-35.5, -68.0);
    glVertex2f(-31.0, -68.0);
    glVertex2f(-31.0, -62.0);
    glVertex2f(-35.5, -62.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-19.0, -68.0);
    glVertex2f(-14.5, -68.0);
    glVertex2f(-14.5, -62.0);
    glVertex2f(-19.0, -62.0);
    glEnd();

    // House chimney
    glColor3ub(100, 100, 100);
    glBegin(GL_POLYGON);
    glVertex2f(-14.5, -56.0);
    glVertex2f(-11.5, -56.0);
    glVertex2f(-11.5, -44.0);
    glVertex2f(-14.5, -44.0);
    glEnd();
}

void drawNewHouse()
{
    // House base
    glColor3ub(255, 105, 180); // Hot pink
    glBegin(GL_POLYGON);
    glVertex2f(-88.0, -80.0);
    glVertex2f(-52.0, -80.0);
    glVertex2f(-52.0, -55.0);
    glVertex2f(-88.0, -55.0);
    glEnd();

    // House roof
    glColor3ub(0, 191, 255); // Deep sky blue
    glBegin(GL_POLYGON);
    glVertex2f(-90.0, -55.0);
    glVertex2f(-50.0, -55.0);
    glVertex2f(-54.0, -45.0);
    glVertex2f(-86.0, -45.0);
    glEnd();

    // House door
    glColor3ub(255, 165, 0); // Bright orange
    glBegin(GL_POLYGON);
    glVertex2f(-74.0, -80.0);
    glVertex2f(-66.0, -80.0);
    glVertex2f(-66.0, -68.0);
    glVertex2f(-74.0, -68.0);
    glEnd();
    circle(4.0, 4.0, -70.0, -68.0);

    // House windows
    glColor3ub(255, 245, 238); // Seashell white
    glBegin(GL_POLYGON);
    glVertex2f(-82.0, -65.0);
    glVertex2f(-78.0, -65.0);
    glVertex2f(-78.0, -60.0);
    glVertex2f(-82.0, -60.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-62.0, -65.0);
    glVertex2f(-58.0, -65.0);
    glVertex2f(-58.0, -60.0);
    glVertex2f(-62.0, -60.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-82.0, -75.0);
    glVertex2f(-78.0, -75.0);
    glVertex2f(-78.0, -70.0);
    glVertex2f(-82.0, -70.0);
    glEnd();

    // House window grids
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_LINES);
    glVertex2f(-80.0, -65.0);
    glVertex2f(-80.0, -60.0);
    glVertex2f(-82.0, -62.5);
    glVertex2f(-78.0, -62.5);
    glVertex2f(-60.0, -65.0);
    glVertex2f(-60.0, -60.0);
    glVertex2f(-62.0, -62.5);
    glVertex2f(-58.0, -62.5);
    glVertex2f(-80.0, -75.0);
    glVertex2f(-80.0, -70.0);
    glVertex2f(-82.0, -72.5);
    glVertex2f(-78.0, -72.5);
    glEnd();

    // House chimney
    glColor3ub(255, 20, 147); // Deep pink
    glBegin(GL_POLYGON);
    glVertex2f(-58.0, -55.0);
    glVertex2f(-55.0, -55.0);
    glVertex2f(-55.0, -50.0);
    glVertex2f(-58.0, -50.0);
    glEnd();
}




void drawFlowerTree1()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(4.0, -95.0);
    glVertex2f(6.0, -95.0);
    glVertex2f(6.0, -100.0);
    glVertex2f(4.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, 5.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, 3.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, 7.0, -95.0);
}

void drawFlowerTree2()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(4.0, -85.0);
    glVertex2f(6.0, -85.0);
    glVertex2f(6.0, -90.0);
    glVertex2f(4.0, -90.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, 5.0, -83.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, 3.0, -85.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, 7.0, -85.0);
}

void drawFlowerTree3()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(4.0, -55.0);
    glVertex2f(6.0, -55.0);
    glVertex2f(6.0, -60.0);
    glVertex2f(4.0, -60.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, 5.0, -53.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, 3.0, -55.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, 7.0, -55.0);
}

void drawFlowerTree4()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(4.0, -45.0);
    glVertex2f(6.0, -45.0);
    glVertex2f(6.0, -50.0);
    glVertex2f(4.0, -50.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, 5.0, -43.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, 3.0, -45.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, 7.0, -45.0);
}

void drawFlowerTree5()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-5.0, -95.0);
    glVertex2f(-3.0, -95.0);
    glVertex2f(-3.0, -100.0);
    glVertex2f(-5.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -4.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -6.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -2.0, -95.0);
}

void drawFlowerTree6()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-15.0, -95.0);
    glVertex2f(-13.0, -95.0);
    glVertex2f(-13.0, -100.0);
    glVertex2f(-15.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -14.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -16.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -12.0, -95.0);
}

void drawFlowerTree7()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-25.0, -95.0);
    glVertex2f(-23.0, -95.0);
    glVertex2f(-23.0, -100.0);
    glVertex2f(-25.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -24.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -26.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -22.0, -95.0);
}


void drawFlowerTree8()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-35.0, -95.0);
    glVertex2f(-33.0, -95.0);
    glVertex2f(-33.0, -100.0);
    glVertex2f(-35.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -34.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -36.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -32.0, -95.0);
}

void drawFlowerTree9()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-45.0, -95.0);
    glVertex2f(-43.0, -95.0);
    glVertex2f(-43.0, -100.0);
    glVertex2f(-45.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -44.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -46.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -42.0, -95.0);
}

void drawFlowerTree10()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-55.0, -95.0);
    glVertex2f(-53.0, -95.0);
    glVertex2f(-53.0, -100.0);
    glVertex2f(-55.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -54.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -56.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -52.0, -95.0);
}

void drawFlowerTree11()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-65.0, -95.0);
    glVertex2f(-63.0, -95.0);
    glVertex2f(-63.0, -100.0);
    glVertex2f(-65.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -64.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -66.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -62.0, -95.0);
}

void drawFlowerTree12()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-75.0, -95.0);
    glVertex2f(-73.0, -95.0);
    glVertex2f(-73.0, -100.0);
    glVertex2f(-75.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -74.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -76.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -72.0, -95.0);
}

void drawFlowerTree13()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-85.0, -95.0);
    glVertex2f(-83.0, -95.0);
    glVertex2f(-83.0, -100.0);
    glVertex2f(-85.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -84.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -86.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -82.0, -95.0);
}

void drawFlowerTree14()
{
    // Tree base
    glColor3ub(74, 132, 19); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(-95.0, -95.0);
    glVertex2f(-93.0, -95.0);
    glVertex2f(-93.0, -100.0);
    glVertex2f(-95.0, -100.0);
    glEnd();

    // Tree flowers
    glColor3ub(255, 51, 0); // Red
    circle(2.0, 2.0, -94.0, -93.0);
    glColor3ub(255, 255, 0); // Yellow
    circle(1.5, 1.5, -96.0, -95.0);
    glColor3ub(255, 102, 0); // Orange
    circle(1.5, 1.5, -92.0, -95.0);
}

void drawRoad()
{
    // Main road
    glColor3ub(60, 40, 80);
    glBegin(GL_POLYGON);
    glVertex2f(10.0, -89.0);
    glVertex2f(100.0, -89.0);
    glVertex2f(100.0, -54.0);
    glVertex2f(10.0, -54.0);
    glEnd();

    // Center line
    glColor3ub(255, 204, 0);
    glBegin(GL_POLYGON);
    glVertex2f(10.0, -71.5);
    glVertex2f(100.0, -71.5);
    glVertex2f(100.0, -70.5);
    glVertex2f(10.0, -70.5);
    glEnd();

    // Lane lines
    glColor3ub(255, 255, 255);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(10.0, -54.5);
    glVertex2f(100.0, -54.5);
    glVertex2f(10.0, -88.5);
    glVertex2f(100.0, -88.5);
    glEnd();
}

void drawModernCar1()
{
    glColor3ub(255, 105, 180);
    glBegin(GL_POLYGON);
    glVertex2f(13.0, -65.0);
    glVertex2f(55.0, -65.0);
    glVertex2f(55.0, -55.0);
    glVertex2f(13.0, -55.0);
    glEnd();

    glColor3ub(200, 50, 150);
    glBegin(GL_POLYGON);
    glVertex2f(23.0, -55.0);
    glVertex2f(28.0, -46.0);
    glVertex2f(45.0, -46.0);
    glVertex2f(50.0, -55.0);
    glEnd();

    glColor3ub(135, 180, 255);
    glBegin(GL_POLYGON);
    glVertex2f(24.0, -55.0);
    glVertex2f(28.0, -48.0);
    glVertex2f(32.0, -48.0);
    glVertex2f(32.0, -55.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(41.0, -55.0);
    glVertex2f(41.0, -48.0);
    glVertex2f(44.0, -48.0);
    glVertex2f(48.0, -55.0);
    glEnd();

    glColor3ub(100, 150, 255);
    glBegin(GL_POLYGON);
    glVertex2f(32.0, -55.0);
    glVertex2f(32.0, -48.0);
    glVertex2f(41.0, -48.0);
    glVertex2f(41.0, -55.0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(37.0, -55.0);
    glVertex2f(37.0, -48.0);
    glVertex2f(32.0, -52.0);
    glVertex2f(34.0, -52.0);
    glVertex2f(39.0, -52.0);
    glVertex2f(41.0, -52.0);
    glEnd();

    glColor3ub(50, 50, 50);
    circle(4.0, 4.0, 26.0, -65.0);
    circle(4.0, 4.0, 47.0, -65.0);
    glColor3ub(255, 215, 0);
    circle(3.0, 3.0, 26.0, -65.0);
    circle(3.0, 3.0, 47.0, -65.0);
    glColor3ub(255, 255, 255);
    circle(1.0, 1.0, 26.0, -65.0);
    circle(1.0, 1.0, 47.0, -65.0);
    glColor3ub(200, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(54.0, -62.0);
    glVertex2f(55.0, -62.0);
    glVertex2f(55.0, -60.0);
    glVertex2f(54.0, -60.0);
    glEnd();

    glColor3ub(200, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(13.0, -62.0);
    glVertex2f(14.0, -62.0);
    glVertex2f(14.0, -60.0);
    glVertex2f(13.0, -60.0);
    glEnd();
}

void drawModernCar2()
{
    glColor3ub(0, 204, 204);
    glBegin(GL_POLYGON);
    glVertex2f(35.0, -82.0);
    glVertex2f(83.0, -82.0);
    glVertex2f(83.0, -70.0);
    glVertex2f(35.0, -70.0);
    glEnd();

    glColor3ub(0, 153, 153);
    glBegin(GL_POLYGON);
    glVertex2f(47.0, -70.0);
    glVertex2f(52.0, -62.0);
    glVertex2f(71.0, -62.0);
    glVertex2f(76.0, -70.0);
    glEnd();

    glColor3ub(135, 180, 255);
    glBegin(GL_POLYGON);
    glVertex2f(48.0, -70.0);
    glVertex2f(52.0, -63.0);
    glVertex2f(56.0, -63.0);
    glVertex2f(56.0, -70.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(67.0, -70.0);
    glVertex2f(67.0, -63.0);
    glVertex2f(70.0, -63.0);
    glVertex2f(74.0, -70.0);
    glEnd();

    glColor3ub(100, 150, 255);
    glBegin(GL_POLYGON);
    glVertex2f(56.0, -70.0);
    glVertex2f(56.0, -63.0);
    glVertex2f(67.0, -63.0);
    glVertex2f(67.0, -70.0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(62.0, -70.0);
    glVertex2f(62.0, -63.0);
    glVertex2f(56.0, -67.0);
    glVertex2f(58.0, -67.0);
    glVertex2f(65.0, -67.0);
    glVertex2f(67.0, -67.0);
    glEnd();

    glColor3ub(50, 50, 50);
    circle(5.0, 5.0, 51.0, -82.0);
    circle(5.0, 5.0, 73.0, -82.0);
    glColor3ub(0, 255, 255);
    circle(3.0, 3.0, 51.0, -82.0);
    circle(3.0, 3.0, 73.0, -82.0);
    glColor3ub(255, 255, 255);
    circle(1.0, 1.0, 51.0, -82.0);
    circle(1.0, 1.0, 73.0, -82.0);
    glColor3ub(200, 200, 200);
    glBegin(GL_POLYGON);
    glVertex2f(81.0, -78.0);
    glVertex2f(83.0, -78.0);
    glVertex2f(83.0, -76.0);
    glVertex2f(81.0, -76.0);
    glEnd();

    glColor3ub(200, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(35.0, -78.0);
    glVertex2f(37.0, -78.0);
    glVertex2f(37.0, -76.0);
    glVertex2f(35.0, -76.0);
    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw background elements
    drawSky();
    if (day < 0) drawStars();
    drawSunMoon();
    drawClouds();
    drawHills();
    drawTreeLeaves();
    drawRiver();
    drawGrass();
    drawRoad();
    drawModernCar1();
    drawModernCar2();

    // Draw foreground elements
    drawFlowerTree1();
    drawFlowerTree2();
    drawFlowerTree3();
    drawFlowerTree4();
    drawFlowerTree5();
    drawFlowerTree6();
    drawFlowerTree7();
    drawFlowerTree8();
    drawFlowerTree9();
    drawFlowerTree10();
    drawFlowerTree11();
    drawFlowerTree12();
    drawFlowerTree13();
    drawFlowerTree14();
    drawHillBoat();
    drawNewBoat();
    drawBigTree1();
    drawBigTree2();
    drawNewHouse();
    drawHouse();
    drawSailBoat();
    drawBirds();
    drawJet();

    // Update animation variables
    birdPosX += 0.1;
    if (birdPosX > 200.0) birdPosX = -200.0;
    cloudPosX += 0.05;
    if (cloudPosX > 200.0) cloudPosX = -200.0;
    if (day > 0)
    {
        sunMoonPos -= 0.025;
        if (sunMoonPos < 00.0) day = -1.0;
    }
    else
    {
        sunMoonPos += 0.025;
        if (sunMoonPos > 110.0) day = 1.0;
    }
    boatPosX += 0.075;
    if (boatPosX > 200.0) boatPosX = -200.0;
    jetPosX += jetSpeed;
    if (jetPosX > 120.0) jetPosX = -120.0;
    hillBoatPosX += 0.06;
    if (hillBoatPosX > 200.0) hillBoatPosX = -200.0;

    glutPostRedisplay();
    glFlush();
}

// Initialize OpenGL settings
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1240, 750);
    glutCreateWindow("Daydream to Nightfall The Animated Village");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
