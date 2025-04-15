#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

// Global variables for animation
float day = 1.0;         // 1.0 for day, -1.0 for night
float sunMoonPos = -10.0; // Vertical position of sun/moon
float cloudPosX = 0.0;    // Horizontal position of clouds
float birdPosX = 0.0;     // Horizontal position of birds
float boatPosX = 0.0;     // Horizontal position of new boat
float hillBoatPosX = 0.0; // Horizontal position of hill boat
float jetPosX = -120.0;   // Horizontal position of jet
float jetPosY = 65.0;     // Vertical position of jet
float jetSpeed = 0.2;     // Jet movement speed

// Draw an ellipse (or circle) using a triangle fan
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++) {
        float angle = 2 * PI * i / 100;
        glVertex2f(cx + rx * cosf(angle), cy + ry * sinf(angle));
    }
    glEnd();
}

// Draw birds in the sky
void drawBirds() {
    glColor3ub(0, 0, 0); // Black color for birds
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

// Draw jet in the sky
void drawJet() {
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
    glColor3ub(50, 205, 50); // Lime green
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

// Draw clouds in the sky
void drawClouds() {
    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
    glPushMatrix();
    glDisable(GL_BLEND);
    glColor3ub(208, 222, 236); // Light gray for clouds
    // Cloud 1
    circle(5.0, 5.0, cloudPosX - 80.0, 80.0);
    circle(6.0, 6.0, cloudPosX - 75.0, 82.0);
    circle(5.0, 5.0, cloudPosX - 70.0, 80.0);
    circle(4.0, 4.0, cloudPosX - 72.0, 83.0);
    // Cloud 2
    circle(5.0, 5.0, cloudPosX + 20.0, 90.0);
    circle(6.0, 6.0, cloudPosX + 25.0, 92.0);
    circle(5.0, 5.0, cloudPosX + 30.0, 90.0);
    circle(4.0, 4.0, cloudPosX + 27.0, 93.0);
    // Cloud 3
    circle(5.0, 5.0, cloudPosX + 120.0, 85.0);
    circle(6.0, 6.0, cloudPosX + 125.0, 87.0);
    circle(5.0, 5.0, cloudPosX + 130.0, 85.0);
    circle(4.0, 4.0, cloudPosX + 127.0, 88.0);
    glPopMatrix();
    glPopAttrib();
}

// Draw sun or moon
void drawSunMoon() {
    if (day > 0) {
        glColor3f(1.0, 1.0, 0.0); // Yellow for sun
        circle(8.0, 12.0, -60.0, sunMoonPos);
    } else {
        glColor3f(1.0, 1.0, 1.0); // White for moon
        circle(4.0, 8.0, -60.0, sunMoonPos);
    }
}

void drawHills() {
    // Volcano-like hills
    glColor3ub(155, 118, 83); // Brown for hills
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

    // Fire-like glow at peaks
    glColor3ub(255, 69, 0); // Red-orange for lava
    circle(3.0, 3.0, 10.0, 65.0);
    circle(2.5, 2.5, 12.0, 66.0);
    circle(2.5, 2.5, 8.0, 66.0);
    circle(3.0, 3.0, 90.0, 65.0);
    circle(2.5, 2.5, 92.0, 66.0);
    circle(2.5, 2.5, 88.0, 66.0);
}

// Draw unified tree leaves at bottom of hills with varied shapes
void drawTreeLeaves() {
    glColor3ub(0, 100, 0); // Dark green
    // Cluster 3: Ellipses (wider)
    circle(9.0, 6.0, -30.0, 25.0);
    circle(7.0, 5.0, -35.0, 20.0);
    circle(7.0, 5.0, -25.0, 20.0);
    // Cluster 4: Triangles
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
    // Cluster 5: Circles
    circle(8.0, 8.0, 0.0, 25.0);
    circle(6.0, 6.0, -5.0, 20.0);
    circle(6.0, 6.0, 5.0, 20.0);
    // Cluster 6: Ellipses (taller)
    circle(6.0, 9.0, 15.0, 25.0);
    circle(5.0, 7.0, 10.0, 20.0);
    circle(5.0, 7.0, 20.0, 20.0);
    // Cluster 7: Ellipses (wider)
    circle(9.0, 6.0, 30.0, 25.0);
    circle(7.0, 5.0, 25.0, 20.0);
    circle(7.0, 5.0, 35.0, 20.0);
    // Cluster 8: Triangles
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
    // Cluster 9: Circles
    circle(8.0, 8.0, 60.0, 25.0);
    circle(6.0, 6.0, 55.0, 20.0);
    circle(6.0, 6.0, 65.0, 20.0);
    // Cluster 10: Ellipses (taller)
    circle(6.0, 9.0, 75.0, 25.0);
    circle(5.0, 7.0, 70.0, 20.0);
    circle(5.0, 7.0, 80.0, 20.0);
    // Cluster 11: Ellipses (wider)
    circle(9.0, 6.0, 90.0, 25.0);
    circle(7.0, 5.0, 85.0, 20.0);
    circle(7.0, 5.0, 95.0, 20.0);
}

// Draw the sky
void drawSky() {
    glBegin(GL_POLYGON);
    if (day > 0) {
        glColor3f(1.0, 1.0, 1.0); // White bottom for day
        glVertex2f(-100.0, 20.0);
        glVertex2f(100.0, 20.0);
        glColor3ub(0, 102, 204); // Blue top for day
        glVertex2f(100.0, 100.0);
        glVertex2f(-100.0, 100.0);
    } else {
        glColor3f(0.0, 0.0, 0.0); // Black for night
        glVertex2f(-100.0, 20.0);
        glVertex2f(100.0, 20.0);
        glVertex2f(100.0, 100.0);
        glVertex2f(-100.0, 100.0);
    }
    glEnd();
}

// Draw stars at night
void drawStars() {
    glColor3ub(255, 255, 255); // White for stars
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


// Draw new boat on the river
// Draw new boat on the river
void drawNewBoat() {
    // Boat hull
    glColor3ub(204, 77, 0); // Orange-brown
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX - 30.0, -30.0);
    glVertex2f(boatPosX + 35.0, -30.0);
    glVertex2f(boatPosX + 50.0, -15.0);
    glVertex2f(boatPosX - 40.0, -15.0);
    glEnd();

    // Boat cabin
    glColor3ub(255, 255, 0); // Yellow
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX - 20.0, -15.0);
    glVertex2f(boatPosX - 10.0, -15.0);
    glVertex2f(boatPosX - 10.0, 15.0);
    glVertex2f(boatPosX - 20.0, 15.0);
    glEnd();

    // Boat cockpit
    glColor3ub(102, 0, 102); // Purple
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX - 10.0, -15.0);
    glVertex2f(boatPosX, -15.0);
    glVertex2f(boatPosX, 10.0);
    glVertex2f(boatPosX - 10.0, 10.0);
    glEnd();

    // Boat deck triangle
    glColor3ub(0, 255, 0); // Green
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX, -15.0);
    glVertex2f(boatPosX + 10.0, -15.0);
    glVertex2f(boatPosX + 10.0, 5.0);
    glVertex2f(boatPosX, 5.0);
    glEnd();

    // Boat mast
    glColor3ub(0, 0, 255); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX + 27.0, -15.0);
    glVertex2f(boatPosX + 28.0, -15.0);
    glVertex2f(boatPosX + 28.0, 25.0);
    glVertex2f(boatPosX + 27.0, 25.0);
    glEnd();

    // Boat deck extension
    glColor3ub(0, 155, 0); // Dark green
    glBegin(GL_POLYGON);
    glVertex2f(boatPosX + 28.0, 1.0);
    glVertex2f(boatPosX + 55.0, 1.0);
    glVertex2f(boatPosX + 55.0, 22.0);
    glVertex2f(boatPosX + 28.0, 22.0);
    glEnd();

    // Boat decorative circle
    glColor3ub(255, 0, 0); // Red
    circle(6.0, 8.0, boatPosX + 42.0, 12.0); // raised from 5.0 to 10.0

    // Boat wake effect
    glColor3ub(102, 248, 255); // Light blue
    glBegin(GL_TRIANGLES);
    glVertex2f(boatPosX - 30.0, -30.0);
    glVertex2f(boatPosX - 35.0, -32.0);
    glVertex2f(boatPosX - 25.0, -32.0);
    glVertex2f(boatPosX - 25.0, -30.0);
    glVertex2f(boatPosX - 30.0, -32.0);
    glVertex2f(boatPosX - 20.0, -32.0);
    glEnd();
}


