#include <iostream>

 #pragma once



struct StateContext //Holds infromation from the Entity that owns the state machine
{
    
};


struct Standing
{
   bool shouldTransition = false;

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

   bool TriggerTransition()
   {
      return shouldTransition;
   }
};

struct Crouch
{
   bool shouldTransition = false;
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

      bool TriggerTransition()
   {
      return shouldTransition;
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




 
 