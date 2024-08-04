#ifndef MOVEMENT_H
#define MOVEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

    bool performConMovement(int arm, char axis, double distance /* in micrometers */);
    bool performTrpMovement(int arm, char axis, double distance /* in micrometers */);

    bool resetAxisPosition(int axis);
    double getAxisPosition(int axis);

#ifdef __cplusplus
}
#endif

#endif // MOVEMENT_H