// Draw hill boat (cargo ship)
void drawHillBoat() {
    // Boat hull
    glColor3ub(204, 77, 0); // Orange-brown
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 0.0);
    glVertex2f(hillBoatPosX - 25.0, 0.0);
    glVertex2f(hillBoatPosX - 20.0, 15.0);
    glVertex2f(hillBoatPosX - 85.0, 15.0);
    glEnd();

    // Boat portholes
    glColor3ub(100, 100, 255); // Blue
    circle(2.0, 2.0, hillBoatPosX - 35.0, 7.5);
    circle(2.0, 2.0, hillBoatPosX - 75.0, 7.5);
    circle(2.0, 2.0, hillBoatPosX - 65.0, 7.5);
    circle(2.0, 2.0, hillBoatPosX - 55.0, 7.5);
    circle(2.0, 2.0, hillBoatPosX - 45.0, 7.5);

    // Cargo containers - Row 1
    glColor3ub(255, 255, 0); // Yellow
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 15.0);
    glVertex2f(hillBoatPosX - 70.0, 15.0);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glVertex2f(hillBoatPosX - 80.0, 20.0);
    glEnd();
    glColor3ub(0, 255, 0); // Green
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 70.0, 15.0);
    glVertex2f(hillBoatPosX - 60.0, 15.0);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glEnd();
    glColor3ub(0, 0, 255); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 60.0, 15.0);
    glVertex2f(hillBoatPosX - 50.0, 15.0);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glEnd();
    glColor3ub(255, 165, 0); // Orange
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 50.0, 15.0);
    glVertex2f(hillBoatPosX - 40.0, 15.0);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glEnd();
    glColor3ub(255, 0, 0); // Red
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 40.0, 15.0);
    glVertex2f(hillBoatPosX - 30.0, 15.0);
    glVertex2f(hillBoatPosX - 30.0, 20.0);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glEnd();

    // Cargo containers - Row 2
    glColor3ub(0, 0, 255); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 20.0);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glVertex2f(hillBoatPosX - 80.0, 25.0);
    glEnd();
    glColor3ub(255, 165, 0); // Orange
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 70.0, 20.0);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glEnd();
    glColor3ub(255, 0, 0); // Red
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 60.0, 20.0);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glEnd();
    glColor3ub(255, 255, 0); // Yellow
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 50.0, 20.0);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glEnd();
    glColor3ub(0, 255, 0); // Green
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 40.0, 20.0);
    glVertex2f(hillBoatPosX - 30.0, 20.0);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glEnd();

    // Cargo containers - Row 3
    glColor3ub(255, 0, 0); // Red
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 80.0, 25.0);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glVertex2f(hillBoatPosX - 70.0, 30.0);
    glVertex2f(hillBoatPosX - 80.0, 30.0);
    glEnd();
    glColor3ub(0, 0, 255); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 70.0, 25.0);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glVertex2f(hillBoatPosX - 60.0, 30.0);
    glVertex2f(hillBoatPosX - 70.0, 30.0);
    glEnd();
    glColor3ub(255, 255, 0); // Yellow
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 60.0, 25.0);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glVertex2f(hillBoatPosX - 50.0, 30.0);
    glVertex2f(hillBoatPosX - 60.0, 30.0);
    glEnd();
    glColor3ub(0, 255, 0); // Green
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 50.0, 25.0);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glVertex2f(hillBoatPosX - 40.0, 30.0);
    glVertex2f(hillBoatPosX - 50.0, 30.0);
    glEnd();
    glColor3ub(255, 165, 0); // Orange
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 40.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 30.0);
    glVertex2f(hillBoatPosX - 40.0, 30.0);
    glEnd();

    // Boat mast
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 15.0);
    glVertex2f(hillBoatPosX - 31.0, 15.0);
    glVertex2f(hillBoatPosX - 31.0, 37.0);
    glVertex2f(hillBoatPosX - 30.0, 37.0);
    glEnd();

    // Boat green stripe
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 31.0);
    glVertex2f(hillBoatPosX - 15.0, 31.0);
    glVertex2f(hillBoatPosX - 15.0, 35.0);
    glVertex2f(hillBoatPosX - 30.0, 35.0);
    glEnd();

    // Boat white stripe
    glColor3ub(255, 255, 255); // White
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 28.0);
    glVertex2f(hillBoatPosX - 15.0, 28.0);
    glVertex2f(hillBoatPosX - 15.0, 31.0);
    glVertex2f(hillBoatPosX - 30.0, 31.0);
    glEnd();

    // Boat red stripe
    glColor3ub(10, 153, 0); // Green
    glBegin(GL_POLYGON);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 15.0, 25.0);
    glVertex2f(hillBoatPosX - 15.0, 28.0);
    glVertex2f(hillBoatPosX - 30.0, 28.0);
    glEnd();

    // Boat flag
    glColor3ub(255, 0, 0); // Red
    glBegin(GL_TRIANGLES);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 35.0);
    glVertex2f(hillBoatPosX - 23.33, 30.0);
    glEnd();

    // Boat flag outline
    glColor3ub(0, 0, 0); // Black
    glBegin(GL_LINE_LOOP);
    glVertex2f(hillBoatPosX - 30.0, 25.0);
    glVertex2f(hillBoatPosX - 30.0, 35.0);
    glVertex2f(hillBoatPosX - 23.33, 30.0);
    glEnd();

    // Boat wake effect
    glColor3ub(102, 178, 255); // Light blue
    glBegin(GL_TRIANGLES);
    glVertex2f(hillBoatPosX - 80.0, 0.0);
    glVertex2f(hillBoatPosX - 85.0, -2.0);
    glVertex2f(hillBoatPosX - 75.0, -2.0);
    glVertex2f(hillBoatPosX - 75.0, 0.0);
    glVertex2f(hillBoatPosX - 80.0, -2.0);
    glVertex2f(hillBoatPosX - 70.0, -2.0);
    glEnd();
}

