#include <iostream>

 #pragma once

struct Standing
{
   void OnStart()
   {
      std::cout << "Standing Start\n";
   }

   void OnUpdate()
   {
      
   }

   void OnExit()
   {
      std::cout << "Standing Exit\n";
   }
};

struct Crouch
{
   void OnStart()
   {
      std::cout << "Crouch Start\n";
   }

   void OnUpdate()
   {

   }

   void OnExit()
   {
      std::cout << "Crouch Exit\n";
   }
};

struct Jumping
{
   void OnStart()
   {
      std::cout << "Jump Start\n";
   }

   void OnUpdate()
   {

   }

   void OnExit()
   {
      std::cout << "Jump Exit\n";
   }
};

struct Falling
{
   void OnStart()
   {
      std::cout << "Falling Start\n";
   }

   void OnUpdate()
   {

   }

   void OnExit()
   {
      std::cout << "Falling End\n";
   }
};




 
 