//
// Created by Mat on 14.11.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_COLLIDER_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_COLLIDER_H_

class Collider {
 private:
  bool is_trigger_;

 public:
  Collider() : is_trigger_(false){}

  //trigger
  void OnTriggerEnter();
  void OnTriggerExit();


  //GET
  [[nodiscard]] bool is_trigger() const {return is_trigger_;}
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_COLLIDER_H_