// Draw grass on the ground
void drawGrass() {
    glColor3f(0.2, 0.9, 0.2); // Vibrant green
    glBegin(GL_POLYGON);
    glVertex2f(-100.0, -100.0);
    glVertex2f(100.0, -100.0);
    glVertex2f(100.0, -40.0);
    glVertex2f(-100.0, -40.0);
    glEnd();
}

// Draw a flower tree at position 1
void drawFlowerTree1() {
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

// Draw a flower tree at position 2
void drawFlowerTree2() {
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

// Draw a flower tree at position 3
void drawFlowerTree3() {
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

// Draw a flower tree at position 4
void drawFlowerTree4() {
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

// Draw a flower tree at position 5
void drawFlowerTree5() {
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

// Draw a flower tree at position 6
void drawFlowerTree6() {
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

// Draw a flower tree at position 7
void drawFlowerTree7() {
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

// Draw a flower tree at position 8
void drawFlowerTree8() {
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

// Draw a flower tree at position 9
void drawFlowerTree9() {
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

// Draw a flower tree at position 10
void drawFlowerTree10() {
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

// Draw a flower tree at position 11
void drawFlowerTree11() {
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

// Draw a flower tree at position 12
void drawFlowerTree12() {
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

// Draw a flower tree at position 13
void drawFlowerTree13() {
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

// Draw a flower tree at position 14
void drawFlowerTree14() {
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

// Draw the river
void drawRiver() {
    glBegin(GL_POLYGON);
    glColor3ub(0, 76, 153); // Dark blue top
    glVertex2f(-100.0, 20.0);
    glVertex2f(100.0, 20.0);
    glColor3ub(102, 178, 255); // Light blue bottom
    glVertex2f(100.0, -40.0);
    glVertex2f(-100.0, -40.0);
    glEnd();
}

// Draw a traditional house
void drawHouse() {
    // House base
    glColor3ub(255, 204, 153); // Light peach
    glBegin(GL_POLYGON);
    glVertex2f(-40.0, -80.0);
    glVertex2f(-10.0, -80.0);
    glVertex2f(-10.0, -62.0);
    glVertex2f(-40.0, -62.0);
    glEnd();

    // House roof
    glColor3ub(139, 69, 19); // Brown
    glBegin(GL_TRIANGLES);
    glVertex2f(-43.0, -62.0);
    glVertex2f(-7.0, -62.0);
    glVertex2f(-25.0, -50.0);
    glEnd();

    // House door
    glColor3ub(102, 51, 0); // Dark brown
    glBegin(GL_POLYGON);
    glVertex2f(-28.0, -80.0);
    glVertex2f(-22.0, -80.0);
    glVertex2f(-22.0, -71.0);
    glVertex2f(-28.0, -71.0);
    glEnd();

    // House windows
    glColor3ub(0, 204, 255); // Cyan
    glBegin(GL_POLYGON);
    glVertex2f(-35.5, -71.0);
    glVertex2f(-31.0, -71.0);
    glVertex2f(-31.0, -66.5);
    glVertex2f(-35.5, -66.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-19.0, -71.0);
    glVertex2f(-14.5, -71.0);
    glVertex2f(-14.5, -66.5);
    glVertex2f(-19.0, -66.5);
    glEnd();

    // House chimney
    glColor3ub(100, 100, 100); // Gray
    glBegin(GL_POLYGON);
    glVertex2f(-14.5, -62.0);
    glVertex2f(-11.5, -62.0);
    glVertex2f(-11.5, -53.0);
    glVertex2f(-14.5, -53.0);
    glEnd();
}

// Draw a modern house
void drawNewHouse() {
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

// Draw a big tree at position 1
void drawBigTree1() {
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

// Draw a big tree at position 2
void drawBigTree2() {
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

// Draw a small sailboat
void drawSailBoat() {
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
    glVertex2f(-8.0, -30.0);
    glVertex2f(2.0, -30.0);
    glEnd();
}

// Draw a sports car
void drawCar() {
    // Car body
    glColor3ub(255, 20, 147); // Hot pink
    glBegin(GL_POLYGON);
    glVertex2f(15.0, -60.0);
    glVertex2f(65.0, -60.0);
    glVertex2f(62.0, -50.0);
    glVertex2f(18.0, -50.0);
    glEnd();

    // Car cockpit
    glColor3ub(0, 255, 255); // Cyan
    glBegin(GL_POLYGON);
    glVertex2f(30.0, -50.0);
    glVertex2f(50.0, -50.0);
    glVertex2f(48.0, -45.0);
    glVertex2f(32.0, -45.0);
    glEnd();

    // Car front spoiler
    glColor3ub(255, 255, 0); // Yellow
    glBegin(GL_POLYGON);
    glVertex2f(15.0, -60.0);
    glVertex2f(18.0, -60.0);
    glVertex2f(18.0, -62.0);
    glVertex2f(15.0, -62.0);
    glEnd();

    // Car windows
    glColor3ub(50, 50, 50); // Dark gray
    glBegin(GL_POLYGON);
    glVertex2f(32.0, -49.0);
    glVertex2f(48.0, -49.0);
    glVertex2f(46.0, -46.0);
    glVertex2f(34.0, -46.0);
    glEnd();

    // Car wheels
    glColor3ub(255, 215, 0); // Gold
    circle(5.0, 5.0, 25.0, -59.0);
    circle(5.0, 5.0, 55.0, -59.0);
    glColor3ub(100, 100, 100); // Gray rims
    circle(3.0, 3.0, 25.0, -59.0);
    circle(3.0, 3.0, 55.0, -59.0);
}

// Draw a modern car
void drawNewCar() {
    // Car body
    glColor3ub(245, 224, 1); // Vibrant green
    glBegin(GL_POLYGON);
    glVertex2f(32.0, -80.0);
    glVertex2f(88.0, -80.0);
    glVertex2f(85.0, -68.0);
    glVertex2f(35.0, -68.0);
    glEnd();

    // Car cockpit
    glColor3ub(100, 100, 248); // Orange
    glBegin(GL_POLYGON);
    glVertex2f(48.0, -70.0);
    glVertex2f(72.0, -70.0);
    glVertex2f(70.0, -65.0);
    glVertex2f(50.0, -65.0);
    glEnd();

    // Car front spoiler
    glColor3ub(128, 0, 128); // Purple
    glBegin(GL_POLYGON);
    glVertex2f(32.0, -80.0);
    glVertex2f(36.0, -80.0);
    glVertex2f(36.0, -83.0);
    glVertex2f(32.0, -83.0);
    glEnd();

    // Car windows
    glColor3ub(50, 50, 50); // Dark gray
    glBegin(GL_POLYGON);
    glVertex2f(52.0, -69.0);
    glVertex2f(68.0, -69.0);
    glVertex2f(66.0, -66.0);
    glVertex2f(54.0, -66.0);
    glEnd();

    // Car wheels
    glColor3ub(0, 255, 255); // Cyan
    circle(5.5, 5.5, 44.0, -78.5);
    circle(5.5, 5.5, 76.0, -78.5);
    glColor3ub(200, 200, 200); // Light gray rims
    circle(3.5, 3.5, 44.0, -78.5);
    circle(3.5, 3.5, 76.0, -78.5);
}

// Display function to render the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up projection and modelview
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
    drawCar();
    drawNewCar();

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
    if (day > 0) {
    sunMoonPos -= 0.025;
    if (sunMoonPos < 00.0) day = -1.0;
    } else {
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
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1240, 750);
    glutCreateWindow("Sky with Clouds, Sun/Moon, Hills, River, and Village");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
