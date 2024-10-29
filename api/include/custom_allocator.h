//
// Created by Mat on 29.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_CUSTOM_ALLOCATOR_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_CUSTOM_ALLOCATOR_H_

template<typename T>
class StandardAllocator
{
 public:
  using value_type = T;
  T* allocate(size_t n)
  {
    return ::operator new(n);
  }
  void deallocate(T* ptr, [[maybe_unused]] size_t n)
  {
    return ::operator delete(ptr);
  }
};

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_CUSTOM_ALLOCATOR_H_
