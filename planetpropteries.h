#ifndef PLANETPROPTERIES_H
#define PLANETPROPTERIES_H

#define DISTANCE_EARTH_MOON 390.0e3         // km
#define DISTANCE_SUN_EARTH 148.9e6          // km
#define MASS_SUN 1.988e21                   // 1e9 kg
#define RADIUS_SUN 6.99e5                   // km
#define POSITION_X_SUN 0.0                  // km related to origin of solar system
#define POSITION_Y_SUN 0.0                  // km related to origin of solar system
#define VELOCITY_X_SUN 0.0                  // km/s
#define VELOCITY_Y_SUN 0.0                  // km/s
#define MASS_EARTH 5.974e15                 // 1e9 kg
#define RADIUS_EARTH 6.37e3                 // km
#define POSITION_X_EARTH -148.9e6           // km related to origin of solar system
#define POSITION_Y_EARTH 0.0                // km related to origin of solar system
#define VELOCITY_X_EARTH 0.0                // km/s
#define VELOCITY_Y_EARTH 29.8               // km/s
// #define ANGULAR_VELOCITY_EARTH 7.2722E-5    // Still m !!!!
#define MASS_MOON 7.349e13                  // 1e9 kg
#define RADIUS_MOON 1.738e3                 // km
#define POSITION_X_MOON POSITION_X_EARTH - DISTANCE_EARTH_MOON
#define POSITION_Y_MOON 0.0                 // km related to origin of solar system
#define VELOCITY_X_MOON 0.0                 // km/s
#define VELOCITY_Y_MOON 30.82               // km/s

#endif // PLANETPROPTERIES_H
