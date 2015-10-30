#include "agent.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

#define NORTE 0
#define ESTE 1
#define SUR 2
#define OESTE 3
#define PARED -1
#define NO_GIRO 0
#define GIRO_IZQ 1
#define GIRO_DER 2

using namespace std;

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
    ActionType accion;

    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            if(M_[i][j]!=PARED) M_[i][j]++;
        }
    }

    M_[x_][y_]=0;

    // 1. SUCIEDAD -> LIMPIAR
    if(dirty_) {
        accion=actSUCK;
        last_turn_=NO_GIRO;

        // Si había chocado, desavanzo
        if(bump_) {
            if(orientacion_==NORTE) x_++;
            if(orientacion_==ESTE) y_--;
            if(orientacion_==SUR) x_--;
            if(orientacion_==OESTE) y_++;
        }
    }
    // 2. NO SUCIEDAD -> MOVERSE
    else {
        // 2.1. CHOCAR -> GIRAR
        if(bump_) {
            // GUARDA POSICIÓN PARED
            M_[x_][y_]=PARED;
            // DESAVANZO
            if(orientacion_==NORTE) x_++;
            if(orientacion_==ESTE) y_--;
            if(orientacion_==SUR) x_--;
            if(orientacion_==OESTE) y_++;
            M_[x_][y_]=0;
            // BUSCA POSICIÓN A LA QUE MOVERSE
            // Si estoy mirando al norte
            if(orientacion_==NORTE) {
                if(M_[x_][y_+1]==PARED) { // hacia la derecha hay pared
                    accion = actTURN_L;
                    last_turn_ = GIRO_IZQ;
                    orientacion_=OESTE;
                } else if(M_[x_][y_-1]==PARED) { // hacia la izquierda hay pared
                    accion = actTURN_R;
                    last_turn_ = GIRO_DER;
                    orientacion_=ESTE;
                } else { // no hay pared hacia ningún lado
                    if(M_[x_][y_+1]<M_[x_][y_-1]) { // derecha preferible
                        accion = actTURN_L;
                        last_turn_ = GIRO_IZQ;
                        orientacion_=OESTE;
                    } else if(M_[x_][y_+1]>M_[x_][y_-1]) { // izquierda preferible
                        accion = actTURN_R;
                        last_turn_ = GIRO_DER;
                        orientacion_=ESTE;
                    } else {
                        switch(rand()%2+1) {
                            case 1: accion = actTURN_L;
                                last_turn_=GIRO_IZQ;
                                orientacion_=OESTE;
                                break;
                            case 2: accion = actTURN_R;
                                last_turn_=GIRO_DER;
                                orientacion_=ESTE;
                        }
                    }
                }
            }
            // Si estoy mirando al este
            else if(orientacion_==ESTE) {
                if(M_[x_+1][y_]==PARED) { // hacia la derecha hay pared
                    accion = actTURN_L;
                    last_turn_ = GIRO_IZQ;
                    orientacion_=NORTE;
                } else if(M_[x_-1][y_]==PARED) { // hacia la izquierda hay pared
                    accion = actTURN_R;
                    last_turn_ = GIRO_DER;
                    orientacion_=SUR;
                } else { // no hay pared hacia ningún lado
                    if(M_[x_+1][y_]<M_[x_-1][y_]) { // derecha preferible
                        accion = actTURN_L;
                        last_turn_ = GIRO_IZQ;
                        orientacion_=NORTE;
                    } else if(M_[x_+1][y_]>M_[x_-1][y_]) { // izquierda preferible
                        accion = actTURN_R;
                        last_turn_ = GIRO_DER;
                        orientacion_=SUR;
                    } else {
                        switch(rand()%2+1) {
                            case 1: accion = actTURN_L;
                                last_turn_=GIRO_IZQ;
                                orientacion_=NORTE;
                                break;
                            case 2: accion = actTURN_R;
                                last_turn_=GIRO_DER;
                                orientacion_=SUR;
                        }
                    }
                }
            }
            // Si estoy mirando al sur
            else if(orientacion_==SUR) {
                if(M_[x_][y_-1]==PARED) { // hacia la derecha hay pared
                    accion = actTURN_L;
                    last_turn_ = GIRO_IZQ;
                    orientacion_=ESTE;
                } else if(M_[x_][y_+1]==PARED) { // hacia la izquierda hay pared
                    accion = actTURN_R;
                    last_turn_ = GIRO_DER;
                    orientacion_=OESTE;
                } else { // no hay pared hacia ningún lado
                    if(M_[x_][y_-1]<M_[x_][y_+1]) { // derecha preferible
                        accion = actTURN_L;
                        last_turn_ = GIRO_IZQ;
                        orientacion_=ESTE;
                    } else if(M_[x_][y_-1]>M_[x_][y_+1]) { // izquierda preferible
                        accion = actTURN_R;
                        last_turn_ = GIRO_DER;
                        orientacion_=OESTE;
                    } else {
                        switch(rand()%2+1) {
                            case 1: accion = actTURN_L;
                                last_turn_=GIRO_IZQ;
                                orientacion_=ESTE;
                                break;
                            case 2: accion = actTURN_R;
                                last_turn_=GIRO_DER;
                                orientacion_=OESTE;
                        }
                    }
                }
            }
            // Si estoy mirando al oeste
            else {
                if(M_[x_-1][y_]==PARED) { // hacia la derecha hay pared
                    accion = actTURN_L;
                    last_turn_ = GIRO_IZQ;
                    orientacion_=SUR;
                } else if(M_[x_+1][y_]==PARED) { // hacia la izquierda hay pared
                    accion = actTURN_R;
                    last_turn_ = GIRO_DER;
                    orientacion_=NORTE;
                } else { // no hay pared hacia ningún lado
                    if(M_[x_-1][y_]<M_[x_+1][y_]) { // derecha preferible
                        accion = actTURN_L;
                        last_turn_ = GIRO_IZQ;
                        orientacion_=SUR;
                    } else if(M_[x_-1][y_]>M_[x_+1][y_]) { // izquierda preferible
                        accion = actTURN_R;
                        last_turn_ = GIRO_DER;
                        orientacion_=NORTE;
                    } else {
                        switch(rand()%2+1) {
                            case 1: accion = actTURN_L;
                                last_turn_=GIRO_IZQ;
                                orientacion_=SUR;
                                break;
                            case 2: accion = actTURN_R;
                                last_turn_=GIRO_DER;
                                orientacion_=NORTE;
                        }
                    }
                }
            }
        }

        // 2.2. TRAS GIRAR -> INTENTO AVANZAR
        else if(last_turn_>0) {
            if(orientacion_==NORTE) {
                if(M_[x_-1][y_]!=PARED) {
                    accion=actFORWARD;
                    last_turn_=NO_GIRO;
                    x_--;
                } else {
                    last_turn_=NO_GIRO;
                    accion=actIDLE;
                }
            } else if(orientacion_==ESTE) {
                if(M_[x_][y_+1]!=PARED) {
                    accion=actFORWARD;
                    last_turn_=NO_GIRO;
                    y_++;
                } else {
                    last_turn_=NO_GIRO;
                    accion=actIDLE;
                }
            } else if(orientacion_==SUR) {
                if(M_[x_+1][y_]!=PARED) {
                    accion=actFORWARD;
                    last_turn_=NO_GIRO;
                    x_++;
                } else {
                    last_turn_=NO_GIRO;
                    accion=actIDLE;
                }
            } else {
                if(M_[x_][y_-1]!=PARED) {
                    accion=actFORWARD;
                    last_turn_=NO_GIRO;
                    y_--;
                } else {
                    last_turn_=NO_GIRO;
                    accion=actIDLE;
                }
            }
        }

        // 2.3. ÚLTIMO GIRO IZQ -> GIRAR IZQ
        else if(last_turn_==GIRO_IZQ) {
            accion = actTURN_L;
            last_turn_=GIRO_IZQ;
            if(orientacion_==NORTE) {
                orientacion_=OESTE;
            } else if(orientacion_==ESTE) {
                orientacion_=NORTE;
            } else if(orientacion_==SUR) {
                orientacion_=ESTE;
            } else {
                orientacion_=SUR;
            }
        }

        // 2.4. ÚLTIMO GIRO DER -> GIRAR DER
        else if(last_turn_==GIRO_DER) {
            accion = actTURN_R;
            last_turn_=GIRO_DER;
            if(orientacion_==NORTE) {
                orientacion_=ESTE;
            } else if(orientacion_==ESTE) {
                orientacion_=SUR;
            } else if(orientacion_==SUR) {
                orientacion_=OESTE;
            } else {
                orientacion_=NORTE;
            }
        }

        // 2.5. NO VIENE DE GIRAR
        else {
            // Si estoy mirando al norte
            if(orientacion_==NORTE) {
                int valorARR=M_[x_-1][y_];
                int valorDER=M_[x_][y_+1];
                int valorIZQ=M_[x_][y_-1];

                if(valorDER==PARED and valorIZQ==PARED and valorARR==PARED) { // Camino sin salida -> doy la vuelta
                    accion = actTURN_L;
                    last_turn_=GIRO_IZQ;
                    orientacion_=OESTE;
                } else {
                    if(valorIZQ>=valorDER and valorIZQ!=PARED) { // valor izq preferible
                        if(valorIZQ<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            x_--;
                        } else { // IZQUIERDA
                            accion = actTURN_L;
                            last_turn_=GIRO_IZQ;
                            orientacion_=OESTE;
                        }
                    } else if(valorDER!=PARED) { // valor der preferible
                        if(valorDER<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            x_--;
                        } else { // DERECHA
                            accion = actTURN_R;
                            last_turn_=GIRO_DER;
                            orientacion_=ESTE;
                        }
                    } else { // paredes a los lados, no arriba -> ARRIBA
                        accion = actFORWARD;
                        last_turn_=NO_GIRO;
                        x_--;
                    }
                }
            }
            // Si estoy mirando al este
            else if(orientacion_==ESTE) {
                int valorARR=M_[x_][y_+1];
                int valorDER=M_[x_+1][y_];
                int valorIZQ=M_[x_-1][y_];

                if(valorDER==PARED and valorIZQ==PARED and valorARR==PARED) { // Camino sin salida -> doy la vuelta
                    accion = actTURN_L;
                    last_turn_=GIRO_IZQ;
                    orientacion_=NORTE;
                } else {
                    if(valorIZQ>=valorDER and valorIZQ!=PARED) { // valor izq preferible
                        if(valorIZQ<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            y_++;
                        } else { // IZQUIERDA
                            accion = actTURN_L;
                            last_turn_=GIRO_IZQ;
                            orientacion_=NORTE;
                        }
                    } else if(valorDER!=PARED) { // valor der preferible
                        if(valorDER<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            y_++;
                        } else { // DERECHA
                            accion = actTURN_R;
                            last_turn_=GIRO_DER;
                            orientacion_=SUR;
                        }
                    } else { // paredes a los lados, no arriba -> ARRIBA
                        accion = actFORWARD;
                        last_turn_=NO_GIRO;
                        y_++;
                    }
                }
            }
            // Si estoy mirando al sur
            else if(orientacion_==SUR) {
                int valorARR=M_[x_+1][y_];
                int valorDER=M_[x_][y_-1];
                int valorIZQ=M_[x_][y_+1];

                if(valorDER==PARED and valorIZQ==PARED and valorARR==PARED) { // Camino sin salida -> doy la vuelta
                    accion = actTURN_L;
                    last_turn_=GIRO_IZQ;
                    orientacion_=ESTE;
                } else {
                    if(valorIZQ>=valorDER and valorIZQ!=PARED) { // valor izq preferible
                        if(valorIZQ<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            x_++;
                        } else { // IZQUIERDA
                            accion = actTURN_L;
                            last_turn_=GIRO_IZQ;
                            orientacion_=ESTE;
                        }
                    } else if(valorDER!=PARED) { // valor der preferible
                        if(valorDER<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            x_++;
                        } else { // DERECHA
                            accion = actTURN_R;
                            last_turn_=GIRO_DER;
                            orientacion_=OESTE;
                        }
                    } else { // paredes a los lados, no arriba -> ARRIBA
                        accion = actFORWARD;
                        last_turn_=NO_GIRO;
                        x_++;
                    }
                }
            }
            // Si estoy mirando al oeste
            else {
                int valorARR=M_[x_][y_-1];
                int valorDER=M_[x_-1][y_];
                int valorIZQ=M_[x_+1][y_];

                if(valorDER==PARED and valorIZQ==PARED and valorARR==PARED) { // Camino sin salida -> doy la vuelta
                    accion = actTURN_L;
                    last_turn_=GIRO_IZQ;
                    orientacion_=SUR;
                } else {
                    if(valorIZQ>=valorDER and valorIZQ!=PARED) { // valor izq preferible
                        if(valorIZQ<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            y_--;
                        } else { // IZQUIERDA
                            accion = actTURN_L;
                            last_turn_=GIRO_IZQ;
                            orientacion_=SUR;
                        }
                    } else if(valorDER!=PARED) { // valor der preferible
                        if(valorDER<=valorARR and valorARR!=PARED) { // ARRIBA
                            accion = actFORWARD;
                            last_turn_=NO_GIRO;
                            y_--;
                        } else { // DERECHA
                            accion = actTURN_R;
                            last_turn_=GIRO_DER;
                            orientacion_=NORTE;
                        }
                    } else { // paredes a los lados, no arriba -> ARRIBA
                        accion = actFORWARD;
                        last_turn_=NO_GIRO;
                        y_--;
                    }
                }
            }
        }
    }

    return accion;
}
// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
    bump_ = env.isJustBump();
    dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
    switch (accion)
    {
        case Agent::actFORWARD: return "FORWARD";
        case Agent::actTURN_L: return "TURN LEFT";
        case Agent::actTURN_R: return "TURN RIGHT";
        case Agent::actSUCK: return "SUCK";
        case Agent::actIDLE: return "IDLE";
        default: return "???";
    }
}
